#!/bin/bash
export XTENSA_CORE=dmx1aRI04
export XTENSA_VER=RI-2020.4-linux

# Please do 'export XTENSA_SYSTEM_BASE' where '/xtensa/XtDevTools/install/tools' folder is present.

export PATH=$XTENSA_SYSTEM_BASE/$XTENSA_VER/XtensaTools/bin:$PATH
export XTENSA_SYSTEM=$XTENSA_SYSTEM_BASE/$XTENSA_VER/XtensaTools/config
