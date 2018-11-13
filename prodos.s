        .export     _get_file_info


MLI             = $bf00
GET_FILE_INFO   = $c4
COUT            = $FDED      ;SUB TO OUTPUT A CHARACTER
PRBYTE          = $FDDA     ;SUB TO PRINT A BYTE
CROUT           = $FD8E     ;SUB TO OUTPUT CARRIAGE RETURN


.code

; This function is defined as "fastcall" which puts the right-most
; parameter into A/X and the return value in A/X.

.proc   _get_file_info

        sta     params
        stx     params+1

        ; Switch in ROM
        bit     $c082

        lda     params
        jsr     PRBYTE
        jsr     CROUT

        lda     params+1
        jsr     PRBYTE
        jsr     CROUT

        jsr     MLI
        .byte   GET_FILE_INFO
params: .word   0

        ; The system call leaves the error status in the Accumulator.
        ; The "fastcall" calling convention returns the A register,
        ; which is what we want.
        rts
.endproc


.bss

file_info_addr:    .res   2

