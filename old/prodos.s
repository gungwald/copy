        .export _prodosGetFileInfo
        .export _prodosSetFileInfo
        .export _onlineSysCall
        .export _onlineVols


PRODOS_MLI      =   $bf00           ;Address for MLI subroutine entry point
SET_FILE_INFO   =   $c3             ;Code for system call
GET_FILE_INFO   =   $c4             ;Code for system call
ON_LINE         =   $c5             ;ID FOR ON_LINE MLI SYSTEM CALL

.proc       _prodosGetFileInfo
            sta     fileInfo        ;Store low-byte of C address param
            stx     fileInfo+1      ;Store high-byte of C address param
            jsr     PRODOS_MLI      ;Call MLI subroutine
            .byte   GET_FILE_INFO   ;Identify the system call
fileInfo:   .addr   $0000           ;Address of system call args
            ldx     #0              ;Zero high byte of int return value
            rts                     ;Accum has error code, low byte of int
.endproc

.proc       _prodosSetFileInfo
            sta     fileInfo        ;Store low-byte of C address param
            stx     fileInfo+1      ;Store high-byte of C address param
            jsr     PRODOS_MLI      ;Call MLI subroutine
            .byte   SET_FILE_INFO   ;Identify the system call
fileInfo:   .addr   $0000           ;Address of system call args
            ldx     #0              ;Zero high byte of int return value
            rts                     ;Accumulator has error code
.endproc

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

