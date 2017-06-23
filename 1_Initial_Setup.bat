::File Name: Initial_Setup.bat
::Author: Abhinav Chennapareddy
::Date: 6/21/2017

:: This script will set up you environment for Keil_v5 in the Documents directory of
:: Windows. As a bonus, it will also update the main.cpp file in the Keil_v5 ide with
:: latest main.cpp file available on github.
::--------------------------------------------------------------------------------------
:: !!!!!!NOTE!!!!!!                                                                    |
::--------------------------------------------------------------------------------------
:: This script is only meant to be used as an initial setup.                           |
:: DO NOT USE THIS SCRIPT AS A MEANS TO UPDATE CODE ON KEIL! YOU WILL LOSE YOUR CODE!! |
:: Please use 2_Update_Project.bat to load the latest code in your local github        |
:: repository into the Keil_v5 project environment.                                    |
:: Please use 3_Update_Github.bat to load you code onto the Github.                    |
:: All these can be found under ...Documents\Github\Semi-Automatic-Shifting-System\    |
::--------------------------------------------------------------------------------------


:: Custom file paths
set setup_dir="%userprofile%\Documents\GitHub\Semi-Automatic-Shifting-System\Setup\"
set update_dir="%userprofile%\Documents\GitHub\Semi-Automatic-Shifting-System\Code\"

:: Go into setup directory 
cd %setup_dir%

:: Run the setup script
start setup_script.bat

:: Wait for one second (this was a hack way of waiting for a second)
ping 127.0.0.1 -n 6 > nul

:: Go into update directory
cd %update_dir%

:: Run the setup script
start update_script.bat

:: End of script
exit