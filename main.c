/*
Felipe da Silva Lima
28/07/2016
*/
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>

void alg_bubble_up(int32_t vetor[],int32_t n);

int32_t mediana (int32_t x,int32_t y,int32_t z)
{
    int32_t m;

    if (x<y&&y<z)
    {
        m=y;
    }
    else if (x<z&&z<y)
    {
        m=z;
    }
    else if (y<x&&x<z)
    {
        m=x;
    }
    else if (y<z&&z<x)
    {
        m=z;
    }
    else if (z<x&&x<y)
    {
        m=x;
    }
    else
    {
        m=y;
    }
	return m;
}

int32_t menu_list_or_vector() // TODO ordering with lists. (hard work to implement and laziness was useful not to implement.)
{
	int32_t opc=0;
	while(opc!=1)
	{
		system("clear");
		printf("\n1 - Ordenar a partir de um vetor\n");
		scanf("%d", &opc);
	}
	return(opc);
}

void record_on_file(int32_t vetor[],int32_t tam,char nomearq[])
{
	FILE *file;
	int32_t t=(strlen(nomearq))+3;
	char nome[t];
	strcpy(nome,nomearq);
	strcpy(nome,strtok(nome,"."));
	strcat(nome,".out");

	file=fopen(nome,"wb");
		fwrite(vetor,sizeof(int32_t),tam,file);
	fclose(file);
	file=NULL;
}
void swap(int32_t *a, int32_t *b)
{
	int32_t aux;
	aux=*a;
	*a=*b;
	*b=aux;
}

void intercala(int32_t vetor[],int32_t ini,int32_t meio,int32_t fim)
{
	int32_t i,j,k,*tmp;
	i=ini;
	j=meio+1;
	k=0;
	tmp=malloc(sizeof(int32_t)*(fim-ini+1));

	while(i<meio+1 || j<fim+1)
	{
		if(i==meio+1)
		{
			tmp[k]=vetor[j];
			j++;
			k++;
		}
		else
		{
			if(j==fim+1)
			{
				tmp[k]=vetor[i];
				i++;
				k++;
			}
			else
			{
				if(vetor[i]<vetor[j])
				{
					tmp[k]=vetor[i];
					i++;
					k++;
				}
				else
				{
					tmp[k]=vetor[j];
					j++;
					k++;
				}
			}
		}
	}
	for(i=ini;i<=fim;i++)
	{
		vetor[i]=tmp[i-ini];
	}
	free(tmp);
	tmp=NULL;
}

void down(int32_t vetor[],int32_t i,int32_t n)
{
	int32_t j=i*2;
	if(j<=n)
	{
		if(j<n)
		{
			if(vetor[j+1]>vetor[j])
			{
				j++;
			}
		}
		if(vetor[i]<vetor[j])
		{
			swap(&vetor[i],&vetor[j]);
			down(vetor,j,n);
		}
	}


}

void constroi_heap(int32_t vetor[],int32_t n)
{
	int32_t i;
	for(i=(n/2);i>=0;i--)
	{
		down(vetor,i,n);
	}
}

void alg_heapsort(int32_t vetor[],int32_t tam)
{
	int32_t m=tam;
	constroi_heap(vetor,tam);

	while(m>=0)
	{
		swap(&vetor[0],&vetor[m]);
		m--;
		down(vetor,0,m);
	}

}

