        .export     _get_file_info
    


MLI             = $bf00
GET_FILE_INFO   = $c4



        .bss

_file_info_addr:    .word   $00



        .code

; This function is defined as "fastcall" which puts the right-most
; parameter into A/X and the return value in A/X.

_get_file_info:
        sta     _file_info_addr
        stx     _file_info_addr+1

        jsr     MLI
        .byte   GET_FILE_INFO
        .word   _file_info_addr

        ; The system call leaves the error status in the Accumulator.
        ; The "fastcall" calling convention returns the A register,
        ; which is what we want.
        rts

