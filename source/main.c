#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/****** STRUTTURE DATI *****/

typedef struct prenotazione{    
    int dataI;
    int dataF;
    int occupanti;
    int codice;
    int finita;
    char CI[8];
    struct prenotazione * next;  
}prenotazione;

typedef struct codicePrenotazione{
    int codice; 
    struct codicePrenotazione * next;
}codicePrenotazione;

typedef struct cliente{
    char nome[17];
    char cognome[17];
    char CI[11];
    char CF[18];
    int dataNascita;
    codicePrenotazione * storico;
    struct cliente * next;
}cliente;

typedef struct stanza{
    int numeroStanza;
    int occupantiM;
    codicePrenotazione * future;
    struct stanza * next;
}stanza;

int data = 20200601;

/************************************************************************************************/
/******* INSERIMENTO LISTE **********************************************************************/

void inserimentoTestaCliente(cliente **head, cliente c,codicePrenotazione * storico){//inserisce in testa ogni cliente
    cliente *p;
    p = malloc(sizeof(cliente));
    strcpy(p->nome,c.nome);
    strcpy(p->cognome,c.cognome);
    strcpy(p->CF,c.CF);
    p->dataNascita = c.dataNascita;
    strcpy(p->CI,c.CI);
    p->storico = storico;
    p->next=*head;
    *head=p;
}

void inserimentoStorico(codicePrenotazione **head, int elem){//inserisce in testa il codice storico
    codicePrenotazione *q;
    q = (codicePrenotazione*)malloc(sizeof(codicePrenotazione));
    q->codice = elem;
    q->next=*head;
    *head=q; 
}

prenotazione * inserimentoTestaP(prenotazione **head, prenotazione dato){//inserisce in testa ogni prenotazione
    prenotazione *q;
    q = (prenotazione*)malloc(sizeof(prenotazione));
    q->occupanti=dato.occupanti;
    q->codice = dato.codice;
    q->dataI = dato.dataI;
    q->dataF = dato.dataF;
    strcpy(q->CI,dato.CI);
    q->finita = dato.finita;
    q->next=*head;
    *head=q;
    return *head;
}

void InserisciOrdinatoS(stanza **head, stanza elem,codicePrenotazione * codice){//Inserisce in modo ordinato le stanze. Le stanze sono ordinate per numero
    stanza *p; /*elemento da inserire*/
    stanza *r = *head, *q = *head; /* predecessore e successore */
    p = (stanza *) malloc(sizeof(stanza));
    p->occupantiM = elem.occupantiM;
    p->numeroStanza = elem.numeroStanza;
    p->future = codice;
    while ((q != NULL) && (q->numeroStanza < p->numeroStanza)){ /* trova il punto di inserimento */
        r = q;
        q = q->next;
    }
    if(q==*head){/* inserimento in testa */
        *head=p;
    }else{
        r->next = p;
    }
    p->next = q;
}

/************************************************************************************************/
/********* FUNZIONI CODICE PRENOTAZIONE *********************************************************/

void cancellaCodicePrenotazione(codicePrenotazione **head,int key){//cancella un codice prenotazione
    codicePrenotazione *q = *head, *r = *head; /* predecessore e successore */
    while ((q != NULL) && (q->codice != key)){
        r = q;
        q = q->next;
    }
    if (q == NULL){
        printf("Codice prenotazione inesistente \n");
        return; /*l'elemento non esiste */
    }
    if (q==*head){ /*l'elemento da cancellare è il primo */
        *head = (*head)->next;
    }else{
        r->next = q->next;
    }
    printf("Cancellazione riuscita del codice prenotazione riuscito\n");
    free(q); /* cancella */
} 

codicePrenotazione * ricercaCodice(codicePrenotazione *head, int key){//ricerca un codice prenotazione
    if(head!=NULL){
        while(head !=NULL){
            if(head -> codice == key){//SONO UGUALI
                return head;
            }else{//PORTO AVANTI LE PRENOTAZIONI
                head= head->next;
            }
        }
    }
    return NULL;//NESSUNA STANZA CON QUEL CODICE NON CI SONO PRENOTAZIONI PER QUELLA STANZA
}

