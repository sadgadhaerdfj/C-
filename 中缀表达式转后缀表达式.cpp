//中缀表达式式转后缀表达式
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100


//定义栈结构
typedef struct
{
	char data[MAX_SIZE];
	int top;
 } Stack;
 
//初始化栈结构
void initStack(Stack *s)
{
	s->top=-1;
}
  
//用来判断栈结构是否为空
int ifEmpty(Stack *s)
{
	return s->top==-1;
}

//用来判断栈结构是否已满
int ifFull(Stack *s)
{
	return s->top==MAX_SIZE-1;
 } 
 
//入栈
void push(Stack *s,char c)
{
	if(ifFull(s))
	{
		printf("满栈\n");
		return; 
	}
	s->data[++(s->top)]=c;
}

//出栈
char pop(Stack *s)
{
	if(ifEmpty(s))
	{
		printf("空栈\n");
		return '\0';
	}
	return s->data[(s->top)--];
 } 
 
//获取栈顶元素
char get(Stack *s)
{
	if(ifEmpty(s))
	{
		printf("空栈\n");
		return '\0';
	}
	return s->data[(s->top)];
}

//判断运算符的优先级
int precedence(char o)
{
	switch(o)
	{
		case '+':
		case '-':
		    return 1;
		case '*':
		case '/':
			return 2;
		case '^':
			return 3;
	}
	return -1;
 }
 
//判断字符是否是操作数
int ifOperand(char c)
{
	return (c>='0' && c<='9');
 } 

//将中缀表达式转换为后缀表达式
void infixToPostfix(char *infix,char *postfix)
{
	Stack stack;
	initStack(&stack);
	int i,j=0;
	int len=strlen(infix);
	for (i=0;i<len;i++)
	{
		char c=infix[i];
		if(ifOperand(c))
		{
			while(ifOperand(infix[i]))
			{
				postfix[j++]=infix[i++];
			}
			postfix[j++]='#';
			i--;
		}
		else
		{
			if(c=='(')
			{
				push(&stack,c);
			}
			else if(c==')')
			{
				while(!ifEmpty(&stack) && get(&stack) !='(')
				{
					postfix[j++]=pop(&stack);
				}
				if(!ifEmpty(&stack) && get(&stack) !='(')
				{
					printf("无效表达\n");
					return;
				}
				else
				{
					pop(&stack);
				}
			}
			else
			{
				while(!ifEmpty(&stack) && precedence(c)<=precedence(get(&stack)))
				{
					postfix[j++]=pop(&stack);
				}
				push(&stack,c);
			}
		}
	}
	while(!ifEmpty(&stack))
	{
		postfix[j++]=pop(&stack);
	}
	postfix[j]='\0';
	
 }

int main()
{
	char infix[MAX_SIZE];
	char postfix[MAX_SIZE];
	printf("请输入中缀表达式：");
	fgets(infix,MAX_SIZE,stdin);
	infix[strlen(infix)-1]='\0';
	infixToPostfix(infix,postfix);
	printf("对应的后缀表达式为：%s\n",postfix);
	return 0; 
 } 
