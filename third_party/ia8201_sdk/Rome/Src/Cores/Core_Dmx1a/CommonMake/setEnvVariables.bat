@echo off

set XTENSA_CORE=dmx1aRI04
set XTENSA_VER=RI-2020.4-win32
set XTENSA_SYSTEM_BASE=C:\usr\xtensa\XtDevTools\install\tools

set XTENSA_SYSTEM=%XTENSA_SYSTEM_BASE%\%XTENSA_VER%\XtensaTools\config
PATH=%XTENSA_SYSTEM_BASE%\%XTENSA_VER%\XtensaTools\bin;%PATH%
