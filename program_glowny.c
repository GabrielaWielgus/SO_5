#include "headers.h"
#include "sem.c"

int main(int argc, char *argv[]){
	int i,exec,str_long,waitpid,x;
    char *nazwa;
	str_long = strlen(argv[1])+4;
	for(int i=0; i<=3; i++)
	{
		nazwa=(char*)malloc(str_long*sizeof(char));
		if(nazwa ==NULL)
		{
			printf("Error malloc");
			exit(2);
		}
	}

	printf("PROGRAM GLOWNY.\n");
	
		if(argc != 4){
			printf("Zla liczba argumentow\nwywolaj program_glowny P1 P2 P3\n");
			exit(1);
		}
	
	//wypisanie danych z wywolania dla sprawdenia poprawnosci	
	printf("P1: %s \tP2: %s\tP3: %s\n",argv[1],argv[2],argv[3]); 
	
    utworz_nowy_semafor();
    ustaw_semafor();
  
    for (i=1; i <= 3; i++)
	{
    	switch(fork()) 
		{
		case -1:
			perror("Nie utworzono procesu potomnego\n");
			exit(3);
      	case 0:
			exec = execv(argv[i],argv);
			if(exec == -1)
			{
         		perror ("Blad exec'a dla potomnego program_glowny\n");
         		exit(4);  
			}
			break;
        }
    }

    for(i=1; i <= 3; i++){
      waitpid = wait(&x);
      if (waitpid == -1){
        perror("Blad funkcji wait\n");
        exit(5);
      }
      printf("Proces %d zakonczyl sie z kodem %d\n", waitpid, x);
    }
    usun_semafor();
    free(nazwa);
	return 0;
}
