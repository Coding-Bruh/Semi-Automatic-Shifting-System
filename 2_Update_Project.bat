::File Name: Update_Project.bat
::Author: Abhinav Chennapareddy
::Date: 6/21/2017

:: This script will set update your keil environment with the lastest code from your local
:: Github repository. For specifics refer to update_script.bat.
::----------------------------------------------------------------------------------------
 
:: Custom file paths
set update_dir="%userprofile%\Documents\GitHub\Semi-Automatic-Shifting-System\Code\"

:: Go into update directory
cd %update_dir%

:: Run the setup script
start update_script.bat

:: End of script
exit