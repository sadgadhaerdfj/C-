//二分查找（冒泡排序）
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <math.h>

typedef struct
{
	int id;//学号
	char name[50];//姓名
	char gender[10];//性别
	char classes[50];//班级
	double score_1;//三项成绩
	double score_2;
	double score_3;
	double average_score; 	 
 } Student;

//交换两个元素的值，用于排序 
 void swap(Student *xp,Student *yp)
 {
 	Student temp=*xp;
 	*xp=*yp;
 	*yp=temp;
 }
 
//学号冒泡排序（升序）
void ID_digit_Sort(Student students[],int n)
{
	int i,j;
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(students[j].id>students[j+1].id)
			{
				swap(&students[j],&students[j+1]);
			}
		}
	}
 } 

//平均分冒泡排序
void digit_Sort(Student students[],int n)
{
	int i,j;
	for(i=0;i<n-1;i++)
	{
		for(j=0;j<n-i-1;j++)
		{
			if(students[j].average_score>students[j+1].average_score)
			{
				swap(&students[j],&students[j+1]);
			}
		}
	}
 } 

//姓名冒泡排序
void characters_Sort(Student students[],int n)
{
	setlocale(LC_COLLATE,"zh_CN");
	for(int i=0;i<n-1;i++)
	{
		for(int j=0;j<n-i-1;j++)
		{
			if(students[j].name>students[j+1].name)
			{
				swap(&students[j],&students[j+1]);
			}
		}
	}
 } 
 
void SearchTotal(Student students[], const char *fileName, int *count)//储存学号/姓名/平均值 
{
	// 将之前的文件指针代码移到这里
    FILE *filePointer = fopen(fileName, "r");
    if (filePointer == NULL) //如果文件打开失败（即返回的指针为NULL），则会输出错误信息并返回。
	{
        printf("无法打开文件\n");
        return;
    }
    
    (*count) = 0; // 将计数器置零，用于统计读取的学生数量 
    char line[100];
    
    while (fgets(line,sizeof(line),filePointer) != NULL) 
	{
	   	char *token = strtok(line, ",");//strtok函数将读取到的一行数据按照逗号分隔为多个子字符串
    	if (token != NULL) 
		{
		    token = strtok(NULL, ",");//第一列 
		    if (token != NULL) 
			{
				students[(*count)].id = atoi(token);//第二列读取id 
		        token = strtok(NULL, ",");
		        if (token != NULL) 
				{
		            strncpy(students[(*count)].name, token, sizeof(students[(*count)].name));//token的名字储存在students 
		            for(int i = 3; i <= 8; i++) //4，5，6，7，8,9列 
					{
			            token = strtok(NULL, ",");
			            if (token != NULL) 
		                {
		                    if (i == 3) { // 第四列
		                        strncpy(students[(*count)].gender, token, sizeof(students[(*count)].gender));
		                    } else if (i == 4) { // 第五列
		                        strncpy(students[(*count)].classes, token, sizeof(students[(*count)].classes));
		                    } else if (i == 5) { // 第六列
		                        students[(*count)].score_1 = atof(token);
		                    } else if (i == 6) { // 第七列
		                        students[(*count)].score_2 = atof(token);
		                    } else if (i == 7) { // 第八列
		                        students[(*count)].score_3 = atof(token);
	                        } else if (i == 8) {// 第九列 
					            students[(*count)].average_score = atof(token); 
				        	}
		                }    
				    }
	            }
	        }
	   	}
	    (*count)++;
	}
	fclose(filePointer);
} 

