# Svolgimento degli esercizi assegnati a lezione

Il file contenente le particelle è presente nalla directory principale, senza estensione

Il file è strutturato nel seguente modo, per ogni evento presente sono presenti in ordine:

- identificatore dell'evento `int`
- coordinate di decadimento x,y,z `float`
- numero di perticelle `int`

	per ogni particella (in riga e in questo ordine) è presente:

- campo elettrico della particella `int`
- momento x,y,z `float`

Per ogni esercizio è predente un file chiamato *compile* che contiene il comando di compilazione ed esecuzione

Negli esercizi che utilizzano ROOT potrebbe essere necessario cambiare la stringa di compilazione 

$(root-config --cflag --libs)

come potrebbe essere necessario cambiare gli include da <> a ""
