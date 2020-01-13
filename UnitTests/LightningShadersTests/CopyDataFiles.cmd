SET PlasmaSource=%1
SET OutDir=%2
SET FragmentExtensionsDir=%PlasmaSource%\Resources\FragmentCore
SET OutputDir=%OutDir%\FragmentCore

SET FragmentExtensionsIRDir=%PlasmaSource%\UnitTests\LightningShaders\FragmentExtensions
SET FragmentExtensionsIROutputDir=%OutDir%\FragmentExtensionsIR

SET FragmentSettingsDir=%PlasmaSource%\Data\LightningFragmentSettings
SET FragmentSettingsOutputDir=%OutDir%\LightningFragmentSettings

Md %OutputDir%
Md %FragmentExtensionsIROutputDir%
Md %FragmentSettingsOutputDir%
echo %FragmentExtensionsDir%
echo %FragmentExtensionsIRDir%
echo %OutputDir%
copy %FragmentExtensionsDir% %OutputDir% /Y
xcopy %FragmentExtensionsIRDir% %FragmentExtensionsIROutputDir% /Y /S
copy %FragmentSettingsDir% %FragmentSettingsOutputDir% /Y