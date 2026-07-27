                     ;Calcolala funzione di fibonacci per questo valore e salvala in memoria
fibonacciNumber      equ     11
risultato            fill    4

                     mov     R0,#fibonacciNumber
                     mov     R12,#risultato
                     cmp     R0, #0
                     beq     impostoAZeroEFinisco
                     cmp     R0, #1
                     beq     impostoAUnoEFinisco
                     mov     R3,#0 ;fibo
                     mov     R4,#1 ;lastFibo
                     mov     R5,#0 ;lastLastFibo
ciclo                sub     R0,R0,#1
                     cmp     R0,#1
                     ;       fibo = lastFibo + lastLastFibo;
                     add     R3,R4,R5
                     ;       lastLastFibo = lastFibo;
                     mov     R5,R4
                     ;       lastFibo = fibo;
                     mov     R4,R3;
                     bgt     ciclo
                     b       salvo

                     end
impostoAZeroEFinisco mov     R3,#0
                     b       salvo

impostoAUnoEFinisco  mov     R3,#1
                     b       salvo

salvo                str     R3,[R12]
                     end