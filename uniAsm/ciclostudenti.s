lista  dcd     1,20,20,20, 2,18,30,27, 3,22,26,28 ; ID ALLIEVO, VOTO1,VOTO2,VOTO3
size   equ     3
somme  fill    12

       ;R9=contatore, parte da 3
       ;R10=Somma temporanea dei vari numeri
       ;R1=lettura dato in memoria
       ;R0=indirizzo del dato da leggere
       ;R8=indirizzo del risultato
       mov     R0,#lista
       mov     R9,#size
       mov     R8,#somme

ciclo  mov     R10,#0;resetto la somma
       add     R0,R0,#4;salto l'id allievo
       ldr     R1,[R0];carico e sommo i tre voti
       add     R10,R10,R1
       ldr     R1,[R0,#4]
       add     R10,R10,R1
       ldr     R1,[R0,#8]
       add     R10,R10,R1
       str     R10,[R8]
       add     R8,R8,#4
       add     R0,R0,#12;salto i tre voti
       sub     R9,R9,#1
       cmp     R9,#0
       bgt     ciclo

