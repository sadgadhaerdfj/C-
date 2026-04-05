#include <stdio.h>
#include <wchar.h>//宽字符函数和类型
#include <string.h>
struct student 
{ // 一个学生的数据 
	int num;//序号 
	long id;//学号 
	char name[50];//姓名 
	char gender[5];//性别 
	char cla[50];//行政班 
	int score1;//进制转换分数 
	int score2;//多进制转换分数 
	int score3;//数值表达逻辑代数分数 
	int average_score;//平均分 
};

FILE* open(const char filename[], char readmode[])
{
	FILE* file;
	file = NULL;
	file = fopen(filename, readmode);
	if (file == NULL) 
	{
		printf("打开文件失败\n");
	}
	else 
	{
		printf("打开文件成功\n");
	}
	return file;
}
struct student read(FILE* file)
{
	struct student onestudent; // 创建一个 student 结构体变量 onestudent
	memset(&onestudent, 0, sizeof(struct student));//使用 memset 函数将其内存清零，以确保结构体中的所有字段都被初始化为0
	char ch[100];//用于存储从文件中读取的一行数据
	fgets(ch, 100, file);//从文件中读取一行数据，最多读取100个字符，并将结果存储在字符数组 ch 中
	sscanf(ch, "%d %d %s %s %s %d %d %d",&onestudent.num, &onestudent.id, onestudent.name, onestudent.gender, 
	onestudent.cla, &onestudent.score1, &onestudent.score2, &onestudent.score3);//将从字符数组 ch 中解析出的各个字段值赋给 onestudent 结构体中相应的字段
	onestudent.average_score = (onestudent.score1 + onestudent.score2 + onestudent.score3) / 3;//计算平均分 
	return onestudent;
}
void write(FILE* file, const char classtxt[]) 
{
	FILE* txt;
	txt = NULL;//声明一个文件指针 txt，并将其初始化为空
	struct student onestudent;
	txt = open(classtxt, "a");//使用 open 函数打开 classtxt 文件，并将返回的文件指针保存在 txt 中。打开模式为 "a"，表示以追加的方式打开文件，如果文件不存在则创建新文件
	fputs("序号 学号 姓名 性别 行政班 进制转换 多进制转换 数值表达逻辑代数 平均分\n", txt);//将表头信息写入文件中
	//fputs函数用于将字符串写入文件中
	//feof(file) 是一个函数，用于检查文件指针 file 是否已经到达文件末尾
	while (!feof(file)) //使用 while 循环读取 file 文件中的学生信息，直到文件末尾
	{
		onestudent = read(file);//从 file 中读取一行学生信息，并将结果保存在 onestudent 中
		fprintf(txt, "%d %d %s %s %s %d %d %d %d\n", onestudent.num, onestudent.id, onestudent.name, onestudent.gender, 
		onestudent.cla, onestudent.score1, onestudent.score2, onestudent.score3, onestudent.average_score);//将 onestudent 结构体中的各个字段值按照格式写入 txt 文件
	}
	fclose(txt);//关闭文件，释放资源
	printf("文件写入完成\n");
}

int main() 
{
	FILE* file;
	file = NULL;//声明一个文件指针 file，并将其初始化为空
	char ch[100];//用于存储从文件中读取的一行数据
	file = open("598854.txt", "r");//打开文件 "598854.txt"，打开模式为 "r"，表示以只读方式打开文件。将返回的文件指针保存在 file 中
	fgets(ch, 100, file);//跳过文件第一行表头信息，确保读取的是学生信息
	write(file, "new598854.txt");//将 file 文件中的学生信息写入新文件 "new598854.txt" 中
	fclose(file);//关闭 file 文件，释放资源
	file = NULL;

	file = open("598856.txt", "r");
	fgets(ch, 100, file);
	write(file, "new598856.txt");
	fclose(file);
	file = NULL;

	file = open("598858.txt", "r");
	fgets(ch, 100, file);
	write(file, "new598858.txt");
	fclose(file);
	file = NULL;
	return 0;
}
	
