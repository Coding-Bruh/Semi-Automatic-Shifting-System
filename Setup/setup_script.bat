::File Name: Setup.dat
::Author: Abhinav Chennapareddy
::Date: 6/21/2017

set git_setup_dir="%userprofile%\Documents\GitHub\Semi-Automatic-Shifting-System\Setup\CAN"
set active_code_dir="%userprofile%\Documents\Senior_Design\Keil_v5\CAN" 

:: Check if active directory exists
if not exist %active_code_dir%\==1(
	:: Make the directory
	mkdir %active_code_dir%
)

:: Copy all files to active directory
xcopy /y /s %git_setup_dir%\*.* %active_code_dir%

:: End of script
exit

::set hh=%time:~0,2%
::if "%time:~0,1%"==" " set hh=0%hh:~1,1%   

::set datestamp=%date:~7,2%-%date:~4,2%-%date:~10,4%_%hh%_%time:~3,2%_%time:~6,2%

::copy %userprofile%\Documents\GitHub\Semi-Automatic-Shifting-System\Code\main_%datestamp%.cpp %userprofile%\Documents\Senior_Design\Keil_v5\CAN\main.cpp

::for /F %%I IN ('%git_code_dir%\*.cpp /B /O:-D') do copy %%I %active_code_dir%