int countCodiciPrenotaioni(codicePrenotazione *head){//conta i codiciPrenotazione
    int count = 0;
    if(head!=NULL){
        while(head!=NULL){
            count++;
            head = head->next;
        }
    }
    return count;
}

/**********************************************************************************************/
/*********** FUNZIONI PRENOTAZIONE ************************************************************/

void changeData(prenotazione **head,prenotazione p){//modifica i dati di un determinato nodo
    prenotazione * q = *head;
    while(q!=NULL){
        if(q->codice == p.codice){
            q->dataI = p.dataI;
            q->dataF = p.dataF;
            return;
        }else{
            q=q->next;
        }
    }
}

prenotazione * ricercaPrenotazione(prenotazione * prenotati, int codice){//ricerca la prenotazione per codice
        while(prenotati != NULL ){//DATO CHE CODICE È UNA LISTA DEVO PERCORRERLA ANCHE QUELLA TUTTA
            if(prenotati -> codice == codice){//SONO UGUALI
                return prenotati;
            }else{//PORTO AVANTI LE PRENOTAZIONI
                prenotati= prenotati->next;
            }
        }
    return NULL;//NESSUNA STANZA CON QUEL CODICE NON CI SONO PRENOTAZIONI PER QUELLA STANZA
}

int ricercaData(prenotazione * pOld, prenotazione pNew){//ricerca la data corretta dove inserire
    
    if((pOld->dataI<pNew.dataI)&&(pOld->dataF<pNew.dataI)&&(pOld->dataF<pNew.dataF)&&(pOld->dataI<pNew.dataF)){
        /*
         *      pOld        pNew
         *      5 - 7      8 - 9
         *      5 < 8
         *      7 < 8
         *      5 < 9
         *      7 < 9
         *      Significa che la stanza in quei giorni dato che sono successivi è libera
         *      pOld < pNew significa successivo
         */
        return 0;
    }else if((pOld->dataI>pNew.dataI)&&(pOld->dataF>pNew.dataI)&&(pOld->dataF>pNew.dataF)&&(pOld->dataI>pNew.dataF)){
            /*
            *      pOld        pNew
            *      5 - 7      3 - 4
            *      5 > 3
            *      7 > 3
            *      5 > 4
            *      7 > 4     
            *      Significa che la stanza in quei giorni dato che sono precedenti è libera
            *      pOld > pNew significa precedente
            */
        return 0;        
    }      
    /*
     * Se anche solo uno dei quattro casi non è verificato significa che le date sono sovrapposte il sistema va alla prossima stanza 
     * 
     */
    return 1;
}

int editPrenotazione(stanza *headS,prenotazione p,prenotazione *prenotati,int codice,int mode){//Ricerca la stanza con gli occupanti necessari per contenere quella prenotazione.
    stanza *stanza =  headS, * temp = headS;
    codicePrenotazione * listaCodici;
    prenotazione * pOld;
    while(stanza!=NULL){ 
        if(stanza->occupantiM >= p.occupanti){ 
            listaCodici = stanza->future;// LA CAPIENZA 
            if(listaCodici!=NULL){
                while(listaCodici!=NULL){
                    pOld = ricercaPrenotazione(prenotati,listaCodici->codice);
                    if(ricercaData(pOld,p)==0){             
                        if(listaCodici->next ==NULL){
                            inserimentoStorico(&temp->future,codice);
                            printf("La prenotazione andata a buon fine per la stanza %d con codice : %d\n",temp->numeroStanza,temp->future->codice);
                            if(mode != 0){
                                changeData(&prenotati,p);
                            }
                            return 0;
                        }else{
                            listaCodici = listaCodici -> next;
                        }
                    }else{
                        stanza = stanza->next;  //servono perchè poi esco dal ciclo
                        temp = temp->next;
                        break;                        
                    }
                }
            }else{
                inserimentoStorico(&temp->future,codice);
                printf("La prenotazione andata a buon fine per la stanza %d con codice : %d \n",temp->numeroStanza,temp->future->codice);
                return 0;
            }
        }else{
            stanza=stanza->next;    // GO NEXT PER LA CAPIENZA
            temp = temp-> next;
        }  
    }
    printf("Nessuna stanza disponibile\n");
    return 1;//RITORNA FAIL
}