void Search(const char *fileName, Student students[], int *count) //从指定文件中读取学生信息，并将读取到的信息存储在Student结构体数组中
{
    FILE *filePointer = fopen(fileName, "r");
    if (filePointer == NULL) {
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
		
        if (token != NULL) {
            students[(*count)].id = atoi(token);//第二列读取id
			//printf("%d",students[(*count)].id); 
            token = strtok(NULL, ",");
            if (token != NULL) {
            	strncpy(students[(*count)].name, token, sizeof(students[(*count)].name));//token的名字储存在students 
                //printf("%s",students[(*count)].name);
				for(int i = 3; i <= 8; i++) {
                    token = strtok(NULL, ",");
                    if (token != NULL) {
                        if (i == 3) { // 第四列
                            strncpy(students[(*count)].gender, token, sizeof(students[(*count)].gender));
                        } else if (i == 4) { // 第五列
                            strncpy(students[(*count)].classes, token, sizeof(students[(*count)].classes));	
					    } else if (i == 5) { // 第六列
                            students[(*count)].score_1 = atof(token);
                            //printf("%lf",students[(*count)].score_1);
                        } else if (i == 6) { // 第七列
                            students[(*count)].score_2 = atof(token);
                            //printf("%lf",students[(*count)].score_2);
                        } else if (i == 7) { // 第八列
                            students[(*count)].score_3 = atof(token);
                            //printf("%lf",students[(*count)].score_3);
                        } else if (i == 8) {// 第九列 
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

int binarySearchAndPrintByName(Student students[], const char *target) //姓名二分法 
{
    int numRecords = 374; // 实际记录数
    int low = 0;//起点，初值为0表示在首端 
    int high = numRecords - 1;//终点，数值为 numRecords - 1表示在尾端 
    int found = 0;//用于表示是否找到匹配的学生记录
    
    while (low <= high) //使用while循环进行二分查找，直到low大于high为止
	{
        int mid = (low + high) / 2;//中值 
        int compareResult = strcoll(students[mid].name, target); 

        if (compareResult == 0) //若compareResult等于0，表示找到匹配的学生记录，打印该学生的信息，将found设置为1，并跳出循环
		{
            printf("找到匹配的学生记录：\n");
            printf("学号：%d\n姓名：%s\n性别：%s\n行政班：%s\n成绩1: %.2f\n成绩2: %.2f\n成绩3: %.2f\n平均成绩: %.2f\n", 
                students[mid].id, students[mid].name, students[mid].gender, students[mid].classes, 
                students[mid].score_1, students[mid].score_2, students[mid].score_3, students[mid].average_score);
                
            found = 1;
            break; // 找到匹配项后退出循环
        } 
		else if (compareResult < 0) //若compareResult小于0，表示目标姓名在当前中间位置的右侧，更新low为mid + 1
		{
            low = mid + 1;
        } 
		else //若compareResult大于0，表示目标姓名在当前中间位置的左侧，更新high为mid - 1
		{
            high = mid - 1;
        }
    }
    if (found == 0) //如果在循环结束后found仍然为0，表示未找到匹配的学生记录，输出"未查找到"
	{
        printf("未查找到\n");
    }
    
    return found;//返回found，表示是否找到了匹配的学生记录（找到为1，未找到为0）
}


int binarySearchAndPrintbyscore(Student students[], double target) //平均成绩二分法 
{
    int numRecords = 374;//实际记录数
    int low = 0;//起点，初值为0表示在首端 
    int high = numRecords - 1;//终点，数值为 numRecords - 1表示在尾端
    int found = 0;//用于表示是否找到匹配的学生记录
    //使用while循环进行二分查找，直到low大于high为止
    while (low <= high) 
	{
        int mid = (low + high) / 2;////中值 
        if (fabs(students[mid].average_score - target) < 0.0001) //使用fabs函数比较students[mid].average_score和目标平均成绩target的差值是否小于0.0001
		{//若比较结果为真，表示找到匹配的学生记录，打印该学生的信息，并将found设置为1
            printf("找到匹配的学生记录：\n");
            printf("学号：%d\n姓名：%s\n性别：%s\n行政班：%s\n成绩1: %.2f\n成绩2: %.2f\n成绩3: %.2f\n平均成绩: %.2f\n", 
                students[mid].id, students[mid].name, students[mid].gender, students[mid].classes, 
                students[mid].score_1, students[mid].score_2, students[mid].score_3, students[mid].average_score);
        
            found = 1;
		
            int left = mid - 1;
            while (left >= 0 && students[left].average_score == target)//向左遍历学生记录，直到找到第一个平均成绩不等于目标平均成绩的学生记录为止，期间打印每个符合条件的学生信息。 
			{
                printf("学号：%d\n姓名：%s\n性别：%s\n行政班：%s\n成绩1: %.2f\n成绩2: %.2f\n成绩3: %.2f\n平均成绩: %.2f\n", 
                    students[left].id, students[left].name, students[left].gender, students[left].classes, 
                    students[left].score_1, students[left].score_2, students[left].score_3, students[left].average_score);
                left--;
            }
		
            int right = mid + 1;
            while (right < numRecords && students[right].average_score == target) //向右遍历学生记录，直到找到第一个平均成绩不等于目标平均成绩的学生记录为止，期间打印每个符合条件的学生信息。
			{
                printf("学号：%d\n姓名：%s\n性别：%s\n行政班：%s\n成绩1: %.2f\n成绩2: %.2f\n成绩3: %.2f\n平均成绩: %.2f\n", 
                    students[right].id, students[right].name, students[right].gender, students[right].classes, 
                    students[right].score_1, students[right].score_2, students[right].score_3, students[right].average_score);
                right++;
            }
		
            break;
        } 
		else if (students[mid].average_score < target) //若比较结果为假且students[mid].average_score小于目标平均成绩，表示目标平均成绩在当前中间位置的右侧，更新low为mid + 1
		{
            low = mid + 1;
        } 
		else //若比较结果为假且students[mid].average_score大于目标平均成绩，表示目标平均成绩在当前中间位置的左侧，更新high为mid - 1
		{
            high = mid - 1;
        }
    }

    if (found == 0) //如果在循环结束后found仍然为0，表示未找到匹配的学生记录，输出"未查找到"
	{
        printf("未查找到\n");
    }

    return found;//返回found，表示是否找到了匹配的学生记录（找到为1，未找到为0）
}

int binarySearchAndPrintbyID(Student students[], int target) //学号二分法 
{
    int numRecords = 374;//实际记录数
    int low = 0;//起点，初值为0表示在首端 
    int high = numRecords - 1;//终点，数值为 numRecords - 1表示在尾端
    int found = 0;//用于表示是否找到匹配的学生记录
    
    while (low <= high) //使用while循环进行二分查找，直到low大于high为止
	{
        int mid = (low + high) / 2;

        if (students[mid].id == target) //使用students[mid].id与目标学号target进行比较
		{//若比较结果为真，表示找到匹配的学生记录，打印该学生的信息，并将found设置为1
            printf("找到匹配的学生记录：\n");
            printf("学号：%d\n姓名：%s\n性别：%s\n行政班：%s\n成绩1: %.2f\n成绩2: %.2f\n成绩3: %.2f\n平均成绩: %.2f\n", 
                students[mid].id, students[mid].name, students[mid].gender, students[mid].classes, 
                students[mid].score_1, students[mid].score_2, students[mid].score_3, students[mid].average_score);
            found = 1;
            break;  // 找到匹配项后退出循环
        } 
		else if (students[mid].id < target) //若比较结果为假且students[mid].id小于目标学号，表示目标学号在当前中间位置的右侧，更新low为mid + 1
		{
            low = mid + 1;
        } 
		else //若比较结果为假且students[mid].id大于目标学号，表示目标学号在当前中间位置的左侧，更新high为mid - 1
		{
            high = mid - 1;
        }
    }

    if (found == 0) //如果在循环结束后found仍然为0，表示未找到匹配的学生记录，输出"未查找到"
	{
        printf("未查找到\n");
    }

    return found;//返回found，表示是否找到了匹配的学生记录（找到为1，未找到为0）
}


int main()
{   
	//按照姓名、学号、平均成分排序 
    char newname[3][50] = {
        "名字排序.txt",
        "学号排序.txt",
        "平均分排序.txt"
    };
    FILE *file = fopen("总成绩单.txt", "r");
    FILE *newfile[3]; // 声明 newfile 数组

    if (file == NULL)
    {
        printf("文件无法打开\n");
        return 1;
    }
    else
    {
        printf("新文件成功储存\n");
    }

    for (int j=0; j<3; j++)
    {
        newfile[j] = fopen(newname[j], "w");
    }
	
	Student students[1000];
	int count = 0;
    SearchTotal(students, "总成绩单.txt", &count);

    // 按名字排序并将数据写入到文件
    characters_Sort(students, count); // 调用排序函数对姓名进行排序
    for(int i = 0; i < count; i++)
    {
        fprintf(newfile[0], "%d,%s,%s,%s,%.2f,%.2f,%.2f,%.2f\n", 
		students[i].id, students[i].name, students[i].gender, students[i].classes, students[i].score_1, students[i].score_2, students[i].score_3, students[i].average_score);
    }

    // 按学号排序并将数据写入到文件
    ID_digit_Sort(students, count); // 调用排序函数对ID进行排序
    for(int i = 0; i < count; i++)
    {
        fprintf(newfile[1], "%d,%s,%s,%s,%.2f,%.2f,%.2f,%.2f\n", 
		students[i].id, students[i].name, students[i].gender, students[i].classes, students[i].score_1, students[i].score_2, students[i].score_3, students[i].average_score);
    }

    // 按平均分排序并将数据写入到文件
    digit_Sort(students, count); // 调用排序函数对平均值进行排序
    for(int i = 0; i < count; i++)
    {
        fprintf(newfile[2], "%d,%s,%s,%s,%.2f,%.2f,%.2f,%.2f\n", 
		students[i].id, students[i].name, students[i].gender, students[i].classes, students[i].score_1, students[i].score_2, students[i].score_3, students[i].average_score);
    }

    for (int j = 0; j < 3; j++)
    {
        fclose(newfile[j]);
    }
    fclose(file);
	
	printf("\n");
	
	//查询
	int judge = 1;//用于再玩一次，初值为1进入while循环进行查询 
	while (judge == 1)
	{
		int type;
		printf("请输入查询类型（1=姓名/2=学号/3=成绩）");//菜单栏 
		scanf("%d",&type);
		
		if(type == 1)
		{
			char query[1000];
			printf("请输入姓名:");
			scanf("%s", query);
			setlocale(LC_COLLATE, ""); // 使用默认 locale
		    Student student_name[1000];
		    int count_1 = 0;
		    Search(newname[0], student_name, &count_1);
		    printf("\n");
		    binarySearchAndPrintByName(student_name, query);
		} 
		
		else if (type == 2)
		{
			int query_1;
			printf("请输入学号:");
			scanf("%d", &query_1);
			Student student_ID[374];
			int count_2 = 0;
		    Search(newname[1], student_ID, &count_2);
		    printf("\n");
			binarySearchAndPrintbyID(student_ID, query_1);
		}
		
		else if (type == 3)
		{
			double query_2;
			printf("请输入成绩:");
			scanf("%lf", &query_2);	
			Student student_score[374];
		   	int count_3 = 0;
		    Search(newname[2], student_score, &count_3);
		    printf("\n");
		    binarySearchAndPrintbyscore(student_score, query_2);
		}
		
		else
		{
			printf("查询类型输入错误\n");
		}
		printf("请问你还想再来一次吗？（1=是/2=否）");
		scanf("%d",&judge);
		printf("\n");
	}
	if (judge == 2)
	{
		printf("查询系统结束");
		printf("\n"); 
	}
	
    return 0;
}
