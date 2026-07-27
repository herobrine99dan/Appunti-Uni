               ;Data   la lista [-10,4,23,50,0,-40,10,7] trovare il minimo e salvare il risultato in memoria.
lista          dcd     -10,4,23,50,0,40,10,7
size           equ     8

               mov     R1,#lista
               mov     R2,#size
               mov     R6,#1000 ;Valore grande

ciclo          sub     R2,R2,#1
               ldr     R3,[R1]
               bl      aggiornaMinimo
               add     R1,R1,#4
               cmp     R2,#0
               bgt     ciclo
               end

aggiornaMinimo cmp     R3,R6
               blt     aggiorna
               mov     pc,lr

aggiorna       mov     R6,R3
               mov     pc,lr