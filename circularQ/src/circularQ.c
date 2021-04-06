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
#define MAX_QUEUE_SIZE 4 //queue의 크기를 4로 지정

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
	setvbuf(stdout, NULL, _IONBF, 0); // Windows용 Eclipse의 Console창 글자 안 나오는 오류 수정
	setvbuf(stderr, NULL, _IONBF, 0);
	QueueType* cQ = createQueue(); //cQ라는 이름의 queue 생성
	element data;
	char command;

	do {
		printf("\n-----------------[김동원] [2020039023]----------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Dubug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'i': case 'I': //data에 원소값을 입력받아 queue에 저장한다
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D': //queue에 들어있는 내용을 지운다
			deQueue(cQ, &data);
			break;
		case 'p': case 'P':
			printQ(cQ); //queue를 출력한다
			break;
		case 'b': case 'B':
			debugQ(cQ); //디버그한다
			break;
		case 'q': case 'Q':
   	        freeQueue(cQ); //queue에 할당된 메모리들을 해제한다
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');


	return 1;
}


QueueType* createQueue() //queue 생성
{
	QueueType* cQ;
	cQ = (QueueType*)malloc(sizeof(QueueType)); //cQ의 메모리를 QueueType의 크기를 통하여 동적할당
	cQ->front = 0; //front와 rear값 초기화
	cQ->rear = 0;
	return cQ;
}

int freeQueue(QueueType* cQ) { //동적할당된 메모리를 풀어주는 역할
	if (cQ == NULL) return 1;
	free(cQ);
	return 1;
}


element getElement() //원소 받기
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item); //getElement함수가 호출됐을 때 element값을 입력받아 item에 저장
	return item;
}


int isEmpty(QueueType* cQ) //queue가 비어있는지 확인
{
	if (cQ->rear == cQ->front) { //rear와 front를 비교, 둘이 같다는 뜻은 큐가 비어있다는 뜻
		printf("Circular Queue is empty!");
		return 1;
	}
	return 0;
}

int isFull(QueueType* cQ) //queue가 꽉 차 있는지 확인
{
	if (((cQ->rear + 1) % MAX_QUEUE_SIZE) == cQ->front) { //rear와 front를 비교, %MAX_QUEUE_SIZE연산을 통해 rear의 값이 무한히 늘어나지 않게 고정
		printf("Circular Queue is full!");
		return 1;
	}
	return 0;
}

void enQueue(QueueType* cQ, element item) //queue에 원소를 채움
{
	if (isFull(cQ)) //element를 추가하기 전, cQ에 element가 차있는지 확인
		return;
	else {
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; //rear를 한칸 뒤로 옮긴다. 역시 %MAX_QUEUE_SIZE연산을 통해 rear 값 고정
		cQ->queue[cQ->rear] = item; //rear의 자리에 원소의 값인 item을 할당
	}
}

void deQueue(QueueType* cQ, element* item) //queue의 원소를 지움(선입선출방식으로)
{
	if (isEmpty(cQ)) //element를 빼기 전, cQ가 비어있는지 확인
		return;
	else {
		cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE; //front를 한 칸 뒤로 옮긴다(앞의 요소를 queue에서 빼내기 위해)
		return;
	}
}


void printQ(QueueType* cQ) //queue를 출력
{
	int i, first, last;

	first = (cQ->front + 1) % MAX_QUEUE_SIZE; //queue안의 첫 번째 원소
	last = (cQ->rear + 1) % MAX_QUEUE_SIZE; //queue안의 마지막 원소

	printf("Circular Queue : [");

	i = first;
	while (i != last) { //first부터 last까지의 원소들의 값을 적어주는 과정
		printf("%3c", cQ->queue[i]);
		i = (i + 1) % MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}

void debugQ(QueueType* cQ) //queue 디버깅 (위치 확인)
{

	printf("\n---DEBUG\n");
	for (int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if (i == cQ->front) { //for문으로 i의 값을 증가시키며 cQ->front의 값과 일치하는 위치를 찾는다
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); //배열에 저장된 element값들을 출력한다

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); //front와 rear의 위치를 출력한다
}

