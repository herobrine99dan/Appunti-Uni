lista          dcd     1,20,20,20, 2,18,30,27, 3,22,26,28 ;ID ALLIEVO, VOTO1,VOTO2,VOTO3
numeroStudenti equ     3
numeroVoti     equ     3
listaFinale    fill    24 ;4 * 3 * 3

               mov     R1,#lista
               ldr     R2,[R1]
               mov     R11,#numeroVoti
               mov     R10,#numeroStudenti
               mov     R3,#listaFinale
               mov     R8,#4

cicloStudenti  ldr     R2,[R1,R7];R2=ID Studente
               add     R7,R7,#16
               str     R2,[R3]
               add     R3,R3,#4
               add     R3,R3,#4
               cmp     R10,#0
               sub     R10,R10,#1
               mov     R12,#0
               mov     R0,R8
               add     R8,R8,#4
               bgt     sommaVoti
               b       fine

sommaVoti      ldr     R2,[R1,R0]
               add     R0,R0,#16
               sub     R11,R11,#1
               add     R12,R12,R2
               cmp     R11,#0
               bgt     sommaVoti
               sub     R3,R3,#4
               str     R12,[R3]
               add     R3,R3,#4
               mov     R11,#numeroVoti
               cmp     R10,#0
               bgt     cicloStudenti

fine           end
