              ;       Data una lista, sommare tutti i numeri compresi tra 10 e 20
lista         dcd     30,10,23,1,17,8,19,10
size          equ     10
primoLimite   equ     10
secondoLimite equ     20
totale        fill    4

              mov     R0,#lista
              mov     R1,#size
              ;Registro per somma totale ---> R6
ciclo         sub     R1,R1,#1
              ldr     R2,[R0]
              bl      comparaESomma
              add     R0,R0,#4
              cmp     R1, #2 ;Attenzione, bisognerebbe mettere #2 anzichè #0 sennò va a leggere fuori memoria
              bgt     ciclo
              ;salvataggio
              mov     R8,#totale
              str     R6,[R8]
              end


comparaESomma cmp     R2,#primoLimite
              bge     test2
              mov     pc,lr

test2         cmp     R2,#secondoLimite
              ble     somma
              mov     pc,lr

somma         add     R6,R6,R2
              mov     pc,lr