             ;trovareil valore 10 in memoria e salvare in memoria l’indirizzo corrispondente.
             ;Se     non viene trovato salvare -1
lista        dcd     1,7,24,12,8,1,10,21,3,1,5,1
size         equ     12
             mov     R1,#lista
             mov     R3,#-1;R3=Risultato
             mov     R4,#0;R4=Indice

ciclo        ldr     R2,[R1]
             add     R1,R1,#4;R1 contiene l'indirizzo
             add     R4,R4,#1
             cmp     R4,#size
             bgt     fineNegativo
             cmp     R2,#10
             beq     finePositivo
             b       ciclo

fineNegativo end

finePositivo sub     R1,R1,#4
             mov     R3,R1