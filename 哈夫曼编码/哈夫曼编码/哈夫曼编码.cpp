#include<stdio.h>
#include <string.h>
#include <cstdlib>
#include <iostream>


// 定义哈夫曼树的节点结构体
typedef struct Node 
{
    int condition;   // 节点状态：0表示未使用，1表示已使用
    int weight;      // 节点权重
    int parent;      // 父节点号
    int lchild;      // 左孩子节点号
    int rchild;      // 右孩子节点号
    char code[100];
} node_1;

node_1 ps[100];  // 哈夫曼树的节点数组

// 用于存储查找最小值时的结果的结构体
typedef struct 
{
    int result_l;       // 最小权重节点的权重
    int result_r;       // 次小权重节点的权重
    int l_subscript;    // 最小权重节点的下标
    int r_subscript;    // 次小权重节点的下标
} Two;

// 查找权重最小的两个节点
Two find_min(int sum) 
{
    int min = 99999999, dex;//初始化变量 min 为一个较大的数值，用于比较节点的权重大小；变量 dex 来记录最小权重节点的下标 
    Two result;//定义了一个结构体变量 result 来存储查找结果
    
    // 查找最小权重节点
    for (int c = 0; c < sum; c++) 
	{
        if (ps[c].weight < min && ps[c].condition == 0) 
		{//循环遍历所有的节点，查找权重最小的未使用节点
            min = ps[c].weight;//将其权重值赋给 min
            dex = c;//将节点的下标赋给 dex
        }
    }
    ps[dex].condition = 1;  // 将最小权重节点标记为已使用
    //将最小权重值和对应的下标存储到 result 结构体的相应字段中
    result.result_l = min;
    result.l_subscript = dex;
    
    min = 99999999;//重新将 min 初始化为一个较大的数值，用于查找次小权重节点
    // 查找次小权重节点
    for (int c = 0; c < sum; c++) 
	{
        if (ps[c].weight < min && ps[c].condition == 0) 
		{//循环遍历所有的节点，查找权重次小的未使用节点
            min = ps[c].weight;//将其权重值赋给 min
            dex = c;//将节点的下标赋给 dex
        }
    }
    ps[dex].condition = 1;  // 将次小权重节点标记为已使用
    //将次小权重值和对应的下标存储到 result 结构体的相应字段中
    result.result_r = min;
    result.r_subscript = dex;
    
    return result;
}
// 给字符串追加一个字符
char* appendOne(const char *original, char append) {
    char *result = (char*)malloc(strlen(original) + 2);  // 动态分配足够的内存，加上一个字符和字符串结束符的空间
    if (result == NULL) {
        // 处理内存分配失败的情况
        exit(1);
    }
    strcpy(result, original);  // 复制原始字符串到新的内存空间
    result[strlen(original)] = append;  // 在新字符串末尾追加指定字符
    result[strlen(original) + 1] = '\0';  // 添加字符串结束符
    return result;  // 返回新的字符串
}
// 生成每个节点的哈夫曼编码
void make_code(int a, int num) { // a 表示第几个节点
    if (a == num * 2 - 2) {
        // 如果是非叶子节点，分别给左右孩子节点赋值哈夫曼编码"0"和"1"
        strcpy(ps[ps[a].lchild].code, "0");
        strcpy(ps[ps[a].rchild].code, "1");
        // 递归处理左右孩子节点
        make_code(ps[a].lchild, num);
        make_code(ps[a].rchild, num);
    } 
    if (a >= num && a != num * 2 - 2) {
        // 给左右孩子节点追加哈夫曼编码并赋值
        strcpy(ps[ps[a].lchild].code, appendOne(ps[a].code, '0'));
        strcpy(ps[ps[a].rchild].code, appendOne(ps[a].code, '1'));
        // 递归处理左右孩子节点
        make_code(ps[a].lchild, num);
        make_code(ps[a].rchild, num);
    }
}

int main() 
{
    int num;
    printf("请输入用来构建哈夫曼树的带权重的节点的个数：\n"); 
    scanf("%d", &num);
    printf("请输入%d个整数来表示权重(输入的数以空格分开)\n", num);
    Two result_min;
    
    // 输入节点的权重
    for (int c = 0; c < num; c++) 
	{
        scanf("%d", &ps[c].weight);
    }
    
    // 构建哈夫曼树的节点数组
    for (int c = num; c < 2 * num - 1; c++) 
	{
        result_min = find_min(c);//调用 find_min 函数来找到权重最小和次小的两个节点
        ps[c].lchild = result_min.l_subscript;
        ps[c].rchild = result_min.r_subscript;
        ps[c].weight = ps[result_min.l_subscript].weight + ps[result_min.r_subscript].weight;//根据它们的权重值和下标信息构建新的节点
        ps[result_min.l_subscript].parent = c;
        ps[result_min.r_subscript].parent = c;
    }

    // 输出每个节点的信息
    for (int c = 0; c < num * 2 - 1; c++) 
	{
        if (c >= num) 
		{//如果当前节点的下标大于等于输入的节点个数 num，说明这是构建哈夫曼树时新增的节点（非输入节点）
            if (ps[c].parent + 1 == 1) //如果父节点下标加1等于1，表示当前节点没有父节点（即为根节点），输出的信息中不包含父节点信息。
			{
                printf("第%-2d个节点  权重为%-5d  左子节点为第%-2d个  右子节点为第%-2d个  (无父节点)\n",
               c + 1, ps[c].weight, ps[c].lchild + 1, ps[c].rchild + 1);
            } 
			else //如果当前节点有父节点（不是根节点），则输出节点的权重、父节点、左子节点和右子节点和哈夫曼编码的信息。
			{
                printf("第%-2d个节点  权重为%-5d  父节点为第%-2d个  左子节点为第%-2d个  右子节点为第%-2d个  哈夫曼编码为%s\n",
               c + 1, ps[c].weight, ps[c].parent + 1, ps[c].lchild + 1, ps[c].rchild + 1,ps[c].code);
            }
        } 
		else //如果当前节点的下标小于输入的节点个数 num，说明这是原始输入的节点，它们没有左子节点和右子节点，只输出节点的权重和父节点和哈夫曼编码的信息
		{
            printf("第%-2d个节点  权重为%-5d  父节点为第%-2d个  哈夫曼编码为%s(无左右子节点)\n", c + 1, ps[c].weight, ps[c].parent + 1,ps[c].code);
        }
    }	
    return 0;
}
