#include <stdio.h>
#include <stdlib.h>
#define MAX_STR_SIZE 50    //一行的字符不超过50个 
#define LEN sizeof(struct Student)

struct Student
{
	char str[MAX_STR_SIZE];   		//某行的所有数据 
	int num;        				//该行的学号 
	char name[10];   			    //该行的姓名 
	short score;   					//该行的分数 
	struct Student * next;
};

FILE * fp;
int n;       //计数变量 
int count;  //总人数，用于求平均分 

//创建一个动态链表并写入数据 
struct Student *  creat(void)
{
	struct Student * head, * p1, * p2;
	n = 0;
	
	fp = fopen("成绩.txt","r");
	if (fp == NULL) 
	{
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
	
	p1 = p2 = (struct Student * )malloc(LEN);//表示分配一个大小为 struct Student 的内存块，并返回一个指向该内存块的指针。
	fgets(p1->str,MAX_STR_SIZE,fp);//使用 fgets 函数从文件中读取一行数据，三个参数分别表示：
	                               //指向一个字符数组的指针，用于存储读取到的字符串；
	                               //要读取的最大字符数（包括换行符和字符串结束符）；
								   //指向一个已打开的文件的指针，表示要从哪个文件中读取数据； 

	head = NULL;
	while (fgets(p1->str, MAX_STR_SIZE, fp) != NULL)   													   
	{
		//将总人数，学号，名字，分数分别存储在 count、p1->num、p1->name 和 p1->score 变量中 
		sscanf(p1->str,"%d %d %s %d",&count,&p1->num,p1->name,&p1->score);  		
		n++;  //增加计数器 n 的值，表示已经读取了一个学生信息
		//如果 n 的值为 1，说明是第一个节点，将 head 指针指向该节点
		if (n == 1)
		{
			head = p1;
		}
		//否则，将上一个节点 p2 的 next 指针指向当前节点 p1
		else
		{
			p2->next = p1;
		}
		p2 = p1;   //更新指针 p2 的值为 p1，以便下一次循环时将当前节点作为上一个节点
		p1 = (struct Student * )malloc(LEN);    //使用 malloc() 函数为下一个节点 p1 分配内存空间，并继续循环，读取并处理下一行学生信息
		
	}
	p2->next = NULL;
	
	fclose(fp);
	return head;
	
}

int max_score,min_score;   //两个变量分别储存最高分和最低分 

int main()
{
	
	// 设置控制台输出为 UTF-8，以解决中文乱码问题 
	//SetConsoleOutputCP(CP_UTF8);
	
	struct Student *head = creat();      //调用creat函数并返回head指针 
	struct Student *current = head;
	max_score = current->score;      //把第一个同学的成绩赋值给max_score和min_score作为初始值 
	min_score = current->score;
	float sum = 0;  //所有人的分数总和 
	
	//第一个循环用于求出sum,max_score和min_score 
	while(current != NULL)   //只要当前指针所指向的节点不为空，就一直执行循环体中的操作
	{
		sum += current->score;    //将当前节点的成绩累加到总成绩 sum 中
		
		if((current->score) > max_score)   //如果当前节点的成绩比最高分 max_score 还要高，就将 max_score 更新为当前节点的成绩
		{
			max_score = current->score;    
		}
		if((current->score) < min_score)   //如果当前节点的成绩比最低分 min_score 还要低，就将 min_score 更新为当前节点的成绩
		{
			min_score = current->score;
		}	
		
		current = current->next;           //将当前指针指向下一个节点，以便下一次循环时继续处理下一个节点
	} 
	
	//输出平均分
	printf("平均分：%.2f\n\n\n",sum/count); 
		
	//第二个循环用于output 
	current = head;           //将 current 指针重新指向链表的头节点，从头开始遍历链表
	while(current != NULL)
	{
		
		if((current->score) == max_score)  //检查当前节点的成绩是否与最高分 max_score 相等
		{
			printf("最高分：%d  姓名：%s  学号：%d\n",max_score,current->name,current->num);   //如果相等，打印出最高分的学生信息，包括成绩、姓名和学号
		}
		if((current->score) == min_score)  //检查当前节点的成绩是否与最低分 min_score 相等
		{
			printf("最低分：%d  姓名：%s  学号：%d\n\n",min_score,current->name,current->num);  //如果相等，打印出最低分的学生信息，包括成绩、姓名和学号
		}	
		
		current = current->next;  //将当前指针指向下一个节点，以便下一次循环时处理下一个节点
	} 

	// 第三个循环用于释放链表内存
    current = head;    //将 current 指针重新指向链表的头节点，从头开始遍历链表
    while (current != NULL) 
	{
    	
        struct Student *temp = current;  //创建一个临时指针 temp，将其指向当前节点 current
        current = current->next;         //将 current 指针指向下一个节点，以便在释放当前节点之后继续遍历链表
        free(temp);                      //使用 free() 函数释放 temp 指针所指向的节点的内存空间
    }

	return 0;

}


