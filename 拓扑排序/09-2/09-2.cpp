#include <stdio.h>
#include <string.h>

// 定义节点结构体
struct node
{
    int A;             // 节点入度
    int B;             // 与当前节点有关联的节点数目
    int C;             // 标记节点是否已经输出
    int num;           // 内容字符个数
    char name[10];     // 节点名称
    char content[100]; // 节点内容
};

// 定义列表结构体
struct list
{
    int pointer;
    char content[200];
};

int main()
{
    char *token;
    FILE* fp = fopen("p01.txt", "r");
    struct node Node[200];
    char ch[200];
    fgets(ch, 200, fp);
    int count = 0;
    
    // 读取文件中的每一行数据并处理
    while (fgets(ch, 200, fp))
    {
        Node[count].num = 0;
        token = strtok(ch, ",");
        
        // 保存节点名称信息
        strcpy(Node[count].name, token);
        
        while (token != NULL)
        {
            strcat(Node[count].content, token);
            Node[count].num++;
            token = strtok(NULL, ",");
        }
        
        // 计算节点入度
        if (strlen(Node[count].content) == 3 && Node[count].content[1] == '^')
        {
            Node[count].A = 0;
        }
        else
        {
            Node[count].A = strlen(Node[count].content) - 2;
        }
        count++;
    }

    // 计算与每个节点相关联的节点数目
    for (int a = 0; a < count; a++)
    {
        Node[a].C = 1;//初始化C为1，表示未输出 
        Node[a].B = 0;
        for (int b = 0; b < count; b++)
        {
            for (int c = 1; c < strlen(Node[b].content) - 1; c++)
            {
                if (Node[b].content[c] == Node[a].content[0])
                {
                    Node[a].B++;
                }
            }
        }
    }

  
    
    int ok = 0;
    struct list stack;
    stack.pointer = 0;

    // 拓扑排序
    while (ok < count)
    {
        for (int a = 0; a < count; a++)
        {
            if (Node[a].A == 0 && Node[a].C == 1)
            {
                ok++;
                Node[a].C = 0;//将C改为0，表示已输出 
                printf("%s ", Node[a].name);  // 输出节点名称
                for (int b = 0; b < count; b++)
                {
                    for (int c = 1; c < strlen(Node[b].content) - 1; c++)
                    {
                        if (Node[a].content[0] == Node[b].content[c])
                        {
                            Node[b].A--;//将已输出的节点相关联的节点入度减一 
                        }
                    }
                }
                break;
            }
        }
    }
    
    return 0;
}
