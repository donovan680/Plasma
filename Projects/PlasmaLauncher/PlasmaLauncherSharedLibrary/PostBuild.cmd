SET OutDir=%1
SET SourceDir=%OutDir%\PlasmaLauncherSharedLibrary
SET DestDir=%OutDir%\PlasmaLauncher

Md %DestDir%
copy %SourceDir%\PlasmaLauncherSharedLibrary.dll %DestDir% /Y
copy %SourceDir%\PlasmaLauncherSharedLibrary.pdb %DestDir% /Y
