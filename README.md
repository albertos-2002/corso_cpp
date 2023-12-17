# Descrizione generale per gli eserci assegnati a lezione
---
## Readme index
---
- [x] [dump v1](dump_v1/readme.md)

- [x] [dump v2](dump_v2/readme.md)

- [x] [mean v1](mean_v1/readme.md)

- [x] [mean v2](mean_v2/readme.md)

- [x] [mean v3](mean_v3/readme.md)

- [x] [mean v4](mean_v4/readme.md)

- [x] [hist v1](hist_v1/readme.md)

- [x] [hist v2](hist_v2/readme.md)

- [ ] [hist v3](hist_v3/readme.md)

- [ ] [hist v4](hist_v4/readme.md)

- [ ] [hist v5](hist_v5/readme.md)

- [ ] [hist v6](hist_v6/readme.md)

## File di dati
---

Il file contenente le particelle è presente nalla directory principale, senza estensione

Il file è strutturato nel seguente modo, per ogni evento sono presenti in ordine:

- identificatore dell'evento `int`
- coordinate di decadimento x,y,z `float`
- numero di perticelle `int`

	per ogni particella (in riga e in questo ordine) è presente:

- campo elettrico della particella `int`
- momento x,y,z `float`

## Note generali
---

Per ogni esercizio è predente un file chiamato *compile* che contiene il comando di compilazione ed esecuzione

Negli esercizi che utilizzano ROOT (*hist_vX*) potrebbe essere necessario cambiare la stringa di compilazione 

$(root-config --cflag --libs)

come potrebbe essere necessario cambiare gli include da <> a ""

## Struttura generale del main
---
Il comando di esecuzione completo è presente nel file *compile*

Da riga di comando viene passato come argomento il nome del file che viene poi estratto e passato come argomento all funzione `read`

La classica sintassi per gli argomenti del main prevede che le *key word* passate da riga di comando vengano contenute in un `array di puntatori a char`, ognuno di questi *puntatori* puntano al primo elemento di un `array di char` in modo tale da poter contenere intere parole

