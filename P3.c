#include "headers.h"
#include "sem.c"

int main()
{
	FILE *fp;
	if((fp=fopen("wynik.txt","w"))==NULL)
	{
		printf("Blad otwarcia pliku");
		exit(1);
	}
	printf("Proces P3.\n");
	fprintf(fp, "Proces P3.\n");
	//utworz_nowy_semafor();
	//ustaw_semafor();
	uzyskanie_dostepu();
    semafor_p(0);
	printf("t31 procesu o PID=%d\n", getpid());
	fprintf(fp,"t31 procesu o PID=%d\n",getpid());
	sleep(1);
	printf("t32 procesu o PID=%d\n", getpid());
	fprintf(fp,"t32 procesu o PID=%d\n",getpid());
	sleep(1);
	semafor_v(1);
	semafor_p(4);
	printf("t33 procesu o PID=%d\n",getpid());
	fprintf(fp,"t33 procesu o PID=%d\n",getpid());
	sleep(1);
	//usun_semafor();
	fclose(fp);

return 0;
}

