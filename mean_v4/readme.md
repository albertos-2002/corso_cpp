<div style="text-align: right">

[Back to index](../README.md)
</div>

# Particle Mean v4
---

## Note generali

Il comando di esecuzione è stato aggiornato al seguente modo:

- execName input fileName

or

- execName sim numberOfEvents [seedNumber]

---

## Classi ottenute da braggMean_v4

### AnalysisStearing (.h .cc)
Viene definita come `abstract class` (pure virtual function), fornisce una base comune per le funzioni `beginJob`, `endJob`, `process`

### EventSource (.h .cc)
Viene definita come `abstract class`, (pure virtual function), fornisce una base comune per una funzione che ritorna un puntatore ad un ogetto *Event*

### EventReadFromFile (.h .cc)
Classe derivata da *EventSource* (eredita pubblicamente)

I membri privati sichiarati sono un oggetto `ifstream` e le variabile interne della ex funzione globale *read*

La classe si occupa di leggere i dati relativi ad un evento e ritornare un puntatore all'ogetto

Il costruttore accetta come parametro una stringa con la quale viene inizzializzato l'ogetto `ifstream` (`new`), il distruttore si occupa poi di eliminare la memoria

La funzione `get` (pure virtual della classe base) ritorna (chiama) la funzione `readFile` che ritorna un puntatore ad un ogetto *Event*

La funzione `readFile` contiene il codice che apparteneva alla ex funzione globale *read*

### EventDump (.h .cc)
Classe derivata da *AnalysisStearing* (eredita pubblicamente)

Viene svolto l' `override` delle funzioni pure virtual

`beginJob`

- empty

`endJob`

- empty

`process`

- questa funzione racchiude il codice che nelle versioni precedenti apparteneva alla funzione globale *dump*


### EventSim (.h .cc)
. . . . . . . . . 

---

## Classi create in questa versione

### ParticleMass (.h .cc)
Classe derivata da *AnalysisStearing* (eredita pubblicamente)

Come membro privato viene dichiarato un `vector` per contenere puntatori ad ogetti `MassMean`

Il costruttore si occupa di fare il reserve per 2 spazi di memoria per il vettore contenente i puntatori agli oggetti `MassMean`

Il distruttore di occupa di eliminare la memoria creata dinamicamente

Viene svolto l' `override` delle funzioni pure virtual

`beginJob`

- si occupa della creazione degli oggetti `MassMean` e di conservarli nel vettore dedicato (l'ordine di creazione è L0, K0)

`endJob`

- per ogni oggetto `MassMean` chiama la relativa funzione `compute` e fa il print dei risultati

	Un controllo `if` sull'indice del vettore permette di fare il print con il nome della particella corretta 

`process`

- accetta come argomento `const Event&` e per ogni ogetto `MassMean` chiama la funzione `add` e passa l'ogetto `Event`

---

## Classi non modificate

Le seguenti classi non sono state modificate sensibilmente, al massimo sono state aggiornate per utilizzare gli aggiornamenti di questa versione

(vedere la documentazione della versione precedente per la descrizione completa)

- classe `Event`
- class `Utilities`
- class `MassMean`

## Main

La sequenza logica del main è la seguente:

- copia su una stringa della keyword per la decisione tra lettura da file e simulazione degli eventi
-  creazione di un puntatore a `EventSourc`
- Controllo tramite un `if-elseif-else` se la prima keyword è *input*, *sim* o una stringa non riconosicuta

	- se la stringa è *input* al puntatore `EventSource` viene assegnato un ogetto di tipo `EventReadFromFile`
	- se la stringa è *sim*, vengono estratti il numero di eventi e il seed per la simulazione e al puntatore `EventSource` viene assegnato un ogetto di tipo `EventSim`

- viene creato un vettore contenete 2 oggetti, un `ParticleMass`e un `EventDump`
- per entrambi gli analizzatori viene chiamata la funzione `beginJob`
- viene creato un puntatore alla classe `Event`
- un ciclo `while`, estrare i singoli eventi chiamando la funzione `get` relativa all'ogetto `EventSource` assegnato in precedenza nol controllo

	per ogni analizzatore viene chiamata la funzione `process`

- per ogni analizzatore viene chiamata la funzione `endJob`
- viene eliminata la memoria creata dinamicamente all'interno del *main*
