/*
 ============================================================================
 Name        : postfix.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/* stack ������ �켱����, lparen = 0 ���� ���� */
typedef enum{
	lparen = 0,  /* ( ���� ��ȣ */
	rparen = 9,  /* ) ������ ��ȣ*/
	times = 7,   /* * ���� */
	divide = 6,  /* / ������ */
	plus = 5,    /* + ���� */
	minus = 4,   /* - ���� */
	operand = 1 /* �ǿ����� */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression�� �����ϴ� �迭 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix�� ����� ���ڿ��� �����ϴ� �迭 */
char postfixStack[MAX_STACK_SIZE];	/* postfix�� ��ȯ�� ���� �ʿ��� ���� */
int evalStack[MAX_STACK_SIZE];		/* ����� ���� �ʿ��� ���� */

int postfixStackTop = -1;  /* postfixStack�� top */
int evalStackTop = -1;	   /* evalStack�� top */

int evalResult = 0;	   /* ��� ����� ���� */

void postfixpush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main()
{
	setvbuf(stdout, NULL, _IONBF, 0); // Windows �� Eclipse�� Consoleâ ���� �� ������ ���� ����
	setvbuf(stderr, NULL, _IONBF, 0);
	char command;

	do{
		printf("----------------------[�赿��] [2020039023]-----------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I': //������ �Է¹޴´�
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix(); //�Է¹��� ������ postfix���·� ��ȯ�Ѵ�
			break;
		case 'e': case 'E':
			evaluation(); //postfix������ ������ ����Ѵ�
			break;
		case 'd': case 'D':
			debug(); //����� ������ �����(���)�Ѵ�
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

void postfixPush(char x) //������ �켱������ ���� ���ÿ� ��ū�� push�Ѵ�
{
    postfixStack[++postfixStackTop] = x;
}

char postfixPop() //������ �켱������ ���� �����ִ� ��ū�� pop�Ѵ�
{
    char x;
    if(postfixStackTop == -1)
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--];
    }
    return x;
}

void evalPush(int x) //������ top��ġ�� �ϳ� �ø���
{
    evalStack[++evalStackTop] = x;
}

int evalPop() //��ū�� pop�� �� ������ top��ġ�� �ϳ� �ٿ��ش�
{
    if(evalStackTop == -1)
        return -1;
    else
        return evalStack[evalStackTop--];
}

/**
 * infix expression�� �Է¹޴´�.
 * infixExp���� �Էµ� ���� �����Ѵ�.
 */
void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp); //
}

precedence getToken(char symbol) //��ū�� �޾ƿ´�
{
	switch(symbol) { //������ ��ū(�ɺ�)�� �������ΰ��� �ǿ������� ��츦 �����Ͽ��ش�
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;
	}
}

precedence getPriority(char x)
{
	return getToken(x); //���� ������ ��ū�� ��ȯ���ش�
}

/**
 * �����ϳ��� ���޹޾�, postfixExp�� �߰�
 */
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

/**
 * infixExp�� ���ڸ� �ϳ��� �о�鼭 stack�� �̿��Ͽ� postfix�� �����Ѵ�.
 * ����� postfix�� postFixExp�� ����ȴ�.
 */
void toPostfix()
{
	/* infixExp�� ���� �ϳ����� �б����� ������ */
	char *exp = infixExp;
	char x; /* �����ϳ��� �ӽ÷� �����ϱ� ���� ���� */

	/* exp�� �������Ѱ��鼭, ���ڸ� �а� postfix�� ���� */
	while(*exp != '\0')
	{
		if(getPriority(*exp) == operand) //��ūȮ��, operand�� ���, ��ū �ٷ� ���
		{
			x = *exp;
        	charCat(&x);
		}
		else if(getPriority(*exp) == rparen) //������ ��ȣ�� ���, ���� ��ȣ�� ���ö� ���� stack�� ��ū���� pop�Ͽ� ���
			{
			while((x = postfixPop()) != '(') {
				charCat(&x);
			}
		}
		else if(getPriority(*exp) == lparen) //���� ��ȣ�� ���, ��ȣ�� stack���� push
        	postfixPush(*exp);
        else
        {
            while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp)) //�� �������� �켱������ ���Ͽ� stack���� ��ū�� �켱������ ũ��, stack���� ��ū�� �����Ͽ� pop�ϰ�, �׷��� �ʴٸ� ���ο� ��ū�� push���ش�
            {
            	x = postfixPop();
            	charCat(&x);
            }
            postfixPush(*exp);
        }
        exp++;
	}

    while(postfixStackTop != -1)
    {
    	x = postfixPop();
    	charCat(&x);
    }
}
void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset() //��� �迭�� �Ҵ���ִ� ���ĵ��� �ʱ�ȭ�Ѵ�
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';

	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

void evaluation() //postfix�� ������ �����Ѵ�
{
	int op1, op2;
	int length = strlen(postfixExp);
	char symbol;
	evalStackTop = -1;

	for(int i = 0; i < length; i++)
	{
		symbol = postfixExp[i];
		if(getToken(symbol) == operand) { //symbol�� �ǿ������̶�� symbol�� ASCII�ڵ忡�� '0'�� ASCII�ڵ带 ����
			evalPush(symbol - '0');
		}
		else {
			op2 = evalPop();
			op1 = evalPop();
			switch(getToken(symbol)) { //���� ��ū�� ���� ������ �����Ѵ�
			case plus:
				evalPush(op1 + op2);
			break;
			case minus:
				evalPush(op1 - op2);
			break;
			case times:
				evalPush(op1 * op2);
			break;
			case divide:
				evalPush(op1 / op2);
			break;
			default:
			break;
			}
		}
	}
	evalResult = evalPop(); //���ο� ��ū�� �ҷ��´�
}

