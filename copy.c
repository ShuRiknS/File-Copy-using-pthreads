#include <fcntl.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

#define SIZE 4096

typedef struct{
	unsigned long offset;
	unsigned long size;
}PART;

char file[50]="/home/oslab/Downloads/1.mkv";
char fileout[50]="/home/oslab/Desktop/1.mkv";

void* func1(void *arg);

int main(int argc, char *argv[]){
	char data[SIZE];
	struct stat f_stat;
	int fin1, fout1, x, chk, i=0;
	int numb;
	unsigned long offset_size=0;
	printf("Number of threads and files:");
	scanf("%d",&numb);
	PART part[numb];
	pthread_t t[numb];
	stat(file, &f_stat);
	printf("Size of file is %lu \n", f_stat.st_size);
	part[0].offset = 0;
	part[0].size = f_stat.st_size / numb;
	for(j =0; j<numb; j++){
		part[j].size=part[0].size;
		offset_size+=part[j].size;
		part[j].offset=offset_size;
	} 
	part2.offset = part1.size;
	part2.size = part1.size;
	part3.offset = part2.offset + part2.size;
	part3.size = f_stat.st_size - part3.offset;

	fin1 = open(file, O_RDONLY);
	fout1 = open(fileout, O_WRONLY|O_CREAT, 0666);

        pthread_create(&t1, NULL, func1, &part2);
	pthread_create(&t2, NULL, func1, &part3);

	while(i < part1.size){	
		x = read(fin1, data, SIZE);
		write(fout1, data, x);
		i += x;
	}
	pthread_join(t1, NULL); // making main to wait for t1
	pthread_join(t2, NULL); // making main to wait for t2
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
        printf("thread is done.\n");
        close(fout);
        close(fin);
}
