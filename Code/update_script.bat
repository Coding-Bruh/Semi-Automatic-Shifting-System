::File Name: flash.bat
::Author: Abhinav Chennapareddy
::Date: 6/21/2017

:: Custom file paths
set git_code_dir = "%userprofile%\Documents\GitHub\Semi-Automatic-Shifting-System\Code"
set active_code_dir="%userprofile%\Documents\Senior_Design\Keil_v5\CAN" 

:: Adding file path onto a stack (I don't what stack)
pushd %git_code_dir%

:: A 'for' loop to find the latest main.cpp file
for /F "tokens=*" %%I IN ('dir *.cpp /O /B  /T:w') do SET latest_file=%%I

:: copy the main.cpp file onto the Keil_v5 environment
copy %latest_file%  %active_code_dir%

:: Pop file path from stack
popd

:: End of script
exit