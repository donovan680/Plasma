pushd %~dp0

set folder_name="VS2015_MSVC_Windows"
rd %folder_name% /s/q

mkdir %folder_name%

pushd %folder_name%

set config=Windows_VS_2015

cmake -E remove_directory ..\..\BuildOutput\Out\%config%

cmake -G "Visual Studio 14 2015" -Dgenerate_with_unit_tests=ON -D%config%Windows_VS_2015=ON -DBits_32=ON ../..

popd
popd
