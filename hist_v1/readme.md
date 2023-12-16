<div style="text-align: right">

[Back to index](../README.md)
</div>

# Particle Hist v1
---

## Note Generali 

Aggiuta CERN ROOT

---

## Classi invariate rispetto alla [versione precedente](../mean_v4/readme.md)

- Event
- EventReadFromFile
- EventSim
- AnalysisSteering
- EventSource
- EventDump
- Constants
- Utilities

La funzione globale *mass* è rimasta invariata

Il *main* è rimasto invariato

## MassMean (.h .cc)

La funzione `add` è stata modificata per fare il `return` di un `bool`, `true` se la massa rienta nel range desiderato, `false` in caso contrario

È stato aggiornato il controllo `if` che fa il check delle masse e aggiunto un `else`

## ParticleMass (.h .cc)

È stata aggiunta una `struct` nominata `Particle` contenente:

- una `string` per il nome dell'istogramma
- un puntatore a `MassMean`
- un puntatore a un ogetto `TH1F`

Il vettore che conteneva puntatori ad oggetti `MassMean` è stato modificato per contenere putatori ad ogegtti `struct Particle`

Sono state modificate e aggiunte le seguenti funzioni

- `beginJob`

	Viene fatto il `.reserve` per 2 spazi di memoria per il *vettore di puntatori* a `Particle`

	Per entrambe le ipotesi, la funzione fa il `.push_back` di una struttura `Particle` (creata dinamicamente) e chiama la funzione `pCreate` passando il nome dell'ipotesi e il range delle masse

- `endJob`

	Viene creato il file *.root*

	Per ogni `Particle` viene chiamata la funzione `compute` di `MassMean`, stampati i risultati su schermo e scritto il relativo istogramma

	Infine viene chiuso il file

- `process`  

	Per ogni struttura `Particle` viene, dentro un controllo `if`, chiamata la funzione `add` di `MassMean` e viene riempito il relativo istogramma tramite `Fill(mass(Event))` (che chiama la funzione mass per il relativo evento in modo da ottenere il valore di massa invariante) 

- `pCreate`

	Accetta come argomento:

	- una `const string&` per il nome dell'istogramma
	- due `float` per il range delle masse 

	La funzione si occupa di riempire la struttura `Particle` con il nome dell'evento, della creazione di un oggetto `MassMean` (creazione dinamica) e della creazione di un oggetto `TH1F` (`new`)

Il distruttore è stato aggiornato per eliminare i nuovi oggetti creati dinamicamente