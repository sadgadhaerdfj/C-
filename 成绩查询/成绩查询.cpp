#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 500

typedef struct 
{
    int index;
    char id[20];
    char name[50];
    char gender[10];
    char className[50];
    int score1;
    int score2;
    int score3;
    float average;
} Student;

void displayStudent(Student student) 
{
    printf("%d %s %s %s %s %d %d %d %.2f\n", student.index, student.id, student.name, student.gender,
           student.className, student.score1, student.score2, student.score3, student.average);
}

void searchById(Student* students, int size, const char* id) 
{
    int i;
    for (i = 0; i < size; i++) 
	{
        if (strcmp(students[i].id, id) == 0) 
		{
            displayStudent(students[i]);
            return;
        }
    }
    printf("未找到学号为 %s 的学生\n", id);
}

void searchByName(Student* students, int size, const char* name) 
{
    int i;
    int found = 0;
    for (i = 0; i < size; i++) 
	{
        if (strcmp(students[i].name, name) == 0) 
		{
            displayStudent(students[i]);
            found = 1;
        }
    }
    if (!found) 
	{
        printf("未找到姓名为 %s 的学生\n", name);
    }
}

int main() 
{
    Student students[MAX_SIZE];
    int size = 0;

    FILE* file1 = fopen("new598858.txt", "r");
    if (file1 == NULL) 
	{
        printf("无法打开文件\n");
        return 1;
    }

    char line[200];
    while (fgets(line, sizeof(line), file1)) 
	{
        if (size >= MAX_SIZE) 
		{
            printf("学生数量超过最大限制\n");
            break;
        }

        Student student;

        sscanf(line, "%d %s %s %s %s %d %d %d",
               &student.index, student.id, student.name, student.gender,
               student.className, &student.score1, &student.score2, &student.score3);

        student.average = (float)(student.score1 + student.score2 + student.score3) / 3.0;

        students[size] = student;
        size++;
    }

    fclose(file1);
    
    FILE* file2 = fopen("new598856.txt", "r");
    if (file2 == NULL) 
	{
        printf("无法打开文件\n");
        return 1;
    }

    while (fgets(line, sizeof(line), file2)) 
	{
        if (size >= MAX_SIZE) 
		{
            printf("学生数量超过最大限制\n");
            break;
        }

        Student student;

        sscanf(line, "%d %s %s %s %s %d %d %d",
               &student.index, student.id, student.name, student.gender,
               student.className, &student.score1, &student.score2, &student.score3);

        student.average = (float)(student.score1 + student.score2 + student.score3) / 3.0;

        students[size] = student;
        size++;
    }

    fclose(file2);
    
    FILE* file3 = fopen("new598854.txt", "r");
    if (file3 == NULL) 
	{
        printf("无法打开文件\n");
        return 1;
    }

    while (fgets(line, sizeof(line), file3)) 
	{
        if (size >= MAX_SIZE) 
		{
            printf("学生数量超过最大限制\n");
            break;
        }

        Student student;

        sscanf(line, "%d %s %s %s %s %d %d %d",
               &student.index, student.id, student.name, student.gender,
               student.className, &student.score1, &student.score2, &student.score3);

        student.average = (float)(student.score1 + student.score2 + student.score3) / 3.0;

        students[size] = student;
        size++;
    }

    fclose(file3);

    int option;
    do {
        printf("\n成绩查询\n");
        printf("1）按学号查询任一同学成绩\n");
        printf("2）按姓名查询任一同学成绩\n");
        printf("0）退出\n");
        printf("请输入选项：");
        scanf("%d", &option);

        switch (option) 
		{
            case 1:
                printf("请输入要查询的同学学号：");
                char id[20];
                scanf("%s", id);
                searchById(students, size, id);
                break;
            case 2:
                printf("请输入要查询的同学姓名：");
                char name[50];
                scanf("%s", name);
                searchByName(students, size, name);
                break;
            case 0:
                printf("程序已退出\n");
                break;
            default:
                printf("无效的选项\n");
                break;
        }
    } while (option != 0);

    return 0;
}
