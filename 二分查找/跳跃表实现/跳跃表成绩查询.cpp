//跳跃表成绩查询 
#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
//学号查询，姓名查询与成绩查询如出一辙
struct student {
	int xu;
	char id[30];
	char name[50];
	char gender[5];
	char cla[50];
	int score1;
	int score2;
	int score3;
	int average_score;
	struct student* next;//进入链表下一元素
	struct student* under;//进入下层链表
};

struct student* p;//写入数组的指针
int j = 0;//记录学生个数
FILE* open(const char file_name[], char x[]) {//打开文件
	FILE* file;
	file = NULL;
	file = fopen(file_name, x);
	if (file == NULL) {
		//printf("打开文件失败\n");
	}
	else {
		//printf("打开文件成功\n");
	}
	return file;
}

struct student read(FILE* file) {//读一行数据
	struct student Stu;//定义一个学生
	memset(&Stu, 0, sizeof(struct student));//将结构体内数据设置为零， 方便处理缺考人员
	char ch[100];
	fgets(ch, 100, file);
	sscanf(ch, "%d %s %s %s %s %d %d %d", &Stu.xu, &Stu.id, Stu.name, Stu.gender, Stu.cla, &Stu.score1, &Stu.score2, &Stu.score3);
	Stu.average_score = (Stu.score1 + Stu.score2 + Stu.score3) / 3;//平均成绩

	return Stu;
}

struct student* daoru(FILE* file) {
	struct student* head = NULL;
	struct student* p1, * p2;
	p1 = NULL;
	p2 = NULL;
	while (!feof(file)) {
		if (j == 0) {//建立链表头
			p1 = (struct student*)malloc(sizeof(struct student));
			*p1 = read(file);//为链表赋值
			p1->under = NULL;//将下层置为空作为查找循环的出口
			head = p1;//附上头指针
			p2 = p1;
			j++;
			continue;
		}	
		p1 = (struct student*)malloc(sizeof(struct student));
		*p1 = read(file);
		p2->next = p1;
		p2 = p1;
		j++;
	}
	p2->next = NULL;
	p2 = NULL;
	p1 = NULL;
	return head;
}
struct student* write_list(struct student* head) {//建立多层链表
	int ls = j;//记录下层的链表元素的数量, 如果, 随机建立, 下层数量接近二则停止
	struct student *p1 = head;
	struct student *p2 = p1;//动态建立上层链表
	struct student* p3 = NULL;
	int x;
	srand(time(0));
	while (ls > 2) {//等于二则停止
		ls = 0;//重置元素数量的值
		p2 = head;//更新高度
		p1 = (struct student*)malloc(sizeof(struct student));
		*p1 = *head;//保留头的数据
		p1->under = p2;

		p2  = p2 -> next;//更新数据
		head = p1;//改变入口
		p3 = p1;//上层节点
		ls++;
		while (p2 ->next != NULL) {
			x = rand() % 2;//生成0或1
			if (x > 0) {//建立上次链表
				p1 = (struct student*)malloc(sizeof(struct student));
				*p1 = *p2;//赋值
				p1->under = p2;
				p3->next = p1;
				p3 = p1;
				ls++;
			}
			p2 = p2->next;
		}
	p1 = (struct student*)malloc(sizeof(struct student));
	*p1 = *p2;
	p1->under = p2;
	p3->next = p1;
	ls++;
	}
	return head;
}
void kaichang(void) {
	printf("欢迎进入学生信息查询系统\n");
	printf("目前已存储%d名学生信息\n", j);
}
FILE* inser(const char x[], char a[]) {
	FILE* file;
	char ch[100];
	file = open(x, a);
	return file;
}
int id_seek(struct student *head, char ch[]) {
	struct student* p1;
	p1 = head;
	struct student* p2;
	p2 = head;
	struct student* p3;
	p3 = head;
	int x = 0;
	if (strcmp(ch, p1->id) < 0) {
		printf("该学生不存在\n");
		//printf("11\n");//排除小于头指针的
		return 0;
	}
	while (p1 != NULL) {
		p2 = p1;
		x = 0;//计数
		while (p2 != NULL) {

			if(strcmp(ch, p2->id)  ==  0) {
				printf("学号      姓名   性别 行政班    进制转换 多进制转换 数值表达逻辑代数 平均分\n");
				printf("%s %s %s   %s %d       %d         %d               %d\n", p2->id, p2->name, p2->gender, p2->cla, p2->score1, p2->score2, p2->score3, p2->average_score);
				return 1;
			}
			if (strcmp(ch, p2->id) < 0) {
				
				break;
			}
			if(x > 1)
			   p1 = p1->next;//避免跳过目标数据
			p2 = p2->next;
			x++;
		}
		p1 = p1->under;
	}

	printf("该学生不存在\n");
	return 0;
}
void clear(struct student* head) {//释放内存
	struct student* ps = head;
	while(ps != NULL){
		struct student* st = ps;
		ps = ps->under;
		while (st != NULL)
		{
			struct student* ts = st;
			st = st->next;
			free(ts);
		}
		st = ps;
	}
	printf("内存清除完成\n");
}
int main() {
	FILE* file = inser("学号排序.txt", "r");//打开文件
	read(file);//读掉第一行
	char ch[100];
	struct student *head = daoru(file);//建立最低层的链表
	fclose(file);
	file = NULL;//置空指针
	head = write_list(head);
	kaichang();
	printf("请输入学生学号进行查询/输入exit退出\n");
	scanf("%s", ch);
	while (strcmp(ch, "exit") != 0) {
		id_seek(head, ch);
		scanf("%s", ch);
	}
	clear(head);//清除动态的内存
	return 0;
}
