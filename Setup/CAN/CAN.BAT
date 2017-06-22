SET PATH=C:\Keil_v5\ARM\ARMCC\Bin;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\Strawberry\c\bin;C:\Strawberry\perl\site\bin;C:\Strawberry\perl\bin;C:\Program Files (x86)\GtkSharp\2.12\bin;C:\Program Files\Java\jdk1.8.0_101\bin;C:\ProgramData\chocolatey\bin;;C:\TDM-GCC-64\bin;C:\Program Files (x86)\Brackets\command;C:\Program Files\PuTTY\;C:\Users\Abhi\AppData\Local\Microsoft\WindowsApps;C:\Users\Abhi\AppData\Local\Box\Box Edit\;
SET CPU_TYPE=LPC1768
SET CPU_VENDOR=NXP
SET UV2_TARGET=CAN
SET CPU_CLOCK=0x00B71B00
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\build\main.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\build\gps.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmCC" --Via ".\build\textlcd.__i"
"C:\Keil_v5\ARM\ARMCC\Bin\ArmLink" --Via ".\BUILD\CAN.lnp"
"C:\Keil_v5\ARM\ARMCC\Bin\fromelf.exe" ".\BUILD\CAN.axf" --i32combined --output ".\BUILD\CAN.hex"
flash.bat
