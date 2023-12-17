<div style="text-align: right">

[Back to index](../README.md)
</div>

# Particle Hist v2
---

## Note generali
Introduzione delle Factory (creational pattern)

## Classi e funzioni non modificate rispetto alla [versione precedente](../hist_v1/readme.md)

- mass
- Event
- EventSource
- EventReadFromFile
- EventSim
- AnalysisSteering
- EventDump
- ParticleMass
- MassMean
- Constants
- Utilities 

## Classi aggiunte da braggPlot_v2

### AnalysisInfo

Si occupa di analizzare le keyword fornite da riga di comando

### SourceFactory

Accetta come argomento un `AnalysisInfo` e si occupa di creare un `EventReadFromFile` o un `EventSim` in relazione all'output di `AnalysisInfo`

## Main

È stato rimosso il controllo `if` che si occupava di distinguere tra *input* e *sim*

Il compito è stato delegato ad un oggetto `AnalysisInfo` e un oggetto `SourceFactory`