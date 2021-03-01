#include "headers.h"
int semafor;

static void poczatek(void);
static void utworz_nowy_semafor(void);
static void ustaw_semafor(void);
static void semafor_p(int sem);
static void semafor_v(int sem);
static void usun_semafor(void);

/*int main()
  {
    poczatek();
    utworz_nowy_semafor();
    ustaw_semafor();
    semafor_v();
    semafor_p();
    usun_semafor();
  }
*/
static void poczatek(void)
  {
    printf("Semafory.\n");
  }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void utworz_nowy_semafor(void)
  {
	key_t key;
	key = ftok(".",'D'); //tworzenie klucza
    semafor=semget(key,5,0600|IPC_CREAT|IPC_EXCL);
	//prawa r w dla uera IPC_CREAT - utworzenie gdy nie ma lub otwarcie gdy jest  - IPC_CREAT | IPC_EXCL - utworzenie gdy nie ma, błąd gdy jest
    if (semafor==-1) 
      {
        printf("Blad w sem.c nie mozna utworzyc nowego semafora.\n");
        exit(EXIT_FAILURE);
      }
    else
      {
	printf("Semafor zostal utworzony : %d z kluczem : %d\n",semafor,key);
      }
  }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void uzyskanie_dostepu(void){
    key_t key;
    key = ftok(".", 'D');
    semafor=semget(key,5,0600|IPC_CREAT); //IPC_CREAT - utworzenie gdy nie ma lub otwarcie gdy jest (a jest bo tworzylismy wczesniej wiec praktycznie otworzenie)
    if  (semafor==-1) {
    	perror("Blad w sem.c w semget dla dostepu do semafora\n");
        printf("Nie moglem uzyskac dostepu do semafora.\n");
        exit(EXIT_FAILURE);
     } 
    else{
    	printf("Proces %d uzyskal dostep do semafora : %d\n",getpid(),semafor);
      }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void ustaw_semafor(void)
  {
    int ustaw_sem;
    ustaw_sem=semctl(semafor,0,SETVAL,1);//ustawiamy wartosc poczatkowa na 1 (pierwszy ktory dostanie dostep do sk zmieni na 0)
    if (ustaw_sem==-1)
      {
        printf("Blad w sem.c Nie mozna ustawic semafora.\n");
        exit(EXIT_FAILURE);
      }
    else
      {
        printf("Semafor zostal ustawiony.\n");
      }
  }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void semafor_p(int sem)
  {
    int zmien_sem;
    struct sembuf bufor_sem;
    bufor_sem.sem_num=sem;
    bufor_sem.sem_op=-1;
    bufor_sem.sem_flg=SEM_UNDO;

	while(1)
	{
    	zmien_sem=semop(semafor,&bufor_sem,1);
		if(zmien_sem==0 || errno != 4)
		{ //errno != 4 => errno == 4 ->Interrupted system call
			break;
		}	
    }
	  if(zmien_sem==-1)
	  {
		if(errno != 4)
		{
			//perror("errow w p");
			//exit(EXIT_FAILURE);
			uzyskanie_dostepu();
		}
	}
    else
	{
        printf("Semafor zostal zamkniety.\n");
    }
  }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void semafor_v(int sem)
  {
    int zmien_sem;
    struct sembuf bufor_sem;
    bufor_sem.sem_num=sem;
    bufor_sem.sem_op=1;
    bufor_sem.sem_flg=SEM_UNDO;

	while(1)
	{
    	zmien_sem=semop(semafor,&bufor_sem,1);
		if(zmien_sem==0 || errno != 4)
		{
			break;
		}
	}
	if(zmien_sem==-1)
	{
		if(errno != 4)
		{
			//perror("errow w p");
			//exit(EXIT_FAILURE);
			uzyskanie_dostepu();
		}
	}
    else
	{
        printf("Semafor zostal otwarty.\n");
    }
  }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void usun_semafor(void)  
  {
    int sem;
	uzyskanie_dostepu();
    sem=semctl(semafor,0,IPC_RMID);//IPC_RMID -> usunięcie danego zbioru semaforów
    if (sem==-1)
      {
        printf("Blad w sem.c Nie mozna usunac semafora.\n");
        exit(EXIT_FAILURE);
      }
    else
      {
		printf("Semafor zostal usuniety : %d\n",sem);
      }
  }
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void stan_semafora(void){
	int stan;
	if ((stan=semctl(semafor,0,GETVAL)) == -1){ //GETVAL = odczytanie wartosci semafora ze sbioru "semafor" nr "0"
		perror ("Blad w sk potomnego funkcji semctl -> kod GETVAL\n");  
	} 
  	printf("Stan semafora %d\n", stan);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void liczba_prcesow_czekajacych(void){
	int liczba;
	if ((liczba=semctl(semafor,0,GETNCNT)) == -1) { //odczytanie liczby procesów czekających na podniesienie semafora
		perror ("Blad w sk potomnego funkcji semctl -> kod GETNCNT\n");
	}
	printf("Liczba semaforow czekajacych na podniesienie semafora %d\n",liczba);	
}
