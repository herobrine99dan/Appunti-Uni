
primoFattore   equ     3
secondoFattore equ     4
Risultato      fill    4

               mov     R1,#primoFattore
               mov     R2,#secondoFattore
               mov     R3,#0

               cmp     R2,#0
               beq     fattoreZero
               b       ciclo

ciclo          subs    R2,R2,#1;posso mettere prima sub e poi "cmp R2,#0", sennò metto direttamente subs
               add     R3,R3,R1
               bgt     ciclo
               b       salva

salva          mov     R4,#Risultato
               str     R3,[R4]

fattoreZero    mov     R3,#0

