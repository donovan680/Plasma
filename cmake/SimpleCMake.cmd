@echo off
SET CMakeOut="..\\CMakeBuilds"
SET PlasmaRoot="..\\"

IF NOT EXIST %CMakeOut% (md %CMakeOut%)

pushd %CMakeOut%

if [%1]==[] (
	@echo Generating Visual Studio 2013
	call cmake -G "Visual Studio 12 2013" %PlasmaRoot%
)

if %1==VS2010 (
    @echo Generating Visual Studio 2010
	call cmake -G "Visual Studio 10 2010" %PlasmaRoot%
)
if %1==VS2013 (
    @echo Generating Visual Studio 2013
	call cmake -G "Visual Studio 12 2013" %PlasmaRoot%
)

popd
