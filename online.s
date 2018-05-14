        .export _onLineSysCall
        .export _onLineVols

ON_LINE     =   $c5     ;ID FOR ON_LINE MLI SYSTEM CALL
PRODOS_MLI  =   $bf00   ;ADDRESS OF MLI ENTRY POINT

.proc       _onLineSysCall

            jsr         PRODOS_MLI  ;CALL MACHINE LANGUAGE INTERFACE
            .byte       ON_LINE     ;SPECIFY THE ON_LINE SYSTEM CALL
            .addr       onlineArgs  ;SPECIFY ADDRESS OF ARGUMENTS

            sta         retCode     ;Store the return code
            lda         #<retCode   ;PUT LOW BYTE INTO ACCUMULATOR
            ldx         #>retCode   ;PUT HIGH BYTE INTO X
            rts
.endproc

.bss
retCode:    .byte       0
_onLineVols:.res        256         ;SPACE FOR 16 DISK VOL RECORDS

onlineArgs: .byte       2           ;PARAMETER COUNT
            .byte       0           ;UNIT NUMBER, 0=ALL
            .addr       _onLineVols ;ADDRESS OF OUTPUT BUFFER

