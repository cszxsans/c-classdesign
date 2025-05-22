#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<windows.h>
#include <stdlib.h>
#include<time.h>
#define MAX_LINE 10
#define MAX_NAME 100

typedef struct Person
{
    char name[50];
    char account[20];
    char id[19];
    char psw[20];
    int cardnum;
}User;
void Login();
void chodoc(int arr[][20],int cho,int t,int cid,char dep[],char optdor[]);
void patientLo();
void admin();
void logadmin();
void patient(int record_id);
void search(int reid);
//登录用户 
void Login()
{
    int t = 0;
    char sec[120],insec[50];
    system("cls");
    int num = 0;
    printf("请输入你的诊疗卡号:");
    scanf("%d",&num);
    FILE *fp = fopen("users.txt","r");
    if (fp == NULL) {
        printf("文件打开失败\n");
        return;
    }
    fseek(fp,-(int)sizeof(int),SEEK_END);
    fscanf(fp, "%08d", &t);
    if(num > t){
        printf("该诊疗卡号不存在,请注册或重新输入\n");
        Sleep(3000);
        patientLo();
        return;
    }
    printf("请输入密码:");
    scanf("%s",insec);
    fseek(fp,0,SEEK_SET);
    int i = num;
    while(i--){
        fgets(sec,120,fp);
    }
    for(int i = 0,j = 0;i < (int)strlen(sec);i++){
        if(sec[i] == ',')j++;
        if(j == 3){
            for(int k = i + 1,l = 0;l < (int)strlen(insec);k++,l++){
                
                if(sec[k] == insec[l])continue;
                else{
                    printf("密码错误，请重试。\n");
                    Sleep(2000);
                    Login();
                    return;
                }    
            }
            printf("登陆成功！");
            Sleep(250);
            patient(num);
            break;
        }
    }
}
//就诊人登陆成功
void patient(int record_id)
{
    system("cls");
    system("color E0");
    printf("\t\t\t\t欢");
    Sleep(300);
    printf("  迎");
    Sleep(300);
    printf("  来");
    Sleep(300);
    printf("  到");
    Sleep(300);
    printf("  X");
    Sleep(300);
    printf("  X");
    Sleep(300);
    printf("  医");
    Sleep(300);
    printf("  院");
    Sleep(300);
    printf("  预");
    Sleep(300);
    printf("  约");
    Sleep(300);
    printf("  挂");
    Sleep(300);
    printf("  号");
    Sleep(300);
    printf("  系");
    Sleep(300);
    printf("  统\n");
    Sleep(300);
    printf("\t\t\t\t\t        ----------------------\n");
        printf("\t\t\t\t\t\t|1.预约挂号          |\n");
        printf("\t\t\t\t\t\t|2.记录查询          |\n");
        printf("\t\t\t\t\t\t|3.退出系统          |\n");
        printf("\t\t\t\t\t        ----------------------\n");
    int opt;
    scanf("%d",&opt);
    system("cls");
    if(opt == 1){
        printf("请选择你要预约的科室：\n");
        printf("1.心血管内科\n2.呼吸内科\n3.消化内科\n4.神经内科\n5.普通外科\n6.骨科\n7.妇产科\n8.儿科\n9.眼科\n10.急诊科\n");
        int cho;
        scanf("%d",&cho);
        char str[200];
        int arr[50][20];
        if(cho == 1){
            int cnt = 0;
            char d[120]="心血管内科";
            char names[MAX_LINE][MAX_NAME];
            system("cls");
            printf("请选择医生：\n");
            FILE *fp = fopen("doctor.txt","rb");
            if (fp == NULL) { // 必须添加此检查
                printf("文件打开失败");
                return;
            }
            fseek(fp, 0, SEEK_SET); 
            for(int j = 0;j < cho;){
                fgets(str,200,fp);
                if(str[0] == '-')j++;
                if(j == cho - 1){
                    if(str[0] == '-')continue;
                    if(str[0] == '*'){
                        for(int i = 0;i < cnt;i++){
                            fscanf(fp,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",arr[i],arr[i] + 1,arr[i] + 2,arr[i] + 3,arr[i] + 4,arr[i] + 5,arr[i] + 6,arr[i] + 7,arr[i] + 8,arr[i] + 9,arr[i] + 10);
                        }
                        break;
                    }
                    for(int i = 2,j = 0;str[i] != ',';i++,j++){
                        names[cnt][j] = str[i];
                    }
                    cnt++;
                    printf("%s",str);
                }
            }
            fclose(fp);
            int t;scanf("%d",&t);
            char target_name[MAX_NAME]="";
            strcpy(target_name,names[t - 1]);
            chodoc(arr,cho,t,record_id,d,target_name);
        }
        
        else if(cho == 2){
            int cnt = 0;
            char d[120]="呼吸内科";
            char names[MAX_LINE][MAX_NAME];
            system("cls");
            printf("请选择医生：\n");
            FILE *fp = fopen("doctor.txt","rb");
            if (fp == NULL) { // 必须添加此检查
                printf("文件打开失败");
                return;
            }
            fseek(fp, 0, SEEK_SET);
            for(int j = 0;j < cho;){
                fgets(str,200,fp);
                if(str[0] == '-')j++;
                if(j == cho - 1){
                    if(str[0] == '-')continue;
                    if(str[0] == '*'){
                        for(int i = 0;i < cnt;i++){
                            fscanf(fp,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",arr[i],arr[i] + 1,arr[i] + 2,arr[i] + 3,arr[i] + 4,arr[i] + 5,arr[i] + 6,arr[i] + 7,arr[i] + 8,arr[i] + 9,arr[i] + 10);
                        }
                        break;
                    }
                    for(int i = 2,j = 0;str[i] != ',';i++,j++){
                        names[cnt][j] = str[i];
                    }
                    printf("%s",str);
                    cnt++;
                }
            }
            fclose(fp);
            int t;scanf("%d",&t);
            char target_name[MAX_NAME]="";
            strcpy(target_name,names[t - 1]);
            chodoc(arr,cho,t,record_id,d,target_name);
        }
        else if(cho == 3){
            int cnt = 0;
            char d[120]="消化内科";
            char names[MAX_LINE][MAX_NAME];
            //        chodoc(d);
            system("cls");
            printf("请选择医生：\n");
            FILE *fp = fopen("doctor.txt","rb");
            if (fp == NULL) { // 必须添加此检查
                printf("文件打开失败");
                return;
            }
            fseek(fp, 0, SEEK_SET);
            for(int j = 0;j < cho;){
                fgets(str,200,fp);
                if(str[0] == '-')j++;
                if(j == cho - 1){
                    if(str[0] == '-')continue;
                    if(str[0] == '*'){
                        for(int i = 0;i < cnt;i++){
                            fscanf(fp,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",arr[i],arr[i] + 1,arr[i] + 2,arr[i] + 3,arr[i] + 4,arr[i] + 5,arr[i] + 6,arr[i] + 7,arr[i] + 8,arr[i] + 9,arr[i] + 10);
                        }
                        break;
                    }
                    for(int i = 2,j = 0;str[i] != ',';i++,j++){
                        names[cnt][j] = str[i];
                    }
                    printf("%s",str);
                    cnt++;
                }
            }
            fclose(fp);
            int t;scanf("%d",&t);
            char target_name[MAX_NAME]="";
            strcpy(target_name,names[t - 1]);
            chodoc(arr,cho,t,record_id,d,target_name);
        }
        else if(cho == 4){
            int cnt = 0;
            char d[120]="神经内科";
            char names[MAX_LINE][MAX_NAME];
            system("cls");
            printf("请选择医生：\n");
            FILE *fp = fopen("doctor.txt","rb");
            if (fp == NULL) { // 必须添加此检查
                printf("文件打开失败");
                return;
            }
            fseek(fp, 0, SEEK_SET);
            for(int j = 0;j < cho;){
                fgets(str,200,fp);
                if(str[0] == '-')j++;
                if(j == cho - 1){
                    if(str[0] == '-')continue;
                    if(str[0] == '*'){
                        for(int i = 0;i < cnt;i++){
                            fscanf(fp,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",arr[i],arr[i] + 1,arr[i] + 2,arr[i] + 3,arr[i] + 4,arr[i] + 5,arr[i] + 6,arr[i] + 7,arr[i] + 8,arr[i] + 9,arr[i] + 10);
                        }
                        break;
                    }
                    for(int i = 2,j = 0;str[i] != ',';i++,j++){
                        names[cnt][j] = str[i];
                    }
                    printf("%s",str);
                    cnt++;
                }
            }
            fclose(fp);
            int t;scanf("%d",&t);
            char target_name[MAX_NAME]="";
            strcpy(target_name,names[t - 1]);
            chodoc(arr,cho,t,record_id,d,target_name);
        }
        else if(cho == 5){
            system("cls");
            printf("请选择医生：\n");
            int cnt = 0;
            char d[120]="普通外科";
            char names[MAX_LINE][MAX_NAME];
            FILE *fp = fopen("doctor.txt","rb");
            if (fp == NULL) { // 必须添加此检查
                printf("文件打开失败");
                return;
            }
            fseek(fp, 0, SEEK_SET);
            for(int j = 0;j < cho;){
                fgets(str,200,fp);
                if(str[0] == '-')j++;
                if(j == cho - 1){
                    if(str[0] == '-')continue;
                    if(str[0] == '*'){
                        for(int i = 0;i < cnt;i++){
                            fscanf(fp,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",arr[i],arr[i] + 1,arr[i] + 2,arr[i] + 3,arr[i] + 4,arr[i] + 5,arr[i] + 6,arr[i] + 7,arr[i] + 8,arr[i] + 9,arr[i] + 10);
                        }
                        break;
                    }
                    for(int i = 2,j = 0;str[i] != ',';i++,j++){
                        names[cnt][j] = str[i];
                    }
                    printf("%s",str);
                    cnt++;
                }
            }
            fclose(fp);
            int t;scanf("%d",&t);
            char target_name[MAX_NAME]="";
            strcpy(target_name,names[t - 1]);
            chodoc(arr,cho,t,record_id,d,target_name);
        }
        else if(cho == 6){
            int cnt = 0;
            char d[120]="骨科";
            char names[MAX_LINE][MAX_NAME];
            system("cls");
            printf("请选择医生：\n");
            FILE *fp = fopen("doctor.txt","rb");
            if (fp == NULL) { // 必须添加此检查
                printf("文件打开失败");
                return;
            }
            fseek(fp, 0, SEEK_SET);
            for(int j = 0;j < cho;){
                fgets(str,200,fp);
                if(str[0] == '-')j++;
                if(j == cho - 1){
                    if(str[0] == '-')continue;
                    if(str[0] == '*'){
                        for(int i = 0;i < cnt;i++){
                            fscanf(fp,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",arr[i],arr[i] + 1,arr[i] + 2,arr[i] + 3,arr[i] + 4,arr[i] + 5,arr[i] + 6,arr[i] + 7,arr[i] + 8,arr[i] + 9,arr[i] + 10);
                        }
                        break;
                    }
                    for(int i = 2,j = 0;str[i] != ',';i++,j++){
                        names[cnt][j] = str[i];
                    }
                    printf("%s",str);
                    cnt++;
                }
            }
            fclose(fp);
            int t;scanf("%d",&t);
            char target_name[MAX_NAME]="";
            strcpy(target_name,names[t - 1]);
            chodoc(arr,cho,t,record_id,d,target_name);
        }
        else if(cho == 7){
            int cnt = 0;
            char d[120]="妇产科";
            char names[MAX_LINE][MAX_NAME];
            system("cls");
            printf("请选择医生：\n");
            FILE *fp = fopen("doctor.txt","rb");
            if (fp == NULL) { // 必须添加此检查
                printf("文件打开失败");
                return;
            }
            fseek(fp, 0, SEEK_SET);
            for(int j = 0;j < cho;){
                fgets(str,200,fp);
                if(str[0] == '-')j++;
                if(j == cho - 1){
                    if(str[0] == '-')continue;
                    if(str[0] == '*'){
                        for(int i = 0;i < cnt;i++){
                            fscanf(fp,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",arr[i],arr[i] + 1,arr[i] + 2,arr[i] + 3,arr[i] + 4,arr[i] + 5,arr[i] + 6,arr[i] + 7,arr[i] + 8,arr[i] + 9,arr[i] + 10);
                        }
                        break;
                    }
                    for(int i = 2,j = 0;str[i] != ',';i++,j++){
                        names[cnt][j] = str[i];
                    }
                    printf("%s",str);
                    cnt++;
                }
            }
            fclose(fp);
            int t;scanf("%d",&t);
            char target_name[MAX_NAME]="";
            strcpy(target_name,names[t - 1]);
            chodoc(arr,cho,t,record_id,d,target_name);
        }
        else if(cho == 8){
            int cnt = 0;
            char d[120]="儿科";
            char names[MAX_LINE][MAX_NAME];
            system("cls");
            printf("请选择医生：\n");
            FILE *fp = fopen("doctor.txt","rb");
            if (fp == NULL) { // 必须添加此检查
                printf("文件打开失败");
                return;
            }
            fseek(fp, 0, SEEK_SET);
            for(int j = 0;j < cho;){
                fgets(str,200,fp);
                if(str[0] == '-')j++;
                if(j == cho - 1){
                    if(str[0] == '-')continue;
                    if(str[0] == '*'){
                        for(int i = 0;i < cnt;i++){
                            fscanf(fp,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",arr[i],arr[i] + 1,arr[i] + 2,arr[i] + 3,arr[i] + 4,arr[i] + 5,arr[i] + 6,arr[i] + 7,arr[i] + 8,arr[i] + 9,arr[i] + 10);
                        }
                        break;
                    }
                    for(int i = 2,j = 0;str[i] != ',';i++,j++){
                        names[cnt][j] = str[i];
                    }
                    printf("%s",str);
                    cnt++;
                }
            }
            fclose(fp);
            int t;scanf("%d",&t);
            char target_name[MAX_NAME]="";
            strcpy(target_name,names[t - 1]);
            chodoc(arr,cho,t,record_id,d,target_name);
        }
        else if(cho == 9){
            int cnt = 0;
            char d[120]="眼科";
            char names[MAX_LINE][MAX_NAME];
            system("cls");
            printf("请选择医生：\n");
            FILE *fp = fopen("doctor.txt","rb");
            if (fp == NULL) { // 必须添加此检查
                printf("文件打开失败");
                return;
            }
            fseek(fp, 0, SEEK_SET);
            for(int j = 0;j < cho;){
                fgets(str,200,fp);
                if(str[0] == '-')j++;
                if(j == cho - 1){
                    if(str[0] == '-')continue;
                    if(str[0] == '*'){
                        for(int i = 0;i < cnt;i++){
                            fscanf(fp,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",arr[i],arr[i] + 1,arr[i] + 2,arr[i] + 3,arr[i] + 4,arr[i] + 5,arr[i] + 6,arr[i] + 7,arr[i] + 8,arr[i] + 9,arr[i] + 10);
                        }
                        break;
                    }
                    for(int i = 2,j = 0;str[i] != ',';i++,j++){
                        names[cnt][j] = str[i];
                    }
                    printf("%s",str);
                    cnt++;
                }
            }
            fclose(fp);
            int t;scanf("%d",&t);
            char target_name[MAX_NAME]="";
            strcpy(target_name,names[t - 1]);
            chodoc(arr,cho,t,record_id,d,target_name);
        }
        else if(cho == 10){
            int cnt = 0;
            char d[120]="急诊科";
            char names[MAX_LINE][MAX_NAME];
            system("cls");
            printf("请选择医生：\n");
            FILE *fp = fopen("doctor.txt","rb");
            if (fp == NULL) { // 必须添加此检查
                printf("文件打开失败");
                return;
            }
            fseek(fp, 0, SEEK_SET);
            for(int j = 0;j < cho;){
                fgets(str,200,fp);
                if(str[0] == '-')j++;
                if(j == cho - 1){
                    if(str[0] == '-')continue;
                    if(str[0] == '*'){
                        for(int i = 0;i < cnt;i++){
                            fscanf(fp,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",arr[i],arr[i] + 1,arr[i] + 2,arr[i] + 3,arr[i] + 4,arr[i] + 5,arr[i] + 6,arr[i] + 7,arr[i] + 8,arr[i] + 9,arr[i] + 10);
                        }
                        break;
                    }
                    for(int i = 2,j = 0;str[i] != ',';i++,j++){
                        names[cnt][j] = str[i];
                    }
                    printf("%s",str);
                    cnt++;
                }
            }
            fclose(fp);
            int t;scanf("%d",&t);
            char target_name[MAX_NAME]="";
            strcpy(target_name,names[t - 1]);
            chodoc(arr,cho,t,record_id,d,target_name);
        }
    }
    else if(opt == 2){
        search(record_id);
    }
    else if(opt == 3){
        if(MessageBox(NULL,TEXT("助您早日康复！"),TEXT("感谢使用!"),MB_OK|MB_ICONASTERISK) == IDOK) {
            exit(0);
        }
    }
}
//选择预约时间并修改文件
void chodoc(int arr[][20],int cho,int t,int cid,char dep[],char optdor[])
{
    system("cls");
    char str[200],str1[200],s[200];
    long fd,fd1;
    t--;
    //    search(cid);
    printf("请选择预约时间段：\n");
    printf("1.8:30-9:00剩余号数:%d\n2.9:00-9:30剩余号数:%d\n3.9:30-10:00剩余号数:%d\n4.10:00-10:30剩余号数:%d\n5.10:30-11:00剩余号数:%d\n6.11:00-11:30剩余号数:%d\n7.14:00-14:30剩余号数:%d\n8.14:30-15:00剩余号数:%d\n9.15:00-15:30剩余号数:%d\n10.15:30-16:00剩余号数:%d\n11.16:00-16:30剩余号数:%d\n",
        arr[t][0],arr[t][1],arr[t][2],arr[t][3],arr[t][4],arr[t][5],arr[t][6],arr[t][7],arr[t][8],arr[t][9],arr[t][10]);
        int a;scanf("%d",&a);
        if (a == 1){
            strcpy(s,"8:30-9:00");
        }else if(a == 2){
            strcpy(s,"9:00-9:30");
        }else if(a == 3){
            strcpy(s,"9:30-10:00");
        }else if(a == 4){
            strcpy(s,"10:00-10:30");
        }else if(a == 5){
            strcpy(s,"10:30-11:00");
        }else if(a == 6){
            strcpy(s,"11:00-11:30");
        }else if(a == 7){
            strcpy(s,"14:00-14:30");
        }else if(a == 8){
            strcpy(s,"14:30-15:00");
        }else if(a == 9){
            strcpy(s,"15:00-15:30");
        }else if(a == 10){
            strcpy(s,"15:30-16:00");
        }else if(a == 11){
            strcpy(s,"16:00-16:30");
        }
        FILE *fp = fopen("record.txt","ab+");
        if (fp == NULL) {
            printf("文件打开失败");
            return;
        }
        fprintf(fp,"%08d,%s,%s,%s\n",cid,dep,optdor,s);
        fclose(fp);
        fp = fopen("doctor.txt","rb+");
        if (fp == NULL) { // 必须添加此检查
            printf("文件打开失败");
            return;
        }
        fseek(fp, 0, SEEK_SET); 
        for(int j = 0,k = 0,l = 0;j < cho;){
            if(cho == 1 && l == 0)fd1 = ftell(fp);
            fgets(str,200,fp);
            if(str[0] == '-')j++;
            if(j == cho - 1){
                if(l == 0){
                    if(cho != 1)fd1 = ftell(fp);
                    else fseek(fp,fd1,SEEK_SET);
                    l++;
                    k = t + 1;
                    while(k--){
                        if(t == 0){
                            fd = ftell(fp);
                        }
                        fgets(str1,200,fp);
                        if(k == 1){
                            fd = ftell(fp);
                        }
                    }
                    for(int i = 0;i < (int)strlen(str1);i++){
                        if(str1[i] == ':'){
                            if(str1[i + 2] == '0' && str1[i + 1] > '0' && str1[i + 1] <= '9'){
                                if(str1[i + 1] == '1'){
                                    str1[i + 1] = '9';
                                    str1[i + 2] = ' ';
                                    break;
                                }
                                str1[i + 2] = '9';
                                str1[i + 1] = str1[i + 1] - 1;
                            }
                            else if(str1[i + 2] > '0' && str1[i + 2] <= '9'){
                                str1[i + 2] = str1[i + 2] - 1;
                            }
                            else str1[i + 1] = str1[i + 1] - 1;
                            break;
                        }
                    }
                    fseek(fp, fd, SEEK_SET);
                    fprintf(fp,"%s",str1);
                    printf("%s",str1);
                    fseek(fp,fd1,SEEK_SET);
                }
                if(str[0] == '-')continue;
                if(str[0] == '*'){
                    fd = ftell(fp);
                    for(int i = 0;i <= t;i++){
                        fgets(str,200,fp);
                    }
                    break;
                }
            }
        }
        fseek(fp,fd,SEEK_SET);
        for(int i = 0,j = 0;i < (int)strlen(str);i++){
            if(str[i] == ',')j++;        
            if(j == a){
                if(arr[t][a - 1] == 10){
                    str[i - 2] = ' ';
                    str[i - 1] = '9';
                }
                else if(arr[t][a - 1] < 10){
                    str[i - 1] = arr[t][a - 1] - 1 + 48;
                }
                else{
                    str[i - 2] = (arr[t][a - 1] - 1)/10 + 48;
                    str[i - 1] = (arr[t][a - 1] - 1)%10 + 48;
                }
                break;
            }
        }
        char s1[200];
        fseek(fp,fd,SEEK_SET);
        for(int i = 0;i < t;i++){
            fgets(s1,200,fp);
        }
        fseek(fp,0,SEEK_CUR);
        fprintf(fp,"%s",str);
        //以下为废弃方案
        // for(int i = 0;i < t;i++){
        //     fgets(str,200,fp);
        // }
        // for(int i = 0,j;i < a - 1;i++){
        //     fscanf(fp,"%d",&j);
        //     fseek(fp,1,SEEK_CUR);
        //     //printf("%ld",ftell(fp));
        // }
        // fprintf(fp,"%02d,",arr[t][a - 1] - 1);
        printf("预约成功！");
        fclose(fp);
        printf("即将返回至主界面\n");
        system("pause");
        patient(cid);
}
//用户界面 
void patientLo()
    {
        system("cls");
        int opt;
        printf("1.注册账户\n");
        printf("2.登录账户\n");
        scanf("%d", &opt);
        //注册用户 
        if (opt == 1) {
            system("cls");
            int cnt;
            User new_user;
            FILE* fp;
            printf("--------------------用户注册-------------------------\n");
            printf("请输入姓名；");
            scanf("%49s", new_user.name);
            printf("请输入手机号；");
            scanf("%19s", new_user.account);
            printf("请输入身份证号；");
            scanf("%18s", new_user.id);
            printf("请输入密码；");
            scanf("%19s", new_user.psw);
            //将用户信息存储在文件里以便查询 
            fp = fopen("users.txt", "a+");
            if (fp == NULL) {
                printf("文件打开失败\n");
                return;
            }
            //printf("文件打开成功\n");
            fseek(fp,-(int)sizeof(int), SEEK_END);
            fscanf(fp,"%d",&cnt);
            new_user.cardnum = ++cnt;
            fseek(fp,0, SEEK_END);
            fprintf(fp,"%s,%s,%s,%s,%08d\n", new_user.name, new_user.account, new_user.id, new_user.psw,new_user.cardnum);
            fclose(fp);
            printf("\n注册成功!\n");
            printf("您的就诊卡号为%08d，该卡号将用来登录预约挂号系统，务必牢记。\n",cnt);
            printf("--------------------------------------------------\n");
            printf("按任意键跳转到登录界面\n");
            system("pause");
            Login();
        }
        //登录用户 
        else if (opt == 2) {
            Login();
        }
    }
//挂号记录查询
void search(int reid)
{
    printf("查询中.");
    Sleep(30);
    printf(".");
    Sleep(30);
    printf(".");
    Sleep(30);
    printf(".");
    Sleep(30);
    printf(".");
    Sleep(30);
    printf(".");
    Sleep(30);
    system("cls");
    system("color FC");
    time_t rawtime;
    struct tm * time_info;

    time(&rawtime);  // 获取日历时间的值
    time_info = localtime(&rawtime);  // 将时间转换为本地时间

    // 打印格式化后的时间信息
    printf("当前时间为：%d年%d月%d日 %02d:%02d:%02d\n您今天的预约记录为:\n",
        time_info->tm_year + 1900,  // 年
        time_info->tm_mon + 1,      // 月
        time_info->tm_mday,         // 日
        time_info->tm_hour,         // 时
        time_info->tm_min,          // 分
        time_info->tm_sec           // 秒
       );
    //system("color E0");
    FILE *fp=fopen("record.txt","rb");
    if (fp == NULL) {
        printf("文件打开失败");
        return;
    }
    //fseek(fp,0,SEEK_SET);
    char line[100],str[200] = {};
    int found = 0,cnt = 0;
    while(1){
        fscanf(fp,"%8d",&found);
        if(found == reid){
            cnt++;
            fseek(fp,1,SEEK_CUR);
            fgets(line,200,fp);
            printf("记录%d:\n",cnt);
            for(int i = 0,j = 0,k = 0;i < (int)strlen(line);i++,k++){
                if(line[i] == ','){
                    j++;
                    if(j == 1)printf("预约科室:%s\n",str);
                    if(j == 2)printf("预约医生:%s\n",str);
                    memset(str, 0, sizeof(str));
                    k = -1;
                }
                else{
                    str[k] = line[i];
                }
            }
            printf("预约时间段:%s\n",str);
            memset(str, 0, sizeof(str));
        }
        else fgets(line,200,fp);
        if(fgetc(fp) == -1)break;
        else fseek(fp,-1,SEEK_CUR);
    }
    if(!cnt){
        printf("未找到卡号为%08d的挂号记录\n",reid);
    }
    fclose(fp);
    printf("即将返回至主界面\n");
    system("pause");
    patient(reid);
}
//管理员界面 
void admin()
    {
        int opt;
        printf("1.新增管理员\n");
        printf("2.登录\n");
        scanf("%d", &opt);
        //注册管理员 
        if (opt == 1) {
            typedef struct Ad 
            {
                char account[20];
                char psw[20];	
            }Admin;
            Admin new_admin;
            FILE* fp;
            printf("--------------------管理员注册-------------------------\n");
            printf("请输入手机号；");
            scanf("%19s", new_admin.account);
            printf("请输入密码；");
            scanf("%19s", new_admin.psw);
            //存储管理员信息 
            fp = fopen("admins.txt", "a+");
            if (fp == NULL) {
                printf("文件打开失败\n");
                return;
            }
            fprintf(fp, "%s,%s\n", new_admin.account, new_admin.psw);
            fclose(fp);
            printf("\n注册成功!\n");
            printf("--------------------------------------------------\n");
            printf("按任意键跳转到登录界面\n");
            system("pause");
            logadmin();
        }
        //登录管理员 
        else if (opt == 2) {
            printf("请输入账号密码：\n");
            printf("账号：");
            printf("密码：");
            
        }
    }
//管理员登录成功
void logadmin()
{
    int opt;
    printf("欢迎你，管理员\n");
    printf("1.已注册用户信息\n");
    printf("2.医生管理\n");
    scanf("%d", &opt);
    if(opt == 1){
            
    }
    else if(opt == 2){
            
    }
}
//主函数
int main()
{
        int opt;
        printf("\t\t\t\t\t        ------------------------\n");
        printf("\t\t\t\t\t\t|欢迎来到预约挂号系统！|\n");
        printf("\t\t\t\t\t\t|请选择您的身份！      |\n");
        printf("\t\t\t\t\t\t|1.就诊人登录          |\n");
        printf("\t\t\t\t\t\t|2.管理员登录          |\n");
        printf("\t\t\t\t\t        ------------------------\n");
        scanf("%d", &opt);
        if (opt == 1) patientLo();
        else if (opt == 2)admin();
        return 0;
}
