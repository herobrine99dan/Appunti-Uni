       ;Esercizio:
       ;Scrivi un programma che:
       ;Chiama una subroutine mysub con BL mysub.
       ;Dentro la subroutine, carica in R0 il valore 42.
       ;Torna  al main e reimposta a 0.

       bl      mysub
       mov     R0,#0
       end

mysub  mov     R0,#42
       mov     PC,LR