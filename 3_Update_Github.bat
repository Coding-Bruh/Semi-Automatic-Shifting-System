::File Name: Setup.dat
::Author: Abhinav Chennapareddy
::Date: 6/23/2017

set git_setup_dir="%userprofile%\Documents\GitHub\Semi-Automatic-Shifting-System\Setup\CAN"
set active_code_dir="%userprofile%\Documents\Senior_Design\Keil_v5\CAN" 

set hh=%time:~0,2%
if "%time:~0,1%"==" " set hh=0%hh:~1,1%   

set datestamp=%date:~7,2%-%date:~4,2%-%date:~10,4%_%hh%_%time:~3,2%_%time:~6,2%

copy %userprofile%\Documents\GitHub\Semi-Automatic-Shifting-System\Code\main_%datestamp%.cpp %userprofile%\Documents\Senior_Design\Keil_v5\CAN\main.cpp

for /F %%I IN ('%git_code_dir%\*.cpp /B /O:-D') do copy %%I %active_code_dir%
