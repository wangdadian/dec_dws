CXX=g++
ifndef DEBUG
DEBUG=1
endif
COMPILEMAIN=-m32

ARM=1
ifeq ($(ARM),1)
    CROSS_COMPILE	=arm-hisiv100nptl-linux-
    AS		= $(CROSS_COMPILE)as
    LD		= $(CROSS_COMPILE)ld
    CXX		= $(CROSS_COMPILE)g++
    CPP		= $(CXX) -E
    AR		= $(CROSS_COMPILE)ar
    NM		= $(CROSS_COMPILE)nm
    STRIP	= $(CROSS_COMPILE)strip
    OBJCOPY	= $(CROSS_COMPILE)objcopy
    OBJDUMP	= $(CROSS_COMPILE)objdump
    COMPILEMAIN=
endif

ifndef (VERSION)
VERSION="\"1.0.0.2\""
endif

ifndef (BUILDDATE)
BUILDDATE= "\"`date +%Y-%m-%d\ %k:%M:%S`\""
endif
#BUILDINFO=-DVERSION=$(VERSION) -DBUILDDATE=$(BUILDDATE)
BUILDINFO= 

ARCHNAME=libdws.a
MODULENAME=dws

INCLUDEDIR=-I./ -I./include/
LIBWEBS	=  ./lib/libwebs.a 
LIBDWS 	=  ./lib/$(ARCHNAME)
LIBDIR	= 

# User Management switch
UMSW	= -DUSER_MANAGEMENT_SUPPORT
# Digest Access switch
DASW	= -DDIGEST_ACCESS_SUPPORT
CFLAGS1	= -DWEBS -DUEMF -DOS="LINUX" -DLINUX $(UMSW) $(DASW) $(SSLSW) $(IFMODSW)
OTHERS	= -DB_STATS -DB_FILL -DDEBUG

ifeq ($(DEBUG),1)
CXXFLAGS=-g -Wall $(INCLUDEDIR) -Wno-deprecated $(BUILDINFO) $(CFLAGS1)
else
CXXFLAGS=-Wall -O3 $(INCLUDEDIR) $(BUILDINFO) $(CFLAGS1)
endif

OBJS_MAIN = main.o
OBJS_MOD= WebSvr.o IniFile.o DWConfig.o Facility.o User.o Network.o SysInfo.o \
		  TimeCfg.o Device.o WebDecoder.o EWConfig.o

all: $(MODULENAME)

$(ARCHNAME): $(OBJS_MOD)
	$(AR) -r $(ARCHNAME) $?
	mv $(ARCHNAME) ./lib/

$(MODULENAME):$(ARCHNAME) $(OBJS_MAIN)
	$(CXX) $(COMPILEMAIN) -o $(MODULENAME) $(OBJS_MAIN) $(LIBDWS) $(LIBWEBS) -ldl $(LIBDIR)  -lpthread -lcrypt	
%.o: %.cpp
	$(CXX) $(COMPILEMAIN) $(CXXFLAGS) -c -o $@ $<

clean:
	@rm -rf $(OBJS_MOD) $(OBJS_MAIN) $(MODULENAME) ./lib/$(ARCHNAME)
install:
	cp -f ./lib/$(ARCHNAME) /opt/Hi3531/MainBranche/lib/dws/lib/
	cp -f *.h /opt/Hi3531/MainBranche/lib/dws/include/
	cp -f ./include/*.h /opt/Hi3531/MainBranche/lib/dws/include/
