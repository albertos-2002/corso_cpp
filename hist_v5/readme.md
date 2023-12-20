<div style="text-align: right">

[Back to index](../README.md)
</div>

# Particle Hist v5

## Note generali

È stato utilizzato il TFileProxy fornito nella cartella util per utilizzare lo stesoo file root con più analizzatori

Da riga di comando per selezionare gli analizzatori

analizzatore mass  : plotMass

analizzatore tempo : plotTime

print degli eventi   : dump

Il nome del file root (stesso file per i due analizzatori) viene passato dopo il comando/opzione *RootFileName*

I valori del range di massa, tempo, tempo scan e scan step vengono letti da file, il nome del file va inserito dopo, rispettivamente per massa e tempo, *MassFileName* e *TimeFileName*

## Classi invariate rispetto alla [versione precedente](../hist_v4/readme.md)

- AnalysisFactory
- SourceFactory
- Event
- EventSource
- EventReadFromFile
- EventSim
- EventDump
- MassMean
- Constants
- Utilities
- ParticleReco
- ProperTime

## Classi modificate

Classi prese da braggPlot_v5:

- AnalysisInfo.h
- AnalysisSteering .h .cc

---

- ParticleMass

	il range delle masse viene letto da un file passato da riga di comando

- LifetimeFit

	come membri privati sono stati dichiarati:
	
	- minimo e massimo per il time range
	- minimo e massimo per il range di scan 
	- step di scansione

	(questi primi 5 parametri sono gli argomenti del costruttore di classe)

	- un contenitore per tutti i tempi calcolati
	- media dei tempi
	- errore della media

	è stato rimosso il numero di eventi accettati

	sono state aggiunte due funzioni *public*:

	- lifeTime per ritornare la media dei tempi

	- lifeTimeError per ritornare l'errore della media


	La funzione `add` prende il tempo di decadimento da una `instance` di `ProperTime`, se è nel range desiderato lo aggiunge al vettore dei tempi di decadimento

	La funzione `nEvents` fa il return della `.size()` del vettore dei tempi di decadimento

	La funzione `compute` calcola la media e l'errore dei tempi di decadimento

	La funzione inoltre si occupa di calcolare la *likelihood* secondo l'equazione 

	$$L(t_s) = \sum_{i = 1}^N \frac{t_i}{t_s} + log(t_s) + log( e^{ \frac{-t_{min}}{t_s} } - e^{ \frac{-t_{max}}{t_s} } )$$

	dove con $t_i$ indichiamo il tempo di decadimento calcolato e conservato nel relativo vettore e con $t_s$ sono i tempi di scandione

	I risultati di *likelihood* e i tempi di scansione vengono conservati in una coppia di vettori

	Viene instanziato un oggetto `QuadraticFitter`, ne viene chiamata la funzione `add` in modo da poter passare i relativi punti

	La classe si occupa di fare il fit e tramite tre funzioni `a(), b(), c()` restituisce i parametri della parabola

	Il tempo minimo viene calcolato come $t = \frac{-b}{2*c}$ e il relativo errore viene calcolato come $\frac{1}{\sqrt{2*c}}$

	In aggiunta viene creato un grafico ROOT, su file distinti in base alle ipotesi, della parabola (per avere una conferma grafica)

- ParticleLifetime

	I parametri di massa e tutti i tempi di range e il valore di step per lo scan sono stati letti da un file passato da riga di comando

	La funzione `pCreate` è stata aggiornata per gestire i nuovi parametri


	

## Classi aggiunte 

- QuadraticFitter

	si occupa di svolgere il fit parabolico necessario per trovare il tempo minimo


## Classi *util*

- Singleton
- Dispatcher
- ActiveObserver
- LazyObserver
- TFileProxy

## Main

Il main è stato modificato per adattarsi alla nuova versione