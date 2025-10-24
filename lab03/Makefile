# the programs we want to use to compile our stuff
CXX=g++
CXXFLAGS=-g 
CC=gcc
CCFLAGS=-g 
AS=as
ASFLAGS=-g 
LD=ld
LDFLAGS=

# if this computer isn't running an ARM32 processor, use QEMU
UNAME=$(shell uname -m)
ifneq ($(UNAME), aarch64)
	CXX=aarch64-linux-gnu-g++
	CC=aarch64-linux-gnu-gcc
	AS=aarch64-linux-gnu-as
	LD=aarch64-linux-gnu-ld
	CXXFLAGS+= -static
	CCFLAGS+= -static
	LDFLAGS+= -static
endif

# what we want to build when we just say "make"
BINARIES=Point3D_add string_to_integer
all: $(BINARIES)

# how to compile each different kind of .o file
%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $^
%.o : %.c
	$(CC) $(CCFLAGS) -c $^
%.o : %.s
	$(AS) $(ASFLAGS) $^ -o $@

Point3D_add: Point3D_add.o Point3D_driver.o
	$(CXX) $(CXXFLAGS) $^ -o $@

string_to_integer: string_to_integer.o string_to_integer_driver.o
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f $(BINARIES) *.o
