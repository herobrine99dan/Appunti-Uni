              ;Data   la lista [1,2,3,4,5,6,7,8,9,10] contare tutti i numeri dispari e
              ;       maggiori di 5 e salvare il risultato in memoria.

lista         dcd     1,2,3,4,5,6,7,8,9,11
size          equ     10
somma         fill    4

              mov     R0,#lista
              mov     R1,#size
              mov     R3,#0 ;contatore numeri

              ldr     R2,[R0]

ciclo         sub     R1,R1,#1
              bl      primoLimite
              add     R0,R0,#4
              ldr     R2,[R0]
              cmp     R1,#0
              bgt     ciclo
              mov     R7,#somma
              str     R3,[R7]
              end

primoLimite   cmp     R2,#5
              bgt     secondoLimite
              mov     pc,lr

secondoLimite and     R4,R2,#1
              cmp     R4,#1 ;1=dispari, 0=pari
              beq     contaERitorna
              mov     pc,lr

contaERitorna add     R3,R3,#1
              mov     pc,lr