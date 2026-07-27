
operatori              dcd     16,8
quoziente              fill    4
resto                  fill    4

                       mov     R2,#operatori;Metto l'indirizzo in R2
                       ldr     R1,[R2];Metto in R1 il dividendo, in R2 il divisore
                       ldr     R2,[R2,#4]

                       mov     R3,#0 ;Metto in R3 il quoziente
ciclo                  subs    R1,R1,R2
                       add     R3,R3,#1
                       bgt     ciclo

                       ;Ora    se non si può perfettamente dividere per il divisore, il resto sarà negativo
                       cmp     R1,#0 ;Struttura tipo if(R1<0) sistemaQuozienteResto else fine
                       blt     sistemaQuozienteEResto
                       b       fine

sistemaQuozienteEResto sub     R3,R3,#1
                       add     R1,R1,R2

fine                   mov     R2,#quoziente
                       str     R3,[R2]

                       mov     R2,#resto
                       str     R1,[R2]