void addPrenotazione(prenotazione **head,stanza *headS,int cod){//Serve per aggiungere tutti i dati di una prenotazione.
    prenotazione p;
    p.codice=cod;
    p.finita=0; 
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
    printf("Carta d'identità cliente : \t");
    fgets(p.CI,8,stdin);
    printf("Occupanti : \t ");
    scanf("%d",&p.occupanti);
    printf("FORMATO YYYYMMGG\n");
    printf ("Inserisci l'inizio del pernottamento : \t");  
    scanf("%d",&p.dataI);
    printf ("Inserisci l'fine del pernottamento : \t");
    scanf("%d",&p.dataF);
    
    if(p.dataI>p.dataF){
        printf("Controllare le date\n");
        return;
    }
    if(editPrenotazione(headS,p,*head,cod,0)==0){//SE TUTTA LA RICERCA DELLA STANZA È ANDATA A BUON FINE INSERISCE LA PRENOTAZIONE
        *head = inserimentoTestaP(head,p);
    }
}

void modificaPrenotazione(prenotazione *head,stanza * s,stanza * vecchia, int key){//modifica una vecchia prenotazione
    prenotazione p;
    p.codice = key;
    p.finita=0; 
    printf("Occupanti : \t ");
    scanf("%d",&p.occupanti);
    printf("FORMATO YYYYMMGG\n");
    printf ("Inserisci l'inizio del pernottamento : \t");
    /* LETTURA DATA  GG/MM/YYYY */
    scanf("%d",&p.dataI);
    printf ("Inserisci l'fine del pernottamento : \t");
    /* LETTURA DATA  GG/MM/YYYY */
    scanf("%d",&p.dataF); 
    if(p.dataF<p.dataI){
        printf("Controllare le date\n");
        return;
    }
    if(editPrenotazione(s,p,head,key,1)==0){
        cancellaCodicePrenotazione(&vecchia->future,key);
        printf("Modifica andata a buon fine \n");
    }else{
        printf("Modifica fallita, date non disponibile\n");
    }
}

void cancellaPrenotazione(prenotazione **head, int key){ //cancella una prenotazione
    prenotazione *q = *head, *r = *head; /* predecessore e successore */
    while ((q != NULL) && (q->codice != key)){
        r = q;
        q = q->next;
    }
    if (q == NULL){
        printf("Prenotazione inesistente \n");
        return; /*l'elemento non esiste */
    }
    if (q==*head){ /*l'elemento da cancellare è il primo */
        *head = (*head)->next;
    }else{
        r->next = q->next;
    }
    printf("Cancellazione della prenotazione riuscita \n");
    free(q); /* cancella */
} 

prenotazione * prenotazioneTerminata(prenotazione * head){//cerca le prenotazioni terminate
    while(head!=NULL){
        if(head->dataF<data){
            return head;
        }else{
            head = head->next;
        }
    }
    return NULL;
}

int ricercaMaxCodice(prenotazione *head){//ricerca il max dei codici
    int max = 0;
    if(head!=NULL){
        while(head!=NULL){
            if(head->codice > max){
                max = head->codice;
            }else{
                head = head->next;
            }
        }
    }
    return max+1;
}

/*****************************************************************************************/
/******** FUNZIONI STANZA *********************************************************************/

stanza * ricercaStanzaPerNumero(stanza *headS,int numeroStanza){//Ricerca la stanza che possiede il numero di stanza passato come paramentro e ritorna il puntatore a quel nodo 
    stanza *stanza =  headS;
        while(stanza!=NULL){
            if(stanza->numeroStanza == numeroStanza){
                return stanza;
            }else{
                stanza = stanza->next;
            }
        }
        return NULL;
}

stanza * ricercaPrenotazioneStanza(stanza * head,int key){//ricerca la prenotazione in base al codice
    while(head!=NULL){
        codicePrenotazione * p = ricercaCodice(head->future,key);
        if(p!=NULL){
            return head;
        }else{
            head = head->next;
        }        
    }
    return NULL;
}

