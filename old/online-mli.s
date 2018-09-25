        .export _onlineSysCall
        .export _onlineVols

ON_LINE     =   $c5     ;ID FOR ON_LINE MLI SYSTEM CALL
PRODOS_MLI  =   $bf00   ;ADDRESS OF MLI ENTRY POINT

.proc       _onlineSysCall

            jsr         PRODOS_MLI  ;CALL MACHINE LANGUAGE INTERFACE
            .byte       ON_LINE     ;SPECIFY THE ON_LINE SYSTEM CALL
            .addr       onlineArgs  ;SPECIFY ADDRESS OF ARGUMENTS

;           sta         retCode     ;Store the return code
;            lda         #<retCode   ;PUT LOW BYTE INTO ACCUMULATOR
;            ldx         #>retCode   ;PUT HIGH BYTE INTO X
            rts
.endproc

; BSS is Block Started by Symbol for zero-initialized read/write data
; Constructed by loader and zeroed out based on required size
            .bss

retCode:    .byte       0
_onlineVols:.res        256         ;SPACE FOR 16 DISK VOL RECORDS

; DATA contains initialized read/write data - encoded into binary
            .data

onlineArgs: .byte       2           ;PARAMETER COUNT
            .byte       0           ;UNIT NUMBER, 0=ALL
            .addr       _onlineVols ;ADDRESS OF OUTPUT BUFFER

