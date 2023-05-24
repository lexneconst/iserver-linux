
# Project: webserver
# Makefile created by Embarcadero Dev-C++ 6.3

WORK_DIR = D:/iserver/iserverv2.5

WEBSERVER = webserver/
LIBAR     = libar/
LIBSRV    = libsrv/
LIBCSP    = libcsp/

CPP      = g++.exe -D__DEBUG__
CC       = gcc.exe -D__DEBUG__
WINDRES  = windres.exe

LIB_AR   =  -llibar
LIB_C    =  -lcrypto -lssl -lcrypto.dll -lssl.dll -lws2_32 -llibcsp $(LIB_AR) -llibsrv  
LIBS     = -L"C:/Program Files (x86)/Embarcadero/Dev-Cpp/TDM-GCC-64/lib" -L"C:/Program Files (x86)/Embarcadero/Dev-Cpp/TDM-GCC-64/x86_64-w64-mingw32/lib" -static-libgcc -L"D:/iserver/iserverv2.5/lib" -L"D:/iserver/iserverv2.5/debug/bin" -pg -g3
INCS     = -I"C:/Program Files (x86)/Embarcadero/Dev-Cpp/TDM-GCC-64/include" -I"C:/Program Files (x86)/Embarcadero/Dev-Cpp/TDM-GCC-64/x86_64-w64-mingw32/include" -I"C:/Program Files (x86)/Embarcadero/Dev-Cpp/TDM-GCC-64/lib/gcc/x86_64-w64-mingw32/9.2.0/include" -I"D:/iserver/iserverv2.5/include" -I"D:/openssl-3.0.5/include"
CXXINCS  = -I"C:/Program Files (x86)/Embarcadero/Dev-Cpp/TDM-GCC-64/include" -I"C:/Program Files (x86)/Embarcadero/Dev-Cpp/TDM-GCC-64/x86_64-w64-mingw32/include" -I"C:/Program Files (x86)/Embarcadero/Dev-Cpp/TDM-GCC-64/lib/gcc/x86_64-w64-mingw32/9.2.0/include" -I"C:/Program Files (x86)/Embarcadero/Dev-Cpp/TDM-GCC-64/lib/gcc/x86_64-w64-mingw32/9.2.0/include/c++" -I"D:/iserver/iserverv2.5/include" -I"D:/openssl-3.0.5/include"

DEL      = C:\Program Files (x86)\Embarcadero\Dev-Cpp\devcpp.exe INTERNAL_DEL

EXEC_LIBS  = $(LIBS) $(LIB_C)
EXEC_OBJ      = $(WEBSERVER)main.o $(WEBSERVER)logs.o $(WEBSERVER)module.o $(WEBSERVER)config.o $(WEBSERVER)request.o $(WEBSERVER)cpath.o $(WEBSERVER)type.o $(WEBSERVER)page.o $(WEBSERVER)read.o $(WEBSERVER)dir.o $(WEBSERVER)ssl.o $(WEBSERVER)script.o
EXEC_LINKOBJ  = $(WEBSERVER)main.o $(WEBSERVER)logs.o $(WEBSERVER)module.o $(WEBSERVER)config.o $(WEBSERVER)request.o $(WEBSERVER)cpath.o $(WEBSERVER)type.o $(WEBSERVER)page.o $(WEBSERVER)read.o $(WEBSERVER)dir.o $(WEBSERVER)ssl.o $(WEBSERVER)script.o
EXEC_BIN      = $(WORK_DIR)/debug/bin/iserver.exe
EXECXXFLAGS = $(CXXINCS) -w -pg -g3 -D__WINCRYPT_H__=1 -DOPENSSL_SYS_WIN32=1
EXECFLAGS   = $(INCS) -w -pg -g3 -D__WINCRYPT_H__=1 -DOPENSSL_SYS_WIN32=1

LIBAR_LIBS = $(LIBS) 
LIBAR_OBJ      = $(LIBAR)dllmain.o $(LIBAR)liberr.o $(LIBAR)libnew.o $(LIBAR)liballoc.o $(LIBAR)libcstr.o $(LIBAR)libmod.o
LIBAR_LINKOBJ  = $(LIBAR)dllmain.o $(LIBAR)liberr.o $(LIBAR)libnew.o $(LIBAR)liballoc.o $(LIBAR)libcstr.o $(LIBAR)libmod.o
LIBAR_BIN      = $(WORK_DIR)/debug/bin/libar.dll
ARCXXFLAGS = $(CXXINCS) -DCBUILDING_DLL=1
ARCFLAGS   = $(INCS) -DCBUILDING_DLL=1
ARDEF      = $(WORK_DIR)/lib/liblibar.def
ARSTATIC   = $(WORK_DIR)/lib/liblibar.a

LIBSRV_LIBS = $(LIBS) $(LIB_AR)
LIBSRV_OBJ      = $(LIBSRV)dllmain.o $(LIBSRV)libsrv.o
LIBSRV_LINKOBJ  = $(LIBSRV)dllmain.o $(LIBSRV)libsrv.o
LIBSRV_BIN      = $(WORK_DIR)/debug/bin/libsrv.dll
SRVCXXFLAGS = $(CXXINCS) -DBUILDING_DLL=1
SRVCFLAGS   = $(INCS) -DBUILDING_DLL=1
SRVDEF      = $(WORK_DIR)/lib/liblibsrv.def
SRVSTATIC   = $(WORK_DIR)/lib/liblibsrv.a

