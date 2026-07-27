       ;obiettivo=sommare tutti i numeri in "numeri" e aggiungere a ciascuno 10

numeri dcd     1,2,3,4,5,6,7
size   equ     7
somma  fill    4

       mov     R4,#0;R4=il totale (dopo lo metterò in somma)
       mov     R1,#numeri ;R1=indirizzo attuale
       mov     R2,#size; R2=dimensione


loop   ldr     R3,[R1];R3=valore atutale
       add     R4,R4,R3
       add     R4,R4,#10
       add     R1,R1,#4
       sub     R2,R2,#1
       cmp     R2, #0
       bne     loop
       mov     R1,#somma
       str     R4,[R1]
