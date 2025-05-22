#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct Person
{
    char name[50];
    char account[20];
    char id[19];
    char psw[20];
    int cardnum;
}User;

int main() {
    FILE *fp = fopen("doctor.txt", "rb+");
    // 检查文件是否成功打开，如果未成功打开，则输出错误信息并退出程序
    if (fp == NULL) {
        printf("文件打开失败");
        return 0;
    }
    // 定义一个字符数组str，用于存储从文件中读取的字符串
    char str[200];
    // 将文件指针移到文件的开头
    fseek(fp, 0, SEEK_SET);
    int i = 3;
    long fd;
    while(i--){
        fgets(str,200,fp);
        if(i == 1)fd = ftell(fp);
    }
    printf("%s",str);
    for(int i = 0;i < (int)strlen(str);i++){
        if(str[i] == ':'){
            if(str[i + 2] == '0' && str[i + 1] > '0' && str[i + 1] <= '9'){
                if(str[i + 1] == '1'){
                    str[i + 1] = '9';
                    str[i + 2] = ' ';
                    break;
                }
                str[i + 2] = '9';
                str[i + 1] = str[i + 1] - 1;
            }
            else if(str[i + 2] > '0' && str[i + 2] <= '9'){
                str[i + 2] = str[i + 2] - 1;
            }
            else str[i + 1] = str[i + 1] - 1;
            break;
        }
    }
    // fseek(fp,0,SEEK_CUR);
    fseek(fp, fd, SEEK_SET);
    printf("%s",str);
    fprintf(fp,"%s",str);
    fclose(fp);
    return 0;
}