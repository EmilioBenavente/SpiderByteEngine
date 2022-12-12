echo >/dev/null # >nul & GOTO WINDOWS & rem ^
echo 'Processing for Linux'

if [ ! -d "../../build" ]; then
    mkdir ../../build
fi

# Eventually -lX11 -lXrandr -lXi 

pushd ../../build
#@TODO(Emilio): On release, make this portable not home/emilio
g++ -g -o Game /home/emilio/Documents/Spider_Byte_Engine/Spider_Byte_Engine/code/Linux64_SpiderByteEngine.cpp \
	/home/emilio/Documents/Spider_Byte_Engine/Spider_Byte_Engine/code/glad.c \
	-I/home/emilio/Documents/Spider_Byte_Engine/Spider_Byte_Engine/res/includes/ -lglfw3 -lGL -ldl -lpthread
popd

exit 0

- - - - - - - - - -

:WINDOWS
echo 'Processing for Windows'

REM Do Windows CMD commands here... for example:
SET StartDir=%cd%
