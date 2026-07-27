
numeroFattoriale     equ     12
Risultato            fill    4
                     ;R1→primoFattore R2→secondoFattore R12→RisultatoMoltiplicazione


                     mov     R3,#numeroFattoriale
                     mov     R12,#1;elemento neutro del prodotto

cicloFattoriale      mov     R1,R12;metti come primo prodotto il risultato delle precedenti operazioni (oppure 1 se è la prima volta)
                     mov     R2,R3;metti il secondo operatore del prodotto
                     sub     R3,R3,#1;contatore ciclo
                     mov     R12,#0;la moltiplicazione funziona sommando a poco a poco, però il totale deve essere zero all'inizio 
                     cmp     R3,#0;se siamo arrivati a zero, vai a salvare
                     beq     salva
                     b       cicloMoltiplicazione;ciclo

cicloMoltiplicazione subs    R2,R2,#1;posso mettere prima sub e poi "cmp R2,#0", sennò metto direttamente subs
                     add     R12,R12,R1;R1→primoFattore R2→secondoFattore R3→Risultato
                     bgt     cicloMoltiplicazione
                     cmp     R2,#0;dobbiamo tornare indietro alla funzione fattoriale
                     beq     cicloFattoriale

salva                mov     R6,#Risultato
                     str     R1,[R6]