void  InserimentoTastieraStanza(stanza **head){//serve all'inserimento da tastiera per le stanze
    stanza p;
    printf("Numero della stanza\n");
    scanf("%d",&p.numeroStanza);
    if(ricercaStanzaPerNumero(*head,p.numeroStanza)==NULL){
        printf("Numero degli occupanti max \n");
        scanf("%d",&p.occupantiM);
        InserisciOrdinatoS(head,p,NULL);
    }else{
        printf("Stanza gia' esistente\n");
    }
}

/*****************************************************************************************/
/*********** FUNZIONI CLIENTE ************************************************************/

cliente * cercaCliente(cliente *head,char dato[]){// Ricerca il cliente in base alla carta d'identita'
    while(head!=NULL){
        if(strcmp(head->CI,dato)==0){  
            return head;        
        }else{
            head=head->next;
        }
    }
    return NULL;                                  //SE DIVERSI TORNA 1
}

void inserisciCliente(cliente **head){//Inserimento del cliente e dei suoi rispettivi dati
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
    cliente c;
    printf("Nome : ");
    fgets(c.nome,16,stdin);
    printf("Cognome : ");
    fgets(c.cognome,16,stdin);
    printf("Codice Fiscale : ");
    fgets(c.CF,18,stdin);
    printf("Carta d'identita': ");
    fgets(c.CI,11,stdin);
    printf("Data di nascita : ");
    scanf("%d",&c.dataNascita);
    while ((ch = getchar()) != '\n' && ch != EOF);
    if(cercaCliente(*head,c.CI)==NULL){
        inserimentoTestaCliente(head,c,NULL);
        printf("Inserimento andato a buon fine \n");
    }else{
        printf("Il cliente esiste già\n");   
    }
}

int storicoClienti(prenotazione *headP,cliente *headC){
    prenotazione *p = prenotazioneTerminata(headP);
    if (p != NULL){
        if(p->finita==0){
            cliente * tmp = cercaCliente(headC, p->CI);
            if(tmp!=NULL){
                p->finita = 1;
                inserimentoStorico(&tmp->storico, p->codice);
                return 0;
            }else{
                printf("Cliente inesistente\n");
                return 1;
            }
        }else{
            return 1;
        }
    }else{
        printf("Nessuna prenotazione si è conclusa oggi \n ");
        return 1;
    }
}

/*****************************************************************************************/
/********* STAMPA ************************************************************************/

void stampaS(stanza *head){//Stampa le stanze e la loro capienzaMax
    int i=1;
    if(head!=NULL){
        while(head!=NULL){
            printf("\t\t||||||||||| INIZIO STANZA |||||||||||\n");
            printf("\t\tNumero stanza : %d \n",head->numeroStanza );
            printf("\t\tOccupanti Max : %d \n",head->occupantiM );
            printf("\t\t||||||||||| FINE STANZA |||||||||||\n");
            head= head->next;
            i++;
        }
    }else{
        printf("\t\tNessuna stanza disponibile \n");        
    }
}

void stampaPrenotazioniStanza(stanza *head,int numeroStanza){//Stampa lo stato di una determinata stanza
    stanza * s = ricercaStanzaPerNumero(head,numeroStanza);
    if(s!=NULL){
        codicePrenotazione * p = s -> future;
    
        printf("\t\tLe prenotazioni della stanza %d sono : \n",s->numeroStanza );
        if(p!=NULL){
            printf("\t\t||||||||||| INIZIO CODICI PRENOTAZIONE |||||||||||\n");
            while(p!=NULL){
                printf("\t\t\tCodice prenotazione stanza : %d \n",p->codice );
                p = p->next;
            }
            printf("\t\t||||||||||| FINE CODICI PRENOTAZIONE |||||||||||\n");
        }else{
                printf("\t\tNessuna prenotazione per questa stanza \n");                    
            }  
    }else{
        printf("\t\tStanza inesistente\n");        
    }
}

