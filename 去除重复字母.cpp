//去除重复字母
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* removeDuplicates(char* s)
{
	if(s==NULL || strlen(s)==0)
	{
		return "";
	}
	if(strlen(s)==1)
	{
		return s;
	}
	int len=(int)strlen(s);
	char recode[26]={0};
	for(int i=0;i<len;i++)
	{
		recode[s[i]-'a']++;
	}
	char * stack=(char*)malloc(sizeof(char)*(len+2));
	int top=-1;
	int isExist;
	for(int i=0;i<len;i++)
	{
		isExist=0;
		for(int j=0;j<=top;j++)
		{
			if(s[i]==stack[j])
			{
				isExist=1;
				break;
			}
		}
		if(isExist)
		{
			recode[s[i]-'a']--;
		}
		else
		{
			while(top>-1 && stack[top]>s[i] && recode[stack[top]-'a']>1)
			{
				recode[stack[top]-'a']--;
				top--;
			}
			stack[++top]=s[i];
		}
	}
	stack[++top]='\0';
	return stack;
}

int main()
{
	char input[100];
	printf("请输入一串字符：");
	scanf("%s",input);
	char *result=removeDuplicates(input);
	printf("去重后且字典序最小的字符串为：%s\n",result);
	free(result);
	return 0;
}
