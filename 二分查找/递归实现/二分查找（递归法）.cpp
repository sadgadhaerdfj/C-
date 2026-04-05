#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>//字符串排序用 
#include <math.h>//后面绝对值比较要用 

 
typedef struct {
    int id;             //学号 
    char name[50];      //姓名 
    char gender[10];    //性别 
    char classes[50];   //班级 
    double score_1;     //三项成绩，双精度浮点数 
    double score_2;
	double score_3;
    double average_score;//平均分 
} Student;

void Search(const char *fileName, Student students[], int *count) //从指定文件中读取学生信息，并将读取到的信息存储在Student结构体数组中
{
    FILE *filePointer = fopen(fileName, "r");
    if (filePointer == NULL) 
	{
        printf("无法打开文件\n");
        return;
    }

    (*count) = 0; // 将计数器置零
    int LineSkipped = 0; // 标记变量，用来判断第一、二行是否已经跳过
    char line[100];

    while (fgets(line,sizeof(line),filePointer) != NULL) 
	{
        char *token = strtok(line, ","); 
        if (LineSkipped<2)
		{
			LineSkipped++; // 标记已经跳过第二行
			continue; // 跳过第一、二行，直接进行下一次循环 
		}
		
        if (token != NULL) 
		{
            students[(*count)].id = atoi(token);//第二列读取id
			//printf("%d",students[(*count)].id); 
            token = strtok(NULL, ",");
            if (token != NULL) 
			{
            	strncpy(students[(*count)].name, token, sizeof(students[(*count)].name));//token的名字储存在students 
                //printf("%s",students[(*count)].name);
				for(int i = 3; i <= 8; i++) 
				{
                    token = strtok(NULL, ",");
                    if (token != NULL) 
					{
                        if (i == 3) 
						{ // 第四列
                            strncpy(students[(*count)].gender, token, sizeof(students[(*count)].gender));
                        } else if (i == 4) 
						{ // 第五列
                            strncpy(students[(*count)].classes, token, sizeof(students[(*count)].classes));	
					    } else if (i == 5) 
						{ // 第六列
                            students[(*count)].score_1 = atof(token);
                            //printf("%lf",students[(*count)].score_1);
                        } else if (i == 6) 
						{ // 第七列
                            students[(*count)].score_2 = atof(token);
                            //printf("%lf",students[(*count)].score_2);
                        } else if (i == 7) 
						{ // 第八列
                            students[(*count)].score_3 = atof(token);
                            //printf("%lf",students[(*count)].score_3);
                        } else if (i == 8) 
						{// 第九列 
                            students[(*count)].average_score = atof(token);
                        }
            		}    
                }
            }
        }
    	(*count)++;
    }
    fclose(filePointer);
} 

//姓名 
Student* reSearchByName(Student students[], const char *target, int low, int high, int count) 
{ 
    if (low > high) 
	{
        return NULL;  // 如果下界大于上界，表示未找到匹配的姓名，返回NULL
    }
    
    int mid = (low + high) / 2;  // 计算中间位置
    int compareResult = strcoll(students[mid].name, target);  // 比较中间位置的姓名与目标姓名
    if (compareResult == 0) 
	{  // 如果比较结果为0，表示找到匹配的姓名
        return &students[mid];  // 返回指向该学生结构体的指针
    } 
	else if (compareResult < 0) 
	{  // 如果比较结果小于0，表示目标姓名在中间位置的右侧
        return reSearchByName(students, target, mid + 1, high, count);  // 在右半部分继续进行查找
    } 
	else 
	{  // 如果比较结果大于0，表示目标姓名在中间位置的左侧
        return reSearchByName(students, target, low, mid - 1, count);  // 在左半部分进行查找
    }
}
//姓名 
void reSearchAndPrintByName(Student students[], const char *target, int count) 
{
    Student* result = reSearchByName(students, target, 0, count - 1, count);  // 调用reSearchByName函数进行查找
    if (result != NULL) 
	{  // 如果查找结果不为NULL，表示找到匹配的姓名
        printf("学号：%d\n姓名：%s\n性别：%s\n行政班：%s\n成绩1: %.2f\n成绩2: %.2f\n成绩3: %.2f\n平均成绩: %.2f\n", 
            result->id, result->name, result->gender, result->classes, 
            result->score_1, result->score_2, result->score_3, result->average_score);  // 打印该学生的信息
    } 
	else 
	{  // 如果查找结果为NULL，表示未找到匹配的姓名
        printf("未查找到该学生\n");  // 输出提示信息
    }
}

