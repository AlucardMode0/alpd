#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include"mpi.h"
#include"dict.h"
#include <regex.h> 
int total=1;

int main (int argc , char **argv)
{
	int rank;
	int np;
	char received_word[100];
	char send_word[100];
	char end[] = "terminat de citit";
	total=argc+1;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&np);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Status status;
	int i=0;
	if(rank==0)
	{
		int j;
		int ok=1;
		Dictionary *d=(Dictionary*)malloc (1);
		d=dict_new();
		int *finished=(int *)malloc(total * sizeof(int));
		int *transmit=(int *)malloc(np * sizeof(int));
		for(j=0;j<argc;++j)
			{
			finished[j]=-1;
			transmit[j]=0;
		}
		for(j=1;j<argc;++j)
		{
			
			transmit[j%np>0?j%np:1]++;
		}
		for(int i=0;i<=np;++i)
		printf("%d nigga",transmit[i]);
		printf("am facut pana la alocare vector\n");
		for( i=1;i<np;++i)
		{printf("trimit la proc %d , %s\n",i%np>0?i%np:1,argv[i]);
			MPI_Send(&transmit[i],1,MPI_INT,i,0,MPI_COMM_WORLD);
			MPI_Send(argv[i],100,MPI_CHAR,(i%np>0)?(i%np):(1),0,MPI_COMM_WORLD);
			finished[i]=0;
		printf("AICI\n");}
		 while(ok)
		 {
			// printf("am inceput receive pe proc 0\n");
			MPI_Recv(received_word,100,MPI_CHAR,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
			if(strcmp(received_word,end)!=0)
			{dict_add(d,received_word,(int)status.MPI_TAG);
			//dict_print(d);
			}
			else{
				printf("am terminat odata");
				int x=0;
				finished[status.MPI_TAG]=1;
				for(j=1;j<argc;j++)
					{printf("%d ",finished[j]);
					if (finished[j]==-1)
						{ok=1;
						
						MPI_Send(argv[j],100,MPI_CHAR,(j%np>0)?(j%np):(1),0,MPI_COMM_WORLD);
						finished[j]=0;
						break;}
					if (finished[j]==0)
						{ok=1;
						break;}
					ok=0;
					}
					
			}
		 }
		 
			 
		 printf("dictionaru final:\n");
			dict_print(d);
		dict_free(d);
		free(d);
		for(int i=0;i<=argc;++i)
		printf("%d ",finished[i]);
	}
		
	else
	{	int Alint_aroma=0;
		if(np>argc)
			if (rank>=argc)
			{MPI_Finalize();
			return 0;
			}
		int x=1;
		int f1=1,fm=argc/(np-1),f;
		printf("am inceput receive pe proc %d\n",rank);
		MPI_Recv(&Alint_aroma,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
		for(x=1;x<=Alint_aroma;++x)
		{MPI_Recv(received_word,100,MPI_CHAR,0,0,MPI_COMM_WORLD,&status);
		printf("%s\n",received_word);
		for (i=1;i<argc;++i)
			{if(strcmp(received_word,argv[i])==0)
				break;
			}
			char *pch;
			FILE *fp = fopen(received_word,"r");
			char buf[100];
			while( fscanf(fp, "%s", buf) != EOF )
			{
				pch = strtok (buf," ,.-\"\'[](){}!?//@#$%^&*(-_=+");
				  while (pch != NULL)
				  {
					if(pch[1]>32)
					MPI_Send(pch,100,MPI_CHAR,0,i,MPI_COMM_WORLD);
					pch = strtok (NULL, " ,.-\"\'[](){}!?//@#$%^&*(-_=+");
				  }
				//MPI_Send(&buf,100,MPI_CHAR,0,i,MPI_COMM_WORLD);
			}
			printf("trimit end de la %d\n",i);
			MPI_Send(end,100,MPI_CHAR,0,i,MPI_COMM_WORLD);
		}
	}
	
	
	
	MPI_Finalize();
	
	return 0;
}
/*
	string end = "stringul transmis de end"
	total=argc;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&np);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	int i=0;
	if(rank==0)
	{
	
	Dictionary *d=(Dictionary*)malloc (1);
	d=dict_new();
	for( i=1;i<argv;++i)
		int *finished=(int *)malloc(total * sizeof(int));
		MPI_Send(argv[i],proc,i%np)
	while(!finished)
		MPI_Recv(word,from_any_tag);
		if(word!=end)
		dict_add(d,word,tag);
		finished[tag]=1;
	dict_print(d);
	dict_free(d);
	free(d);
	}
		
	else
	{
		
		MPI_Recv(file);
		for (int i=0;i<argc;++i)
		{if(file==argv[i])
				break;
			start_reading()->MPI_Send_every_word(word,to 0, tag=i)
			finalize_reading()->MPI_Send(end,to 0, tag=i)
		}
		
	}
	 */

/*
Dictionary *d=(Dictionary*)malloc (1);
d=dict_new();
dict_free(d);
free(d);

*/
