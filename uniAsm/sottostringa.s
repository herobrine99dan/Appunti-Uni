TSTRING       DCB     0x43, 0x49, 0x41, 0x4F, 0x20, 0x43, 0x41, 0x52, 0x4C, 0x41, 0x21, 0x21
SUBSTR        DCB     0x41, 0x49, 0x41, 0x4F
              mov     R0,#12 ;n
              mov     R1,#4 ;m
returnVal     fill    4

              mov     R2,#0 ;i
              sub     R3,R0,R1

ciclo         
              mov     R4,#0 ;j
              ;bl     ciclo interno
              cmp     R4,R1
              beq     salvaEFinisci
              cmp     R2,R3
              add     R2,R2,#1
              blt     ciclo
              mov     R2,#-1
              b       salvaEFinisci
              end

salvaEFinisci mov     R12,#returnVal
              str     R2,[R12]
              end

cicloInterno cmp R4,R1
blt secondaCondizione
mov pc,lr

secondaCondizione ldr R5,
cmp ..,..
beq aggiungiUnoETorna
mov pc,lr

aggiungiUnoETorna add R4,R4,#1
mov pc,lr