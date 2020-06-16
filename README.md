GESTIONE ALBERGO
FUNZIONI CREAZIONE/INSERIMENTO/MODIFICA CONTENUTO
void inserimentoTestaCliente(cliente **, cliente,codicePrenotazione) riceve come paramentro un puntatore alla testa della lista cliente, una variabile cliente ed una lista codicePrenotazione. Serve ad inserire in testa.
void inserimentoStorico(codicePrenotazione **, int) riceve come parametro un puntatore alla testa della lista codicePrenotazione, ed un intero che rappresenta la nuova prenotazione. Serve ad inserire in testa.
prenotazione * inserimentoTestaP(prenotazione **, prenotazione) riceve come paramentro un puntatore alla testa della lista prenotazione, ed una variabile prenotazione. Serve ad inserire in testa. Restituisce la testa della lista.
void InserisciOrdinatoS(stanza **, stanza,codicePrenotazione)  riceve come paramentro un puntatore alla testa della lista stanza, una variabile stanza ed una lista codicePrenotazione. Serve ad inserire in maniera ordinata. 
FUNZIONI CODICE PRENOTAZIONE
codicePrenotazione * ricercaCodice(codicePrenotazione *, int) Riceve come parametro la lista codicePrenotazione ed un intero che rappresenta il codice da ricercare. Il suo scopo è:
Ricerca del nodo con il codice = a quello passato come parametro
Restituisce il nodo in caso di buona riuscita, restituisce NULL in caso di non riuscita
int countCodiciPrenotaioni(codicePrenotazione *head) Riceve come parametro la lista codici. Il suo scopo è :
Contare i codici prenotazione di una stanza, per dare un indice count alla funzione per la scrittura.
void cancellaCodicePrenotazione(codicePrenotazione **,int) Riceve come parametro la lista codicePrenotazione ed un intero che rappresenta il codice da ricercare. Il suo scopo è :
Effettua una ricerca del codicePrenotazione, nel caso in cui venga trovato lo elimina TODO : Far richiamare la funzione ricercaCodiceStanza(...) ed eliminare quel nodo.
FUNZIONI PRENOTAZIONI
prenotazione * ricercaPrenotazione(prenotazione *, int) Riceve come paramentro un puntatore alla lista prenotazione, ed un intero che identifica il codicePrenotazione ricercato. Effettua una ricerca se la ricerca va a buon fine restituisce il nodo corrispondente
void changeData(prenotazione **,prenotazione) riceve come paramentro un puntatore alla lista prenotazione precedentemente trovato tramite l'utilizzo della funzione modificaPrenotazione(..), ed una variabile prenotazione. Serve a modificare il contenuto della prenotazione.
int ricercaData(prenotazione *, prenotazione) Riceve come parametro la lista prenotazione, ed una variabile prenotazione. Effettua un controllo con le date in questo seguente modo :

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