LIBCSP_LIBS = $(LIBS) $(LIB_AR)
LIBCSP_OBJ      = $(LIBCSP)dllmain.o $(LIBCSP)libcsp.o $(LIBCSP)csprint.o $(LIBCSP)isql.o $(LIBCSP)init.o $(LIBCSP)header.o $(LIBCSP)sha2.o $(LIBCSP)xspapi.o $(LIBCSP)webapi.o
LIBCSP_LINKOBJ  = $(LIBCSP)dllmain.o $(LIBCSP)libcsp.o $(LIBCSP)csprint.o $(LIBCSP)isql.o $(LIBCSP)init.o $(LIBCSP)header.o $(LIBCSP)sha2.o $(LIBCSP)xspapi.o $(LIBCSP)webapi.o
LIBCSP_BIN      = $(WORK_DIR)/debug/bin/libcsp.dll
CSPCXXFLAGS = $(CXXINCS) -w -DBUILDING_DLL=1 -D__WINCRYPT_H__=1
CSPCFLAGS   = $(INCS) -w -DBUILDING_DLL=1 -D__WINCRYPT_H__=1
CSPDEF      = $(WORK_DIR)/lib/liblibcsp.def
CSPSTATIC   = $(WORK_DIR)/lib/liblibcsp.a

.PHONY: all all-before all-after clean clean-custom

all: all-before $(LIBAR_BIN) $(LIBSRV_BIN) $(LIBCSP_BIN) $(EXEC_BIN) all-after

biserver: all-before $(EXEC_BIN) all-after

blibar: all-before $(LIBAR_BIN) all-after

blibsrv: all-before $(LIBSRV_BIN) all-after

blibcsp: all-before $(LIBCSP_BIN) all-after

run:
	$(EXEC_BIN)

clean: clean-custom
	${DEL} $(EXEC_OBJ) $(EXEC_BIN)
	${DEL} $(LIBAR_OBJ) $(LIBAR_BIN) $(ARDEF) $(ARSTATIC)
	${DEL} $(LIBSRV_OBJ) $(LIBSRV_BIN) $(SRVDEF) $(SRVSTATIC)
	${DEL} $(LIBCSP_OBJ) $(LIBCSP_BIN) $(CSPDEF) $(CSPSTATIC)
	
ciserver:
	${DEL} $(EXEC_OBJ) $(EXEC_BIN)

clibar:
	${DEL} $(LIBAR_OBJ) $(LIBAR_BIN) $(ARDEF) $(ARSTATIC)
	
clibsrv:
	${DEL} $(LIBSRV_OBJ) $(LIBSRV_BIN) $(SRVDEF) $(SRVSTATIC)
	
clibcsp:
	${DEL} $(LIBCSP_OBJ) $(LIBCSP_BIN) $(CSPDEF) $(CSPSTATIC)
	
# iserver.exe compiler
	
$(EXEC_BIN): $(EXEC_OBJ)
	$(CC) $(EXEC_LINKOBJ) -o $(EXEC_BIN) $(EXEC_LIBS)

$(WEBSERVER)main.o: $(WEBSERVER)main.c
	$(CC) -c $(WEBSERVER)main.c -o $(WEBSERVER)main.o $(EXECFLAGS)

$(WEBSERVER)logs.o: $(WEBSERVER)logs.c
	$(CC) -c $(WEBSERVER)logs.c -o $(WEBSERVER)logs.o $(EXECFLAGS)

$(WEBSERVER)module.o: $(WEBSERVER)module.c
	$(CC) -c $(WEBSERVER)module.c -o $(WEBSERVER)module.o $(EXECFLAGS)

$(WEBSERVER)config.o: $(WEBSERVER)config.c
	$(CC) -c $(WEBSERVER)config.c -o $(WEBSERVER)config.o $(EXECFLAGS)

$(WEBSERVER)request.o: $(WEBSERVER)request.c
	$(CC) -c $(WEBSERVER)request.c -o $(WEBSERVER)request.o $(EXECFLAGS)

$(WEBSERVER)cpath.o: $(WEBSERVER)cpath.c
	$(CC) -c $(WEBSERVER)cpath.c -o $(WEBSERVER)cpath.o $(EXECFLAGS)

$(WEBSERVER)type.o: $(WEBSERVER)type.c
	$(CC) -c $(WEBSERVER)type.c -o $(WEBSERVER)type.o $(EXECFLAGS)

$(WEBSERVER)page.o: $(WEBSERVER)page.c
	$(CC) -c $(WEBSERVER)page.c -o $(WEBSERVER)page.o $(EXECFLAGS)

$(WEBSERVER)read.o: $(WEBSERVER)read.c
	$(CC) -c $(WEBSERVER)read.c -o $(WEBSERVER)read.o $(EXECFLAGS)

