          ;Scrivi una subroutine sumAndInc che:

          ;riceve due parametri: a in R0 e b in R1;

          ;somma  i due numeri e li salva in una variabile locale nello stack;

          ;incrementa il risultato di 1 e lo restituisce in R0.

first     equ     1
second    equ     2

          mov     R0,#first
          mov     R1,#second
          bl      sumAndInc
          end

sumAndInc add     r0,r0,r1
          add     r0,r0,#1
          mov     pc, lr