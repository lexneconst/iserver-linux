
PROJECT=redq

LIBC=-lcrypto -lcrypt -lgcrypt -pthread -lssl -lm -lc -ldl -lanl -lz
CC= gcc
PROJECT_DIR=$(shell pwd)
DFLAGS=-c -Wall -fpic
CFLAGS= -L"/usr/lib/x86_64-linux-gnu/" -DEXEC_PROC=1 -w 
LIBCRT= $(LIBC) -lcrt0 
LIBCDM= -lar -lsec -lhta 

PROJECT00=iserver
PROJECTL0=libar.so
PROJECTL1=libhta.so
PROJECTL2=libsec.so
PROJECTL3=libcrt0.so

MODULEDIR=mod_dir.so
MODULECSP=mod_csp.so
MODULESTA=mod_status.so

OUTPUT_DIR=debug

LIBRPX= -Wl,-rpath=$(PROJECT_DIR)/$(OUTPUT_DIR)/bin

all: $(PROJECTL3) $(PROJECTL0) $(PROJECTL1) $(PROJECTL2) $(PROJECT00) $(MODULEDIR) $(MODULECSP) $(MODULESTA) 
##	$(CC) -o $(PROJECT) $(PROJECT).c $(LIBC)

###################################################################################################################################################


#                                      LIBRARY PROJECT


###################################################################################################################################################

OBJLIBCRT=libcrt/main.o	libcrt/liberr.o
libcrt/liberr.o:
	$(CC) -I"$(PROJECT_DIR)/include" -L"$(PROJECT_DIR)"  -L"$(PROJECT_DIR)/$(OUTPUT_DIR)/bin" $(CFLAGS) $(DFLAGS) -o $@ libcrt/liberr.c
libcrt/main.o:
	$(CC) -I"$(PROJECT_DIR)/include" -L"$(PROJECT_DIR)"  -L"$(PROJECT_DIR)/$(OUTPUT_DIR)/bin" $(CFLAGS) $(DFLAGS) -o $@ libcrt/main.c
$(PROJECTL3): $(OBJLIBCRT)
	$(CC) -shared $(OBJLIBCRT) -I$(PROJECT_DIR)/include -L$(PROJECT_DIR)  -L"$(PROJECT_DIR)/$(OUTPUT_DIR)/bin" $(CFLAGS) -o $(OUTPUT_DIR)/bin/$@

OBJLIBL00=libar/main.o libar/liballoc.o libar/libnew.o libar/libcstr.o libar/libmod.o libar/libread.o
libar/libread.o:
	$(CC) -I"$(PROJECT_DIR)/include" -L"$(PROJECT_DIR)"  -L"$(PROJECT_DIR)/$(OUTPUT_DIR)/bin" $(CFLAGS) $(DFLAGS) -o $@ libar/libread.c
libar/libmod.o:
	$(CC) -I"$(PROJECT_DIR)/include" -L"$(PROJECT_DIR)"  -L"$(PROJECT_DIR)/$(OUTPUT_DIR)/bin" $(CFLAGS) $(DFLAGS) -o $@ libar/libmod.c
libar/libcstr.o:
	$(CC) -I"$(PROJECT_DIR)/include" -L"$(PROJECT_DIR)"  -L"$(PROJECT_DIR)/$(OUTPUT_DIR)/bin" $(CFLAGS) $(DFLAGS) -o $@ libar/libcstr.c
libar/libnew.o:
	$(CC) -I"$(PROJECT_DIR)/include" -L"$(PROJECT_DIR)"  -L"$(PROJECT_DIR)/$(OUTPUT_DIR)/bin" $(CFLAGS) $(DFLAGS) -o $@ libar/libnew.c
libar/liballoc.o:
	$(CC) -I"$(PROJECT_DIR)/include" -L"$(PROJECT_DIR)"  -L"$(PROJECT_DIR)/$(OUTPUT_DIR)/bin" $(CFLAGS) $(DFLAGS) -o $@ libar/liballoc.c
libar/main.o:
	$(CC) -I"$(PROJECT_DIR)/include" -L"$(PROJECT_DIR)" -L"$(PROJECT_DIR)/$(OUTPUT_DIR)/bin" $(CFLAGS) $(DFLAGS) $(LIBCRT) -o $@ libar/main.c
$(PROJECTL0): $(OBJLIBL00)
	$(CC) -shared $(OBJLIBL00) -I$(PROJECT_DIR)/include -L$(PROJECT_DIR) -L"$(PROJECT_DIR)/$(OUTPUT_DIR)/bin" $(CFLAGS)  $(LIBCRT) -o $(OUTPUT_DIR)/bin/$@

