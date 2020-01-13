@echo off

SET PLASMA_SOURCE=%~1
SET TempFile=%2
SET BuildFolder=%PLASMA_SOURCE%\Build
SET BuildVersionIdsFolder=%BuildFolder%\BuildVersionIds
REM Hardcode to the default build info file. Branch information is not part of a commit node in git.
SET BuildIdBranchFileName="%BuildVersionIdsFolder%\default.txt"

REM Extract the "revision id" from git. This is number of commits from HEAD to the root of the repo
SET cmd=git rev-list --count HEAD
FOR /F "tokens=*" %%i IN (' %cmd% ') DO SET RevisionId=%%i
SET RevisionIdDefine=#define PlasmaRevisionId %RevisionId%

REM Output a pragma once, the version id file, and the revision id
@echo #pragma once > %TempFile%
type %BuildIdBranchFileName% >> %TempFile%
@echo %RevisionIdDefine% >> %TempFile%

REM build up the git log fomatting string
SET Format=format:
SET Format=%Format%#define PlasmaShortChangeSet %%h%%n
SET Format=%Format%#define PlasmaChangeSet %%H%%n
SET Format=%Format%#define PlasmaChangeSetDate \"%%cd\"%%n

REM Log the current commit info to the temp file (hardcode the short changeset to 12 characters)
git log -1 --abbrev=12 --date=format:"%%Y-%%m-%%d" --pretty="%Format%" >> %TempFile%


