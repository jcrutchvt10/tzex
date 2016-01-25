This is a rewrite of laginimaineb TrustZone zero-write exploit as a kernel module instead of using a user space program and using a custom kernel, which is the case for his FuzzZone application. See:
	http://bits-please.blogspot.com/2015/08/full-trustzone-exploit-for-msm8974.html
	https://github.com/laginimaineb/MSM8974_exploit

The original exploit was built around the Nexus 5 hammerhead. My test device was both a Nexus 5 and a LG G2

Build: 
	1) Update environment paths in ./Makefile
	2) Update environment paths in ./shellcode/Makefile
	3) Run make

Install: 
	1) Transfer modeule and shellcode to device
	2) Run insmod tz_exploit.ko [SHELLCODE_PATH] [SHELLCODE_IS_THUMB]
		ex for thumb code:  insmod tz_exploit.ko /sdcard/shellcode.bin 1  
		ex for arm code: 	insmod tz_exploit.ko /sdcard/shellcode.bin 0 

The provided shell code template has two helper functions you can use to call other truztzone functions by address, either from arm -> to thumb or from thumb -> to arm. Thumb requires the address +1