OBJLIBHTA=libhta/main.o	libhta/script.o
libhta/script.o:
	$(CC) -I"$(PROJECT_DIR)/include" -L"$(PROJECT_DIR)"  -L"$(PROJECT_DIR)/$(OUTPUT_DIR)" $(CFLAGS) $(DFLAGS) $(LIBCRT) -o $@ libhta/script.c
libhta/main.o:
	$(CC) -I"$(PROJECT_DIR)/include" -L"$(PROJECT_DIR)"  -L"$(PROJECT_DIR)/$(OUTPUT_DIR)" $(CFLAGS) $(DFLAGS) $(LIBCRT) -o $@ libhta/main.c
$(PROJECTL1): $(OBJLIBHTA)
	$(CC) -shared $(OBJLIBHTA) -I$(PROJECT_DIR)/include -L$(PROJECT_DIR)  -L"$(PROJECT_DIR)/$(OUTPUT_DIR)/bin" $(CFLAGS)  $(LIBCRT) -o $(OUTPUT_DIR)/bin/$@

OBJLIBSEC=libsec/main.o	
libsec/main.o:
	$(CC) -I"$(PROJECT_DIR)/include" -L"$(PROJECT_DIR)"  -L"$(PROJECT_DIR)/$(OUTPUT_DIR)/bin" $(CFLAGS) $(DFLAGS) $(LIBCRT) -o $@ libsec/main.c
$(PROJECTL2): $(OBJLIBSEC)
	$(CC) -shared $(OBJLIBSEC) -I$(PROJECT_DIR)/include -L$(PROJECT_DIR)  -L"$(PROJECT_DIR)/$(OUTPUT_DIR)/bin" $(CFLAGS) $(LIBCRT) -o $(OUTPUT_DIR)/bin/$@
###################################################################################################################################################


#                                      EXEC PROJECT


###################################################################################################################################################


OBJTESTW00=webserver/main.o webserver/config.o webserver/cpath.o webserver/logs.o webserver/module.o webserver/ctrl.o webserver/request.o webserver/ssl.o webserver/type.o
webserver/config.o:
	$(CC) -I"$(PROJECT_DIR)/include" -L"$(PROJECT_DIR)/include" -L"$(PROJECT_DIR)/$(OUTPUT_DIR)/bin"  $(CFLAGS) $(DFLAGS) $(LIBCRT) $(LIBRPX) -o $@ webserver/config.c
webserver/cpath.o:
	$(CC) -I"$(PROJECT_DIR)/include" -L"$(PROJECT_DIR)/include" -L"$(PROJECT_DIR)/$(OUTPUT_DIR)/bin"  $(CFLAGS) $(DFLAGS) $(LIBCRT) $(LIBRPX) -o $@ webserver/cpath.c
webserver/logs.o:
	$(CC) -I"$(PROJECT_DIR)/include" -L"$(PROJECT_DIR)/include" -L"$(PROJECT_DIR)/$(OUTPUT_DIR)/bin"  $(CFLAGS) $(DFLAGS) $(LIBCRT) $(LIBRPX) -o $@ webserver/logs.c
webserver/module.o:
	$(CC) -I"$(PROJECT_DIR)/include" -L"$(PROJECT_DIR)/include" -L"$(PROJECT_DIR)/$(OUTPUT_DIR)/bin"  $(CFLAGS) $(DFLAGS) $(LIBCRT) $(LIBRPX) -o $@ webserver/module.c
webserver/ctrl.o:
	$(CC) -I"$(PROJECT_DIR)/include" -L"$(PROJECT_DIR)/include" -L"$(PROJECT_DIR)/$(OUTPUT_DIR)/bin"  $(CFLAGS) $(DFLAGS) $(LIBCRT) $(LIBRPX) -o $@ webserver/ctrl.c
webserver/request.o:
	$(CC) -I"$(PROJECT_DIR)/include" -L"$(PROJECT_DIR)/include" -L"$(PROJECT_DIR)/$(OUTPUT_DIR)/bin"  $(CFLAGS) $(DFLAGS) $(LIBCRT) $(LIBRPX) -o $@ webserver/request.c
webserver/ssl.o:
	$(CC) -I"$(PROJECT_DIR)/include" -L"$(PROJECT_DIR)/include" -L"$(PROJECT_DIR)/$(OUTPUT_DIR)/bin"  $(CFLAGS) $(DFLAGS) $(LIBCRT) $(LIBRPX) -o $@ webserver/ssl.c