$(WEBSERVER)dir.o: $(WEBSERVER)dir.c
	$(CC) -c $(WEBSERVER)dir.c -o $(WEBSERVER)dir.o $(EXECFLAGS)

$(WEBSERVER)ssl.o: $(WEBSERVER)ssl.c
	$(CC) -c $(WEBSERVER)ssl.c -o $(WEBSERVER)ssl.o $(EXECFLAGS)

$(WEBSERVER)script.o: $(WEBSERVER)script.c
	$(CC) -c $(WEBSERVER)script.c -o $(WEBSERVER)script.o $(EXECFLAGS)


# libar.dll compiler


$(LIBAR_BIN): $(LIBAR_LINKOBJ)
	$(CC) -shared $(LIBAR_LINKOBJ) -o $(LIBAR_BIN) $(LIBAR_LIBS) -Wl,--output-def,$(ARDEF),--out-implib,$(ARSTATIC),--add-stdcall-alias

$(LIBAR)dllmain.o: $(LIBAR)dllmain.c
	$(CC) -c $(LIBAR)dllmain.c -o $(LIBAR)dllmain.o $(ARCFLAGS)

$(LIBAR)liberr.o: $(LIBAR)liberr.c
	$(CC) -c $(LIBAR)liberr.c -o $(LIBAR)liberr.o $(ARCFLAGS)

$(LIBAR)libnew.o: $(LIBAR)libnew.c
	$(CC) -c $(LIBAR)libnew.c -o $(LIBAR)libnew.o $(ARCFLAGS)

$(LIBAR)liballoc.o: $(LIBAR)liballoc.c
	$(CC) -c $(LIBAR)liballoc.c -o $(LIBAR)liballoc.o $(ARCFLAGS)

$(LIBAR)libcstr.o: $(LIBAR)libcstr.c
	$(CC) -c $(LIBAR)libcstr.c -o $(LIBAR)libcstr.o $(ARCFLAGS)

$(LIBAR)libmod.o: $(LIBAR)libmod.c
	$(CC) -c $(LIBAR)libmod.c -o $(LIBAR)libmod.o $(ARCFLAGS)

# libsrv.dll compiler


$(LIBSRV_BIN): $(LIBSRV_LINKOBJ)
	$(CC) -shared $(LIBSRV_LINKOBJ) -o $(LIBSRV_BIN) $(LIBSRV_LIBS) -Wl,--output-def,$(SRVDEF),--out-implib,$(SRVSTATIC),--add-stdcall-alias

$(LIBSRV)dllmain.o: $(LIBSRV)dllmain.c
	$(CC) -c $(LIBSRV)dllmain.c -o $(LIBSRV)dllmain.o $(SRVCFLAGS)

$(LIBSRV)libsrv.o: $(LIBSRV)libsrv.c
	$(CC) -c $(LIBSRV)libsrv.c -o $(LIBSRV)libsrv.o $(SRVCFLAGS)

# libcsp.dll compiler

$(LIBCSP_BIN): $(LIBCSP_LINKOBJ)
	$(CC) -shared $(LIBCSP_LINKOBJ) -o $(LIBCSP_BIN) $(LIBCSP_LIBS) -Wl,--output-def,$(CSPDEF),--out-implib,$(CSPSTATIC),--add-stdcall-alias

$(LIBCSP)dllmain.o: $(LIBCSP)dllmain.c
	$(CC) -c $(LIBCSP)dllmain.c -o $(LIBCSP)dllmain.o $(CSPCFLAGS)

$(LIBCSP)libcsp.o: $(LIBCSP)libcsp.c
	$(CC) -c $(LIBCSP)libcsp.c -o $(LIBCSP)libcsp.o $(CSPCFLAGS)

$(LIBCSP)csprint.o: $(LIBCSP)csprint.c
	$(CC) -c $(LIBCSP)csprint.c -o $(LIBCSP)csprint.o $(CSPCFLAGS)

$(LIBCSP)isql.o: $(LIBCSP)isql.c
	$(CC) -c $(LIBCSP)isql.c -o $(LIBCSP)isql.o $(CSPCFLAGS)

$(LIBCSP)init.o: $(LIBCSP)init.c
	$(CC) -c $(LIBCSP)init.c -o $(LIBCSP)init.o $(CSPCFLAGS)

$(LIBCSP)header.o: $(LIBCSP)header.c
	$(CC) -c $(LIBCSP)header.c -o $(LIBCSP)header.o $(CSPCFLAGS)

$(LIBCSP)sha2.o: $(LIBCSP)sha2.c
	$(CC) -c $(LIBCSP)sha2.c -o $(LIBCSP)sha2.o $(CSPCFLAGS)

$(LIBCSP)xspapi.o: $(LIBCSP)xspapi.c
	$(CC) -c $(LIBCSP)xspapi.c -o $(LIBCSP)xspapi.o $(CSPCFLAGS)

$(LIBCSP)webapi.o: $(LIBCSP)webapi.c
	$(CC) -c $(LIBCSP)webapi.c -o $(LIBCSP)webapi.o $(CSPCFLAGS)
	