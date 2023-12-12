

# Particle Mean v1
---

## Note generali
---

Questa versione introduce il riconoscimento degli eventi (particella che decade), in base all'appartenze ad un range di massa invariante

Per evitare problemi di precisione si è passati dai `float` ai `double` per molte delle variabili in gioco

## Main 
---

Vengono definite le seguenti variabili interne:

- `int` numero di eventi accettati
-  `double` somma delle masse invarianti
-  `double` somma dei quadrati delle masse invarianti
-  `double` media delle masse invarianti
-  `double` RMS delle masse invarianti

Il main è strutturato come segue:

- Apertura di un ogetto `ifstream` con stringa passata da terminale

	controllo (`if`) sulla corretta apertura del file

- ciclo `while` controllato dall'ogetto `ifstream`

	- chiamata alla funzione `read`
	- `if`, controllato dalla chiamata alla funzione `add`, se `true` update del numero eventi accettati
	- chiamata alla funzione `dump` (disattivata)
	- chiamata alla funzione `clear`

- calcolo della media delle masse invarianti

- calcolo di RMS

$$ \sqrt{ \frac{somma dei quadrati massa invariante}{numero eventi accettati} - {media masse invarianti}^2 } $$

	- `if` se positivo il valore viene assegnato alla variabile, se negativo viene impostato a 0

- print a schermo dei risultati


## struct.h
---
Invariato rispetto a [dump_v2](../dump_v2)

Sono state aggiunte qui le variabili di tipo `const` che contengono i valori di riferimento della massa delle particelle e le variabili dell'intervallo di selezione

## Funzione read `Event*` (read.cc)
---
Invariato rispetto a [dump_v2](../dump_v2)

## Funzione dump `void` (dump.cc)
---
Invariato rispetto a [dump_v2](../dump_v2)

## Funzione clear `void` (clear.cc)
---
Invariato rispetto a [dump_v2](../dump_v2)

## Funzione massa_invariante ed energia `double` (funzioni.cc)
---

### massa_invariante

La funzione accetta come argomento:

- *reference* `float` momento x,y,x
- *reference* `double` energia

La funzione calcola la massa invariante di una particella, la assegna ad un variabile interna e poi ne fa il `return`

$$ \sqrt{ { energia }^2 -  \sum{momento^2} } $$

### energia 

La funzione accetta come argomento:

- *reference* `const float` momento x,y,x
- *reference* `const double` massa invariante

La funzione calcola l'energia di una particella, la assegna ad un variabile interna e poi ne fa il `return`

$$ \sqrt{ { massa invariante }^2 -  \sum{momento^2} } $$

## Funzione mass `double` (mass.cc)
---
La funzione accetta come argomento una *reference* a `const Event`

È stato introdotto un `typedef` per rinominare `const Particle*`

Sono state dichiarate le seguente variabili interne:
- `int` contatore particelle cariche positivamente
- `int` contatore particelle cariche negativamente
- `double` somma momento x,y,z
- `double` somma energia per ipotesi di K0
- `double` somma energia per ipotesi di L0
- `double` massa invariante per ipotesi K0
- `double` massa invariante per ipotesi L0

La funzione esegue i seguenti blocchi:

Ciclo `for` su tutte le particelle: 

- con un `if-else` update del counter per la carica delle particelle in esame
- update della somma dei momenti per componenti
- calcolo + update delle energie per entrambe le ipotesi

	chimata alla funzione `energia` 
	
	- per ipotesi K0 con la massa del pione
	- per ipotesi di L0, tramite un ciclo `if-else` con la massa del protone se la particella è carica positivamente e con la massa del pione se negativa
	
- controllo (`if`) se i conuter per le particelle cariche positivamente o negativamente differice da 1
(`return -1` valore non fisico)
- calcolo della massa invariante per entrambe le ipotesi (con le relative energie calcolate in precedenza) chimando la funzione `massa_invariante`
- calcolo della differenza tra la massa invariante e la relativa costante nota a priori (`abs()`) 

	questo permette di selezionare l'ipotesi che si avvicina di più alla particella che realmente è decaduta

- tramite un ciclo `if-else` controllato dai valori al punto sopra viene fatto il `return` dell'ipotesi corretta

## Funzione add `bool` (add.cc)
---

La funzione `add` si occupa di discriminare gli eventi e di fare l'update della somma delle masse invarianti e del loro quadrato

Argomenti della funzione:

- *reference* to `const Event`
- *reference* `const float` minimo del range della massa invariante
- *reference* `const float` massimo del range della massa invariante
- *reference* `double` alla somma delle masse invarianti
- *reference* `double` alla somma del quadrato delle masse invarianti

Viene chiamata la funzione `mass` passando un evento, il risultato viene mantenuto in una variabile interna, un `if` si occupa di controllare se il valore di test è interno al range, per esito positivo vengono aggiornati i valori delle somme e fatto il `return true`, in caso contrario le somme non vengono aggiornate e viene fatto `return false`