void stampaC(cliente *head){//Stampa tutti i clienti
    int i=1;
    if(head!=NULL){
        while(head!=NULL){
            printf("\t\t||||||||| INIZIO CLIENTE |||||||||\n");
            printf("\t\tCliente numero %d\n",i);
            printf("\t\tNome : %s",head->nome );
            printf("\t\tCognome : %s",head->cognome );
            printf("\t\tCodice Fiscale : %s",head->CF );
            printf("\t\tCarta d'identita : %s",head->CI);
            printf("\t\tData di nascita : %d\n",head->dataNascita );
            codicePrenotazione * listaCodici = head->storico;
            if(listaCodici!=NULL){
                printf("\t\t||||||||| INIZIO PRENOTAZIONI PASSATE |||||||||\n");
                while(listaCodici!=NULL){
                    printf("\t\t\tCodice prenotazione %d \n",listaCodici->codice);
                    listaCodici = listaCodici->next;
                }
                printf("\t\t||||||||| FINE PRENOTAZIONI PASSATE |||||||||\n");
            }
            printf("\t\t||||||||| FINE CLIENTE |||||||||\n\n");
            head= head->next;
            i++;
        }
    }else{
          printf("\t\tNessun cliente disponibile\n");  
    }
}

void stampaP(prenotazione *head){//Stampa lo storico di tutte le prenotazioni
    int i=1;
    if(head!=NULL){
        while(head!=NULL){
            printf("\t\t||||||||||| PRENOTAZIONE |||||||||||\n");
            printf("\t\tCodice della %d prenotazione : %d \n",i,head->codice );
            printf("\t\tOccupanti prenotazione %d : %d \n",i,head->occupanti );
            printf("\t\tData inzio pernottamento %d\n",head->dataI);
            printf("\t\tData fine pernottamento : %d\n",head->dataF);
            printf("\t\tCarta d'identita del cliente :%s\n",head->CI);
            printf("\t\tFinita : %d\n",head->finita);
            printf("\t\t|||||||||||||||||||||||||||||||||\n");
            head= head->next;
            i++;
        }
    }else{
        printf("Nessuna prenotazione disponibile\n");
    }
}

void stampaDisponibilita(prenotazione *head,stanza * headS,int dataI,int dataF){//stampa la disponibilità
    prenotazione p;
    stanza * s;
    int check = 0;
    p.dataI = dataI;
    p.dataF = dataF;
    if(head!=NULL){
        while(head!=NULL){
            if(head->finita!=1){
                s = ricercaPrenotazioneStanza(headS,head->codice);
                if(ricercaData(head,p)!=0){ 
                    printf("\t\tQuesta stanza non e' libera : %d\n",s->numeroStanza);
                    check = 1;
                }
            }
            head = head->next;       
        }
    }
    if(check==0){
        printf("\t\tTutte le stanze sono disponibili\n");
    }
}

/*****************************************************************************************/
/******** MENU' SPECIFICI*****************************************************************/

void menuCliente(cliente **head){
    int choose;
    do{     
        
        printf("Effettua la tua scelta : \n");
        printf(" 1 - Inserisci Cliente\n");
        printf(" 2 - Stampa Cliente\n");
        printf(" 0 - Esci\n");
        scanf("%d",&choose);
        switch(choose){
            case 1 : { //Inserimento cliente e relativa prenotazione
                inserisciCliente(head); 
                break;
            }
            case 2 : {//Inserimento prenotazione per cliente esistente
                stampaC(*head);
                break;
            }
            case 0 :{//Uscita
                printf("Uscita menu cliente\n");
                break;
            }
        }
    }while(choose!= 0); 
}

