# Minesweeper - Guida all'Installazione e al Gioco

## Introduzione
Benvenuto nel mondo di Minesweeper! Questo gioco di logica ti sfida a scoprire celle su una griglia senza attivare mine nascoste. Segui questa guida per scaricare il gioco, comprendere come funziona la pagina GitHub e imparare a giocare.

## Come Scaricare il Gioco
1. **Trova la sezione "Release"**: Nella pagina principale del repository, cerca la scheda "Releases" sulla destra.
3. **Scarica il file eseguibile**: Clicca sul link per scaricare il file `[https://github.com/Nic0las-R0ssi/MineSweeperMinesweeper_v1.0.exe](https://github.com/Nic0las-R0ssi/MineSweeper/releases/tag/1.0)`.
4. **Installa il gioco**: Una volta completato il download, esegui il file e segui le istruzioni sullo schermo per installare il gioco.

## Come Funziona la Pagina GitHub
La pagina GitHub del progetto contiene:
- **Codice sorgente**: Puoi esplorare il codice del gioco per capire come è stato realizzato.
- **Issues**: Qui puoi segnalare bug o suggerire nuove funzionalità.
- **Wiki**: Trova ulteriori informazioni e documentazione sul gioco.
- **Release**: Trova le versioni più recenti del gioco e le note di rilascio.

## Come Giocare
### Sezione 1 - Comando di Input
Per giocare, inserisci comandi nel seguente formato:
```
r 2 2
```
Dove:
- `'r'` sta per 'rivelare' (per scoprire una cella).
- Il primo numero è la riga (partendo da 0).
- Il secondo numero è la colonna (partendo da 0).

**Esempi**:
- `r 0 1` → Rivela la cella alla riga 0, colonna 1.
- `f 3 4` → Segna la cella alla riga 3, colonna 4 come mina.

### Sezione 2 - Meccaniche del Gioco
- L'obiettivo è scoprire tutte le celle che NON contengono mine.
- Ogni numero sulla griglia indica quante mine circondano quella cella (in 8 direzioni).
- Se scopri una cella con 0 mine vicine, le celle vuote adiacenti verranno rivelate automaticamente.
- Utilizza il comando di bandiera (`f riga colonna`) per segnare potenziali mine.
- Scoprire una mina termina il gioco.

**Suggerimenti Strategici**:
- Inizia dagli angoli o dai bordi.
- Usa gli indizi numerici per dedurre dove sono nascoste le mine.
- Segna le celle sospette prima di rivelare quelle vicine.

### Sezione 3 - Divisione del Testo Guida
Il tutorial è suddiviso in sezioni per aiutarti a concentrarti su un concetto alla volta. Ogni parte introduce un nuovo argomento e attende che tu continui manualmente.

### Sezione 4 - Opzioni di Navigazione
Puoi utilizzare i seguenti comandi durante il tutorial:
- Premi Invio per passare alla sezione successiva.
- Digita 'menu' per uscire dal tutorial e tornare alla schermata principale.

### Sezione 5 - Esempi Pratici
Ecco un esempio di tavola di gioco dopo alcune mosse:
```
   0 1 2 3
  ---------
0| 1 F 1 .
1| 1 2 2 .
2| 0 0 1 F
3| . . . .
```
**Legenda**:
- Numeri: quante mine sono vicine.
- 'F': cella segnata (mina sospetta).
- '.': cella non rivelata.

**Esempi di Mosse**:
- `r 2 0` → Rivela uno 0, espande automaticamente le celle circostanti.
- `f 0 1` → Segna la cella (0,1) come mina.
- `r 0 3` → Mossa rischiosa! Potrebbe essere sicura... o no.

Usa queste strategie per padroneggiare il gioco!

## Conclusione
Grazie per aver scelto Minesweeper! Buon divertimento e buona fortuna nel tuo viaggio attraverso il campo minato!

