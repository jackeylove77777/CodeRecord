//
// Created by Administrator on 2022/4/3.
//
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>
#include <stdio.h>
#include "DFS.h"
#define Default_Stack_Len 550
const int N=550;
const int M=550;
//orientation 1234分别对应右下左上,因为迷宫从（0，0）出发,所以初始尝试方向为右的效率有可能会更高
struct Position {
    int x, y, orientation;
    bool oriVisited[4];
};
//根据坐标创建Position
struct Position CreatePosition(int x, int y) {
    struct Position res;
    res.orientation = -1;
    res.x = x, res.y = y;
    memset(res.oriVisited, false, sizeof(res.oriVisited));
    return res;
}
//根据父位置和方向创造一个新的Position结构体
struct Position NewPoint(struct Position father, int orientation) {
    struct Position res = CreatePosition(father.x, father.y);
    switch (orientation) {
        //0为向右
    case 0: {
        res.x += 1;
        break;
    }
          //下
    case 1: {
        res.y += 1;
        break;
    }
          //左
    case 2: {
        res.x -= 1;
        break;
    }
          //上
    case 3: {
        res.y -= 1;
        break;
    }
    }
    return res;

}
struct DFSAns {
    //isOk 0代表没有出路，1代表有出路
    int isOk;
    //若有出路
    struct Position* Path;
    int pathLen;
};

struct Stack {
    struct Position* body;
    int top;
};
//初始化栈
struct Stack* CreateStack() {
    struct Stack* res = (struct Stack*)malloc(sizeof(struct Stack));
    res->top = -1;
    res->body = (struct Position*)malloc(sizeof(struct Position) * Default_Stack_Len);
    return res;
}
//出栈 0表示失败，1表示成功
int Stack_Pop(struct Stack* stack) {
    if (stack->top < 0) {
        return 0;
    }
    stack->top -= 1;
    return 1;
}
//入栈 0表示失败，1表示成功
int Stack_Push(struct Stack* stack, struct Position val) {
    if (stack->top >= 550)return 0;
    stack->body[++stack->top] = val;
    return 1;
}
//栈的长度
int Stack_Len(struct Stack* stack) {
    return stack->top + 1;
}
//因为是在while(Stack_Len(stack))里的第一步执行，所以不用判断栈空的情况
struct Position* Stack_Top(struct Stack* stack) {
    return &stack->body[stack->top];
}
struct Position Stack_Top_Value(struct Stack* stack) {
    return stack->body[stack->top];
}

//坐标系:m为x方向，n为y方向
struct DFSAns DFS(struct Stack* stack, int** Maze, int n, int m) {
    //初始化工作
    bool visited[N][M];
    memset(visited, false, sizeof(visited));
    struct Position source = CreatePosition(0, 0);
    visited[0][0] = true;
    Stack_Push(stack, source);
    //标记是否走到终点的flag；
    bool isReachEnd = false;
    while (Stack_Len(stack)) {
        struct Position* NowPoint = Stack_Top(stack);
        //判断是不是终点
        if (NowPoint->x == m - 1 && NowPoint->y == n - 1) {
            isReachEnd = true;
            break;
        }
        //如果四个方向都尝试过了并且不是终点，则出栈回溯
        if (NowPoint->oriVisited[0] && NowPoint->oriVisited[1] && NowPoint->oriVisited[2] && NowPoint->oriVisited[3]) {
            Stack_Pop(stack);
            continue;
        }
        //遍历四个方向
        for (int ori = 0; ori < 4; ++ori) {
            //true则为这个方向已经走过
            if (!NowPoint->oriVisited[ori]) {
                NowPoint->oriVisited[ori] = true;
                struct Position newP = NewPoint(*NowPoint, ori);
                NowPoint->orientation = ori + 1;
                //判断该点是否未访问过并且位置合理
                if (!visited[newP.y][newP.x] && newP.x < m && newP.x >= 0 && newP.y < n && newP.y >= 0 && Maze[newP.y][newP.x] != 1) {
                    visited[newP.y][newP.x] = true;
                    Stack_Push(stack, newP);
                    break;
                }              
            }
        }
    }
    struct DFSAns res;
    if (isReachEnd) {
        res.isOk = true;
        res.pathLen = Stack_Len(stack);
        res.Path = (struct Position*)malloc(sizeof(struct Position) * res.pathLen);
        int index = res.pathLen - 1;
        while (Stack_Len(stack)) {
            res.Path[index--] = *Stack_Top(stack);
            Stack_Pop(stack);
        }
    }
    else {
        res.isOk = false;
    }
    return res;
}

void DFS_Run(int** Maze, int n, int m) {
    struct Stack* stack = CreateStack();
    struct DFSAns ans = DFS(stack, Maze, n, m);
    printf("DFS ");
    if (ans.isOk) {
        printf("该迷宫存在出口,路径如下:\n");
        for (int i = 0; i < ans.pathLen; ++i) {
            printf("==>坐标( %d , %d ),方向为 %d\n", ans.Path[i].x, ans.Path[i].y, ans.Path[i].orientation);
        }
    }
    else {
        printf("该迷宫没有出口");
    }
}