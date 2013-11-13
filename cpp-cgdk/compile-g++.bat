set name=MyStrategy

if not exist %name%.cpp (
    echo Unable to find %name%.cpp > compilation.log
    exit 1
)

del /F /Q %name%.exe

SET FILES=

for %%i in (*.cpp) do (
    call concatenate %%i
)

for %%i in (model\*.cpp) do (
    call concatenate %%i
)

for %%i in (csimplesocket\*.cpp) do (
    call concatenate %%i
)

g++.exe -static -fno-optimize-sibling-calls -fno-strict-aliasing -DONLINE_JUDGE -lm -s -x c++ -Wl,--stack=268435456 -O2 -o %name%.exe %FILES% -lws2_32 -lwsock32 2>compilation.log
