       ;Data   la lista [1,2,3,4,5,6,7,8,9,10] moltiplicazione ogni elemento x2 e sovrascrivere il valore in memoria


lista  dcd     1,2,3,4,5,6,7,8,9,10
size   equ     10

       mov     R0,#lista
       mov     R1,#size
       ldr     R2,[R0] ; primo errore

ciclo  sub     R1,R1,#1
       ;lsr    r2,r2,#1
       lsl     r2,r2,#1
       str     r2,[r0]
       add     R0,R0,#4
       ldr     R2,[R0]
       cmp     R1,#0
       bgt     ciclo
