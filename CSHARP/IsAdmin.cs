
using System.Runtime.InteropServices;
using System.Security.Principal;
using System.Text.Json;

[DllImport("libc")]
static extern uint getuid();

if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
{
    using var identity = WindowsIdentity.GetCurrent();
    var principal = new WindowsPrincipal(identity);
    Console.WriteLine(principal.IsInRole(WindowsBuiltInRole.Administrator));
}
else
{
    Console.WriteLine(getuid()==0);
}


