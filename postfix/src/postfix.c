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

/* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum{
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;	   /* evalStack용 top */

int evalResult = 0;	   /* 계산 결과를 저장 */

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
	setvbuf(stdout, NULL, _IONBF, 0); // Windows 용 Eclipse의 Console창 글자 안 나오는 오류 수정
	setvbuf(stderr, NULL, _IONBF, 0);
	char command;

	do{
		printf("----------------------[김동원] [2020039023]-----------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I': //수식을 입력받는다
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix(); //입력받은 수식을 postfix형태로 변환한다
			break;
		case 'e': case 'E':
			evaluation(); //postfix형태의 수식을 계산한다
			break;
		case 'd': case 'D':
			debug(); //계산한 내용을 디버그(출력)한다
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

void postfixPush(char x) //연산자 우선순위에 따라 스택에 토큰을 push한다
{
    postfixStack[++postfixStackTop] = x;
}

char postfixPop() //연산자 우선순위에 따라 스택있는 토큰을 pop한다
{
    char x;
    if(postfixStackTop == -1)
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--];
    }
    return x;
}

void evalPush(int x) //스택의 top위치를 하나 올린다
{
    evalStack[++evalStackTop] = x;
}

int evalPop() //토큰을 pop한 뒤 스택의 top위치를 하나 줄여준다
{
    if(evalStackTop == -1)
        return -1;
    else
        return evalStack[evalStackTop--];
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp); //
}

precedence getToken(char symbol) //토큰을 받아온다
{
	switch(symbol) { //가져온 토큰(심볼)이 연산자인경우와 피연산자인 경우를 구분하여준다
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
	return getToken(x); //현재 차례의 토큰을 반환해준다
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp;
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while(*exp != '\0')
	{
		if(getPriority(*exp) == operand) //토큰확인, operand일 경우, 토큰 바로 출력
		{
			x = *exp;
        	charCat(&x);
		}
		else if(getPriority(*exp) == rparen) //오른쪽 괄호일 경우, 왼쪽 괄호가 나올때 까지 stack의 토큰들을 pop하여 출력
			{
			while((x = postfixPop()) != '(') {
				charCat(&x);
			}
		}
		else if(getPriority(*exp) == lparen) //왼쪽 괄호일 경우, 괄호를 stack으로 push
        	postfixPush(*exp);
        else
        {
            while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp)) //두 연산자의 우선순위를 비교하여 stack안의 토큰의 우선순위가 크면, stack에서 토큰을 제거하여 pop하고, 그렇지 않다면 새로운 토큰을 push해준다
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

void reset() //모든 배열에 할당돼있는 수식들을 초기화한다
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';

	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

void evaluation() //postfix된 수식을 연산한다
{
	int op1, op2;
	int length = strlen(postfixExp);
	char symbol;
	evalStackTop = -1;

	for(int i = 0; i < length; i++)
	{
		symbol = postfixExp[i];
		if(getToken(symbol) == operand) { //symbol이 피연산자이라면 symbol의 ASCII코드에서 '0'의 ASCII코드를 뺀다
			evalPush(symbol - '0');
		}
		else {
			op2 = evalPop();
			op1 = evalPop();
			switch(getToken(symbol)) { //받은 토큰에 따라 연산을 진행한다
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
	evalResult = evalPop(); //새로운 토큰을 불러온다
}

