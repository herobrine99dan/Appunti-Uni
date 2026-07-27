          ;       Sommare i numeri da 1 a 8 presi dalla memoria e ricaricare la somma in essa
Numerini  DCD     1,2,3,4,5,6,7,8
          mov     R1, #Numerini
          ldr     R2, [R1]
          ldr     R3, [R1,#4]
          ldr     R4, [R1,#8]
          ldr     R5, [R1,#12]
          ldr     R6, [R1,#16]
          ldr     R7, [R1,#20]
          ldr     R8, [R1,#24]
          ldr     R9, [R1,#28]
          add     R2,R2,R3
          add     R2,R2,R4
          add     R2,R2,R5
          add     R2,R2,R6
          add     R2,R2,R7
          add     R2,R2,R8
          add     R2,R2,R9
Risultato Fill    4
          mov     R3,#Risultato
          str     R2,[R3]