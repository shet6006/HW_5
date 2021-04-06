/*
 ============================================================================
 Name        : circularQ.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 4 //queue�� ũ�⸦ 4�� ����

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType* createQueue();
int freeQueue(QueueType* cQ);
int isEmpty(QueueType* cQ);
int isFull(QueueType* cQ);
void enQueue(QueueType* cQ, element item);
void deQueue(QueueType* cQ, element* item);
void printQ(QueueType* cQ);
void debugQ(QueueType* cQ);
element getElement();


int main(void)
{
	setvbuf(stdout, NULL, _IONBF, 0); // Windows�� Eclipse�� Consoleâ ���� �� ������ ���� ����
	setvbuf(stderr, NULL, _IONBF, 0);
	QueueType* cQ = createQueue(); //cQ��� �̸��� queue ����
	element data;
	char command;

	do {
		printf("\n-----------------[�赿��] [2020039023]----------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Dubug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'i': case 'I': //data�� ���Ұ��� �Է¹޾� queue�� �����Ѵ�
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D': //queue�� ����ִ� ������ �����
			deQueue(cQ, &data);
			break;
		case 'p': case 'P':
			printQ(cQ); //queue�� ����Ѵ�
			break;
		case 'b': case 'B':
			debugQ(cQ); //������Ѵ�
			break;
		case 'q': case 'Q':
   	        freeQueue(cQ); //queue�� �Ҵ�� �޸𸮵��� �����Ѵ�
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');


	return 1;
}


QueueType* createQueue() //queue ����
{
	QueueType* cQ;
	cQ = (QueueType*)malloc(sizeof(QueueType)); //cQ�� �޸𸮸� QueueType�� ũ�⸦ ���Ͽ� �����Ҵ�
	cQ->front = 0; //front�� rear�� �ʱ�ȭ
	cQ->rear = 0;
	return cQ;
}

int freeQueue(QueueType* cQ) { //�����Ҵ�� �޸𸮸� Ǯ���ִ� ����
	if (cQ == NULL) return 1;
	free(cQ);
	return 1;
}


element getElement() //���� �ޱ�
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item); //getElement�Լ��� ȣ����� �� element���� �Է¹޾� item�� ����
	return item;
}


int isEmpty(QueueType* cQ) //queue�� ����ִ��� Ȯ��
{
	if (cQ->rear == cQ->front) { //rear�� front�� ��, ���� ���ٴ� ���� ť�� ����ִٴ� ��
		printf("Circular Queue is empty!");
		return 1;
	}
	return 0;
}

int isFull(QueueType* cQ) //queue�� �� �� �ִ��� Ȯ��
{
	if (((cQ->rear + 1) % MAX_QUEUE_SIZE) == cQ->front) { //rear�� front�� ��, %MAX_QUEUE_SIZE������ ���� rear�� ���� ������ �þ�� �ʰ� ����
		printf("Circular Queue is full!");
		return 1;
	}
	return 0;
}

void enQueue(QueueType* cQ, element item) //queue�� ���Ҹ� ä��
{
	if (isFull(cQ)) //element�� �߰��ϱ� ��, cQ�� element�� ���ִ��� Ȯ��
		return;
	else {
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; //rear�� ��ĭ �ڷ� �ű��. ���� %MAX_QUEUE_SIZE������ ���� rear �� ����
		cQ->queue[cQ->rear] = item; //rear�� �ڸ��� ������ ���� item�� �Ҵ�
	}
}

void deQueue(QueueType* cQ, element* item) //queue�� ���Ҹ� ����(���Լ���������)
{
	if (isEmpty(cQ)) //element�� ���� ��, cQ�� ����ִ��� Ȯ��
		return;
	else {
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE; //front�� �� ĭ �ڷ� �ű��(���� ��Ҹ� queue���� ������ ����)
		return;
	}
}


void printQ(QueueType* cQ) //queue�� ���
{
	int i, first, last;

	first = (cQ->front + 1) % MAX_QUEUE_SIZE; //queue���� ù ��° ����
	last = (cQ->rear + 1) % MAX_QUEUE_SIZE; //queue���� ������ ����

	printf("Circular Queue : [");

	i = first;
	while (i != last) { //first���� last������ ���ҵ��� ���� �����ִ� ����
		printf("%3c", cQ->queue[i]);
		i = (i + 1) % MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}

void debugQ(QueueType* cQ) //queue ����� (��ġ Ȯ��)
{

	printf("\n---DEBUG\n");
	for (int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if (i == cQ->front) { //for������ i�� ���� ������Ű�� cQ->front�� ���� ��ġ�ϴ� ��ġ�� ã�´�
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); //�迭�� ����� element������ ����Ѵ�

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); //front�� rear�� ��ġ�� ����Ѵ�
}

