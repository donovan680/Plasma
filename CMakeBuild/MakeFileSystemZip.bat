REM Make sure 7-Zip is installed and added to the path
cd ..

REM Make the editor file system
del /F /Q "BuildOutput/PlasmaEditorFileSystem.zip"
7z a -tzip -mx=9 -mfb=128 -mpass=10 "BuildOutput/PlasmaEditorFileSystem.zip" "Resources/Loading" "Resources/FragmentCore" "Resources/PlasmaCore" "Resources/Editor" "Resources/EditorUi" "Resources/UiWidget" "PrebuiltPlasmaContent" "Tools/SpriteVersion.txt" "Data/ColorSchemes" "Data/Fallback" "Data/Licenses" "Data/LightningFragmentSettings" "Data/*.*"

REM Make the launcher file system
del /F /Q "BuildOutput/PlasmaLauncherFileSystem.zip"
7z a -tzip -mx=9 -mfb=128 -mpass=10 "BuildOutput/PlasmaLauncherFileSystem.zip" "Resources/Loading" "Resources/FragmentCore" "Resources/PlasmaCore" "Resources/PlasmaLauncherResources" "PrebuiltPlasmaContent" "Tools/SpriteVersion.txt" "Data/ColorSchemes" "Data/Fallback" "Data/Licenses" "Data/LightningFragmentSettings" "Data/*.*"

pause