<div style="text-align: right">

[Back to index](../README.md)
</div>

# Particle Hist v4

## Note generali

È stata aggiunta la truttura di base per un analizzatore di tipo tempo

È stato utilizzato il TFileProxy fornito nella cartella util per utilizzare lo stesso file root con più analizzatori

Da riga di comando per selezionare gli analizzatori

analizzatore mass  : plotMass

analizzatore tempo : plotTime

print degli eventi   : dump

Il nome del file root (stesso file per i due analizzatori) viene passato dopo il comando/opzione *RootFileName*

## Classi invariate rispetto alla [versione precedente](../hist_v3/readme.md)

- AnalysisFactory
- AnalysisInfo
- SourceFactory
- Event
- EventReadFromFile
- EventSim
- Utilities

## Classi modificate

- AnalysisSteering

	rimossa la funzione `process`

- EventSource

	la funzione `get` è stada dichiarata come `private`

	è stata aggiunta una funzione `run` che incorpora quello che prima era il *loop over events* del main della versione precedente, all'interno della funzione viene chiamata la funzione `notify` di `Dispatcher<Event>`

- EventDump

	la classe eredita pubblicamente anche da `ActiveObserver<Event>`

	la funzione `process` è stata rinominata in `update`

- ParticleMass

	la classe eredita pubblicamente anche da `ActiveObserver<Event>`

	la funzione `process` è stata rinominata in `update`

	la funzione `update` chiama una `instance()` di `ParticleReco` (*Singleton*), ne chiama la funzione `update` e ottiene la massa invariante

	il nome dell'istogramma è dato da *mass + nome_ipotesi*

- MassMean

	la funzione `add` chiama una `instance()` di `ParticleReco`, ne chiama la funzione `update` e ottiene la massa invariante

- Constants
	
	è stata aggiunta la costante `lightVelocity`

	

## Classi aggiunte 

- ParticleReco

	la funzione eredita pubblicamente da `Singleton<Event>` e da `LazyObserver<Event>`

	come membri *privati* sono stati dichiarati

	- `enum` per la tipologia di decadimento
	- `double` per l'energia totale
	- `double` per la massa invariante
	- `double` per la distanza di decadimento 

	come membri *pubblici* sono stati dichiarati

	- una funzione `update`, che accetta come argomento `const Event&` e contiene il codice della ex funzione globale mass, assegna i valori alle relative variabili, inoltre calcola e assegna la distanza di decadimento
	- una variabile del tipo `enum`
	- tre funzioni per ritornare il valore della massa invariante, energia totale e distanza

- ProperTime

	la classe è una copia di `ParticleReco` con le seguenti modifiche:

	come membri privati:

	- `enum` (uguale a quello di ParticleReco)
	- `double` per l'energia e uno per la massa invariante
	- `double` per il tempo
	- un puntatore a ParticleReco che viene assegnato chiamando `instance()` nel costruttore di classe

	come membri privati:

	- una funzione `update` che calcola il tempo proprio, dato da 

	$$
		t = \frac{ distance * massa \ invariante }{ momento * c }
	$$

	con 

	$$
		momento = \sqrt{ energia^2 - massa \ invariante^2 } 
	$$

	- una funzione `decayTime` che fa il return della variabile *time*
	- una variabile di tipo *enum*



- LifetimeFit

	la classe è una copia di `MassMean` con le seguenti modifiche:

	vengono eliminati i memebri che contengono le somme, la media e rms, come le funzioni che li ritornano

	la funzione `add` gestisce un oggetto `ParticleReco`, lo usa per ottenere la massa invariante e se rientra nel range aggiorna il contatore degli eventi

	la funzione `compute` verrà implementata nella prossima versione

- ParticleLifetime

	la classe è una copia di `ParticleMass` con le seguenti modifiche:

	la struttura `Particle` è stata aggiornata per contenere un puntatore a `LifetimeFit` invece che a *MassMean*

	la funzione `pCreate` è stata aggiornata per prendere come argomneto anche un minimo e un massimo per il tempo

	l'implementazione delle funzioni `pCreate`, `beginJob`, `endJob`, e `update` sono state adattate (mantenendo il concetto di base di *ParticleMass*) per lavorare sui tempi


## Classi *util*

- Singleton
- Dispatcher
- ActiveObserver
- LazyObserver
- TFileProxy

## Main

Il loop su tutti gli eventi è stato trasformato un una chimata alla funzione `run` di EventSource`