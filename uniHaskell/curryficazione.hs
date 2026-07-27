---funzione pallino, composizione
pallino f g = \x -> (f (g x))
--- notare che se faccio :type + ottengo errore, se faccio :type (+) mi dà il tipo giusto
--- quindi posso considerare l'operatore somma come una funzione (notazione prefissa) o proprio come operatore (notazione infissa)
--- se lo considero con la notazione infissa considero sum: NxN->N
--- se lo considero con la notazione prefissa sto considerando sum: N -> N(->N)

