# **GESTIONE ALBERGO** 
															  
## OPERAZIONI DI ALTO LIVELLO
- Mostra lista cliente : visualizza tutti i clienti della lista riferita ai clienti.
- Mostra Disponibilità stanze : visualizza tutte le stanze occupate in una determinata data o intervallo, della lista riferita alle stanze.
- Mostra stanze : visualizza lo stato di tutte le stanze in una determinata data o intervallo, della lista riferita alle stanze.
- Aggiungi cliente e prenotazione : Questa funzione permette di aggiungere un cliente, se non esistente, e di associare ad esso una prenotazione per una stanza disponibile con la capienza corretta.
- Modifica prenotazione : Questa funzione permette di modificare una già esistente prenotazione e non svolta, con il passaggio del codice di prenotazione.
- Elimina prenotazione : Questa funzione permette di eliminare definitivamente una prenotazione già esistente e non svolta, con il passaggio del codice prenotazione.
- Salva stato : salva lo stato delle prenotazioni, delle stanze e dei clienti su tre file differenti.

## OPERAZIONI SULLE LISTE
- Lista Clienti 
- Lista Stanze
- Lista Prenotazioni

Nelle liste si effettureannno degli inserimenti in testa ed in modo ordinato.
Le ricerche per codice prenotazione andranno effettuate sia nella lista prenotazioneStanza sia in listaPrenotazione, poichè sono le uniche strutture che contengono i dati delle prenotazioni future e presenti. 
Si suppone che le prenotazioni passate non si possano eliminare o modificare. 
La ricerca confronterà prima nella lista prenotazione quale prenotazione deve eliminare/modificare,controllerà la disponibilità in caso di modifica ed effettuerà tale modifica.

## FUNCTION

### FUNCTION CREAZIONE/INSERIMENTO/MODIFICA CONTENUTO
- stanza*crea_listaStanza(stanza)	***riceve come parametro una variabile di tipo stanza ed inizializza la lista stanza. Restituisce la testa della lista***
- void inserimentoTestaCliente(cliente **, cliente) ***riceve come paramentro un puntatore alla testa della lista cliente, ed una variabile cliente. Serve ad inserire in testa.***
- void inserimentoStorico(codicePrenotazione **, int) ***riceve come parametro un puntatore alla testa della lista codicePrenotazione, ed un intero che rappresenta la nuova prenotazione. Serve ad inserire in testa.***
- prenotazione * inserimentoTestaP(prenotazione **, prenotazione) ***riceve come paramentro un puntatore alla testa della lista prenotazione, ed una variabile prenotazione. Serve ad inserire in testa. Restituisce la testa della lista***
- void changeData(prenotazione **,prenotazione) ***riceve come paramentro un puntatore alla lista prenotazione precedentemente trovato tramite l'utilizzo della funzione modificaPrenotazione(..), ed una variabile prenotazione. Serve a modificare il contenuto della prenotazione.***
### FUNCTION PRENOTAZIONI
- prenotazione * ricercaPrenotazione(prenotazione *, int) ***Riceve come paramentro un puntatore alla lista prenotazione, ed un intero che identifica il codicePrenotazione ricercato. Effettua una ricerca se la ricerca va a buon fine restituisce il nodo corrispondente***
- int ricercaData(prenotazione *, prenotazione) ***Riceve come parametro la lista prenotazione, ed una variabile prenotazione. Effettua un controllo con le date in questo seguente modo :***

		pOld       pNew
		5 - 7      8 - 9
        5 < 8
        7 < 8
        5 < 9
        7 < 9
        Significa che la stanza in quei giorni dato che sono successivi è libera
        pOld < pNew significa successivo
		OPPURE
        pOld        pNew
        5 - 7      3 - 4
        5 > 3
        7 > 3
        5 > 4
        7 > 4     
        Significa che la stanza in quei giorni dato che sono precedenti è libera
        pOld > pNew significa precedente
	***controlla dataI e dataF sia di pOld si di pNew e cerca di controllare i vari casi nel quale non si sovrappongono.***
	***Ritorna 0 se tutto va a buon fine, 1 se non è disponibile.***
