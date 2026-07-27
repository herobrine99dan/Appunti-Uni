NumeroBase              DCD     9
NumeroPrimaOperazione   DCD     1
NumeroSecondaOperazione DCD     -1
                        mov     R1,#NumeroBase
                        mov     R2,#NumeroPrimaOperazione
                        mov     R3,#NumeroSecondaOperazione
                        ldr     R4, [R1]
                        ldr     R5, [R2]
                        ldr     R6, [R3]
PrimaOperazione         fill    4
                        add     R1, R4,R5
                        mov     R3,#PrimaOperazione
                        str     R1, [R3]
SecondaOperazione       fill    4
                        ;add    R2, R4,R6 oppure, con il sub:
                        sub     R1,R4,R5 ;devo mettere R5, che corrisponde a R2, quindi 1
                        mov     R3,#SecondaOperazione
                        str     R1, [R3]
