using System.Runtime.InteropServices;
//调用Windows动态库方法制造蓝屏
[DllImport("ntdll.dll")]
static extern void RtlSetProcessIsCritical(int i, int j, int k);

RtlSetProcessIsCritical(1, 0, 0);
