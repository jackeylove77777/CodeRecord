
using System;
using System.Runtime.InteropServices;
//C#11 新特性



//C#11 列表模式新特性  （Rust出生自带）
int[] nums = { 5, 4, 3, 2, 1, 3, 4, 5 };
Console.WriteLine(isHuiWenArr(nums));//false
int[] tmp = { 3, 2, 1, 2, 3 };
Console.WriteLine(isHuiWenArr(tmp));//true


bool isHuiWenArr(int[] arr)=>arr switch{
    [] => false,
    [_]=> true,
    [var first, .. var mid, var last] => first == last ? isHuiWenArr(mid) : false,
};
try
{
    test();
    Console.WriteLine(111);
}
catch (Exception e)
{
    Console.WriteLine();
    Console.WriteLine(222);
}//print 222

//参数空值检查,!!标记的参数是null值，自动抛出异常
void test(object obj!! = null) { };











