       ;Data   la lista [1,2,3,4,5,6,7,8,9,10] sommare tutti i numeri pari
       ;e      minori di 8 e salvare il risultato in memoria.

lista  dcd     1,2,3,4,5,6,7,8,9,10
size   equ     10
somma  fill    4

       mov     R0,#lista
       mov     R1,#size
       mov     R3,#0 ;somma totale

ciclo  sub     R1,R1,#1
       ldr     R2,[R0]
       add     R0,R0,#4;dopo aver caricato il valore, aumento l'indirizzo
       and     R4,R2,#1
       cmp     R4,#0
       bne     ciclo
       cmp     R2,#8
       bge     ciclo
       add     R3,R3,R2
       cmp     R1,#0
       bgt     ciclo
       mov     R5,#somma
       str     R3,[R5]