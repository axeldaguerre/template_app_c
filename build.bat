@echo off
IF NOT EXIST ..\build mkdir ..\build
pushd ..\build

set CommonCompilerFlags=-MTd -nologo -fp:fast -Gm- -GR- -EHa- -Od -Oi -WX -W4 -wd4201 -wd4100 -wd4189 -wd4505  -FC -Z7
set CommonLinkerFlags= -incremental:no -opt:ref user32.lib gdi32.lib winmm.lib

call cl %CommonCompilerFlags% ..\code\app_name.cpp -Fmapp_name.map -LD /link -incremental:no -opt:ref -PDB:app_name.pdb -EXPORT:AppUpdateAndRender
call cl %CommonCompilerFlags%  ..\code\win32_app_name.cpp -Feapp_name_msvc_debug.exe /link %CommonLinkerFlags%

