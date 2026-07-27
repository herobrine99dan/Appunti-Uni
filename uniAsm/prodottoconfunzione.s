           ;moltiplicare due numeri con una routine
           ;cose   utili
           ;       call → bl metodo
           ;return → mov pc, lr
           ;       backup registri: stmfd SP!, {r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12}
           ;       restore registri: ldmfd SP!, {r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12}

fattore1   equ     4
fattore2   equ     9
prodotto   fill    4

           stmfd   SP!, {r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12}
           mov     R1,#fattore1
           mov     R2,#fattore2
           mov     R4, #prodotto
           bl      moltiplica
           ldmfd   SP!, {r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,r12}
           ;
           end

moltiplica sub     R1,R1,#1
           add     R3,R3,R2
           cmp     R1,#0
           bgt     moltiplica
           str     R3,[R4]
           mov     pc, lr
