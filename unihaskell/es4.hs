--Implementazione brutta
sommaN 0 = 0
sommaN n = n + sommaN(n-1)
mavah n = (sommaN n)^2
