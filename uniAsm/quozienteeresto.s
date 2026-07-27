          ;Eseguire la divisione 231 / 13 e salvare il risultato e il resto

dividendo equ     231
divisore  equ     13

          mov     R0,#dividendo
          mov     R1,#divisore

ciclo     sub     R0,R0,R1
          add     R2,R2,#1
          cmp     R0,#divisore
          bgt     ciclo

quoziente fill    4
resto     fill    4
          mov     R3,#quoziente
          str     R2,[R3]

          mov     R3,#resto
          str     R0,[R3]