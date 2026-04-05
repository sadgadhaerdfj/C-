//力扣原题（逆波兰表达式求值）
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int evalRPN(char ** tokens,int tokensSize)
{
	int stack[tokensSize];
	int top=-1;
	for(int i=0;i<tokensSize;++i)
	{
		char* token=tokens[i];
		if((token[0]>='0' && token[0]<='9') || strlen(token)>1)
		{
			stack[++top]=atoi(token);
		}
		else
		{
			switch(token[0])
			{
				case'+':
					stack[top-1]=stack[top-1]+stack[top];
					break;
				case'-':
					stack[top-1]=stack[top-1]-stack[top];
					break;
				case'*':
					stack[top-1]=stack[top-1]*stack[top];
					break;
				case'/':
					stack[top-1]=stack[top-1]/stack[top];
					break;
				
			}
			--top;
		}
	}
	return stack[top];
}

int main()
{
	char *tokens[]={"2","1","+","3","*"}; 
	//字符串数组tokens中的元素分别为示例1后缀表达式中对应的元素
	int tokensSize=sizeof(tokens)/sizeof(tokens[0]);
	int result=evalRPN(tokens,tokensSize);
	printf("计算结果为：%d\n",result);
	return 0; 
}
