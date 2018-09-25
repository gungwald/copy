
ENOERR         equ  $00
EBADCALLNUM    equ  $01
EBADPARMCNT    equ  $04
EINTRTBLFULL   equ  $25
EIO            equ  $27
ENODEV         equ  $28
EROFS          equ  $b2
EDISKSWITCHED  equ  $2e
EINVALIDPATH   equ  $40
EMAXFILES      equ  $42
EINVALIDREF    equ  $43
EDIRNOTFOUND   equ  $44
EVOLNOTFOUND   equ  $45
ENOENT         equ  $46
EDUPFILENAME   equ  $47
EVOLFULL       equ  $48
EVOLDIRFULL    equ  $49
EFILEFORMAT    equ  $4a
ESTRGTYPE      equ  $4b
EEOF           equ  $4c
EOUTOFRANGE    equ  $4d
EFILELOCKED    equ  $4e
EFILEISOPEN    equ  $50
EDAMAGEDDIR    equ  $51
ENOTPRODOS     equ  $52
EBADPARAM      equ  $53
EVCBTBLFULL    equ  $55
EBADADDR       equ  $56
EDUPVOL        equ  $57
EDAMAGEDFILE   equ  $5a

handleError
    sta errorCode
    ldx #0
    ldy #0
nextCode    
    lda errorCodes,x
    cmp errorCode
    beq foundCode
    inx
    iny
    iny
    cpy errorCodeCount
    bmi nextCode
unknownCode
    puts errorLabel
    lda errorCode
    jsr PRBYTE
    jsr CROUT
    rts
foundCode   
    lda errorMessages,y
    sta errorMessage
    iny
    lda errorMessage,y
    sta errorMessage+1
    puts (errorMessage)
    rts 

errorCode       db  0
errorMessage    da  0
errorLabel      asc "Error ",00

EMNOERR          ASC "No error",00                           ;$00
EMBADCALLNUM     ASC "Bad system call number",00             ;$01
EMBADPARMCNT     ASC "Bad system call parameter count",00    ;$04
EMINTRTBLFULL    ASC "Interrupt table full",00               ;$25
EMIO             ASC "I/O error",00                          ;$27
EMNODEV          ASC "No device connected",00                ;$28
EMROFS           ASC "Disk write protected",00               ;$b2
EMDISKSWITCHED   ASC "Disk switched",00   ;$2e
EMINVALIDPATH    ASC "Invalid pathname",00    ;$40
EMMAXFILES       ASC "Maximum number of files open",00    ;$42
EMINVALIDREF     ASC "Invalid reference number",00           ;$43
EMDIRNOTFOUND    ASC "Directory not found",00 ;$44
EMVOLNOTFOUND    ASC "Volume not found",00    ;$45
EMNOENT          ASC "File not found",00  ;$46
EMDUPFILENAME    ASC "Duplicate filename",00  ;$47
EMVOLFULL        ASC "Volume full",00 ;$48
EMVOLDIRFULL     ASC "Volume directory full",00   ;$49
EMFILEFORMAT     ASC "Incompatible file format",00   ;$4a
EMSTRGTYPE       ASC "Unsupported storage_type",00    ;$4b
EMEOF            ASC "End of file encountered",00 ;$4c
EMOUTOFRANGE     ASC "Position out of range",00   ;$4d
EMFILELOCKED     ASC "File access error or file locked",00 ;$4e
EMFILEISOPEN     ASC "File is open",00    ;$50
EMDAMAGEDDIR     ASC "Directory structure damaged",00 ;$51
EMNOTPRODOS      ASC "Not a ProDOS volume",00 ;$52
EMBADPARAM       ASC "Invalid system call parameter",00   ;$53
EMVCBTBLFULL     ASC "Volume Control Block table full",00     ;$55
EMBADADDR        ASC "Bad buffer address",00  ;$56
EMDUPVOL         ASC "Duplicate volume",00    ;$57
EMDAMAGEDFILE    ASC "File structure damaged",00  ;$5a

errorCodes
    DB  ENOERR
    DB  EBADCALLNUM
    db  EBADPARMCNT
    db  EINTRTBLFULL
    db  EIO        
    db  ENODEV    
    db  EROFS    
    db  EDISKSWITCHED
    db  EINVALIDPATH
    db  EMAXFILES  
    db  EINVALIDREF
    db  EDIRNOTFOUND
    db  EVOLNOTFOUND
    db  ENOENT     
    db  EDUPFILENAME
    db  EVOLFULL   
    db  EVOLDIRFULL
    db  EFILEFORMAT
    db  ESTRGTYPE 
    db  EEOF     
    db  EOUTOFRANGE
    db  EFILELOCKED
    db  EFILEISOPEN
    db  EDAMAGEDDIR
    db  ENOTPRODOS
    db  EBADPARAM
    db  EVCBTBLFULL 
    db  EBADADDR   
    db  EDUPVOL   
    db  EDAMAGEDFILE 
errorCodeCount
    db  errorCodeCount - errorCodes

errorMessages
    DA  EMNOERR
    DA  EMBADCALLNUM
    da  EMBADPARMCNT
    da  EMINTRTBLFULL
    da  EMIO        
    da  EMNODEV    
    da  EMROFS    
    da  EMDISKSWITCHED
    da  EMINVALIDPATH
    da  EMMAXFILES  
    da  EMINVALIDREF
    da  EMDIRNOTFOUND
    da  EMVOLNOTFOUND
    da  EMNOENT     
    da  EMDUPFILENAME
    da  EMVOLFULL   
    da  EMVOLDIRFULL
    da  EMFILEFORMAT
    da  EMSTRGTYPE 
    da  EMEOF     
    da  EMOUTOFRANGE
    da  EMFILELOCKED
    da  EMFILEISOPEN
    da  EMDAMAGEDDIR
    da  EMNOTPRODOS
    da  EMBADPARAM
    da  EMVCBTBLFULL 
    da  EMBADADDR   
    da  EMDUPVOL   
    da  EMDAMAGEDFILE 
