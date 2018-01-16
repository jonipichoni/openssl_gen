# Config build
DIRECTORY=build
RELEASE_MODE=Release
TOOL_CHAIN="Visual Studio 15 2017"
SHARED_LIBS=OFF

# Openssl include and lib dirs
C_OPENSSL_ROOT_DIR="C:/OpenSSL-Win322"
C_OPENSSL_INCLUDE_DIR="C:/OpenSSL-Win32/include"

# OS Detection
unameOut="$(uname -s)"
case "${unameOut}" in
    Linux*)     machine=Linux;;
    Darwin*)    machine=Mac;;
    CYGWIN*)    machine=Cygwin;;
    MINGW*)     machine=MinGw;;
    *)          machine="UNKNOWN:${unameOut}"
esac
echo "Bash interpreter detected: "${machine}

if [ "${machine}" == "Linux" ]; then
	DIRECTORY=build_linux
else
	DIRECTORY=build
fi

if [ -d "$DIRECTORY" ]; then
	rm -r $DIRECTORY
	if [ $? -eq 0 ]
	then
	  echo "Successfully erased build directory"
	else
	  echo "Failed to erase build directory. Used on the IDE?" >&2
	  exit 1
	fi
fi

mkdir $DIRECTORY
cd $DIRECTORY

if [ "${machine}" == "Linux" ]; then
	cmake .. -DCMAKE_BUILD_TYPE=$RELEASE_MODE -DBUILD_SHARED_LIBS="${SHARED_LIBS}"
else
	cmake .. -G "${TOOL_CHAIN}"  -DCMAKE_BUILD_TYPE=$RELEASE_MODE -DOPENSSL_ROOT_DIR="$C_OPENSSL_ROOT_DIR"  -DOPENSSL_INCLUDE_DIR="$C_OPENSSL_INCLUDE_DIR" -DBUILD_SHARED_LIBS="${SHARED_LIBS}"
fi

if [ $? -eq 0 ]
then
  echo "Successfully cmake config"
else
  echo "Failed to cmake config" >&2
  exit 1
fi

#cmake --build . --target $TARGET --config $RELEASE_MODE
cmake --build . --config $RELEASE_MODE

if [ $? -eq 0 ]
then
  echo "Successfully cmake build"
else
  echo "Failed to cmake build" >&2
  exit 1
fi

ctest -C $RELEASE_MODE -V

if [ $? -eq 0 ]
then
  echo "All tests passed"
else
  echo "Tests Failed" >&2
  exit 1
fi

exit 0