void alg_quicksort(int32_t vetor[], int32_t ini, int32_t fim,int32_t opcPivo)
{
    int32_t i,j,pivo=0;
    int32_t meio=0,aux=0;

    if(opcPivo==5)
    {
    	pivo=vetor[fim];
    }
    if(opcPivo==6)
    {
    	pivo=vetor[(rand()%(fim-ini))+ini];
    }
    if(opcPivo==7)
    {
    	meio=(ini+fim)/2;
    	pivo=mediana(vetor[ini],vetor[meio],vetor[fim]);
    }

    if((fim-ini)<2)
    {
    	if((fim-ini)==1)
    	{
    		if(vetor[ini]>vetor[fim])
    		{
    			aux=vetor[ini];
	            vetor[ini]=vetor[fim];
	            vetor[fim]=aux;
    		}
    	}
    }
    else
    {
	    i=ini;
	    j=fim;
	    while(i<=j)
	    {
	        while(vetor[i]<pivo && i<fim)
	        {
	            i++;
	        }
	        while(vetor[j]>pivo && j>ini)
	        {
	            j--;
	        }
	        if(i<=j)
	        {
		    	swap(&vetor[i],&vetor[j]);
	            i++;
	            j--;
	        }
	    }
	    if(j>ini)
	        alg_quicksort(vetor,ini,j,opcPivo);
	    if(i<fim)
	        alg_quicksort(vetor,i,fim,opcPivo);
	}
}

void alg_mergesort(int32_t vetor[],int32_t ini,int32_t fim)
{
	int32_t meio;

	if(ini==fim)
		return;

	meio=(ini+fim)/2;
	alg_mergesort(vetor,ini,meio);
	alg_mergesort(vetor,meio+1,fim);
	intercala(vetor,ini,meio,fim);

}

void alg_insertionsort(int32_t vetor[],int32_t n)
{
	int32_t i,j,prov;

	for(i=0;i<n;i++)
	{
		prov=vetor[i];
		j=i-1;

		while( (j>=0) && (prov<vetor[j]) )
		{
			vetor[j+1]=vetor[j];
			j--;
		}
		vetor[j+1]=prov;
	}
}

void alg_bubble_up(int32_t vetor[],int32_t n)
{
	int32_t swp=1;
	int32_t n1=n-1;
	int32_t keep;
	int32_t j;
	while(swp)
	{
		j=0;
		swp=0;
		while(j<n1)
		{
			if(vetor[j]>vetor[j+1])
			{
				swap(&vetor[j],&vetor[j+1]);
				swp=1;
				keep=j;
			}
			j++;
		}
		n1=keep;
	}
}

void alg_bubble(int32_t vetor[],int32_t n)
{
	int32_t i,j;

	for(i=0;i<n;i++)
	{
		for(j=0;j<n-1;j++)
		{
			if(vetor[j]>vetor[j+1])
				swap(&vetor[j],&vetor[j+1]);
		}
	}
}

FILE *abrir_arq(char nomearq[],int32_t *tam)
{
	FILE *file;
	struct stat buf;
	int32_t fd=-1;
	fd=open(nomearq,O_RDONLY); /*obtem o file descriptor do arquivo;*/
	if(fd<0)
	{
		printf("Erro na leitura do arquivo 1\n");
		exit(1);
	}
	else
	{
		fstat(fd,&buf);
		*tam=(buf.st_size/sizeof(int32_t));
		printf("Existem no arquivo %d numeros\n", *tam);
	}
	file=fopen(nomearq,"rb");
	if(file==NULL)
	{
		printf("Erro na leitura do arquivo 2\n");
		exit(2);
	}
	return(file);
}

void bubblesort(char nomearq[])
{
	FILE *file;
	int32_t opc=0;
	int32_t tam;
	int32_t *vetor;

	struct timeval ini,fim;
	float time;

	opc=menu_list_or_vetor();
	printf("Bubble-Sort\n");

	switch(opc)
	{
		case 1:

			file=abrir_arq(nomearq,&tam);
			vetor=malloc(sizeof(int32_t)*tam);
			fread(vetor,sizeof(int32_t),tam,file);

			gettimeofday(&ini,NULL);
				alg_bubble(vetor,tam);
			gettimeofday(&fim,NULL);

			record_on_file(vetor,tam,nomearq);

			time=(float)(fim.tv_sec-ini.tv_sec);
			time=time+(float)(fim.tv_usec-ini.tv_usec)/1000000.0;
			printf("Tempo de ordenação: %.6f\nDigite algo\n", time);
			__fpurge(stdin);
			getchar(); /*pausa*/

		break;

		default:
			printf("Opção incorreta\n");
		break;
	}
	fclose(file);
	free(vetor);
	vetor=NULL;
}

