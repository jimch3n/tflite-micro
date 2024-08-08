# compiler / linking tools
AR			:= ar
CC			:= gcc
CPP			:= g++
RANLIB		:= ranlib
RL			:= ld
STRIP		:= strip

# compiler flags
COMPILER_DEFS=-D__int64="long long"
COMPILER_FLAGS=-fsigned-char -fmessage-length=0 -m32 -fno-strict-aliasing $(COMPILER_DEFS)

# optimization flag
OPT_FLAGS=-O2

# warning flag
WARN_ERR_FLAGS=

PREFIX=gcc
SUFFIX=a