- int creaPrenotazione(stanza *,prenotazione,prenotazione *,int) ***Riceve la lista stanze, una variabile prenotazione, la lista prenotazione ed un intero che identifica il codicePrenotazione.***

***Effettua due ricerche, la prima di una stanza in base al numero di occupanti. La secondo sempre di una stanza in base alla disponibilità della data usando la funzione ricercaData(...)***
***La ricerca per data viene effettuata finche la lista codicePrenotazione contenuta nel nodo stanza designato come papabile per capienza, effettua il confronto con ogni nodo che appartiene***
***alla lista codicePrenotazione usufruendo della funzione ricercaPrenotazione(...) trova il nodo prenotazioni corrispondente e passa quello come paramentro da confrontare con la nuova prenotazione***
***se in tutta la lista codicePrenotazione il confronto da esito positivo (cioè ritorna sempre 0) potrò dire che la mia prenotazione è andata a buon fine e verrà aggiunto il nodo prenotazione alla sua relativa lista***
***ed il nodo codicePrenotazione alla sua relativa lista che è contenuta in un nodo stanza. Ritorna 0 se tutto a buon fine, Ritorna 1 se c'è un problema***
- void addPrenotazione(prenotazione **,stanza *,int) ***Riceve come parametro un puntatore alla lista prenotazione, la lista stanza ed un intero che identifica il codicePrenotazione. Il suo scopo è :***
	- **Di fare I/O con l'stdin per i dati della nuova prenotazione**
	- **Richiamare la funzione creaPrenotazione(...)**
	- **Se la funzione creaPrenotazione(...) ritorna 0 inserisce in testa  tramite la funzione inserimentoTestaP(...) un nodo prenotazione**
	- **Se la funzione creaPrenotazione(...) ritorna 1 stampa un messaggio d'errore**
	
- int checkPrenotazione(prenotazione *, codicePrenotazione *, prenotazione) ***Riceve la lista prenotazione, la lista codicePrenotazione ed una variabile prenotazione.***
***Effettua un controllo nella lista codicePrenotazione tramite l'utilizzo della funzione ricercaPrenotazione(...) per trovare il nodo corrispondente al codice ricercato***
***Tramite la funzione ricercaData(...) se la funzione restituisce 0 e la lista codicePrenotazione non ha successivo nullo, va al successivo e ripete da capo.***
***Nel caso in cui la funzione ricercaData(...) restituisce 1 il ciclo si interrompe e la funzione checkPrenotazione(...) restituisce 1, in caso la ricerca vada a buon fine restituisce 0***

- void modificaPrenotazione(prenotazione *head,codicePrenotazione * stanza, int key)  ***Riceve come parametro un puntatore alla lista prenotazione, la lista stanza ed un intero che identifica il codicePrenotazione. Il suo scopo è :***
	- **Di fare I/O con l'stdin per i dati della nuova prenotazione**
	- **Richiamare la funzione ricercaPrenotazione(...) per avere il nodo interessato alla modifica **
	- **Se la funzione checkprenotazione(...) ritorna 0 richiama la funzione changeData(...)**
	- **Se la funzione checkPrenotazione(...) ritorna 1 stampa un messaggio d'errore**
- void cancellaPrenotazione(prenotazione **, int) ***Riceve come parametro un puntatore alla lista prenotazione ed un intero che identifica il codicePrenotazione. Il suo scopo è :***
	- **Ricerca il nodo con il codicePrenotazione passato come paramentro in caso lo trova lo elimina**
	TODO : si potrebbe richiamare la funzione ricercaPrenotazione(...) ed eliminare il nodo che restituisce