void bubblesort_up(char nomearq[])
{
	FILE *file;
	int32_t opc;
	int32_t tam;
	int32_t *vetor;
	struct timeval ini,fim;
	float time;

	opc=menu_list_or_vetor();
	printf("Bubble-Sort Melhorado\n");

	switch(opc)
	{
		case 1:

			file=abrir_arq(nomearq,&tam);
			vetor=malloc(sizeof(int32_t)*tam);
			fread(vetor,sizeof(int32_t),tam,file);

			gettimeofday(&ini,NULL);
				alg_bubble_up(vetor,tam);
			gettimeofday(&fim,NULL);

			record_on_file(vetor,tam,nomearq);

			time=(float)(fim.tv_sec-ini.tv_sec);
			time=time+(float)(fim.tv_usec-ini.tv_usec)/1000000.0;
			printf("Tempo de ordenação: %.6f\nDigite algo\n", time);
			__fpurge(stdin);
			getchar(); /*pausa*/

		break;

		default:
			printf("Opcão incorreta\n");
		break;
	}
	fclose(file);
	free(vetor);
	vetor=NULL;
}

void insertionsort(char nomearq[])
{
	FILE *file;
	int32_t opc;
	int32_t tam;
	int32_t *vetor;
	struct timeval ini,fim;
	float time;

	opc=menu_list_or_vetor();
	printf("Insertion-Sort\n");

	switch(opc)
	{
		case 1:

			file=abrir_arq(nomearq,&tam);
			vetor=malloc(sizeof(int32_t)*tam);
			fread(vetor,sizeof(int32_t),tam,file);

			gettimeofday(&ini,NULL);
				alg_insertionsort(vetor,tam);
			gettimeofday(&fim,NULL);

			record_on_file(vetor,tam,nomearq);

			time=(float)(fim.tv_sec-ini.tv_sec);
			time=time+(float)(fim.tv_usec-ini.tv_usec)/1000000.0;
			printf("Tempo de ordenação: %.6f\nDigite algo\n", time);
			__fpurge(stdin);
			getchar(); /*pausa*/

		break;

		default:
			printf("Opcão incorreta\n");
		break;
	}
	fclose(file);
	free(vetor);
	vetor=NULL;
}

void mergesort(char nomearq[])
{
	FILE *file;
	int32_t opc;
	int32_t tam;
	int32_t *vetor;
	struct timeval ini,fim;
	float time;

	opc=menu_list_or_vetor();
	printf("Merge-Sort\n");

	switch(opc)
	{

		case 1:

			file=abrir_arq(nomearq,&tam);
			vetor=malloc(sizeof(int32_t)*tam);
			fread(vetor,sizeof(int32_t),tam,file);
			gettimeofday(&ini,NULL);
				alg_mergesort(vetor,0,tam-1);
			gettimeofday(&fim,NULL);

			record_on_file(vetor,tam,nomearq);

			time=(float)(fim.tv_sec-ini.tv_sec);
			time=time+(float)(fim.tv_usec-ini.tv_usec)/1000000.0;
			printf("Tempo de ordenação: %.6f\nDigite algo\n", time);
			__fpurge(stdin);
			getchar(); /*pausa*/

		break;

		default:
			printf("Opção incorreta\n");
		break;
	}
	fclose(file);
	free(vetor);
	vetor=NULL;
}

