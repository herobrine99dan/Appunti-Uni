                 ;Data   la lista [30,10,23,1,17,8,19,10] sommare tutti i numeri compresi tra 10 e 20.
lista            dcd     30,10,23,1,17,8,19,10
size             equ     8

                 mov     R0,#lista
                 mov     R1,#size
                 mov     R4,#0

ciclo            sub     R1,R1,#1
                 ldr     R2,[R0]
                 bl      sommaConfrontata
                 add     R0,R0,#4
                 cmp     R1,#0
                 bgt     ciclo
                 end

sommaConfrontata cmp     R2,#10
                 bge     primolimite
                 mov     pc,lr

primolimite      cmp     R2,#20
                 blt     secondoLimite
                 mov     pc,lr

secondoLimite    add     R6,R6, R2
                 mov     pc,lr