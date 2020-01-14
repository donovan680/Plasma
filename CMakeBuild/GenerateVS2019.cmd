pushd %~dp0

set folder_name="VS2019_MSVC_Windows"
rd %folder_name% /s/q

mkdir %folder_name%

cd %folder_name%

set config=Windows_VS_2017

cmake -E remove_directory ..\..\BuildOutput\Out\%config%

cmake -G "Visual Studio 16 2019" -A Win32 -DWindows_VS_2017=ON -DBits_32=ON ../..

popd
