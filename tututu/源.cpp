#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<windows.h>
#include<string.h>
#define white 0
#define gray 1
#define black 2
typedef struct num1
{
	struct num1* next;
	int num;
}*node1,node2;
typedef struct ver{
	int num;
	int color;
	int father;
	int d;
	int f;
	node1 next;
}vertex1;
int versize=8, size;
int time1;
int sort[256];
int count;
FILE* fp,*fp1;
vertex1 vertex[256],vertexT[256];
void DFS(vertex1* vertex);
void DFSVISIT(vertex1* vertex, int i);
void DFST(vertex1* vertex,FILE* fp);
void DFSVISITT(vertex1* vertex, int i, FILE* fp);
void main()
{
	int i, a, b,k;
	node1 node;
	double f;
	char string[100], string1[100],string2[100];
	LARGE_INTEGER  fre, start, fin;
	a = versize;
	b = 0;
	while (a != 1)
	{
		a >>= 1;
		b++;
	}
	size = b*versize;
	for (k = 0; k < 6; k++)
	{
		switch (versize)
		{
		case 8:strcpy(string, "../input/size1/input.txt");
			strcpy(string1, "../output/size1/output1.txt");
			strcpy(string2, "../output/size1/time1.txt");
			break;
		case 16:strcpy(string, "../input/size2/input.txt");
			strcpy(string1, "../output/size2/output1.txt");
			strcpy(string2, "../output/size2/time1.txt");
			break;
		case 32:strcpy(string, "../input/size3/input.txt");
			strcpy(string1, "../output/size3/output1.txt");
			strcpy(string2, "../output/size3/time1.txt");
			break;
		case 64:strcpy(string, "../input/size4/input.txt");
			strcpy(string1, "../output/size4/output1.txt");
			strcpy(string2, "../output/size4/time1.txt");
			break;
		case 128:strcpy(string, "../input/size5/input.txt");
			strcpy(string1, "../output/size5/output1.txt");
			strcpy(string2, "../output/size5/time1.txt");
			break;
		case 256:strcpy(string, "../input/size6/input.txt");
			strcpy(string1, "../output/size6/output1.txt");
			strcpy(string2, "../output/size6/time1.txt");
			break;

		}
		count = 0;
		for (i = 0; i < versize; i++)
		{
			vertex[i].next = NULL;
			vertexT[i].next = NULL;
		}
		if ((fp = fopen(string, "r")) == NULL)
			printf("error");
		for (i = 0; i < size; i++)
		{
			fscanf(fp, "%d,%d", &a, &b);
			node = (node1)malloc(sizeof(node2));
			node->num = b;
			node->next = NULL;
			node->next = vertex[a].next;
			vertex[a].next = node;
			node = (node1)malloc(sizeof(node2));
			node->num = a;
			node->next = NULL;
			node->next = vertexT[b].next;
			vertexT[b].next = node;
		}
		fclose(fp);
		if ((fp = fopen(string1, "w")) == NULL)
			printf("error");
		QueryPerformanceFrequency(&fre);
		QueryPerformanceCounter(&start);
		DFS(vertex);
		QueryPerformanceCounter(&fin);
		DFST(vertexT,fp);
		
		fp1 = fopen(string2, "w");
		f = (double)(fin.QuadPart - start.QuadPart) / (double)fre.QuadPart;
		fprintf(fp1, "time for size %d:%.0fus\n", k+1,f*pow(10.0, 6));
		fclose(fp1);
		fclose(fp);	
		versize *= 2;
		a = versize;
		b = 0;
		while (a != 1)
		{
			a >>= 1;
			b++;
		}
		size = b*versize;
	}
}
void DFS(vertex1* vertex)
{
	int i;
	for (i = 0; i < versize; i++)
	{
		vertex[i].color = white;
		vertex[i].father = -1;
	}
	time1 = 0;
	for (i = 0; i < versize; i++)
	{
		if (vertex[i].color == white)
			DFSVISIT(vertex, i);
	}
}
void DFSVISIT(vertex1* vertex, int i)
{
	node1 ptr;
	time1++;
	vertex[i].d = time1;
	vertex[i].color = gray;
	ptr = vertex[i].next;
	while (ptr != NULL)
	{
		if (vertex[ptr->num].color == white)
		{
			vertex[ptr->num].father = i;
			DFSVISIT(vertex, ptr->num);
		}
		ptr = ptr->next;
	}
	vertex[i].color = black;
	time1 = time1 + 1;
	vertex[i].f = time1;
	sort[count++] = i;
}
void DFST(vertex1* vertex, FILE* fp)
{
	int i;
	for (i = 0; i < versize; i++)
	{
		vertex[i].color = white;
	}
	for (i = 0; i < versize; i++)
	{
		count--;
		if (vertex[sort[count]].color == white)
		{
			fputc('(', fp);
			fprintf(fp, "%d", sort[count]);
			DFSVISITT(vertex, sort[count],fp);
			fputs(")\n", fp);
		}
		
	}
}
void DFSVISITT(vertex1* vertex, int i, FILE* fp)
{
	node1 ptr;
	LARGE_INTEGER  fre, start, fin;
	double f;
	vertex[i].color = gray;
	ptr = vertex[i].next;
	while (ptr != NULL)
	{
		if (vertex[ptr->num].color == white)
		{
			fprintf(fp,",%d", ptr->num);
			DFSVISITT(vertex, ptr->num,fp);
		}
		ptr = ptr->next;
	}
	vertex[i].color = black;
}
