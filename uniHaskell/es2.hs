sommaPari 0 = 0
sommaPari n = if (even n) then (n+(sommaPari (n-1))) else (sommaPari (n-1))
