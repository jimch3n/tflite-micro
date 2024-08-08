# compiler / linking tools
AR			:= xt-ar
CC			:= xt-xcc
CPP			:= xt-xc++
RANLIB		:= ranlib
RL			:= xt-ld
STRIP		:= xt-strip

# Resolve flags.
ifeq "$(XTENSA_CORE)" "dmx1aRI04"
XTOOLS_VNUM := RI04
endif

# compiler flags
XTENSA_SYS = --xtensa-system=$(XTENSA_SYSTEM) --xtensa-core=$(XTENSA_CORE) --xtensa-params=
XTENSA_FLAGS= -DPROC_$(XTENSA_CORE) -DCONFIG_$(XTENSA_CORE) $(XTENSA_SYS)

CUSTOM_FLAGS?= -g # Enable full debug here

# If code needs to be compiled for 'c++11'
# CUSTOM_FLAGS?= -g -std=c++11 # Enable full debug here

NO_IPA?=1
ifeq ($(NO_IPA),1)
IPA_FLAGS=
else
IPA_FLAGS=-ipa
endif
COMPILER_DEFS=-DBS_ISS_PROF_SWITCH
COMPILER_FLAGS=$(IPA_FLAGS) $(CUSTOM_FLAGS) $(XTENSA_FLAGS) $(COMPILER_DEFS)  -DXTOOLS_VNUM=$(XTOOLS_VNUM)

# optimization flag
OPT_FLAGS=-O2

# warning flag
WARN_ERR_FLAGS=

PREFIX=xcc
SUFFIX=a