- prenotazione * prenotazioneTerminata(prenotazione *) ***Riceve come parametro una lista prenotazione il suo scopo :***
 	-**Controlla se la data globale è maggiore della dataI di un nodo. In caso si trova un nodo con la dataI < data restituisce il puntatore a quel nodo. In caso contrario restituisce NULL**

### FUNCTION STANZA
- stanza * ricercaStanza(stanza *,int) ***Riceve come parametro la lista stanza ed un intero che rappresenta il numero della stanza. Il suo scopo è :***
	- **Ricerca del nodo con il numeroStanza uguale a quello passato come parametro**
	- **Restituisce il nodo in caso di buona riuscita, restituisce NULL in caso di non riuscita**
- codicePrenotazione * ricercaCodiceStanza(codicePrenotazione *, int) ***Riceve come parametro la lista codicePrenotazione ed un intero che rappresenta il codice da ricercare. Il suo scopo è:
	- **Ricerca del nodo con il codice = a quello passato come parametro**
	- **Restituisce il nodo in caso di buona riuscita, restituisce NULL in caso di non riuscita**
- stanza * ricercaPrenotazioneStanza(stanza * head,int key) ***Riceve come parametro la lista stanza ed un intero che rappresenta il codice da ricercare. Il suo scopo è :***
	- **Richiama la funzione ricercaCodiceStanza(...) finchè la funzione prima richiamata non restituisce un nodo diverso da NULL**
	- **Restituisce il nodo in caso di buona riuscita, restituisce NULL in caso di non riuscita**
- void letturaS(stanza **)	***Riceve in ingresso il puntatore alla lista stanza. Il suo scopo è :***
	- ***Versione noFile***
		- **I/O con l'utente da stdin**
		- **Effettua un inserimento in testa**
	- ***Versione File***
		- **I/O da un file di nome stanze.txt**
		- **Effettua un inserimento ordinato in base al numeroStanza**
- void cancellaCodicePrenotazione(codicePrenotazione **,int) ***Riceve come parametro la lista codicePrenotazione ed un intero che rappresenta il codice da ricercare. Il suo scopo è :***
	- **Effettua una ricerca del codicePrenotazione, nel caso in cui venga trovato lo elimina**
	TODO : Far richiamare la funzione ricercaCodiceStanza(...) ed eliminare quel nodo

### FUNCTION CLIENTE
- cliente * cercaCliente(cliente *,char[]) ***Riceve come parametro la lista clienti ed una stringa che rappresenta la CI. Il suo scopo :***
	- **Ricerca se esiste un cliente avente la CI passata come paramentro**
	- **Restituisce il puntatore al nodo se esiste, restituisce NULL se non esiste**
- cliente inserisciCliente(cliente *) ***Riceve come paramentro la lista clienti. Il suo scopo :***
	- **Di fare I/O con l'stdin per i dati del nuovo cliente**
	- **Controlla la sua esistenza**
	- **In caso non esista nessun cliente con quella CI restituisce il dato preso da I/O. In caso contrario restituisce NULL**
- int ricercaCodiceStorico(int,codicePrenotazione *) ***Riceve come parametro un intero che rappresenta il codice da ricercare e la lista codicePrenotazione riferita ad un nodo cliente. Il suo scopo è :***
	- **Ricercare se esiste un nodo codicePrenotazione esistente con il codice passato come parametro**
	- **Restituisce 0 se esiste, restituisce 1 se non esiste**
- void storicoClienti(prenotazione *,cliente *) ***Riceve come parametro un nodo prenotazione e la lista clienti. Il suo scopo è :***
	- **Tramite la funzione cercaCliente(...) cerca il cliente con la CI della prenotazione passata come parametro**
	- **Se esiste richiama la funzione ricercaCodiceStorico(...) se essa restituisce 0 richiama la funzione inserisciScorico(...) ed inserisce un codice nella lista codicePrenotazione inerente a quel cliente**
	- **Se non esiste stampa un messaggio d'errore**


