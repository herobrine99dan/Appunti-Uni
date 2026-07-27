import struct

# Specifiche della matrice dalle immagini
R = 6  # Numero di righe
C = 4  # Numero di colonne

# I valori della matrice elencati in ordine row-major (riga per riga)
valori_matrice = [
    -16,   2,  13, -12,
     -9, -24,  40,  -1,
    -39,  38,  18, -27,
     49, -34,  27,  -9,
    -34, -38,  16,  50,
      0,  36,  28, -48
]

# Nome del file binario di output
nome_file = "matrice.bin"

try:
    with open(nome_file, "wb") as f:
        # Scrive i primi due interi: R e C
        # 'i' indica un intero standard (solitamente a 4 byte / 32-bit)
        f.write(struct.pack("i", R))
        f.write(struct.pack("i", C))
        
        # Scrive gli R*C valori della matrice in ordine row-major
        for valore in valori_matrice:
            f.write(struct.pack("i", valore))
            
    print(f"File binario '{nome_file}' generato con successo!")
    print(f"Contenuto: R={R}, C={C}, ed {len(valori_matrice)} valori.")

except IOError as e:
    print(f"Errore durante la scrittura del file: {e}")
