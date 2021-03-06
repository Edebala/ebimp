#include <stdio.h>
#include <stdlib.h>

void printPGM(int n, int m,int max,unsigned char **a,char* out){
	unsigned char tmp;
	if(a == 0){
		printf("Empty\n");
		return;	
	}
	printf("%i %i \n",n,m);
	if(out == 0){
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<m;j++)
			{
				tmp = ((unsigned char**)a)[i][j];
				for(int k=0;k<2;k++)
				putchar(tmp == 0?' ':(max/tmp>4?'.':(max/tmp>3?',':
					((float)max/tmp>2.6?'i':((float)max/tmp>2.2?'8':
					(((float)max/tmp)>1.9?'M':(unsigned char)(219)))))));
			}
		putchar('\n');
		}
	}
	else{
		FILE *fo = fopen(out,"w");
		fprintf(fo,"P5\n");
		fprintf(fo,"%i ",n);
		fprintf(fo,"%i\n",m);
		fprintf(fo,"%i\n",max);
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++)
				fprintf(fo,"%hhu ",((unsigned char**)a)[i][j]);
			fprintf(fo,"\n");
		}
		fclose(fo);
	}
}

unsigned char** readPGM(char* in,int *n,int *m,int *max){
	FILE *fi = fopen(in,"r");
	if(fi == 0){
		printf("Error\n");	
		return 0;
	}
	int mn = 10000, mx = 0;
	char title[4];
	for(int i=0;i<3;i++)
		title[i] = (char)fgetc(fi);
	fscanf(fi,"%i\n",m);
	fscanf(fi,"%i\n",n);
	fscanf(fi,"%i\n",max);
	unsigned char **a = (unsigned char**) malloc((*n) *sizeof(unsigned char*));
	for(int i=0;i<*n;i++){
		a[i] = (unsigned char*) malloc((*m) * sizeof(unsigned char));
		for(int j=0;j<*m;j++){
			a[i][j] = (char)fgetc(fi);
			if(mn >a[i][j]) mn = a[i][j];
			if(mx <a[i][j]) mx = a[i][j];
		}
	}

	for(int i=0;i<*n;i++)
		for(int j=0;j<*m;j++)
			a[i][j] -= mn;
	*max = mx-mn;
	return a;
}

int main()
{
	char source[15];
	int n,m,max;
	scanf("%s", source);
	unsigned char **a = readPGM(source,&n,&m,&max);
	printPGM(n,m,max,a,0);
	return 0;
}
