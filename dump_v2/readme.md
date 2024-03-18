<div style="text-align: right">

[Back to index](../README.md)
</div>

# ParticleDump versione 2 


Introduzione delle `struct`

File contenente i dati [particles_events](../particles_events)

## Main

Il main svolge le seguenti istruzioni:

- creazione di un ogetto di tipo `ifstream`, il nome del file viene recuperato della riga di comando

	viene anche svolto un controllo `if` per verificare che 	il file sia aperto correttamente (`.is_open()`)

- Ciclo `while` il cui controllo è dato dall'ogetto `ifstream`

	chimata della funzione
	`read`, `dump`, `clear`

	(alla funzione `dump` non viene passato una reference const ma un puntatore dereferenziato)

## Struct.h `struct`

Sono state definite due strutture

`struct Event`

La struttura evento contiene 

- identificatore dell'evento `int`
- coordinate impatto x,y,z `float`
- numero di particelle `int`
- puntatore ad un array di puntatori ad una struttura di tipo Particle `Particle** ptr_name`
(questa sintassi si riferisce ad avere un puntatore che punta al primo elemento di un array che a sua volta contiene dei puntaori di tipologia Particle, ci sono casi in cui un array decade a puntatore)

	In questo modo possiamo velocemente accede a tutte le 		particelle presenti in un evento

`struct Particle`

La struttura particle si occupa di contenere le variabili relative ad una particella

- campo elettrico `int`
- momento x,y,z `float`

## Read function `Event*`


La funzione `read` svolge il medesimo compito descritto per il caso [Dump_v1](../dump_v1/readme.md)

Modifiche: 

- Creazione di un *puntatore* ad un ogetto `Event` in modo dinamico (`new` keyword)

- Al *puntatore di puntatori* viene assegnato (`new`) un `array` di puntatori alle strutture `Particle` pari al numero di particelle letto dall'evento

- Viene svolto un ciclo `for` per un numero pari a quello di particelle, ad ogni puntatore creato al punto precedente (contenuto nel *puntatore di puntatori*) viene creata (`new`) una struttura `Particle`, la quale viene riempita con i dati letti dall'evento  

- Al termine del file (`eof`) viene restituito un `nullptr`

La funzione ritorna un puntatore ad una struttura `Event` (quello creato in precedenza)

## Dump function `void`


La funzione `dump` svolge il medesimo compito descritto per il caso [Dump_v1](../dump_v1/readme.md)

Sono state fatte le seguenti modifiche:

- argomento accettato:

	la funzione accetta come argomento `const Event&`

- accesso tramite struttura, operatore `.` per le *reference* e `->` per i *pointer*

	gli elementi contenuti nella struttura di tipo `Event` sono utilizzati tramite `.`, gli elementi contenuti in una struttura di tipo `Particle` sono utilizzati tramite `->` dato che la struttura `Event` contiene dei *puntatori* alla struttura `Particle`

## Clear function `void`

Il compito della funzione `clear` è di eliminare la memoria creata dinamicamente

La funzione accetta come argomento un puntatore ad una struttura `Event`, svolge un ciclo `for` ed elimina tutte le struttura `Particle` contenute nel *puntatore di puntatori*, successivamente viede eliminato il *puntatore di puntatori* e per ultimo viene eliminato il puntatore alla struttura `Event`