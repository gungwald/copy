        .export         _online
        .export         _olerr
    
        .include        "mli.inc"

        .bss

_olerr: .byte   $00

        .code

_open:
        lda     #ON_LINE_CALL
        ldx     #ON_LINE_COUNT
        jsr     callmli
        bcc     done

        sta     _olerr

done:
        rts
