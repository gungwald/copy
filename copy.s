********************************
*                              *
* COPY - COPIES FILES          *
*                              *
* AUTHOR:  BILL CHATFIELD      *
* LICENSE: GPL2                *
*                              *
********************************

               org  $2000
               dsk  copy
               typ  $ff             ;System type

********************************
*                              *
* CONSTANTS                    *
*                              *
********************************

IN          equ $0200
RDKEY          equ  $FD0C           ;Reads 1 character
GETLN       equ $fd6a
GETLN1         equ  $fd6f           ;Get line, no prompt
CROUT          equ  $FD8E           ;Output carriage return
COUT           equ  $FDED           ;Output a character
PRBYTE         equ  $FDDA           ;Print error message
BELL           equ  $FF3A           ;Subroutine to beep
PRODOS_MLI     equ  $bf00           ;Address for MLI subroutine entry point
SET_FILE_INFO  equ  $c3             ;Code for system call
GET_FILE_INFO  equ  $c4             ;Code for system call
ON_LINE        equ  $c5             ;Id for ON_LINE MLI system call

********************************
*                              *
* puts                         *
*                              *
********************************

puts        mac
            tya                     ;Preserve y
            pha
            ldy     #0              ;Prepare loop index
]nextchar   lda     ]1,y            ;Load a character
            cmp     #0              ;Check for end of string
            beq     finish
            jsr     COUT
            iny
            jmp     ]nextchar
finish      pla                     ;Restore y
            tay
            <<<

********************************
*                              *
* movb - Move byte             *
*                              *
********************************

movb        mac
            lda     ]2
            sta     ]1
            <<<

********************************
*                              *
* mova - Move addrs            *
*                              *
********************************

mova        mac
            lda     src
            sta     dest
            lda     src+1
            sta     dest+1
            <<<

********************************
*                              *
* Main                         *
*                              *
********************************

main

; Read in source file name and store it in srcFile

getSource   puts    srcPrompt
            jsr     GETLN1
            cpx     #64
            bpl     getSource

            stx     srcFileLength
            ldx     #0
srcChar     lda     IN,x
            sta     srcFileChars,x
            inx
            cpx     srcFileLength
            bmi     srcChar

; Set fiParamCount parameter

            lda     #$a
            sta     fiParamCount

; Set fiPathName parameter

            lda     #<srcFile
            sta     fiPathName
            lda     #>srcFile
            sta     fiPathName+1

            jsr     PRODOS_MLI          ;Call MLI subroutine
            db      GET_FILE_INFO       ;Identify the system call
            da      fileInfo            ;Address of system call args
            beq     cont1               ;Returns 0 on success
            jsr     handleError
cont1

; Read in destination file name and store it in dstFile

getDest     puts    dstPrompt
            jsr     GETLN1
            cpx     #64
            bpl     getDest  

            stx     dstFileLength
            ldx     #0
dstChar     lda     IN,x
            sta     dstFileChars,x
            inx
            cpx     dstFileLength
            bmi     dstChar

            rts

********************************
*                              *
* Data                         *
*                              *
********************************

srcPrompt       asc "File to copy: ",00
srcFile
srcFileLength   db  0               ;Length byte
srcFileChars    ds  64              ;Characters of srcFile

dstFile
dstFileLength   db  0               ;Length byte
dstFileChars    ds  64              ;Characters of dstFile

onlineVols      ds  256             ;Space for 16 disk vol records

onlineArgs
olParamCount    db  2               ;Parameter count
olUnitNumber    db  0               ;Unit number, 0=all
olBufferAddr    da  onlineVols      ;Address of output buffer

fileInfo
fiParamCount    db  0
fiPathName      da  0
fiAccess        db  0
fiFileType      db  0
fiAuxType       dw  0
fiStorageType   db  0
fiBlocksUsed    dw  0
fiModDate       dw  0
fiModTime       dw  0
fiCreateDate    dw  0
fiCreateTime    dw  0