webserver/type.o:
	$(CC) -I"$(PROJECT_DIR)/include" -L"$(PROJECT_DIR)/include" -L"$(PROJECT_DIR)/$(OUTPUT_DIR)/bin"  $(CFLAGS) $(DFLAGS) $(LIBCRT) $(LIBRPX) -o $@ webserver/type.c
webserver/main.o:
	$(CC) -I"$(PROJECT_DIR)/include" -L"$(PROJECT_DIR)/include" -L"$(PROJECT_DIR)/$(OUTPUT_DIR)/bin"  $(CFLAGS) $(DFLAGS) $(LIBCRT) $(LIBRPX) -o $@ webserver/main.c
$(PROJECT00): $(OBJTESTW00)
	$(CC) $(OBJTESTW00) -I$(PROJECT_DIR)/include -L$(PROJECT_DIR)  -L"$(PROJECT_DIR)/$(OUTPUT_DIR)/bin" $(CFLAGS) $(LIBCDM) $(LIBCRT) $(LIBS0) $(LIBRMD) $(LIBRPX) -o $(OUTPUT_DIR)/bin/$@


###################################################################################################################################################


#                                      MODULE PROJECT


###################################################################################################################################################

OBJMODDIR=libmod/libdir/main.o	
libmod/libdir/main.o:
	$(CC) -I"$(PROJECT_DIR)/include" -L"$(PROJECT_DIR)"  -L"$(PROJECT_DIR)/$(OUTPUT_DIR)/bin" $(CFLAGS) $(DFLAGS) $(LIBCRT) -o $@ libmod/libdir/main.c
$(MODULEDIR): $(OBJMODDIR)
	$(CC) -shared $(OBJMODDIR) -I$(PROJECT_DIR)/include -L$(PROJECT_DIR)  -L"$(PROJECT_DIR)/$(OUTPUT_DIR)/bin" $(CFLAGS) $(LIBCRT) -o $(OUTPUT_DIR)/module/$@

OBJMODCSP=libmod/libcsp/main.o	
libmod/libcsp/main.o:
	$(CC) -I"$(PROJECT_DIR)/include" -L"$(PROJECT_DIR)"  -L"$(PROJECT_DIR)/$(OUTPUT_DIR)/bin" $(CFLAGS) $(DFLAGS) $(LIBCRT) -o $@ libmod/libcsp/main.c
$(MODULECSP): $(OBJMODCSP)
	$(CC) -shared $(OBJMODCSP) -I$(PROJECT_DIR)/include -L$(PROJECT_DIR)  -L"$(PROJECT_DIR)/$(OUTPUT_DIR)/bin" $(CFLAGS) $(LIBCRT) -o $(OUTPUT_DIR)/module/$@

OBJMODSTA=libmod/libstatus/main.o	
libmod/libstatus/main.o:
	$(CC) -I"$(PROJECT_DIR)/include" -L"$(PROJECT_DIR)"  -L"$(PROJECT_DIR)/$(OUTPUT_DIR)/bin" $(CFLAGS) $(DFLAGS) $(LIBCRT) -o $@ libmod/libstatus/main.c
$(MODULESTA): $(OBJMODSTA)
	$(CC) -shared $(OBJMODSTA) -I$(PROJECT_DIR)/include -L$(PROJECT_DIR)  -L"$(PROJECT_DIR)/$(OUTPUT_DIR)/bin" $(CFLAGS) $(LIBCRT) -o $(OUTPUT_DIR)/module/$@



###################################################################################################################################################


#                                      CLEAN PROJECT


###################################################################################################################################################

clean: 
	rm -rf $(OUTPUT_DIR)/bin/$(PROJECTL0) libar/*.o
	rm -rf $(OUTPUT_DIR)/bin/$(PROJECTL1) libhta/*.o
	rm -rf $(OUTPUT_DIR)/bin/$(PROJECTL2) libsec/*.o
	rm -rf $(OUTPUT_DIR)/bin/$(PROJECTL3) libcrt/*.o
	rm -rf $(OUTPUT_DIR)/bin/$(PROJECT00) webserver/*.o
	rm -rf libmod/libstatus/*.o
	rm -rf libmod/libdir/*.o
	rm -rf libmod/libcsp/*.o
	rm -rf libmod/libhta/*.o
	rm -rf $(OUTPUT_DIR)/module/*.*
exp:
	LD_LIBRARY_PATH=$(PROJECT_DIR)/bin:$LD_LIBRARY_PATH
	echo $(LD_LIBRARY_PATH)





