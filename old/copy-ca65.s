********************************
*                              *
* COPY - COPIES FILES          *
*                              *
* AUTHOR:  BILL CHATFIELD      *
* LICENSE: GPL2                *
*                              *
********************************

********************************
*                              *
* CONSTANTS                    *
*                              *
********************************

RDKEY          EQU   $FD0C      ;READS 1 CHAR
CROUT          EQU   $FD8E      ;SUB TO OUTPUT CARRIAGE RETURN
COUT           EQU   $FDED      ;SUB TO OUTPUT A CHARACTER
PRBYTE         EQU   $FDDA      ;SUB TO PRINT ERROR MESSAGE
BELL           EQU   $FF3A      ;SUBROUTINE TO BEEP
PRODOS_MLI      =   $bf00           ;Address for MLI subroutine entry point
SET_FILE_INFO   =   $c3             ;Code for system call
GET_FILE_INFO   =   $c4             ;Code for system call
ON_LINE         =   $c5             ;ID FOR ON_LINE MLI SYSTEM CALL


********************************
*                              *
* puts                         *
*                              *
********************************

.macro      puts    s
            .local  nextchar
            .local  finish
            tya                 ;Preserve y
            pha
            ldy     #0          ;Prepare loop index
nextchar:   lda     s,y         ;Load a character
            cmp     #0          ;Check for end of string
            beq     finish
            jsr     cout
            iny
            jmp     nextchar
finish:     pla                 ;Restore y
            tay
.endmacro

.macro      movb    dest,src
            lda     src
            sta     dest
.endmacro

.macro      mova    dest,src
            lda     src
            sta     dest
            lda     src+1
            sta     dest+1
.endmacro

.proc       handleError
            rts
.endproc

********************************
*                              *
* Main                         *
*                              *
********************************

main:
            movb    fileInfo+FileInfo::paramCount,$a
            mova    fileInfo+FileInfo::pathName,srcFile

            jsr     PRODOS_MLI      ;Call MLI subroutine
            .byte   GET_FILE_INFO   ;Identify the system call
            .addr   fileInfo        ;Address of system call args
            beq     cont1           ;Returns 0 on success
            jsr     handleError
            rts


; BSS is Block Started by Symbol for zero-initialized read/write data
; Constructed by loader and zeroed out based on required size
            .bss

onlineVols: .res        256         ;SPACE FOR 16 DISK VOL RECORDS
srcFile     .byte                   ;Length byte
            .res        64          ;Characters of srcFile


; DATA contains initialized read/write data - encoded into binary
            .data

onlineArgs: .byte       2           ;PARAMETER COUNT
            .byte       0           ;UNIT NUMBER, 0=ALL
            .addr       _onlineVols ;ADDRESS OF OUTPUT BUFFER

.struct     FileInfo
            paramCount  .byte
            pathName    .addr
            access      .byte
            fileType    .byte
            auxType     .word
            storageType .byte
            blocksUsed  .word
            modDate     .word
            modTime     .word
            createDate  .word
            createTime  .word
.endstruct

fileInfo:   .tag        FileInfo

