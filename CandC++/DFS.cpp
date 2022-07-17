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
//orientation 1234�ֱ��Ӧ��������,��Ϊ�Թ��ӣ�0��0������,���Գ�ʼ���Է���Ϊ�ҵ�Ч���п��ܻ����
struct Position {
    int x, y, orientation;
    bool oriVisited[4];
};
//�������괴��Position
struct Position CreatePosition(int x, int y) {
    struct Position res;
    res.orientation = -1;
    res.x = x, res.y = y;
    memset(res.oriVisited, false, sizeof(res.oriVisited));
    return res;
}
//���ݸ�λ�úͷ�����һ���µ�Position�ṹ��
struct Position NewPoint(struct Position father, int orientation) {
    struct Position res = CreatePosition(father.x, father.y);
    switch (orientation) {
        //0Ϊ����
    case 0: {
        res.x += 1;
        break;
    }
          //��
    case 1: {
        res.y += 1;
        break;
    }
          //��
    case 2: {
        res.x -= 1;
        break;
    }
          //��
    case 3: {
        res.y -= 1;
        break;
    }
    }
    return res;

}
struct DFSAns {
    //isOk 0����û�г�·��1�����г�·
    int isOk;
    //���г�·
    struct Position* Path;
    int pathLen;
};

struct Stack {
    struct Position* body;
    int top;
};
//��ʼ��ջ
struct Stack* CreateStack() {
    struct Stack* res = (struct Stack*)malloc(sizeof(struct Stack));
    res->top = -1;
    res->body = (struct Position*)malloc(sizeof(struct Position) * Default_Stack_Len);
    return res;
}
//��ջ 0��ʾʧ�ܣ�1��ʾ�ɹ�
int Stack_Pop(struct Stack* stack) {
    if (stack->top < 0) {
        return 0;
    }
    stack->top -= 1;
    return 1;
}
//��ջ 0��ʾʧ�ܣ�1��ʾ�ɹ�
int Stack_Push(struct Stack* stack, struct Position val) {
    if (stack->top >= 550)return 0;
    stack->body[++stack->top] = val;
    return 1;
}
//ջ�ĳ���
int Stack_Len(struct Stack* stack) {
    return stack->top + 1;
}
//��Ϊ����while(Stack_Len(stack))��ĵ�һ��ִ�У����Բ����ж�ջ�յ����
struct Position* Stack_Top(struct Stack* stack) {
    return &stack->body[stack->top];
}
struct Position Stack_Top_Value(struct Stack* stack) {
    return stack->body[stack->top];
}

//����ϵ:mΪx����nΪy����
struct DFSAns DFS(struct Stack* stack, int** Maze, int n, int m) {
    //��ʼ������
    bool visited[N][M];
    memset(visited, false, sizeof(visited));
    struct Position source = CreatePosition(0, 0);
    visited[0][0] = true;
    Stack_Push(stack, source);
    //����Ƿ��ߵ��յ��flag��
    bool isReachEnd = false;
    while (Stack_Len(stack)) {
        struct Position* NowPoint = Stack_Top(stack);
        //�ж��ǲ����յ�
        if (NowPoint->x == m - 1 && NowPoint->y == n - 1) {
            isReachEnd = true;
            break;
        }
        //����ĸ����򶼳��Թ��˲��Ҳ����յ㣬���ջ����
        if (NowPoint->oriVisited[0] && NowPoint->oriVisited[1] && NowPoint->oriVisited[2] && NowPoint->oriVisited[3]) {
            Stack_Pop(stack);
            continue;
        }
        //�����ĸ�����
        for (int ori = 0; ori < 4; ++ori) {
            //true��Ϊ��������Ѿ��߹�
            if (!NowPoint->oriVisited[ori]) {
                NowPoint->oriVisited[ori] = true;
                struct Position newP = NewPoint(*NowPoint, ori);
                NowPoint->orientation = ori + 1;
                //�жϸõ��Ƿ�δ���ʹ�����λ�ú���
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
        printf("���Թ����ڳ���,·������:\n");
        for (int i = 0; i < ans.pathLen; ++i) {
            printf("==>����( %d , %d ),����Ϊ %d\n", ans.Path[i].x, ans.Path[i].y, ans.Path[i].orientation);
        }
    }
    else {
        printf("���Թ�û�г���");
    }
}