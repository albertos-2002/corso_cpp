<div style="text-align: right">

[Back to index](../README.md)
</div>

# Particle Hist v3

## Note generali

Il nome del file root viene estratto dalla riga di comando, dopo la keyword *plot* è necessario mettere il nome del file root che si desidera

## Classi e funzioni invariate rispetto alla [versione precedente](../hist_v1/readme.md)

- funzione mass
- AnalysisInfo
- SourceFactory
- Event
- EventSource
- EventReadFromFile
- EventSim
- MassMean
- Constants
- Utilities


## Classi aggiunte

- AnalysisFactory

	si occupa di creare gli analizzatori in base alle keyword passate da riga di comando

	accetta come argomento di costruzione un *puntatore* ad `AnalysisInfo`

## Classi modificate

- AnalysisSteering
	
	è stato aggiunto un *puntatore* a `AnalysisInfo` come membro `protected`, il costruttore di classe accetta come argomento un *puntatore* ad `AnalysisInfo` e lo assegna al membro `protected`

- EventDump

	è stato aggiunto un analizzatore concreto

- ParticleMass

	è stato aggiunto un analizzatore concreto

## Main 

È rimasto sostanzialmente invariato, il vettore che contiene gli analizzatori, non viene riempito con una serie di push_back ma viene riempito da una chiamata alla funzione `create` di `AnalysisFactory`

