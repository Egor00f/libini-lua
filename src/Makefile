
CC=kos32-gcc
LD=kos32-ld
STRIP=kos32-strip
OBJCOPY=kos32-objcopy
FASM=fasm
STD=-std=c11
CFLAGS=$(SYSCFLAGS) -O2 -Wall -Wextra $(STD) $(MYCFLAGS)
LDFLAGS=$(SYSLDFLAGS) $(MYLDFLAGS)
LIBS=$(SYSLIBS) $(MYLIBS)

ifeq ($(OS),Windows_NT)
	TOOLCHAIN_PATH=C:/MinGW/msys/1.0/home/autobuild/tools/win32
else
	TOOLCHAIN_PATH=/home/autobuild/tools/win32
endif

KOLIBRIOS_REPO=../../kolibrios

C_LAYER_DIR=$(KOLIBRIOS_REPO)/contrib/C_Layer
LUA_DIR=../../lua-kolibrios

SDK_DIR=$(KOLIBRIOS_REPO)/contrib/sdk
NewLib_DIR=$(SDK_DIR)/sources/newlib
SYSCFLAGS=-fno-ident -fomit-frame-pointer -U__WIN32__ -U_Win32 -U_WIN32 -U__MINGW32__ -UWIN32 -nostdlib -I$(NewLib_DIR)/libc/include -I$(C_LAYER_DIR)/INCLUDE -I$(LUA_DIR)/src
SYSLDFLAGS=--image-base 0 -Tapp-dynamic.lds
SYSLIBS=-nostdlib -L $(SDK_DIR)/lib -L$(TOOLCHAIN_PATH)/lib -L$(TOOLCHAIN_PATH)/mingw32/lib -lgcc -lc.dll -ldll
MYCFLAGS=
MYLDFLAGS=
MYLIBS=
MYOBJS=

OBJECTS=libini.o loadlibini.obj

default: libini.dll


libini.dll: $(OBJECTS) (LUA_DIR)/src/lua54.dll
	$(CC) -shared -T dll.lds --entry _DllStartup -o $@ $(OBJECTS) $(LUA_DIR)/src/lua54.dll $(LIBS)


(LUA_DIR)/src/lua54.dll:
	$(MAKE) -C $(LUA_DIR)/src lua54.dll 

libini.o: libini.c libini.h

loadlibini.obj: loadlibini.asm

clean:
	rm -f $(OBJECTS) libini.dll

%.obj: %.asm
	$(FASM) $< $%
