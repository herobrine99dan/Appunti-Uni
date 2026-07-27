                   ;Calcolare il fattoriale usando le funzioni
numero             equ     4

                   mov     R0,#numero
                   bl      fattoriale
                   mov     R1,#1
                   end

fattorialeCasoBase mov     R4,#0
                   mov     pc, lr

fattoriale         stmfd   SP!, {r14}
                   cmp     R0,#0
                   blt     fattorialeCasoBase
                   mov     R1,R3
                   mov     R2,R0
                   mov     R3,#0
                   bl      moltiplica
                   sub     R0,R0,#1
                   ldmfd   SP!, {r14}
                   mov     pc, lr


moltiplica         stmfd   SP!, {r14}
                   sub     R1,R1,#1 ;R1 primo fattore
                   add     R3,R3,R2 ;R2 secondo fattore
                   cmp     R1,#0;In R3 ho il risultato
                   bgt     moltiplica
                   ldmfd   SP!, {r14}
                   mov     pc, lr