void quicksort(char nomearq[],int32_t opcPivo)
{
	FILE *file;
	int32_t opc;
	int32_t tam;
	int32_t *vetor;
	struct timeval ini,fim;
	float time;

	opc=menu_list_or_vetor();
	if(opcPivo==5)
		printf("Quick-Sort\nPivo: Último\n");
	if(opcPivo==6)
		printf("Quick-Sort\nPivo: Elemento aleatório\n");
	if(opcPivo==7)
		printf("Quick-Sort\nPivo: Mediana de três\n");


	switch(opc)
	{
		case 1:

			file=abrir_arq(nomearq,&tam);
			vetor=malloc(sizeof(int32_t)*tam);
			fread(vetor,sizeof(int32_t),tam,file);

			gettimeofday(&ini,NULL);
				alg_quicksort(vetor,0,tam-1,opcPivo);
			gettimeofday(&fim,NULL);

			record_on_file(vetor,tam,nomearq);

			time=(float)(fim.tv_sec-ini.tv_sec);
			time=time+(float)(fim.tv_usec-ini.tv_usec)/1000000.0;
			printf("Tempo de ordenação: %.6f\nDigite algo\n", time);
			__fpurge(stdin);
			getchar(); /*pausa*/

		break;
		default:
			printf("Opção incorreta\n");
		break;
	}
	fclose(file);
	free(vetor);
	vetor=NULL;
}

void heapsort(char nomearq[])
{
	FILE *file;
	int32_t opc;
	int32_t tam;
	int32_t *vetor;
	struct timeval ini,fim;
	float time;

	opc=menu_list_or_vetor();
	printf("Heap-Sort\n");

	switch(opc)
	{

		case 1:

			file=abrir_arq(nomearq,&tam);
			vetor=malloc(sizeof(int32_t)*tam);
			fread(vetor,sizeof(int32_t),tam,file);
			gettimeofday(&ini,NULL);
				alg_heapsort(vetor,tam-1);
			gettimeofday(&fim,NULL);

			record_on_file(vetor,tam,nomearq);

			time=(float)(fim.tv_sec-ini.tv_sec);
			time=time+(float)(fim.tv_usec-ini.tv_usec)/1000000.0;
			printf("Tempo de ordenação: %.6f\nDigite algo\n", time);
			__fpurge(stdin);
			getchar(); /*pausa*/

		break;

		default:
			printf("Opção incorreta\n");
		break;
	}
	fclose(file);
	free(vetor);
	vetor=NULL;
}

int32_t main(int32_t argc, char *argv[])
{
    char *nomearq;
    int32_t opc;
    srand(time(NULL));
    if(argc!=2)
    {
    	printf("Falta o arquivo binário com os numeros de entrada\n");
    	exit(1);
    }
    else
    {
    	nomearq=malloc(sizeof(char)*strlen(argv[1]));
    	strcpy(nomearq,argv[1]);

    	if( (fopen(nomearq,"rb"))==NULL)
    	{
    		printf("Arquivo não encontrado\n");
    		exit(1);
    	}

    }
    while(opc!=9)
    {
	    system("clear");
        printf("%s\n", nomearq);
		printf("1 - Bubble-Sort\n");
		printf("2 - Bubble-Sort Melhorado\n");
		printf("3 - Insertion-Sort\n");
		printf("4 - Merge-Sort\n");
		printf("5 - Quick-Sort com o pivô igual ao último elemento\n");
		printf("6 - Quick-Sort com o pivô sendo um elemento aleatório\n");
		printf("7 - Quick-Sort com o pivô sendo a mediana de três\n");
		printf("8 - Heap-Sort\n");
		printf("9 - Sair\n");
		scanf("%d", &opc);
		if(opc==1)
		{
			bubblesort(nomearq);
		}
		if(opc==2)
		{
			bubblesort_up(nomearq);
		}
		if(opc==3)
		{
			insertionsort(nomearq);
		}
		if(opc==4)
		{
			mergesort(nomearq);
		}
		if(opc==5)
		{
			quicksort(nomearq,opc);
		}
		if(opc==6)
		{
			quicksort(nomearq,opc);
		}
		if(opc==7)
		{
			quicksort(nomearq,opc);
		}
		if(opc==8)
		{
			heapsort(nomearq);
		}
	}
    return 0;
}

