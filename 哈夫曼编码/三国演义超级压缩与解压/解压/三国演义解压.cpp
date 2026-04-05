#include<stdio.h>
#include <string.h>
#include <cstdlib>
#include <iostream>
unsigned char byte = 0;
int bitCount = 0;


// 定义哈夫曼树的节点结构体
typedef struct Node 
{
	char name[10];
    int condition;   // 节点状态：0表示未使用，1表示已使用
    int weight;      // 节点权重
    int parent;      // 父节点号
    int lchild;      // 左孩子节点号
    int rchild;      // 右孩子节点号
    char code[100];
} node_1;
node_1 ps[100000];  // 哈夫曼树的节点数组

// 用于存储查找最小值时的结果的结构体
typedef struct 
{
    int result_l;       // 最小权重节点的权重
    int result_r;       // 次小权重节点的权重
    int l_subscript;    // 最小权重节点的下标
    int r_subscript;    // 次小权重节点的下标
} Two;

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

int main(){
	
	 node_1 gdx[10000];
	FILE* fp=fopen("三国演义权重.txt","r");
	if(fp==NULL){
		printf("打开失败"); 
		return 0;	
	}
	char ch[200] ;
	int count1=0;
	while(fgets(ch,200,fp)){                        
    char *token = strtok(ch, ",");
    int count = 0;                                            
    while (token != NULL) {
        switch (count) {
            case 0:
                strcpy(ps[count1].name, token); 
                break;
            case 1:
            	ps[count1].weight=atoi(token);
                break;
            default:
                break;
        }

        // 获取下一个字段
        token = strtok(NULL, ",");
        count++;
    }
	count1++;
}

	int num=count1;
	Two result_min;
	for (int c =num ;c<2*num-1;c++){
		result_min=find_min(c);
		ps[c].lchild=result_min.l_subscript;
		ps[c].rchild=result_min.r_subscript;
		ps[c].weight=ps[result_min.l_subscript].weight+ps[result_min.r_subscript].weight;
		ps[result_min.l_subscript].parent=c;
		ps[result_min.r_subscript].parent=c;
	}
	make_code(num*2-2,num);
	int min=1000;
for (int c = 0; c < num * 2 - 1; c++) {
    if (c >= num) {
    	if(ps[c].parent + 1==1){
    		// 无父节点的情况
		}else{
		// 输出节点的相关信息，包括父节点、子节点和哈夫曼编码
			   }
    } 
	else {
		if (min>strlen(ps[c].code)){
			min=strlen(ps[c].code);
		}
        printf("%s  出现次数为%-5d次    哈夫曼编码为%s\n",ps[c].name , ps[c].weight,ps[c].code);
    }
}		
		fclose(fp);

FILE *fp4 = fopen("三国演义压缩.txt", "rb");
    FILE* fp5=fopen("三国演义解压.txt","w");
    if (fp4 == NULL) {
        perror("Error opening file");
        return 1;
    }

    int bit;
    int byte;
    char content[100];
    char binaryString[9];  // 8位比特 + 结尾的空字符
    int ok=0;
    while ((byte = fgetc(fp4)) != EOF ) {    	 
        for (int i = 7; i >= 0; i--) {
            bit = (byte >> i) & 1;
            binaryString[7 - i] = '0' + bit;  // 转换为字符 '0' 或 '1'
        }
        binaryString[8] = '\0';  // 添加字符串结束符
        for (int a = 0;a<8;a++){
        	char nb[3];
        	
        	nb[0]=binaryString[a];
        	nb[1]='\0';
        	strcat(content,nb);
        
           for (int c =0 ;c<num; c++){
           	   if (strcmp(ps[c].code,content)==0){          	   	
           	   	   memset(content, 0, sizeof(content));
           	   	   if (strcmp("\\n",ps[c].name)==0){
           	   	   	printf("\n");
           	   	   	fputs("\n",fp5);
						 }else{
						 	printf("%s",ps[c].name);
						 	fprintf(fp5,"%s",ps[c].name);						 	
						 }break;           	   	   
				  }
		   }        	
		}
}
    fclose(fp4);
printf("%d",min);
	return 0;
}
