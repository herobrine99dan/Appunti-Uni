inversa [] = []
inversa (a:x) = inversa(x)++[a]
--- In Haskell non si usano array, ma sempre liste. Quindi una lista o è vuota, o è formata da un elemento concatenato ad un altro elemento
--- se io eseguo 'g':['a','b'] ottengo la stringa "gab", che è equivalente a fare "g"++"ab", non esiste il casting
--- 

inversaAlternative x = if(null x) then [] else (inversaAlternative(tail x)) ++ [(head x)]
