#include<fstream>
#include<iostream>
using namespace std;
//获取文件内容
int getfilecontent(char *content)
{
    FILE *file=fopen("./1.txt","r");
    char buff[1024];
    fread(buff,1024,1,file);
    fclose(file);
    int j=0;
    for(int i=0;i<1024;i++)
    {
        if(buff[i]=='\0')
        {
            content[j++]='\0';
            //printf("%d\n",j);
            break;
        }
        if(buff[i]=='\n')
        {
            continue;
        }
        content[j++]=buff[i];
    }
    return j-1;
}
//二进制处理
void binarydeal(char* x,int s)
{
    FILE *file=fopen("./2.txt","wb");
    int l=8-s%8;//一个字节等于八位不被8整除需要补位0
    l%=8;
    s+=l;
    unsigned char buff;
    for(int i=l;i>0;i--)
    {
        x+='0';
    }
    int charlen=s;
    int data=0;
    for(int i=0;i<s;i++)
    {
        data*=2;
        if(x[i]=='1')
        {
            data++;
        }
        charlen--;
        if(charlen%8==0)//一个字节等于八位
        {
            buff=data;
            printf("%d ",buff);
            fputc(buff,file);//文件数据写入
            data=0;
        }
    }
    fclose(file);
}
//解码
void mydecode()
{
    //读取压缩内容
    FILE *file=fopen("./2.txt","rb");
    unsigned char buff[1024];
    fread(buff,1024,1,file);
    fclose(file);
    FILE *file_w=fopen("./3.txt","wb");
    int a=0;   
    int lenth=0;
    int b[8];//八个字节
    while(buff[lenth]!='\0')
    {
        a=buff[lenth++];
        for(int i=7;i>-1;i--)
        {
            b[i]=a%2;
            a/=2;
        }
        for(int i=0;i<8;i++)
        {
            printf("%d",b[i]);
            fprintf(file_w,"%d",b[i]);
        }
    } 
    fclose(file_w);
}
int main()
{
    char content[1024];
    int sum=getfilecontent(content);
    printf(content);
    printf("\n");
    binarydeal(content,sum);
    printf("\n");
    mydecode();
}