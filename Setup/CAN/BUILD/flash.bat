::File Name: flash.bat
::Author: Abhinav Chennapareddy
::Date: 6/21/2017

:: This script will generate a CAN.bin file, when it is run. The script subsequently searches all available drives for another instance of CAN.bin, excluding the C drive. 
:: If another CAN.bin file is found, then the script  replaces that instance of CAN.bin with the recently generated CAN.bin.
::---------------------------------------------------------------------------------------------------------------------------------------------------------------------------   

set fromElf="C:\Keil_v5\ARM\ARMCC\bin"
set buildFile="%userprofile%\Documents\Senior_Design\Keil_v5\CAN\BUILD"

:: The following code generates a .bin file from a .axf file:

%fromElf%\fromelf.exe --bin --output=%buildFile%\CAN.bin %buildFile%\CAN.axf

:: The following code search for all drives, starting from the D drive for a CAN.bin file.
:: If found the file is replaced:

for %%d in (D E F G H I J K L M N O P Q R S T U V W X Y Z) do (
  if exist "%%d:CAN.bin" copy %buildFile%\CAN.bin "%%d:CAN.bin"
)

:: end script.
exit