void menuPrenotazione(prenotazione **head,stanza **headS,int * codice){
    int choose;
    int key;
    do{     
        
        printf("Effettua la tua scelta : \n");
        printf(" 1 - Inserisci prenotazione\n");
        printf(" 2 - Modifica prenotazione\n");
        printf(" 3 - Elimina prenotazione\n");
        printf(" 4 - Stampa prenotazione\n");
        printf(" 0 - Esci\n");
        scanf("%d",&choose);
        switch(choose){
            case 1 : { 
                addPrenotazione(head,*headS,*codice);
                (*codice)++;
                break;
            }
            case 2 : {
                if(*head!=NULL){
                    printf("Si prega di fornire il codice della prenotazione : \t");
                    scanf("%d",&key);
                    stanza * s = ricercaPrenotazioneStanza(*headS,key);
                    if(s!=NULL){
                        modificaPrenotazione(*head,*headS,s,key);
                    }else{
                        printf("Nessuna stanza presente con quella prenotazione, probabilmente sara' terminata. E' impossibile cancellare una prenotazione terminata\n");
                    }
                }else{
                    printf("Nessuna prenotazione esistente \n");
                }         
                break;
            }
            case 3 : {
                if(*head!=NULL){
                    printf("Si prega di fornire il codice della prenotazione : ");
                    scanf("%d",&key);
                    stanza * s = ricercaPrenotazioneStanza(*headS,key);
                    if(s!=NULL){
                        cancellaPrenotazione(head,key);//Cancella la prenotazione con il codice corrispondente
                        cancellaCodicePrenotazione(&s->future,key);                                 
                    }else{
                        printf("Nessuna stanza presente con quella prenotazione, probabilmente sara' terminata. E' impossibile cancellare una prenotazione terminata\n");           
                    }
                }else{
                    printf("Nessuna prenotazione esistente\n");                    
                }
                break;
            }
            case 4 : {
                stampaP(*head);
                break;
            }
            case 0 :{//Uscita
                printf("Uscita dal menu prenotazione\n");
                break;
            }
        }
    }while(choose!= 0); 
}

void menuStanza(stanza * head,prenotazione * headP){
    int choose;
    int key;
    int dataI;
    int dataF;
    do{     
        
        printf("Effettua la tua scelta : \n");
        printf(" 1 - Stampa tutte le stanze\n");
        printf(" 2 - Stampa lo storico di una stanza\n");
        printf(" 3 - Stampa disponibilita' stanza\n");
        printf(" 4 - Inserisci Stanza\n");
        printf(" 0 - Esci\n");
        scanf("%d",&choose);
        switch(choose){
            case 1 : { //Inserimento cliente e relativa prenotazione
                stampaS(head);
                break;
            }
            case 2 : {//Inserimento prenotazione per cliente esistente
                printf("Inserire il numero della stanza :\t");
                scanf("%d",&key);
                stampaPrenotazioniStanza(head,key);
                break;
            }
            case 3 : { //Inserimento cliente e relativa prenotazione
                printf("Immettere dataInizio YYYYMMGG\n");
                scanf("%d",&dataI);
                printf("Immettere dataFine YYYYMMGG\n");
                scanf("%d",&dataF);
                if((dataI<dataF)){          
                    /*  dataI < dataF
                          4   <   6     OK
                          5   <   4     NO
                        dataI > data
                          4   >   3     OK
                          4   <   5     NO
                        dataF > data 
                          6   >   3     OK
                          6   <   8     NO                    
                    */
                   stampaDisponibilita(headP,head,dataI,dataF);
                }else{
                    printf("Controllare le date poichè errate\n");
                }
                break;
            }
            case 4:{
                    InserimentoTastieraStanza(&head);
                    break;
            }
            case 0 :{//Uscita
                printf("Uscita dal menu stanza\n");
                break;
            }
        }
    }while(choose!= 0); 
}

/*****************************************************************************************/
/******** LETTURA ************************************************************************/

stanza *letturaS(){//Legge da file tutte le stanze. Si potrebbe modificare per far si che l'utente decida da che file far leggere le stanze
	FILE *f = fopen("stanze.txt","r");
    stanza dato;
    stanza *head;
    int count;
    int num;
    head=NULL;
	if(f==NULL){
		printf("ERRORE forse il file stanze.txt non esiste\n");
		exit(1);	//Uscita programma con codice 1 quindi non apertura del file
	}else{
		while(fscanf(f,"%d%d\n%d",&(dato.numeroStanza),&(dato.occupantiM),&count)!= EOF){
            codicePrenotazione * p = NULL;
            if(count!=0){ 
                for(int j = 0;j<count;j++){
                    fscanf(f,"%d\n",&num);
                    inserimentoStorico(&p,num);
                }
            }
            dato.future = p;
            InserisciOrdinatoS(&head,dato,p); 
    	}
	}
	return head;
}

