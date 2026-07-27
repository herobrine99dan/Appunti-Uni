lista       dcd     1,24,12,8,10,1,4,21,3,1,5,1
size        equ     12

            ;in     R8 metto la somma totale
            mov     R8,#0
            mov     R12,#size
            mov     R1,#lista
            mov     R3,#0
            ldr     R2,[R1]; in R2 c'è il valore attuale
ciclo       add     R3,R3,#1
            ldr     R2,[R1]
            add     R1,R1,#4
            cmp     R2,#10
            bge     sommaNumero

            cmp     R3,R12
            blt     ciclo
            b       fine
fine        end

sommaNumero add     R10,R10,R2
            b       ciclo