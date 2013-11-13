set name=MyStrategy

if not exist %name%.cpp (
    echo Unable to find %name%.cpp > compilation.log
    exit 1
)

if not "%VS100COMNTOOLS%"=="" (
    call "%VS100COMNTOOLS%\vsvars32.bat"
    call "%VS100COMNTOOLS%\..\..\VC\bin\vcvars32.bat"
) else (
    if not "%VS90COMNTOOLS%"=="" (
        call "%VS90COMNTOOLS%\vsvars32.bat"
        call "%VS90COMNTOOLS%\..\..\VC\bin\vcvars32.bat"
    ) else (
        if not "%VS80COMNTOOLS%"=="" (
            call "%VS80COMNTOOLS%\vsvars32.bat"
            call "%VS80COMNTOOLS%\..\..\VC\bin\vcvars32.bat"
        )
    )
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

cl /Fe%name%.exe /W4 /F268435456 /EHsc /O2 /DONLINE_JUDGE /DWIN32 ws2_32.lib %FILES% 1>compilation.log
