#include "headers.h"
#include "sem.c"

int main()
{
	FILE *fp;
	if((fp=fopen("wynik.txt", "w"))==NULL)
	{
		printf("Blad otwarcia pliku");
		exit(1);
	}

	printf("Proces P2.\n");
	fprintf(fp, "Proces P2.\n");
	//utworz_nowy_semafor();
	//ustaw_semafor();
	uzyskanie_dostepu();
	printf("t21 procesu o PID=%d\n",getpid());
	
	fprintf(fp,"t21 procesu o PID=%d\n",getpid());
	sleep(1);
	semafor_v(0);
    semafor_p(1);
	printf("t22 procesu o PID=%d\n", getpid());
	fprintf(fp,"t22 procesu o PID=%d\n",getpid());
	sleep(1);
	semafor_v(2);
	semafor_p(3);
	printf("t23 procesu o PID=%d\n", getpid());
	fprintf(fp,"t23 procesu o PID=%d\n", getpid());
	sleep(1);

	semafor_v(4);
	//usun_semafor();
	fclose(fp);

return 0;
}
