<div style="text-align: right">

[Back to index](../README.md)
</div>

# Particle Mean v3
---

Il codice rimane sostanzialmente invariato 

È stato aggiornato per utilizzare i `vector` al posto delgi `array` nella classe *Event* per il *puntatore di puntatori*; è stato rimossa la variabile contenente il numero di particelle e quella contenente il numero di particelle massime, sostituite rispettivamente con un .size() e un .reserve(10)

Sono state aggiornate anche le funzioni che fanno uso delle variabili modificate


Gli argomenti passati al main sono stati convertiti da `C-style string` a `string` di tipo C++ (STL)
