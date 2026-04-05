//中缀表达式转后缀表达式
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100
//转化规则： 
// 如果当前字符是左括号(，则直接将其入栈。
// 如果当前字符是右括号)，则需要将栈中的运算符出栈，直到遇到左括号为止。
// 出栈的运算符将被添加到后缀表达式中。
// 如果在出栈过程中没有遇到左括号，说明表达式的括号不匹配，会输出"无效表达"并结束程序。
// 如果遇到左括号，则将其弹出栈。
// 如果当前字符是运算符，则需要与栈顶的运算符进行优先级比较。
// 如果栈顶的运算符优先级大于等于当前运算符，则将栈顶的运算符出栈并添加到后缀表达式中。
// 重复这个过程直到栈为空或栈顶的运算符优先级小于当前运算符的优先级。
// 然后将当前运算符入栈。

// 定义栈结构 
typedef struct   //typedef用于给已有的数据类型起一个新的别名Stack
{
    char data[MAX_SIZE];
    int top;    //  top 变量表示栈顶元素的索引，它随着栈的操作而动态变化。
} Stack;

// 初始化栈 栈顶为-1 表示栈为空
void initStack(Stack *s) 
{
    s->top = -1;
}

// 用来判断栈是否为空 
int ifEmpty(Stack *s) 
{
    return s->top == -1;// 判断栈顶 top 是否等于 -1。如果等于 -1，则返回1，表示栈为空；否则，返回0，表示栈不为空。
}

// 用来判断栈是否已满 
int ifFull(Stack *s) 
{
    return s->top == MAX_SIZE - 1;//如果栈顶 top等于 MAX_SIZE - 1，则返回1，表示栈已满；否则，返回0，表示栈未满。
}

// 入栈 
void push(Stack *s, char c) 
{ // char c要入栈的元素 
    if (ifFull(s)) //如果栈已满，则输出提示信息 "满栈" 并返回，表示无法执行入栈操作
	{
        printf("满栈\n");
        return;
    }
    // (s->top) 表达式获取栈顶指针 top 的当前值,++(s->top)将top递增 
    s->data[++(s->top)] = c;//将栈顶指针 top 移动到新的位置，然后再将元素 c 存储到该位置上。
}

// 出栈 
char pop(Stack *s) 
{
    if (ifEmpty(s)) //如果栈为空，则输出提示信息 "空栈" 并返回空字符 '\0'，表示无法执行出栈操作
	{
        printf("空栈\n");
        return '\0';
    }
    return s->data[(s->top)--];//先取出栈顶元素，然后将栈顶指针指向下一个位置，实现出栈操作。
}

// 获取栈顶元素 
char get(Stack *s) 
{
    if (ifEmpty(s)) 
	{
        printf("空栈\n");
        return '\0';
    }
    return s->data[s->top];//s->data 表示栈的数据数组，s->top 表示栈顶指针，通过 s->top 来访问栈顶元素的值
}

// 判断运算符的优先级 
int precedence(char o) 
{ // switch据表达式的值选择不同的执行路径 
    switch (o) 
	{ // 将op与每个case进行比较，相等则执行，返回优先级1，2，3 
        case '+':
        case '-':
            return 1;//优先级最低
        case '*':
        case '/':
            return 2;//优先级较高
        case '^':
            return 3;//优先级最高 
    }
    return -1;//如果输入的运算符不是上述三种运算符之一，则返回整数值 -1，表示输入的运算符无效
}

// 判断字符是否是操作数 
int ifOperand(char c) 
{
    return (c >= '0' && c <= '9');
}

// 将中缀表达式转换为后缀表达式 
void infixToPostfix(char *infix, char *postfix) 
{
    Stack stack; // 定义一个栈 
    initStack(&stack);// 初始化栈传递地址用于指针操作 
    int i, j = 0;
    int len = strlen(infix);// 输入的中缀长度 

    for (i = 0; i < len; i++) //循环遍历中缀表达式中的每个字符
	{
        char c = infix[i];//获取中缀元素 
        if (ifOperand(c)) 
		{//如果是否数字，则将连续的操作数依次添加到后缀表达式中，并在操作数后添加一个特殊符号 # 
            while (ifOperand(infix[i])) 
			{
//            	printf("%d和%d\n",i,j);
                postfix[j++] = infix[i++]; 
            }
//            printf("%d和%d\n",i,j);
            postfix[j++] = '#';  // 在操作数后添加"#"
//            printf("%d和%d\n",i,j);
            i--;  // 回退一个字符，因为在外层循环中会自增 
        } 
		else //如果字符 c 是运算符，根据运算符的优先级进行处理：
		{
            if (c == '(') 
			{ // 左括号直接入栈 
                push(&stack, c);
            } 
			else if (c == ')') 
			{ // 右括号出栈直到碰到左括号 
                while (!ifEmpty(&stack) && get(&stack) != '(') 
				{
                    postfix[j++] = pop(&stack);
                }
                if (!ifEmpty(&stack) && get(&stack) != '(') 
				{
                    printf("无效表达\n");
                    return;
                } else {
                    pop(&stack);  // 弹出'('
                }
            } 
			else 
			{ // 优先级比较 
                while (!ifEmpty(&stack) && precedence(c) <= precedence(get(&stack))) //如果栈顶的运算符优先级大于等于当前运算符 c 的优先级，则将栈顶的运算符弹出并添加到后缀表达式中
				{
                    postfix[j++] = pop(&stack); 
                }
                push(&stack, c); //然后将当前运算符 c 入栈
            }
        }
    }

    while (!ifEmpty(&stack)) //将栈中剩余的元素依次弹出并添加到后缀表达式中，最后在后缀表达式的末尾添加一个字符串结束符 \0
	{  
        postfix[j++] = pop(&stack);
    }
    postfix[j] = '\0';
}
                                                                                                                                                                                                                                                                               
int main() 
{
    char infix[MAX_SIZE];
    char postfix[MAX_SIZE];  

    printf("请输入中缀表达式： ");
    fgets(infix, MAX_SIZE, stdin); // stdin,输入流 
    infix[strlen(infix) - 1] = '\0';  // 去除换行符为结束符 
    infixToPostfix(infix, postfix);
    printf("对应的后缀表达式为: %s\n", postfix);
    return 0;
}

