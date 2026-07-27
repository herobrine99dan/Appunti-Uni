                   ;Obiettivo generale
                   ;Scrivere un programma assembly che, dato un array di numeri interi con segno a 32 bit:
                   ;calcolila somma dei numeri positivi
                   ;calcolila somma dei numeri negativi
                   ;conti  quanti numeri sono pari
                   ;per    ogni numero:
                   ;se     è positivo, lo moltiplichi per 2
                   ;se     è negativo, lo divida per 2 (shift aritmetico)
                   ;salvi  i risultati in memoria
                   ;usi    almeno una subroutine con parametri passati tramite stack

array              DCD     10, -3, 4, -8, 7, -1
size               equ     6

SUM_POS            FILL    4 ;R6
SUM_NEG            FILL    4 ;R7
COUNT_EVEN         FILL    4 ;R8

                   mov     R0,#array
                   mov     R1,#size
                   ldr     R2,[R0] ;R2=Valore attuale

ciclo              sub     R1,R1,#1
                   ;Fai    cose belle
                   stmfd   sp!, {R0, R2}
                   bl      aggiornaArray
                   ldmfd   sp!, {R0, R2}
                   bl      sommaSePositivo
                   bl      sommaSeNegativo
                   bl      numeroPariTest
                   add     R0,R0,#4 ;prossimo numero
                   ldr     R2,[R0]
                   cmp     R1,#0
                   bgt     ciclo
                   mov     R0,#SUM_POS
                   str     R6,[R0]
                   mov     R0,#SUM_NEG
                   str     R7,[R0]
                   mov     R0,#COUNT_EVEN
                   str     R8,[R0]
                   end

numeroPariTest     and     R9, R2, #1
                   cmp     R9,#0
                   beq     numeroPariConta
                   mov     pc,lr

numeroPariConta    add     R8,R8,#1
                   mov     pc,lr

aggiornaArray      cmp     R2, #0
                   bgt     raddoppiaEAggiorna
                   asr     R2,R2,#1 ;Uso asr al posto di lsr per gestire anche i negativi
                   str     R2,[R0] ;dimezza e aggiorna
                   mov     pc,lr

raddoppiaEAggiorna lsl     R2,R2,#1
                   str     R2,[R0]
                   mov     pc,lr

sommaSePositivo    cmp     R2,#0
                   bgt     somma
                   mov     pc,lr

somma              add     R6,R6,R2 ;Il numero in R2 è positivo
                   mov     pc,lr

sommaSeNegativo    cmp     R2,#0
                   blt     somma1
                   mov     pc,lr

somma1             add     R7,R7,R2
                   ;il     numero in R2 è negativo
                   mov     pc,lr