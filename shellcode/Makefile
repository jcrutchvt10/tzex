all: secboot_hash write_qfprom scratch

TARGET_DEVICE = TARGET_DEVICE_G2
PWD 		:= $(shell pwd)
CCPATH 		:= /path/to/your/androideabi/bin
OUTDIR 		= ./../build

shellcode:
	$(CCPATH)/arm-eabi-gcc -c secboot_hash.S -o $(OUTDIR)/shellcode -march=armv7-a
	$(CCPATH)/arm-eabi-objcopy -O binary $(OUTDIR)/shellcode $(OUTDIR)/shellcode.bin        
	$(CCPATH)/arm-eabi-objdump -d $(OUTDIR)/shellcode
