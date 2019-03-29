/*
Felipe da Silva Lima
28/07/2016
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int32_t main()
{
    FILE *archive;
	int32_t i;
	int32_t tudo[999];
	archive = fopen("archive","wb");
	if( archive==NULL)
	{
		printf("Don't cry, baby. Archive didn't open only.. Try again!\n");
	    exit(1);
	}
	
	for(i=0; i<1000;i++){ /* modify and do everthing you want. random numbers, inverse ordering, more numbers...  */
    	fwrite(&i, sizeof(int32_t), 1, archive);
	}
	fclose(archive);
	printf("That's all folks!");
    return 0;
}

