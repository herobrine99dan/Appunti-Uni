       ;Esercizio:
       ;Scrivi un programma che:
       ;Carichinei registri R0, R1, R2 i valori 10, 20, 30.
       ;Li     salvi sullo stack.
       ;Li     ripristini in altri registri (R3, R4, R5).
       ;Alla   fine, i registri R3–R5 devono contenere 10, 20, 30.

       mov     R0,#10
       mov     r1,#20
       mov     r2,#30
       stmfd   SP!,{r0,r1,r2}
       ldmfd   SP!, {r3,r4,r5}
