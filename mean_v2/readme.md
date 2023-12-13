<div style="text-align: right">

[Back to index](../README.md)

</div>

# Particle Mean v2

## Note generali

## Main 

Creazione di un ogetto `ifstream` con la stringa passata da terminale e svolge un controllo (`if`) sulla corretta apertura del file (`is_open()`)

Creazione di due istanze della classe [MassMean](##-Classe-`MassMean`-(class_massmean-.h-.cc)), una per il range di L0 (1.115, 1.116) e una per il range di K0 (0.495,0.500)

Ciclo `while`, controllato dall'oggetto `ifstream`:

- chiamata alla funzione [read](##-Funzione-read-`Event*`-(read.cc)) con creazione dinamica (`new`) di un puntatore a `Event` 
- chiamata alla funzione [add](###-Funzione-add-`void`) per entrambi gli oggetti *MassMean*
- chiamata alla funzione [dump](##-Funzione-dump-`void`-(dump.cc)) (disattivata)
- chiamata a `delete` per il puntatore a `Event`

Chiamata alla funzione [compute](###-Funzione-compute-`void`) per entrambi gli oggetti *MassMean*

Print a schermo dei risultati

## Funzione read `Event*` (read.cc)
Adattamento della [mean_v1](../mean_v1) per utilizare le classi

## Funzione mass `double` (mass.cc)
Adattamento della [mean_v1](../mean_v1) per utilizare le classi

## Funzione dump `void` (dump.cc)
Adattamento della [mean_v1](../mean_v1) per utilizare le classi

## Classe `Constants` (class_constants.h)

La classe dichiara come membri `public` le masse per il pionr, protone, L0 e K0

I valori sono stati dichiarati `double` e con le seguenti keyword

- `static` per non renderle specifiche alle singole istanze della classe
- `constexpr` in modo tale da poterle dichiarare all'interno della classe anche se non sono `int` (senza creare un file .cc), inoltre in questo modo l'espressione viene valutata a *compilation time*

## Classe `Event` (class_eventi .h .cc)

Vengono dichiarati come membri `private` quelli precedentemente presenti nella [`struct Event`](../mean_v1/readme.md)

Viene aggiunta una variabile di tipo `const static int` per contenere il numero massimi di particelle possibili in un evento (10)

### Costrutture

Argomenti:

- `int` id evento
- `float` punto impatto x,y,z
- `int` numero di particelle

con cui vengono inizzializzate le variabili

al *puntatore di puntatori* assegna i 10 puntatori a `Particle` (`new`)

ognuno di questi puntatori viene settato a `nullptr`

un numero di puntatori pari al numero di particelle lette viene riassegnato a una `struct Particle` (`new`)

### Distruttore
Per prima cosa elimina ogni `struct Particle` (`for`) e successivamente elimina l'*array di puntatori*

### Funzione add `void`

Argomenti:

- `int` campo elettrico
- `float` momento x,y,z
- `int&` index

La funzione di occupa di riempiere la `struct Particle` all indice *index* con gli argomenti passati 

### Funzione eventNumber `int` `const`
Restituisce il numero identificativo

### Funzione xdecay `float` `const`
Restituisce la coordinata x del punto di impatto

### Funzione ydecay `float` `const`
Restituisce la coordinata y del punto di impatto

### Funzione zdecay `float` `const`
Restituisce la coordinata z del punto di impatto

### Funzione nParticles `int` `const`
Restituisce il numero di particelle

### Funzione particles `Particle*` `const`
Restituisce il puntatore ad una `struct Particle` se il valore `int` passato come argomento è minore del numero di particelle (`if`) in caso contrario restituisce `nullptr` (`else`)

## Classe `MassMean` (class_massmean .h .cc)

Membri dichiarati `private`

- `double` minimo e massimo del range della massa invariante
- `int` numero di eventi selezionati
- `double` somma delle masse invarianti
- `double` somma dei quadrati delle masse invarianti
- `double` media
- `double` rms
- altre variabili interne 

Membri dichiarati `public`

### Costruttore
Argomenti

- `double` minimo e massimo della massa invariante (range di ricerca)

assegna i parametri passati come argomento alle rispettive variabili interne e *setta* le altre a 0

### Distruttore
(default)

### Funzione add `void`

Come argomento acceta `const Event&`

Chiama la funzione [`mass`](##-Funzione-mass-`double`-(mass.cc)) passandogli l'evento, controlla che il risultato sia interno al range desiderato (`if`) e in caso di esito positivo aggiorna la somma delle masse, la somma dei quadrati delle masse e il contatore degli eventi accettati

### Funzione compute `void`

La funzione si occupa di calcolare la media delle masse invarianti e il relativo rms 

([Matematicamente come nel Particle Mean v1](../mean_v1/readme.md))

### Funzione nEvents `int`
Ritorna il numero di eventi selezionati

### Funzione mMean `double` `const`
Ritorna la media delle masse invarianti

### Funzione mRMS `double` `const`
Se (`if`) positivo, ristorna il valore di RMS, altrimenti (`else`) ritorna 0

## Classe `Utilities` (class_utilities .h .cc)

La classe raccoglie come membri `public` le funzioni `massa_invariante` ed `energia` precedentemente definite per [Particle Mean v1](../mean_v1/readme.md)

Le due funzioni sono dichiarate static