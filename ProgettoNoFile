#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/****** STRUTTURE DATI *****/
typedef struct tm * date;
typedef struct prenotazione{    
    int dataI;
    int dataF;
    int occupanti;
    int numeroStanza;
    int codice;
    char CI[8];
    struct prenotazione * next;  
}prenotazione;
typedef struct codicePrenotazione{
    int codice; 
    struct codicePrenotazione * next;
}codicePrenotazione;
typedef struct cliente{
    char nome[30];
    char cognome[30];
    char CI[8];
    char CF[20];
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
int data = 20200515;
/************************************************************************************************/
/******* CREAZIONI LISTE ************************************************************************/

stanza *crea_listaStanza(stanza s){ //Crea la lista stanza 
    stanza *head;
    head= (stanza*)malloc(sizeof(stanza));
    head->occupantiM = s.occupantiM;
    head->numeroStanza = s.numeroStanza;
    head->next=NULL;
    return head;
}
prenotazione *crea_listaPrenotazione(){ //Crea la lista prenotazione 
    prenotazione *head;
    head= (prenotazione*)malloc(sizeof(prenotazione));
    head->occupanti = 0;
    head->numeroStanza = 0;
    head->next=NULL;
    return head;
}
void inserimentoTestaCliente(cliente **head, cliente c){//inserisce in testa ogni cliente
    cliente *p;
    p = (cliente*)malloc(sizeof(cliente));
    strcpy(p->nome,c.nome);
    strcpy(p->CI,c.CI);
    p->next=*head;
    *head=p;
}
void  inserimentoStorico(codicePrenotazione **head, int elem){
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
    q->next=*head;
    *head=q;
    return *head;
}

void changeData(prenotazione **head,prenotazione p){
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

/**********************************************************************************************/
/*********** FUNZIONI PRENOTAZIONE ************************************************************/

prenotazione * ricercaPrenotazione(prenotazione * prenotati, int codice){
        while(prenotati != NULL ){//DATO CHE CODICE È UNA LISTA DEVO PERCORRERLA ANCHE QUELLA TUTTA
            if(prenotati -> codice == codice){//SONO UGUALI
                return prenotati;
            }else{//PORTO AVANTI LE PRENOTAZIONI
                prenotati= prenotati->next;
            }
        }
    return NULL;//NESSUNA STANZA CON QUEL CODICE NON CI SONO PRENOTAZIONI PER QUELLA STANZA
}

int ricercaData(prenotazione * pOld, prenotazione pNew){
    
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
int creaPrenotazione(stanza *headS,prenotazione p,prenotazione *prenotati,int codice){//Ricerca la stanza con gli occupanti necessari per contenere quella prenotazione.
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
                            printf("Prenotazione va bene\n");
                            return 0;
                        }else{
                            listaCodici = listaCodici -> next;
                        }
                    }else{
                        stanza = stanza->next;
                        temp = temp->next;
                        break;                        
                    }
                }
            }else{
                inserimentoStorico(&temp->future,codice);
                printf("Prenotazione ok\n");
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
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
    printf("Carta d'identità cliente\t");
    fgets(p.CI,8,stdin);
    printf("Occupanti:\t ");
    scanf("%d",&p.occupanti);
    printf ("Inserisci l'inizio del pernottamento:\t");
    printf("FORMATO YYYYMMGG\t");
    /* LETTURA DATA  GG/MM/YYYY */
    scanf("%d",&p.dataI);
    printf ("Inserisci l'fine del pernottamento:\t");
    /* LETTURA DATA  GG/MM/YYYY */
    scanf("%d",&p.dataF);
    
    if(p.dataF<p.dataI){
        printf("La fine non può essere prima dell'inzio \n");
        return;
    }
    if(creaPrenotazione(headS,p,*head,cod)==0){//SE TUTTA LA RICERCA DELLA STANZA È ANDATA A BUON FINE INSERISCE LA PRENOTAZIONE
        *head = inserimentoTestaP(head,p);
    }
}
int checkPrenotazione(prenotazione *head, codicePrenotazione * nextPrenotazione , prenotazione p){
    prenotazione * pOld;
    while(nextPrenotazione!=NULL){
                    pOld = ricercaPrenotazione(head,nextPrenotazione->codice);
                    if(ricercaData(pOld,p)==0){
                        if(nextPrenotazione->next !=NULL){
                            nextPrenotazione = nextPrenotazione->next;
                        }else{
                            return 0;
                        }
                    }else{
                        break;
                    }
    }
    return 1;
}
void modificaPrenotazione(prenotazione *head,codicePrenotazione * stanza, int key){
 
    prenotazione p;
    p.codice = key;
    printf("FORMATO YYYYMMGG\t");
    printf ("Inserisci l'inizio del pernottamento:\t");
    /* LETTURA DATA  GG/MM/YYYY */
    scanf("%d",&p.dataI);
    printf ("Inserisci l'fine del pernottamento:\t");
    /* LETTURA DATA  GG/MM/YYYY */
    scanf("%d",&p.dataF);  
    
    prenotazione * prenotati = ricercaPrenotazione(head,key);
    if(prenotati !=NULL){
        if(checkPrenotazione(head,stanza,p)==0){
            printf("Modifica andata a buon fine \n");
            changeData(&prenotati,p);
        }else{
            printf("Modifica fallita\n");
        }
    }else{
        printf("Prenotazione inesistente \n ");
    }
}
void cancellaPrenotazione(prenotazione **head, int key){ 
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
    printf("Cancellazione riuscita \n");
    free(q); /* cancella */
} 
prenotazione * prenotazioneTerminata(prenotazione * head){
    while(head!=NULL){
        if(head->dataI<data){
            return head;
        }else{
            head = head->next;
        }
    }
    return NULL;
}
/*****************************************************************************************/
/******** FUNZIONI STANZA *********************************************************************/
stanza * ricercaStanza(stanza *headS,int numeroStanza){//Ricerca la stanza che possiede il numero di stanza passato come paramentro e ritorna il puntatore a quel nodo 
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
codicePrenotazione * ricercaCodiceStanza(codicePrenotazione *head, int key){
    while(head !=NULL){
            if(head -> codice == key){//SONO UGUALI
                return head;
            }else{//PORTO AVANTI LE PRENOTAZIONI
                head= head->next;
            }
        }
    return NULL;//NESSUNA STANZA CON QUEL CODICE NON CI SONO PRENOTAZIONI PER QUELLA STANZA
}
stanza * ricercaPrenotazioneStanza(stanza * head,int key){
    while(head!=NULL){
        codicePrenotazione * p = ricercaCodiceStanza(head->future,key);
        if(p!=NULL){
            return head;
        }else{
            head = head->next;
        }        
    }
}

void letturaS(stanza **head){
    stanza * p;
    p = (stanza *)malloc(sizeof(stanza));
    printf("Numero stanza\n");
    scanf("%d",&p->numeroStanza);
    printf("OccupantiMax \n");
    scanf("%d",&p->occupantiM);
    p->next = *head;
    *head = p;
}


void cancellaCodicePrenotazione(codicePrenotazione **head,int key){
    codicePrenotazione *q = *head, *r = *head; /* predecessore e successore */
    while ((q != NULL) && (q->codice != key)){
        r = q;
        q = q->next;
    }
    if (q == NULL)
        return; /*l'elemento non esiste */
    if (q==*head) /*l'elemento da cancellare è il primo */
        *head = (*head)->next;

    else
        r->next = q->next;
    free(q); /* cancella */
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

cliente inserisciCliente(cliente *head){
    //Inserimento del cliente e dei suoi rispettivi dati, invoca la funzione addPrenotazione(), per poter creare contestualmente una prenotazione
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
    cliente c;
    printf("Nome: ");
    fgets(c.nome,30,stdin);
    printf("Carta d'identita': ");
    fgets(c.CI,8,stdin);
    if(cercaCliente(head,c.CI)==NULL){
            return c;
    }else{
         printf("Il cliente esiste già\n");   
    }
}
int ricercaCodiceStorico(int codice,codicePrenotazione * head){
    while(head!=NULL){
        if(head->codice == codice){
            return 0;
        }else{
            head = head->next;
        }
    }
    return 1;
}
void storicoClienti(prenotazione *headP,cliente *headC){
    prenotazione *p = prenotazioneTerminata(headP);
    if (p != NULL){
        cliente * tmp = cercaCliente(headC, p->CI);
        if (tmp!=NULL){
            codicePrenotazione * listaCodici = tmp->storico;
            if (ricercaCodiceStorico(p->codice, listaCodici) != 0){
                inserimentoStorico(&tmp->storico, p->codice);
                headC = headC->next;
            }
        }
        else{
            headC = headC->next;
        }
    }else{
        printf("Nessuna prenotazione si è conclusa oggi \n ");
    }
}
/*****************************************************************************************/
/********* STAMPA ************************************************************************/

void stampaS(stanza *head){//Stampa le stanze e la loro capienzaMax
    int i=1;
    if(head!=NULL){
        while(head!=NULL){
            printf("\t\tOccupanti Max : %d \n",head->occupantiM );
            printf("\t\tNumero stanza : %d \n",head->numeroStanza );
            head= head->next;
            i++;
        }
    }else{
        printf("\t\tNessuna stanza disponibile \n");        
    }
}

void stampaPrenotazioniStanza(stanza *head,int numeroStanza){//Stampa lo stato di una determinata stanza
    stanza * s = ricercaStanza(head,numeroStanza);
    if(s!=NULL){
        codicePrenotazione * p = s -> future;
        printf("\t\tLe prenotazioni della stanza %d sono : \n",s->numeroStanza );
        if(p!=NULL){
            while(p!=NULL){
                printf("\t\tCodice prenotazione stanza : %d \n",p->codice );
                p = p->next;
            }
        }else{
                printf("\t\tNessuna prenotazione per questa stanza \n");                    
            }  
    }else{
        printf("Stanza inesistente\n");        
    }
}

void stampaC(cliente *head){//Stampa tutti i clienti
    int i=1;
    if(head!=NULL){
        while(head!=NULL){
            printf("||||||||| INIZIO CLIENTE |||||||||\n");
            printf("\t\tCliente numero %d\n",i);
            printf("\t\tNome : %s \n",head->nome );
            printf("\t\tCarta d'identita : %s \n",head->CI);
            printf("||||||||| INIZIO PRENOTAZIONI PASSATE |||||||||\n");
            codicePrenotazione * listaCodici = head->storico;
            while(listaCodici!=NULL){
                printf("\t\t\tCodice prenotazione %d \n",listaCodici->codice);
                listaCodici = listaCodici->next;
            }
             printf("||||||||| FINE CLIENTE |||||||||\n");
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
            printf("\t\tOccupanti prenotazione %d : %d \n",i,head->occupanti );
            printf("\t\tCodice della %d prenotazione : %d \n",i,head->codice );
            printf("\t\tData inzio pernottamento %d\n",head->dataI);
            printf("\t\tData fine pernottamento : %d\n",head->dataF);
            head= head->next;
            i++;
        }
    }else{
        printf("Nessuna prenotazione disponibile\n");
    }
}
void stampaDisponibilita(prenotazione *head,stanza * headS,int dataI,int dataF){
    prenotazione p;
    stanza * s;
    p.dataI = dataI;
    p.dataF = dataF;
    while(head!=NULL){
        if(ricercaData(head,p)==0){
            s = ricercaPrenotazioneStanza(headS,head->codice);
            printf("Questa stanza e' libera : %d\n",s->numeroStanza);
            head = head->next;
        }else{
            head = head->next;
        }
    }
}
/*****************************************************************************************/
/******** MENU' **************************************************************************/
void menuCliente(cliente **head){
    int choose;
    cliente c;
    do{     
        
        printf("Effettua la tua scelta : \n");
        printf(" 1 - Inserisci Cliente\n");
        printf(" 2 - Stampa Cliente\n");
        printf(" 0 - Esci\n");
        scanf("%d",&choose);
        switch(choose){
            case 1 : { //Inserimento cliente e relativa prenotazione
                c = inserisciCliente(*head);
                inserimentoTestaCliente(head,c);
                break;
            }
            case 2 : {//Inserimento prenotazione per cliente esistente
                stampaC(*head);
                break;
            }
            case 0 :{//Uscita
                printf("Arrivederci\n");
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
            case 1 : { //Inserimento cliente e relativa prenotazione
                addPrenotazione(head,*headS,*codice);
                (*codice)++;
                break;
            }
            case 2 : {//Inserimento prenotazione per cliente esistente
                printf("Si prega di fornire il codice della prenotazione : ");
                scanf("%d",&key);
                stanza * s = ricercaPrenotazioneStanza(*headS,key);
                codicePrenotazione * listaPrenotazione = s->future;
                modificaPrenotazione(*head,listaPrenotazione,key);
                break;
            }
            case 3 : {//Inserimento prenotazione per cliente esistente
                if(head!=NULL){
                    printf("Si prega di fornire il codice della prenotazione : ");
                    scanf("%d",&key);
                    cancellaPrenotazione(head,key);//Cancella la prenotazione con il codice corrispondente
                    stanza * s = ricercaPrenotazioneStanza(*headS,key);
                    if(s!=NULL){
                        codicePrenotazione * listaCodici = s->future;
                        cancellaCodicePrenotazione(&listaCodici,key);                            
                    }else{
                        printf("Nessuna stanza presente con quella prenotazione\n");
                        
                    }
                }else{
                    printf("Nessuna prenotazione esistente\n");                    
                }
                break;
            }
            case 4 : {//Inserimento prenotazione per cliente esistente
                stampaP(*head);
                break;
            }
            case 0 :{//Uscita
                printf("Arrivederci\n");
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
        printf(" 0 - Esci\n");
        scanf("%d",&choose);
        switch(choose){
            case 1 : { //Inserimento cliente e relativa prenotazione
                stampaS(head);
                break;
            }
            case 2 : {//Inserimento prenotazione per cliente esistente
                printf("Inserire numero stanza :\t");
                scanf("%d",&key);
                stampaPrenotazioniStanza(head,key);
                break;
            }
            case 3 : { //Inserimento cliente e relativa prenotazione
                printf("Immettere dataInizio YYYYMMGG\n");
                scanf("%d",&dataI);
                printf("Immettere dataFine YYYYMMGG\n");
                scanf("%d",&dataF);               
                stampaDisponibilita(headP,head,dataI,dataF);
                break;
            }
            case 0 :{//Uscita
                printf("Arrivederci\n");
                break;
            }
        }
    }while(choose!= 0); 
}
void menu(stanza ** headS){
    int choose; 
    prenotazione * headP = NULL;
    cliente * headC = NULL;
    int codice = 1;
    do{       
        printf("Effettua la tua scelta : \n");
        printf(" 1 - Menu Cliente\n");
        printf(" 2 - Menu Prenotazione\n");
        printf(" 3 - Menu Stanza\n");
        printf(" 4 - Andare avanti di giorno\n");
        printf(" 0 - Esci\n");
        scanf("%d",&choose);
        switch(choose){
            case 1 : { //Inserimento cliente e relativa prenotazione
                menuCliente(&headC);
                break;
            }
            case 2 : {//Inserimento prenotazione per cliente esistente
                menuPrenotazione(&headP,headS,&codice);
                break;
            }
            case 3 :{//Stampa lista clienti
                menuStanza(*headS,headP);
                break;
            }
            case 4 :{
                data = data+1;
                printf("Data nuova e' %d \n",data);
                prenotazione * tmp = headP;
                while(tmp !=NULL){
                    storicoClienti(tmp,headC);
                    tmp= tmp->next;
                }
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
    int choose;
    stanza * headS=NULL;
    do{
        letturaS(&headS);
        printf("inserisci 0 per uscire \n");
        scanf("%d",&choose);
    }while(choose!=0);
    
    menu(&headS);
}
