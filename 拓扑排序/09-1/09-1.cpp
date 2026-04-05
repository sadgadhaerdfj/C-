#include<stdio.h>
#include<string.h>

struct node
{
    int A;          // 存储计算得到的值A
    int num;        // 存储内容数量
    char name[10];  // 名称字段
    char content[100];  // 存储内容字符串
};

int main()
{
    char *token;
    FILE* fp=fopen("p01.txt","r");
    if (fp == NULL) {
        printf("Failed to open file.\n");
        return 1;
    }
    
    struct node Node[200];
    char ch[200];
    fgets(ch,200,fp);  // 读取文件中的一行作为标题行

    int count=0;
    
    while(fgets(ch,200,fp)) {
        memset(Node[count].content, 0, sizeof(Node[count].content));  // 清空 content 字段
        Node[count].num = 0;  // 初始化 num 字段
        token = strtok(ch, ",");  // 使用逗号分割字符串
        strcpy(Node[count].name, token);
        
        // 解析每行内容并存储到 content 字段中
        while (token != NULL) {
            strcat(Node[count].content, token);
            Node[count].num++;
            token = strtok(NULL, ",");
        }

        // 计算 A 字段的值
        if (strlen(Node[count].content) == 3 && Node[count].content[1] == '^') {
            Node[count].A = 0;
        } else {
            Node[count].A = strlen(Node[count].content) - 2;
        }
        count++;
   }
   
   fclose(fp);
   
   // 输出处理后的数据
   printf("序号\t入度数\t字符名\t指向\n");
   for (int a = 0; a < count; a++) {
       printf("%d\t%d\t%s\t", a, Node[a].A, Node[a].name);
       for (int b = 0; b < count; b++) {
           for (int c = 1; c < strlen(Node[b].content) - 1; c++) {
               if (Node[b].content[c] == Node[a].content[0]) {
                   printf("->%d", b);
               }
           }
       }
       printf("^\n");
   }
   
   return 0;
}
