ARR                     dcd     1,2,3,4,5,6,0
LUNG                    equ     7
POSMIN                  fill    4
VALMAX                  fill    4
                        mov     r0,#LUNG
                        mov     r1,#ARR
                        mov     r7,#ARR
                        ldr     r8,[r7]
                        mov     r9,r8
ciclo                   sub     r0,r0,#1
                        ldr     r2,[r1]
                        bl      aggiornaindirizzominimo
                        bl      aggiornavaloremax
                        add     r1,r1,#4
                        cmp     r0,#0
                        bgt     ciclo
                        mov     r10,#POSMIN
                        str     r7,[r10]
                        mov     r10,#VALMAX
                        str     r9,[r10]
                        end
return                  mov     pc,lr
aggiornaindirizzominimo cmp     r2,r8
                        blt     aggiornaminimo
                        b       return
aggiornaminimo          mov     r8,r2
                        mov     r7,r1
                        b       return
aggiornavaloremax       cmp     r2,r9
                        bgt     aggiornamax
                        b       return
aggiornamax             mov     r9,r2
                        b       return