# Compiler / Linker tools
AR     := xt-ar
CC     := xt-xcc
CPP    := xt-xc++
RANLIB := ranlib
RL     := xt-ld
STRIP  := xt-strip
RUN    := xt-run
# Xtensa info
ifeq "$(XTENSA_CORE)" "hemilite_shapiro_RI04"
XTOOLS_VNUM := RI04
endif

XTENSA_SYS = --xtensa-system=$(XTENSA_SYSTEM) --xtensa-core=$(XTENSA_CORE) --xtensa-params=
XTENSA_FLAGS= -DPROC_$(XTENSA_CORE) -DCONFIG_$(XTENSA_CORE) $(XTENSA_SYS)


#Custom compiler flags
CUSTOM_FLAGS = -g -c -fsigned-char -mtext-section-literals -mlongcalls -fmessage-length=0 -fno-strict-aliasing

#If code needs to be compiled for 'c++11'
# CUSTOM_FLAGS ?= -g -c -fsigned-char -mtext-section-literals -mlongcalls -fmessage-length=0 -fno-strict-aliasing -std=c++11


NO_IPA?=1
ifeq ($(NO_IPA),1)
IPA_FLAGS=
else
IPA_FLAGS=-ipa
endif

COMPILER_DEFS=-DBS_ISS_PROF_SWITCH

COMPILER_FLAGS = $(XTENSA_FLAGS) $(CUSTOM_FLAGS) $(IPA_FLAGS) $(COMPILER_DEFS) -DXTOOLS_VNUM=$(XTOOLS_VNUM)

# Optimization flags
OPT_FLAGS=-O2 -Os

# Warning flags
WARN_ERR_FLAGS += -Werror -Wall

# Full set of 'C' flags
CFLAGS := $(COMPILER_FLAGS) $(OPT_FLAGS) $(WARN_ERR_FLAGS)

PREFIX=xcc
SUFFIX=a
