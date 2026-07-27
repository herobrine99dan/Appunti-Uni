               ;       Sommare i numeri 2, 3, 4, 1 e salvare in memoria il risultato
NumeriniCarini DCD     9, 3, 4,-5
               ;       Istruzioni che so usare: ldr, str, Add, sub, dcd, fill, mov
               ;       Man mano mi devo mettere le cose nei registri della cpu per lavorare
               mov     R1, #NumeriniCarini ;l'indirizzo, ora so dove si trova la mia lista nella Ram
               ldr     R2, [R1];per fare la somma tra i primi due numeri, prima li devo prendere
               ldr     R3, [R1,#4];modo con indice e spiazzamento, così evito di sommare gli indirizzi e risparmio tempo di esecuzione
               ldr     R4, [R1,#8]
               ldr     R5, [R1,#12]
               add     R2,R2,R3
               add     R2,R2,R4
               add     R2,R2,R5
SommaSimpatica Fill    4
               mov     R1, #SommaSimpatica
               str     R2, [R1]