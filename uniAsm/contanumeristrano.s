              ;Data   la lista [1,2,3,4,5,6,7,8,9,10,11,12,13] contare tutti i numeri minori di 5, pari a 5 e maggiori di 5.

lista         dcd     1,2,3,4,5,6,7,8,9,10,11,12,13
size          equ     13

              mov     R0,#lista ;R0=Indirizzo lista
              mov     R1,#size ;R1=contatore ciclo

ciclo         ldr     R2,[R0] ;R2=contiene il dato
              bl      limite
              add     R0,R0,#4
              sub     R1,R1,#1
              cmp     R1,#0
              bgt     ciclo
              end

sommaERitorna add     R6,R6,R2
              mov     pc,lr

limite        cmp     R2,#5
              beq     sommaERitorna
              bgt     sommaERitorna
              blt     sommaERitorna
              mov     pc,lr

