//添加平均成绩
#include <stdio.h>
#include <wchar.h>
#include <string.h>

struct student
{
	int num;//序号 
	long id;//学号 
	char name[50];//姓名
	char gender[5];//性别
	char cla[50];//行政班
	int score1;//进制转换分数
	int score2;//多进制转换分数
	int score3;//数值表达逻辑代数分数
	int average_score;//分均分 
  }; 
 
FILE* open(const char filename[],char readmode[])
{
	FILE* file;
	file=NULL;
	file=fopen(filename,readmode);
	if(file==NULL)
	{
		printf("文件打开失败\n");
	}
	else
	{
		printf("文件打开成功\n");
	}
	return file;
 } 
 
struct student read(FILE* file)
{
	struct student onestudent;
	memset(&onestudent,0,sizeof(struct student));
	char ch[100];
	fgets(ch,100,file);
	sscanf(ch,"%d %d %s %s %s %d %d %d",&onestudent.num,&onestudent.id,&onestudent.name,&onestudent.gender,&onestudent.cla,
	&onestudent.score1,&onestudent.score2,&onestudent.score3);
	onestudent.average_score=(onestudent.score1+onestudent.score2+onestudent.score3)/3;
	return onestudent;
}

void write(FILE* file,const char classtxt[])
{
	FILE* txt;
	txt=NULL;
	struct student onestudent;
	txt=open(classtxt,"a");
	fputs("序号 学号 姓名 性别 行政班 进制转换 多进制转换 数值表达逻辑代数 平均分\n",txt);
	while(!feof(file))
	{
		onestudent=read(file);
		fprintf(txt,"%d %d %s %s %d %d %d\n",onestudent.num,onestudent.id,onestudent.name,onestudent.gender,onestudent.cla,
		onestudent.score1,onestudent.score2,onestudent.score3,onestudent.average_score);
	}
	fclose(txt);
	printf("文件写入完成"); 
}

int main()
{
	FILE* file;
	file=NULL;
	char ch[100];
	file=open("598854.txt","r");
	fgets(ch,100,file);
	write(file,"new598854.txt");
	fclose(file);
	file=NULL;
	
	file=open("598856.txt","r");
	fgets(ch,100,file);
	write(file,"new598856.txt");
	fclose(file);
	file=NULL;
	
	file=open("598858.txt","r");
	fgets(ch,100,file);
	write(file,"new598858.txt");
	fclose(file);
	file=NULL;
	return 0;
}