prenotazione * letturaP(){//legge da file tutte le prenotazioni
    FILE *f = fopen("prenotazioni.txt","r");
    prenotazione dato;
    prenotazione *head;
    char * buffer = malloc( 100 * sizeof(char)); 
    head= NULL;
	if(f==NULL){
		printf("ERRORE forse il file prenotazioni.txt non esiste\n");
		exit(1);	//Uscita programma con codice 1 quindi non apertura del file
	}else{
		while(fscanf(f,"%d%d%d%d%d%s\n",&(dato.codice),&(dato.dataI),&(dato.dataF),&(dato.occupanti),&(dato.finita),buffer)!= EOF){
            strcpy(dato.CI,buffer);
            head = inserimentoTestaP(&head,dato);   

    	}
	}
	return head; 
}

cliente * letturaC(){ //legge da file tutti i clienti
    FILE *f = fopen("clienti.txt","r");
    cliente dato;
    cliente *head;
    int count=0;
    int num;
    head= NULL;
	if(f==NULL){
		printf("ERRORE forse il file clienti.txt non esiste\n");
		exit(1);	//Uscita programma con codice 1 quindi non apertura del file
	}else{
        while(!feof(f)){
            fgets(dato.nome, sizeof(dato.nome), f);
            fgets(dato.cognome, sizeof(dato.cognome),f);
            fgets(dato.CF, sizeof(dato.CF),f);
            fgets(dato.CI, sizeof(dato.CI),f);
            fscanf(f,"%d\n",&dato.dataNascita);
            fscanf(f,"%d\n",&count);
            codicePrenotazione * p = NULL;
            if(count!=0){ 
                for(int j = 0;j<count;j++){
                    fscanf(f,"%d\n",&num);
                    inserimentoStorico(&p,num);
                }
            }
            inserimentoTestaCliente(&head,dato,p);
        }
	}
	return head; 
}

void file(stanza **headS,cliente ** headC, prenotazione ** headP){//è un driver per fare tutte le letture
    *headS = letturaS();
    *headP = letturaP();
    *headC = letturaC();
}

/*****************************************************************************************/
/**************************** SALVA ******************************************************/

void salvaCliente(cliente * head){//salva i clienti su di un file
    FILE * output;
    int zero = 0;
    if(output=fopen("clienti.txt" ,"w")){
        printf("\t\tSalvataggio cliente in corso\n");
            while(head!=NULL){  
                fprintf(output,"%s%s%s%s%d\n",head->nome,head->cognome,head->CF,head->CI,head->dataNascita);
                codicePrenotazione * p = head->storico;
                if(p!=NULL){
                    int count = countCodiciPrenotaioni(p);
                    fprintf(output,"%d\n",count);
                    while(p!=NULL){
                        fprintf(output,"%d\n",p->codice);
                        p=p->next;
                    }
                }else{
                    fprintf(output,"%d\n",zero);
                    printf("\t\tNessuna prenotazione per questo cliente \n ");
                }
                head=head->next;
            }
    }else{
        printf("ERRORE nella scrittura sul file clienti.txt, controllare i permessi\n");
        return;
    }
    printf("\t\tSalvataggio cliente completato \n");
    fclose(output);
}

void salvaStanza(stanza * head){//salva le stanze su di un file
    FILE * output;
    int zero=0;
    if(output=fopen("stanze.txt" ,"w")){
        printf("\t\tSalvataggio stanza in corso \n");
        while(head!=NULL){  
            fprintf(output,"%d\t",head->numeroStanza);
            fprintf(output,"%d\n",head->occupantiM);
            codicePrenotazione * p = head->future;
            if(p!=NULL){
                int count = countCodiciPrenotaioni(p);
                fprintf(output,"%d\n",count);
                while(p!=NULL){
                    fprintf(output,"%d\n",p->codice);
                    p=p->next;
                }
            }else{
                fprintf(output,"%d\n",zero);
                printf("\t\tNessuna prenotazione per questa stanza \n ");
            }
            head=head->next;
        }
    }else{
         printf("\n\nERRORE nella scrittura del file stanze.txt , controllare i permessi\n\n");
         return;
    }	
    printf("\t\tSalvataggio stanza completato \n");
    fclose(output);
}

