# OSES - Laboratori Sistemi Operativi Embedded

Questa repository contiene una serie di esercitazioni pratiche sui Sistemi Operativi Embedded, basate su Trampoline OS e script Python per la compilazione e l'analisi dei trace.

## Struttura della repository

- **lab00.pdf, lab01.pdf, ...**: Materiale teorico e istruzioni dei laboratori.
- **script/**: Cartella principale con i sorgenti, script di build e configurazione per ciascun laboratorio.
    - Ogni sottocartella (`lab01_ex01`, `lab01_ex02`, ecc.) contiene:
        - Sorgenti C/C++ e file OIL di configurazione.
        - Script Python (`build.py`, `make.py`, `readTrace.py`) per compilazione e analisi.
        - File di trace (`trace.json`) e output di simulazione.

## Esempio: script/lab01_ex01

- **lab01_ex01.c**: Codice sorgente con task periodici e gestione allarmi.
- **lab01_ex01.oil**: Configurazione Trampoline OS (stack, allarmi, build).
- **build.py / make.py**: Script generati da goil per la compilazione.
- **readTrace.py**: Analisi dei trace generati dall'applicazione.
- **trace.json**: Esempio di trace in formato JSON.

## Compilazione e analisi

1. Modifica il file OIL se necessario.
2. Esegui `python make.py` per generare i file di build.
3. Esegui `python build.py` per compilare l'applicazione.
4. Analizza i trace con `python readTrace.py -i trace.json -a load`.

## Note

- I file PDF contengono la teoria e le istruzioni dettagliate per ciascun laboratorio.
- Gli script Python e i file OIL sono generati automaticamente e non vanno modificati manualmente, salvo indicazioni specifiche.

---
Per dettagli su ciascun laboratorio, consulta il relativo PDF e la cartella in `script/`.
