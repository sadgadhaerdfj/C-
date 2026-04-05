#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* removeDuplicates(char* s) 
{
    if (s == NULL || strlen(s) == 0) 
	{
        return "";
    }
    if (strlen(s) == 1) 
	{
        return s;
    }
    int len = (int)strlen(s); // s的长度 
    char recode[26] = {0}; // 计数，每一个字母出现次数 
    
    for (int i=0; i<len; i++) 
	{
        recode[s[i] - 'a']++;// 'a'是字符'a'的ASCII码值97 (s[i] - 'a')偏移量0-25表示a-z 
    }


    char * stack = (char *)malloc(sizeof(char) * (len+2));
    int top = -1;                                         
    
    int isExist;  // 已经存在过
    for (int i=0; i<len; i++) 
	{
        isExist = 0;
        for (int j=0; j <= top; j++) 
		{
            if (s[i] == stack[j]) 
			{
                isExist = 1;
                break;
            }
        }
        
        if (isExist) 
		{
            recode[s[i] - 'a']--;
        }
		else
		{
            while(top>-1 && stack[top] > s[i] && recode[stack[top] - 'a'] > 1) 
			{
            	
                //如果栈顶字符比当前大，并且后边还会出现
                recode[stack[top] - 'a']--;
                //出栈
                top--;

            }
            //入栈
            stack[++top] = s[i];
        }
    }
    stack[++top] = '\0';
    return stack;
}


int main() 
{
    char input[100];
    printf("请输入一串字符：");
    scanf("%s", input);
    char *result = removeDuplicates(input);
    printf("去重后且字典序最小的字符串为：%s\n", result);
    free(result); // 释放内存
    return 0;
}



