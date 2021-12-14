
#this ensures newer versions of g++ will not be used with cmake

if command -v g++-9 > /dev/null 2>&1; then
export CXX=$(command -v g++-9)
else
echo "please install g++-9"
exit
fi

rm -rf ./bin
mkdir -p bin && cd bin

conan install .. -pr=../conanprofile.txt

cmake ..
cmake --build . -- -j `nproc`
