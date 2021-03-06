
VERSION = 3
all: module

PATCHLEVEL = 4
SUBLEVEL = 0
EXTRAVERSION =


obj-m := tz_exploit.o
tz_exploit-objs := main.o file_io.o exploit.o

TARGET_DEVICE = TARGET_DEVICE_G2
KDIR 		:= /path/to/your/kernel/files/
PWD 		:= $(shell pwd)
CCPATH 		:= /path/to/your/androideabi/bin
CFLAGS_MODULE := -fno-pic -D $(TARGET_DEVICE) -Wno-unused-variable
SHELLCODE_PATH = $(PWD)/shellcode

module:
	$(MAKE) ARCH=arm CROSS_COMPILE=$(CCPATH)/arm-linux-androideabi- -C $(KDIR) M=$(PWD) modules 
	$(CCPATH)/arm-linux-androideabi-strip --strip-unneeded tz_exploit.ko -o $(PWD)/build/tz_exploit.ko
	$(MAKE) -C $(SHELLCODE_PATH)

clean:
	rm -f *.o *.mod.c Module.symvers Module.markers modules.order .*.o.cmd .*.ko.cmd .*.o.d *.ko
	rm -rf \.tmp_versions	
	rm -rf build/*