//学号 
int recursiveBinarySearchAndPrintbyID(Student students[], int target, int low, int high) 
{ 
    if (low > high) 
	{  // 如果下界大于上界，表示未查找到
        printf("未查找到\n");  // 输出提示信息
        return 0;  // 返回0表示未查找到
    }

    int mid = (low + high) / 2;  // 计算中间位置
    
    if (students[mid].id == target) 
	{  // 如果中间位置的学号与目标学号相等，表示找到匹配的学生记录
        printf("找到匹配的学生记录：\n");
        printf("学号：%d\n姓名：%s\n性别：%s\n行政班：%s\n成绩1: %.2f\n成绩2: %.2f\n成绩3: %.2f\n平均成绩: %.2f\n", 
            students[mid].id, students[mid].name, students[mid].gender, students[mid].classes, 
            students[mid].score_1, students[mid].score_2, students[mid].score_3, students[mid].average_score);  // 打印该学生的信息
        return 1;  // 返回1表示查找成功
    } 
	else if (students[mid].id < target) 
	{  // 如果中间位置的学号小于目标学号，说明目标学号在右侧
        return recursiveBinarySearchAndPrintbyID(students, target, mid + 1, high);  // 在右半部分继续进行递归查找
    } 
	else 
	{  // 如果中间位置的学号大于目标学号，说明目标学号在左侧
        return recursiveBinarySearchAndPrintbyID(students, target, low, mid - 1);  // 在左半部分进行递归查找
    }
}
//平均成绩
int recursiveBinarySearchAndPrint(Student students[], double target, int low, int high) 
{ 
    if (low > high) 
    {
        printf("未查找到\n"); // 输出未查找到的提示信息
        return 0;
    }

    int mid = (low + high) / 2; // 计算中间位置
    if (fabs(students[mid].average_score - target) < 0.0001) // 如果找到匹配的学生记录
    {
        printf("找到匹配的学生记录：\n");
        printf("学号：%d\n姓名：%s\n性别：%s\n行政班：%s\n成绩1: %.2f\n成绩2: %.2f\n成绩3: %.2f\n平均成绩: %.2f\n", 
            students[mid].id, students[mid].name, students[mid].gender, students[mid].classes, 
            students[mid].score_1, students[mid].score_2, students[mid].score_3, students[mid].average_score);
        
        int left = mid - 1;
        while (left >= 0 && fabs(students[left].average_score - target) < 0.0001) 
        {
            printf("学号：%d\n姓名：%s\n性别：%s\n行政班：%s\n成绩1: %.2f\n成绩2: %.2f\n成绩3: %.2f\n平均成绩: %.2f\n", 
                students[left].id, students[left].name, students[left].gender, students[left].classes, 
                students[left].score_1, students[left].score_2, students[left].score_3, students[left].average_score);
            left--;
        }
        
        int right = mid + 1;
        while (right < high && fabs(students[right].average_score - target) < 0.0001) 
        {
            printf("学号：%d\n姓名：%s\n性别：%s\n行政班：%s\n成绩1: %.2f\n成绩2: %.2f\n成绩3: %.2f\n平均成绩: %.2f\n", 
                students[right].id, students[right].name, students[right].gender, students[right].classes, 
                students[right].score_1, students[right].score_2, students[right].score_3, students[right].average_score);
            right++;
        }
        
        return 1;  // 找到匹配项后返回 1
    } 
    else if (students[mid].average_score < target) // 目标平均成绩较大，向右查找
    {
        return recursiveBinarySearchAndPrint(students, target, mid + 1, high);
    } 
    else // 目标平均成绩较小，向左查找
    {
        return recursiveBinarySearchAndPrint(students, target, low, mid - 1);
    }
}

int main()
{
	//开始查询
	int judge = 1;
	while (judge == 1)
	{
		int type;
		printf("请输入查询类型（1=姓名/2=学号/3=成绩）");
		scanf("%d",&type);
		
		if(type == 1)
		{
			char query[1000];
			printf("请输入姓名:");
			scanf("%s", query);
			setlocale(LC_COLLATE, ""); // 使用默认 locale
		    Student student_name[1000];
		    int count_1 = 0;
		    Search("名字排序.txt", student_name, &count_1);
		    printf("\n");
		    reSearchAndPrintByName(student_name, query, count_1);
		} 
		
		else if (type == 2)
		{
			int query_1;
			printf("请输入学号:");
			scanf("%d", &query_1);
			Student student_ID[374];
			int count_2 = 0;
		    Search("学号排序.txt", student_ID, &count_2);
		    printf("\n");
			recursiveBinarySearchAndPrintbyID(student_ID, query_1, 0, count_2);
		}
		
		else if (type == 3)
		{
			double query_2;
			printf("请输入成绩:");
			scanf("%lf", &query_2);	
			Student student_score[374];
		   	int count_3 = 0;
		    Search("平均分排序.txt", student_score, &count_3);
		    printf("\n");
		    recursiveBinarySearchAndPrint(student_score, query_2, 0, count_3);
		}
		
		else
		{
			printf("请输入正确的查询类型\n");
		}
		printf("请问你还想再用一次吗？（1=是/2=否）");
		scanf("%d",&judge);
		printf("\n");
	}
	if (judge == 2)
	{
		printf("查询结束");
		printf("\n"); 
	}
	
    return 0;
} 