controlla dataI e dataF sia di pOld si di pNew e cerca di controllare i vari casi nel quale non si sovrappongono. Ritorna 0 se tutto va a buon fine, 1 se non è disponibile.
int editPrenotazione(stanza *,prenotazione,prenotazione *,int,int) Riceve la lista stanze, una variabile prenotazione, la lista prenotazione, un intero che identifica il codicePrenotazione ed un intero che identifica la modalità .
Effettua due ricerche, la prima di una stanza in base al numero di occupanti. La secondo sempre di una stanza in base alla disponibilità della data usando la funzione ricercaData(...) La ricerca per data viene effettuata finche la lista codicePrenotazione contenuta nel nodo stanza designato come papabile per capienza, effettua il confronto con ogni nodo che appartiene alla lista codicePrenotazione usufruendo della funzione ricercaPrenotazione(...) trova il nodo prenotazioni corrispondente e passa quello come paramentro da confrontare con la nuova prenotazione se in tutta la lista codicePrenotazione il confronto da esito positivo (cioè ritorna sempre 0) potrò dire che la mia prenotazione è andata a buon fine e verrà aggiunto il nodo prenotazione alla sua relativa lista ed il nodo codicePrenotazione alla sua relativa lista che è contenuta in un nodo stanza. Ritorna 0 se tutto a buon fine, Ritorna 1 se c'è un problema. Se nella modalità è impostata ad 1 modificherà i dati della prenotazione di appartenenza.
void addPrenotazione(prenotazione **,stanza *,int) Riceve come parametro un puntatore alla lista prenotazione, la lista stanza ed un intero che identifica il codicePrenotazione. Il suo scopo è :
Di fare I/O con l'stdin per i dati della nuova prenotazione
Richiamare la funzione creaPrenotazione(...)
Se la funzione creaPrenotazione(...) ritorna 0 inserisce in testa tramite la funzione inserimentoTestaP(...) un nodo prenotazione
Se la funzione creaPrenotazione(...) ritorna 1 stampa un messaggio d'errore
int checkPrenotazione(prenotazione *, codicePrenotazione *, prenotazione) Riceve la lista prenotazione, la lista codicePrenotazione ed una variabile prenotazione. Effettua un controllo nella lista codicePrenotazione tramite l'utilizzo della funzione ricercaPrenotazione(...) per trovare il nodo corrispondente al codice ricercato Tramite la funzione ricercaData(...) se la funzione restituisce 0 e la lista codicePrenotazione non ha successivo nullo, va al successivo e ripete da capo. Nel caso in cui la funzione ricercaData(...) restituisce 1 il ciclo si interrompe e la funzione checkPrenotazione(...) restituisce 1, in caso la ricerca vada a buon fine restituisce 0
void modificaPrenotazione(prenotazione *head,codicePrenotazione * stanza, int key) Riceve come parametro un puntatore alla lista prenotazione, la lista stanza ed un intero che identifica il codicePrenotazione. Il suo scopo è :
Di fare I/O con l'stdin per i dati della nuova prenotazione
**Richiamare la funzione ricercaPrenotazione(...) per avere il nodo interessato alla modifica **
Se la funzione checkprenotazione(...) ritorna 0 richiama la funzione changeData(...)
Se la funzione checkPrenotazione(...) ritorna 1 stampa un messaggio d'errore
La modifica può essere effettuata solamente alla data, per cambiare numero di occupanti occorre creare una nuova prenotazione
void cancellaPrenotazione(prenotazione **, int) Riceve come parametro un puntatore alla lista prenotazione ed un intero che identifica il codicePrenotazione. Il suo scopo è :
Ricerca il nodo con il codicePrenotazione passato come paramentro in caso lo trova lo elimina TODO : si potrebbe richiamare la funzione ricercaPrenotazione(...) ed eliminare il nodo che restituisce
prenotazione * prenotazioneTerminata(prenotazione *) Riceve come parametro una lista prenotazione il suo scopo : 
Controlla se la data globale è maggiore della dataI di un nodo. In caso si trova un nodo con la dataI < data restituisce il puntatore a quel nodo. In caso contrario restituisce NULL
int ricercaMaxCodice(prenotazione *) Riceve come parametro una lista prenotazione il suo scopo : 
Ricerca il codice più grande della lista prenotazione e lo restituisce.
FUNZIONI STANZA
stanza * ricercaStanzaPerNumero	(stanza *,int) Riceve come parametro la lista stanza ed un intero che rappresenta il numero della stanza. Il suo scopo è :
Ricerca del nodo con il numeroStanza uguale a quello passato come parametro
Restituisce il nodo in caso di buona riuscita, restituisce NULL in caso di non riuscita
stanza * ricercaPrenotazioneStanza(stanza * head,int key) Riceve come parametro la lista stanza ed un intero che rappresenta il codice da ricercare. Il suo scopo è :
Richiama la funzione ricercaCodiceStanza(...) finchè la funzione prima richiamata non restituisce un nodo diverso da NULL
Restituisce il nodo in caso di buona riuscita, restituisce NULL in caso di non riuscita
void InserimentoTastieraStanza(stanza **head) Riceve come parametro la lista stanza. Il suo scopo è : 
Permettere l’inserimento di una nuova stanza da tastiera.


FUNZIONI CLIENTE	
cliente * cercaCliente(cliente *,char[]) Riceve come parametro la lista clienti ed una stringa che rappresenta la CI. Il suo scopo :
Ricerca se esiste un cliente avente la CI passata come paramentro
Restituisce il puntatore al nodo se esiste, restituisce NULL se non esiste
cliente inserisciCliente(cliente *) Riceve come paramentro la lista clienti. Il suo scopo :
Di fare I/O con l'stdin per i dati del nuovo cliente
Controlla la sua esistenza
In caso non esista nessun cliente con quella CI restituisce il dato preso da I/O. In caso contrario restituisce NULL
int ricercaCodiceStorico(int,codicePrenotazione *) Riceve come parametro un intero che rappresenta il codice da ricercare e la lista codicePrenotazione riferita ad un nodo cliente. Il suo scopo è :
Ricercare se esiste un nodo codicePrenotazione esistente con il codice passato come parametro
Restituisce 0 se esiste, restituisce 1 se non esiste
void storicoClienti(prenotazione *,cliente *) Riceve come parametro un nodo prenotazione e la lista clienti. Il suo scopo è :
Tramite la funzione cercaCliente(...) cerca il cliente con la CI della prenotazione passata come parametro
Se esiste richiama la funzione ricercaCodiceStorico(...) se essa restituisce 0 richiama la funzione inserisciScorico(...) ed inserisce un codice nella lista codicePrenotazione inerente a quel cliente
Se non esiste stampa un messaggio d'errore

FUNZIONI I/O DA FILE
void letturaP() Il suo scopo è :
I/O da un file di nome prenotazioni.txt
void letturaS() Il suo scopo è :
Versione noFile
vedi InserimentoTastieraStanze(..)
Versione File
I/O da un file di nome stanze.txt
Effettua un inserimento ordinato in base al numeroStanza
void letturaC() Il suo scopo è :
I/O da un file di nome clienti.txt
void salvaCliente(cliente * head) Riceve in ingresso una lista clienti. Il suo scopo è :
I/O da un file di nome clienti.txt
void salvaStanze(stanze *) Riceve in ingresso una lista stanze. Il suo scopo è :
I/O da un file di nome stanze.txt
void salvaPrenotazione(prenotazione *) Riceve in ingresso una lista prenotazione. Il suo scopo è :
I/O da un file di nome prenotazioni.txt


	


