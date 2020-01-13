echo off
SET PLASMA_SOURCE=%~1
SET BuildFolder=%PLASMA_SOURCE%\Build
SET BuildVersionIdsFolder=%BuildFolder%\BuildVersionIds
SET TempFile="%BuildFolder%\BuildVersion.temp"

REM otherwise, check if git exists
call git status > nul
if %errorlevel% == 0 goto :GitPresent

REM Check if mercurial exists
call hg status > nul
if %errorlevel% == 0 goto :MercurialPresent

REM otherwise, fallback on having no source control
goto :NoSourceControl

REM Run the mercurial commit information extraction step
:MercurialPresent
call "%BuildFolder%\UpdateBuildVersion.hg.cmd" %1 %TempFile%
goto :Finish

REM Run the git commit information extraction step
:GitPresent
call "%BuildFolder%\UpdateBuildVersion.git.cmd" %1 %TempFile%
goto :Finish

REM Run a backup information extraction step (uses stub info)
:NoSourceControl
call "%BuildFolder%\UpdateBuildVersion.none.cmd" %1 %TempFile%
goto :Finish

:Finish
REM Only copy this file over the one in source if it's different or doesn't exist.
REM Do this to prevent always rebuilding.
fc %TempFile% "%PLASMA_SOURCE%\Systems\Engine\BuildVersion.inl" > nul
if %errorlevel%==0 (
  echo BuildVersion file was the same, not updating to avoid rebuild.
  goto :removetemp
)
copy %TempFile% "%PLASMA_SOURCE%\Systems\Engine\BuildVersion.inl"

REM Delete the temporary file
:removetemp
del %TempFile%
