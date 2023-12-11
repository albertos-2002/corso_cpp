# ParticleDump versione 1

## Main function
---

Da riga di comando viene passato come argomento il nome del file che viene poi estratto e passato come argomento all funzione `read`

La classica sintassi per gli argomenti del main prevede che le *key word* passate da riga di comando vengano contenute in un `array di puntatori a char`, ognuno di questi *puntatori* puntano al primo elemento di un `array di char` in modo tale da poter contenere intere parole

La sequenza del main è la seguente:

- Creazione delle variabili necessarie per contenere i dati di un evento
- Creazione di un ogetto `<fstream>`
- Ciclo `while` con operatore `>>` e chiamata interna alle funzioni `read` e `dump`

	L'operatore `>>` automaticamente tiene traccia del punto del file in cui la lettura si trova e del controllo del raggiungimento del carattere speciale `eof`

Nel ciclo `while`, che rimane `true` fino al raggiungimento del carattere speciale `eof`, viene letto il primo valore di un evento (*id della misura*), successivamente viene passato il controllo alla funzione `read` che si occupa di leggere e assegnare i successivi valori (la *reference* al file permette di mantenere correttamente il punto di lettura del file durante tutto il cilo) e ritornare il valore per *numero di particelle* che viene assegnato direttamente nel main, successivamente la funzione `dump` fa il print su scermo degli eventi

## Read function `int`
---

La funzione `read` si occupa di leggere gli eventi da un [file di testo](../particles_events)

La funzione accetta per *pass-by-reference* gli argomenti:

- file `ifstream` 
- punti di impatto x,y,z

inceve come *pass-by-value* i seguenti `array`:

- campo elettrico
- momento x,y,z

La funzione si occupa di restituire il valore del numero di particelle che nel `main` viene assegnato alla variabile che esegue la chiamata

## Dump function `void`

La funzione `dump` si occupa di printare a schermo, con lo stesso ordine presente nel file di lettura, i dati degli eventi precedentemente letti

La funzione accetta per *pass-by-reference* gli argomenti:

- id misure
- punti di impatto x,y,z
- numero di particelle

invece come *pass-by-value* i seguenti `array`

- campo elettrico
- momento x,y,z

Il *dump* degli eventi viene svolto printando a schermo i primi valori e tramice un ciclo `for` per tutte le particelle dell'evento