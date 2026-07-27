              ;Data   la lista [10,20,12,12,5,1,5,1] contare tutti i numeri diversi da 1 e 10.

lista         dcd     10,20,12,12,5,1,5,1
size          equ     8

              mov     R0, #lista
              ldr     R1, [R0]
              mov     R2, #size

ciclo         sub     R2,R2,#1
              add     R0,R0,#4
              bl      firstCompare
              ldr     R1,[R0]
              cmp     R2,#0
              bgt     ciclo
              end

firstCompare  cmp     R1,#1
              bne     secondCompare
              mov     PC,lr

secondCompare cmp     R1,#10
              bne     sommaERitorna
              mov     PC,lr

sommaERitorna add     R5,R5,#1
              mov     PC,lr