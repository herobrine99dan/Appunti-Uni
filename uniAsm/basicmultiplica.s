         ;moltiplica

fattore1 equ     9
fattore2 equ     3

         mov     R0,#fattore1
         mov     R1,#fattore2

ciclo    sub     R1,R1,#1
         add     R2,R2,R0
         cmp     R1,#0
         bgt     ciclo