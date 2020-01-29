#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void
print_menu(void)
{
	
	printf("1. Idli\n");
	printf("2. Dosa\n");
	printf("3. Pulihora\n");
	printf("4. Bayatiki potha\n");
	printf("Em kaavale? : ");
	return;
}

int
main ()
{

	char c;
	
	print_menu();
	while(1){
		c = getchar();
		fflush(stdin);
		switch (c)	{
			case '1': printf("Idli lu levu\n");
				break;
			case '2': printf("Dosa lu levu\n");
				break;
			case '3': printf("Pulihora ledu\n");
				break;
			case '4':
				break;
			default:
				printf("wrong choice\n");
				break;
		}
		if(c == '4') {
			break;
		}
		getchar();
		system("clear");
		print_menu();
	}
	return 0;
}
