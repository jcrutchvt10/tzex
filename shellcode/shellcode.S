.code 32
.align 4
.global _start
    STMFD   SP!, {R4 - R11, LR}
    
    @ DO STUFF HERE ..

    LDMFD   SP!, {R4 - R11, PC}


@ arm_jump helper, place function address in R6
arm_jump:
    BX R6

.code 16
.thumb_func

@ thumb_jump helper, place function address in R6
thumb_jump:
    BX R6
