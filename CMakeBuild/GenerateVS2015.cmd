pushd %~dp0

set folder_name="VS2015_MSVC_Windows"
rd %folder_name% /s/q

mkdir %folder_name%

cd %folder_name%

set config=Windows_VS_2015

cmake -E remove_directory ..\..\BuildOutput\Out\%config%

cmake -G "Visual Studio 14 2015" -D%config%=ON -DBits_32=ON ../..

popd