void salvaPrenotazione(prenotazione * head){//salva le prenotazioni su di un file
    FILE * output;
    if(output=fopen("prenotazioni.txt" ,"w")){
        printf("\t\tSalvataggio prenotazioni in corso \n");
        while(head!=NULL){  
                    fprintf(output,"%d\t",head->codice);
                    fprintf(output,"%d\t",head->dataI);
                    fprintf(output,"%d\t",head->dataF);
                    fprintf(output,"%d\t",head->occupanti);
                    fprintf(output,"%d\t",head->finita);
                    fprintf(output,"%s\n",head->CI);
                    head=head->next;
        }
    }else{
         printf("\n\nERRORE nella scrittura del file prenotazioni.txt, controllare i permessi\n\n");
         return;
    }	
    printf("\t\tSalvataggio prenotazioni completato \n");
    fclose(output);
}

/*****************************************************************************************/
/********* DATA **************************************************************************/

void terminazione(prenotazione * tmp,stanza * headS, cliente * headC){//sposta la prenotazione da stanze -> future a cliente ->storico
        while(tmp !=NULL){
            int ok = storicoClienti(tmp,headC);
            if(ok==0){
                stanza * s = ricercaPrenotazioneStanza(headS,tmp->codice);
                if(s!=NULL){
                    cancellaCodicePrenotazione(&s->future,tmp->codice);          
                }
            }
            tmp = tmp->next;
        }
}

void letturaData(){
    FILE *f = fopen("data.txt","r");
	if(f==NULL){
		printf("ERRORE forse il file data.txt non esiste\n");
		exit(1);	//Uscita programma con codice 1 quindi non apertura del file
	}else{
		while(fscanf(f,"%d\n",&data)!= EOF){}
	}
}

void salvaData(){
    FILE * output;
    if(output=fopen("data.txt" ,"w")){ 
        fprintf(output,"%d\t",data);
    }else{
         printf("ERRORE nella scrittura del file data.txt, controllare i permessi \n");
         return;
    }	
    fclose(output);
}

/**********************************************************************/
/*********************** MENU *****************************************/

void menu(){
    int choose; 
    stanza * headS = NULL;
    cliente *headC = NULL;
    prenotazione *headP = NULL;
    printf("Devo leggere dati da file? \n 1 - Si \n 0 - No\n");
    scanf("%d",&choose);
    if(choose == 1){
        file(&headS,&headC,&headP);        
    }else{
        printf("Vuoi leggere solamente le stanze e la data? \n 1 - Si\n 0 -  No  \n");
        scanf("%d",&choose);
        if(choose == 1){
            headS = letturaS();
            letturaData();
        }else{
            while(choose != -1){
                InserimentoTastieraStanza(&headS);
                printf("Per terminare inserire -1 \n");
                scanf("%d",&choose);
            }
        }
    }
    
    choose = -1;
    int codice = ricercaMaxCodice(headP); 
    do{    
         
        printf("Effettua la tua scelta : \n");
        printf(" 1 - Menu Cliente\n");
        printf(" 2 - Menu Prenotazione\n");
        printf(" 3 - Menu Stanza\n");
        printf(" 4 - Andare avanti di giorno\n");
        printf(" 5 - Salvataggio\n");
        printf(" 0 - Esci\n");
        scanf("%d",&choose);
        switch(choose){
            case 1 : { //Inserimento cliente e relativa prenotazione
                menuCliente(&headC);
                break;
            }
            case 2 : {//Inserimento prenotazione per cliente esistente
                menuPrenotazione(&headP,&headS,&codice);
                break;
            }
            case 3 :{//Stampa lista clienti
                menuStanza(headS,headP);
                break;
            }
            case 4 :{
                data = data+1;
                if(data == 20200631){
                    data = 20200701;
                }
                printf("Data nuova e' %d \n",data);
                terminazione(headP,headS,headC);
                break;
            }
            case 5 :{
                printf("\n\n");
                salvaPrenotazione(headP);
                salvaCliente(headC);
                salvaStanza(headS);
                salvaData();
                printf("\n\n");
                break;
            }
            case 0 :{//Uscita
                printf("Arrivederci\n");
                break;
            }
        }
    }while(choose!= 0);
}

/*****************************************************************************************/
/******** MAIN ***************************************************************************/

int main(){
    menu();
}
