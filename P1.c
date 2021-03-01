#include "headers.h"
#include "sem.c"

int main()
{
	printf("Proces P1.\n");
	//utworz_nowy_semafor();
	//ustaw_semafor();
	uzyskanie_dostepu();
    semafor_p(2);
	printf("t11 procesu o PID=%d\n",getpid());
	sleep(1);
	printf("t12 procesu o PID=%d\n", getpid());
	sleep(1);

	semafor_v(3);
	//usun_semafor();
return 0;
}

