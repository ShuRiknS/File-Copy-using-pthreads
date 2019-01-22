#include <stdio.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define SIZE 4098

typedef struct{
	unsigned long offset;
	unsigned long size;
}PART;
int thread_count=1;
char file[50]="/home/oslab/Desktop/gnu.c";
char fileout[50]="/home/oslab/gnu.c";

void* func1(void *arg);

int main(int argc, char *argv[]){
	char data[SIZE];
	struct stat f_stat;
	int fin1, fout1, x, chk, i=0;
	int numb, j;
	unsigned long offset_size=0;
	printf("Enter number of threads: ");
	scanf("%d",&numb); 				
	PART part[numb];
	pthread_t t[numb];
	stat(file, &f_stat);
	printf("Size of file is %lu \n", f_stat.st_size);
	part[0].offset = 0;
	part[0].size = f_stat.st_size /numb;
	for(j =1; j<numb; j++){
		offset_size+=part[j-1].size;
		part[j].offset=offset_size;
		part[j].size=part[0].size;
		}
	fin1 = open(file, O_RDONLY);
	fout1 = open(fileout, O_WRONLY|O_CREAT, 0666);
	for(j=0; j<numb; j++){
		pthread_create(&t[j], NULL, func1, &part[j]);
		}
	for(j=0; j<numb;j++){
		pthread_join(t[j], NULL);
		}
	printf("file is copied");
	close(fout1);
	close(fin1);
	return 0;
}

void* func1(void *arg){
	int fin, fout, x, i;
	PART *part;
	char data[SIZE];
	part = (PART *)arg;
	fin = open(file, O_RDONLY);
        fout = open(fileout, O_WRONLY);
	lseek(fin, part->offset, SEEK_SET);
	lseek(fout, part->offset, SEEK_SET);
        while(i < part->size){
                x = read(fin, data, SIZE);
                write(fout, data, x);
                i += x;
        }
        printf("thread no. %d completed.\n", thread_count);
        close(fout);
        close(fin);
        thread_count++;
}
