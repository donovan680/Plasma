echo off
SET PLASMA_SOURCE=%~1
SET TempFile=%~2
SET BuildFolder=%PLASMA_SOURCE%\Build
SET BuildVersionIdsFolder=%BuildFolder%\BuildVersionIds

echo #pragma once > %TempFile%
REM Always read from the default version id file
type %BuildVersionIdsFolder%\default.txt >> %TempFile%

REM We don't have any source control so just hard-code all of this information to empty
echo #define PlasmaRevisionId 0 >> %TempFile%
echo #define PlasmaShortChangeSet 0 >> %TempFile%
echo #define PlasmaChangeSet 0 >> %TempFile%
echo #define PlasmaChangeSetDate "" >> %TempFile%
