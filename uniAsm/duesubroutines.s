           ;Esercizio:
           ;Scrivi due subroutine:

           ;square:calcola il quadrato di un numero (R0 = R0 × R0)

           ;sumSquares: chiama due volte square per calcolare a² + b²

           ;Nel    main, imposta R0=3 e R1=4, chiama sumSquares, e ottieni in R0 il risultato 25.
first      equ     2
second     equ     4

           bl      sumSquares
           end

sumSquares stmfd   SP!, {R14,r1,r2,r3,r4,r0}
           mov     R0,#first
           bl      square
           mov     R4, R3
           mov     R3,#0
           mov     R0,#second
           bl      square
           add     r3,r3,r4
           mov     r12,r3
           ldmfd   SP!, {R14,r1,r2,r3,r4,r0}
           mov     pc,lr

square     stmfd   SP!, {R14}
           mov     R1,R0
           mov     R2,R0
           bl      moltiplica
           ldmfd   SP!, {R14}
           mov     pc,lr

moltiplica sub     R1,R1,#1
           add     R3,R3,R2
           cmp     R1,#0
           bgt     moltiplica
           mov     pc, lr