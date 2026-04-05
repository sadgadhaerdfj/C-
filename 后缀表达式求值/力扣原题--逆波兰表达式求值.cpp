#include <stdlib.h>
#include <string.h>
#include <stdio.h>
int evalRPN(char ** tokens, int tokensSize)
{
    int stack[tokensSize];                                              //创建栈
    int top = -1;                                                       //栈顶指针

    for(int i=0; i < tokensSize; ++i)     //遍历后缀表达式字符串
	{                                  
        char* token = tokens[i];
        if((token[0] >= '0' && token[0] <= '9') || strlen(token) > 1)    //如果当前元素是操作数，则将其转换为整数并压入栈中
		{
            stack[++top] = atoi(token);                                 
        }
		else   //如果当前元素是运算符，则从栈中弹出两个操作数，并按照当前运算符进行相应的计算，再将计算结果压入栈中
		{                                                          
            switch(token[0])
			{
                case'+':
                    stack[top-1] = stack[top-1] + stack[top];           
                    break;
                case'-':
                    stack[top-1] = stack[top-1] - stack[top];
                    break;
                case'*':
                    stack[top-1] = stack[top-1] * stack[top];
                    break;
                case'/':
                    stack[top-1] = stack[top-1] / stack[top];
                    break;
            }
            --top;
        }
    }

    return stack[top];                                                  //最终结果为栈顶元素
}

int main() {
    char *tokens[] = {"2", "1", "+", "3", "*"}; 
    //字符串数组tokens中的元素分别为示例1后缀表达式中对应的元素 
    int tokensSize = sizeof(tokens) / sizeof(tokens[0]);
    int result = evalRPN(tokens, tokensSize);   //调用evalRPN 函数并将 tokens 数组和其大小作为参数传入，将计算结果存储在变量 result 中  
    printf("计算结果：%d\n", result);
    return 0;
}
