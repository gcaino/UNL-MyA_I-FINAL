@echo off

set (PROJECT_DIR)=%~1
set (TARGET_OUTPUT_DIR)=%~2

Xcopy /E /I /Y /D "%(PROJECT_DIR)%assets" "%(TARGET_OUTPUT_DIR)%assets"

Xcopy /E /I /Y /D "%(PROJECT_DIR)%libs\SFML\bin\openal32.dll" "%(TARGET_OUTPUT_DIR)%"