
PROJECT=redq

LIBC=-lcrypto -lcrypt -lgcrypt -lssl -lm -lc -ldl -lanl -lz
CC= gcc
PROJECT_DIR=$(shell pwd)
DFLAGS=-c -Wall 
CFLAGS= -L"/usr/lib/x86_64-linux-gnu/" -DEXEC_PROC=1 -w 
LIBCRT= $(LIBC)
LIBS0 =  


PROJECT00=genkeys
PROJECT01=localsign_trusted
PROJECT02=localsign_incmedia
PROJECT03=localsign_accept
PROJECT04=crlserials
PROJECT05=P7Pack

OUTPUT_DIR=release

all: $(PROJECT00) $(PROJECT01) $(PROJECT02) $(PROJECT03) $(PROJECT04) $(PROJECT05)
##	$(CC) -o $(PROJECT) $(PROJECT).c $(LIBC)

###################################################################################################################################################


#                                      LIBRARY PROJECT


###################################################################################################################################################


OBJTESTW00=genkeys/main.o
genkeys/main.o:
	$(CC) -I"$(PROJECT_DIR)/include" -L"$(PROJECT_DIR)" -L"$(PROJECT_DIR)/$(OUTPUT_DIR)"  $(CFLAGS) $(DFLAGS) $(LIBCRT) -o $@ genkeys/main.c
$(PROJECT00): $(OBJTESTW00)
	$(CC) $(OBJTESTW00) -I$(PROJECT_DIR)/include -L$(PROJECT_DIR)  -L"$(PROJECT_DIR)/$(OUTPUT_DIR)" $(CFLAGS) $(LIBCRT) $(LIBS0) $(LIBRMD) -o $(OUTPUT_DIR)/$@

OBJTESTW01=LocalSign_Trusted/main.o
LocalSign_Trusted/main.o:
	$(CC) -I"$(PROJECT_DIR)/include" -L"$(PROJECT_DIR)" -L"$(PROJECT_DIR)/$(OUTPUT_DIR)"  $(CFLAGS) $(DFLAGS) $(LIBCRT) -o $@ LocalSign_Trusted/main.c
$(PROJECT01): $(OBJTESTW01)
	$(CC) $(OBJTESTW01) -I$(PROJECT_DIR)/include -L$(PROJECT_DIR)  -L"$(PROJECT_DIR)/$(OUTPUT_DIR)" $(CFLAGS) $(LIBCRT) $(LIBS0) $(LIBRMD) -o $(OUTPUT_DIR)/$@


OBJTESTW02=LocalSign_IncMedia/main.o
LocalSign_IncMedia/main.o:
	$(CC) -I"$(PROJECT_DIR)/include" -L"$(PROJECT_DIR)" -L"$(PROJECT_DIR)/$(OUTPUT_DIR)"  $(CFLAGS) $(DFLAGS) $(LIBCRT) -o $@ LocalSign_IncMedia/main.c
$(PROJECT02): $(OBJTESTW02)
	$(CC) $(OBJTESTW02) -I$(PROJECT_DIR)/include -L$(PROJECT_DIR)  -L"$(PROJECT_DIR)/$(OUTPUT_DIR)" $(CFLAGS) $(LIBCRT) $(LIBS0) $(LIBRMD) -o $(OUTPUT_DIR)/$@


OBJTESTW03=LocalSign_Accept/main.o
LocalSign_Accept/main.o:
	$(CC) -I"$(PROJECT_DIR)/include" -L"$(PROJECT_DIR)" -L"$(PROJECT_DIR)/$(OUTPUT_DIR)"  $(CFLAGS) $(DFLAGS) $(LIBCRT) -o $@ LocalSign_Accept/main.c
$(PROJECT03): $(OBJTESTW03)
	$(CC) $(OBJTESTW03) -I$(PROJECT_DIR)/include -L$(PROJECT_DIR)  -L"$(PROJECT_DIR)/$(OUTPUT_DIR)" $(CFLAGS) $(LIBCRT) $(LIBS0) $(LIBRMD) -o $(OUTPUT_DIR)/$@


OBJTESTW04=CRLSerials/main.o
CRLSerials/main.o:
	$(CC) -I"$(PROJECT_DIR)/include" -L"$(PROJECT_DIR)" -L"$(PROJECT_DIR)/$(OUTPUT_DIR)"  $(CFLAGS) $(DFLAGS) $(LIBCRT) -o $@ CRLSerials/main.c
$(PROJECT04): $(OBJTESTW04)
	$(CC) $(OBJTESTW04) -I$(PROJECT_DIR)/include -L$(PROJECT_DIR)  -L"$(PROJECT_DIR)/$(OUTPUT_DIR)" $(CFLAGS) $(LIBCRT) $(LIBS0) $(LIBRMD) -o $(OUTPUT_DIR)/$@


OBJTESTW05=P7Pack/main.o
P7Pack/main.o:
	$(CC) -I"$(PROJECT_DIR)/include" -L"$(PROJECT_DIR)" -L"$(PROJECT_DIR)/$(OUTPUT_DIR)"  $(CFLAGS) $(DFLAGS) $(LIBCRT) -o $@ P7Pack/main.c
$(PROJECT05): $(OBJTESTW05)
	$(CC) $(OBJTESTW05) -I$(PROJECT_DIR)/include -L$(PROJECT_DIR)  -L"$(PROJECT_DIR)/$(OUTPUT_DIR)" $(CFLAGS) $(LIBCRT) $(LIBS0) $(LIBRMD) -o $(OUTPUT_DIR)/$@


###################################################################################################################################################


#                                      EXEC PROJECT


###################################################################################################################################################



clean: 
	rm -rf $(OUTPUT_DIR)/$(PROJECT00) genkeys/*.o
	rm -rf $(OUTPUT_DIR)/$(PROJECT01) LocalSign_Trusted/*.o
	rm -rf $(OUTPUT_DIR)/$(PROJECT02) LocalSign_IncMedia/*.o
	rm -rf $(OUTPUT_DIR)/$(PROJECT03) LocalSign_Accept/*.o
	rm -rf $(OUTPUT_DIR)/$(PROJECT04) CRLSerials/*.o
	rm -rf $(OUTPUT_DIR)/$(PROJECT05) P7Pack/*.o
	rm -rf $(OUTPUT_DIR)/certs/*.*
exp:
	LD_LIBRARY_PATH=$(PROJECT_DIR)/bin:$LD_LIBRARY_PATH
	echo $(LD_LIBRARY_PATH)





