pushd %~dp0

set folder_name="VS2015_LLVM-vs2014_Windows"
rd %folder_name% /s/q

mkdir %folder_name%

pushd %folder_name%

set config=VS_LLVM_2014

cmake -E remove_directory ..\..\BuildOutput\Out\%config%

cmake -G "Visual Studio 14 2015" -Dgenerate_with_unit_tests=ON -D%config%=ON -DBits_32=ON -TLLVM-vs2014 ../..

popd
popd