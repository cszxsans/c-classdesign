#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<windows.h>
#include <stdlib.h>
#include<time.h>
#define MAX_LINE 10
#define MAX_NAME 100

//用户信息结构体
typedef struct Person
{
    char name[50];
    char account[20];
    char id[19];
    char psw[20];
    int cardnum;
}User;
//医生信息结构体
typedef struct Doctor
{
    char name[50];
    char jobtitle[20];
    int num;
}docter;
//模式枚举
typedef enum
{
	SEARCH_CARD,
	SEARCH_DOC
}SearchMode;

void set_cursor_pos(int x, int y);
void Login();
void Login1();
void chodoc(int arr[][20],int cho,int t,int cid,char dep[],char optdor[]);
void patientLo();
void admin();
void logadmin();
void patient(int record_id);
void search(int reid);
void search_record(SearchMode mode);
void doctor();
void doctormanage(long *x,long *y,int cho,int mode);

//设置光标位置
void set_cursor_pos(int x, int y) {
    // 获取标准输出句柄（操作控制台的核心接口）
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    // 验证句柄有效性并进行异常处理
    if (h == INVALID_HANDLE_VALUE) {
        perror("获取控制台句柄失败");
        exit(1);
    }
    // 构造COORD结构体并设置光标位置
    COORD pos = {(short int)x, (short int)y};
    // 设置光标位置
    SetConsoleCursorPosition(h, pos);
}
//就诊人登录 
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
                        if(cnt == 0){
                            fclose(fp);
                            printf("该科室暂无医生\n");
                            system("pause");
                            patient(record_id);
                            return;
                        }
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
                        if(cnt == 0){
                            fclose(fp);
                            printf("该科室暂无医生\n");
                            system("pause");
                            patient(record_id);
                            return;
                        }
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
                        if(cnt == 0){
                            fclose(fp);
                            printf("该科室暂无医生\n");
                            system("pause");
                            patient(record_id);
                            return;
                        }
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
                        if(cnt == 0){
                            fclose(fp);
                            printf("该科室暂无医生\n");
                            system("pause");
                            patient(record_id);
                            return;
                        }
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
                        if(cnt == 0){
                            fclose(fp);
                            printf("该科室暂无医生\n");
                            system("pause");
                            patient(record_id);
                            return;
                        }
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
                        if(cnt == 0){
                            fclose(fp);
                            printf("该科室暂无医生\n");
                            system("pause");
                            patient(record_id);
                            return;
                        }
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
                        if(cnt == 0){
                            fclose(fp);
                            printf("该科室暂无医生\n");
                            system("pause");
                            patient(record_id);
                            return;
                        }
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
                        if(cnt == 0){
                            fclose(fp);
                            printf("该科室暂无医生\n");
                            system("pause");
                            patient(record_id);
                            return;
                        }
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
                        if(cnt == 0){
                            fclose(fp);
                            printf("该科室暂无医生\n");
                            system("pause");
                            patient(record_id);
                            return;
                        }
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
                        if(cnt == 0){
                            fclose(fp);
                            printf("该科室暂无医生\n");
                            system("pause");
                            patient(record_id);
                            return;
                        }
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
                    //printf("%s",str1);
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
//注册和选择登录
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
    printf("点击返回至主界面\n");
    system("pause");
    patient(reid);
}
//管理员注册和选择登录
void admin()
{
    system("cls");
    int opt;
    printf("1.新增管理员\n");
    printf("2.登录\n");
    scanf("%d", &opt);
    //注册管理员 
    if (opt == 1) {
        system("cls");
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
        fp = fopen("admins.txt", "ab+");
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
        Login1();
    }
    else if (opt == 2) {
        Login1();
    }
}
//管理员登录
void Login1()
{
    system("cls");
    printf("请输入账号密码：\n");
    printf("账号(手机号):");
    int t = 0;
    char username[20],phone[20],sec[50],insec[50],tmp[50];
    scanf("%s",username);
    FILE *fp = fopen("admins.txt","ab+");
    fseek(fp,0,SEEK_SET);
    if (fp == NULL) {
        printf("文件打开失败\n");
        return;
    }
    while(!feof(fp)){
        fscanf(fp,"%11[^,],",phone);
        if(!strcmp(phone,username)){
            fscanf(fp,"%50[^\n]",sec);
            fgets(tmp,50,fp);
            t++;
            break;
        }
        else fgets(sec,50,fp);
    }
    if(t == 0){
        printf("用户不存在，请注册或重新输入\n");
        system("pause");
        admin();
        return;
    }
    printf("请输入密码:");
    scanf("%s",insec);
    if(!strcmp(sec,insec)){
        printf("登陆成功！");
        Sleep(250);
        logadmin();
    }
    else{
        printf("密码错误，请重试\n");
        system("pause");
        Login1();
    }
}
//管理员查询
void search_record(SearchMode mode)
{
    system("cls");
	FILE *fp=fopen("record.txt","ab+");
    if (fp == NULL){
        printf("文件打开失败");
        return;
    }
	if(mode == SEARCH_CARD){
        int cid;
        printf("请输入要查询的卡号:");
        scanf("%d",&cid);
        system("cls");
        time_t rawtime;
        struct tm * time_info;

        time(&rawtime);  // 获取日历时间的值
        time_info = localtime(&rawtime);  // 将时间转换为本地时间

        // 打印格式化后的时间信息
        printf("当前时间为：%d年%d月%d日 %02d:%02d:%02d\n今日用户%08d的预约记录为:\n",
        time_info->tm_year + 1900,  // 年
        time_info->tm_mon + 1,      // 月
        time_info->tm_mday,         // 日
        time_info->tm_hour,         // 时
        time_info->tm_min,          // 分
        time_info->tm_sec,          // 秒
        cid
        );
        char line[100],str[200] = {};
        int found = 0,cnt = 0;
        while(1){
            fscanf(fp,"%8d",&found);
            if(found == cid){
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
            printf("未找到卡号为%08d的挂号记录\n",cid);
        }
        fclose(fp);
        printf("点击返回至主界面\n");
        system("pause");
        logadmin();
    }
	else if(mode == SEARCH_DOC){
        char name[100];
        printf("请输入要查询的医生:");
        scanf("%s",name);
        system("cls");
        char line[100],str[5][200] = {};
        int cnt = 0;
        while(1){
            fgets(line,200,fp);
            for(int i = 0,j = 0,k = 0;i < (int)strlen(line);i++,k++){
                if(line[i] == ','){
                    j++;
                    k = -1;
                }
                else{
                    str[j][k] = line[i];
                }
            }
            if(strcmp(str[2],name))memset(str,0,sizeof(str));
            else{
                cnt++;
                printf("记录%d:\n",cnt);
                printf("病人卡号:%s\n",str[0]);
                printf("所处科室:%s\n",str[1]);
                printf("预约时间段:%s\n",str[3]);
                memset(str, 0, sizeof(str));
            }
            if(fgetc(fp) == -1)break;
            else fseek(fp,-1,SEEK_CUR);
        }
        if(!cnt){
            printf("未找到医生%s的挂号信息\n",name);
        }
        printf("点击返回至主界面\n");
        fclose(fp);
        system("pause");
        logadmin();
    } 
}    
//管理员登录成功
void logadmin()
{
    system("cls");
    FILE *fp=fopen("record.txt","ab+");
    if (fp == NULL){
        printf("文件打开失败");
        return;
    }
    int opt;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 10);
    printf("\t\t\t\t\t\t    欢迎你，管理员\n");
    printf("\t\t\t\t\t        ----------------------\n");
    printf("\t\t\t\t\t\t|1.挂号信息          |\n");
    printf("\t\t\t\t\t\t|2.医生管理          |\n");
    printf("\t\t\t\t\t\t|3.退出系统          |\n");
    printf("\t\t\t\t\t        ----------------------\n");
    scanf("%d", &opt);
    system("cls");
    if(opt == 1){
        int choice;
        printf("请选择查询方式：\n");
        printf("1.按卡号查询:\n");
        printf("2.按医生查询:\n");
        scanf("%d",&choice);
        if(choice==1){
            search_record(SEARCH_CARD);
        }
        if(choice==2){
            search_record(SEARCH_DOC);
        }	
    }
    else if(opt == 2){
        doctor();
    }
    else if(opt == 3){
        if(MessageBox(NULL,TEXT("祝您生活愉快！"),TEXT("感谢使用!"),MB_OK|MB_ICONASTERISK) == IDOK) {
            exit(0);
        }
    }
}
//医生管理
void doctor()
{
    system("cls");
    FILE *fp = fopen("doctor.txt","ab+");
    if (fp == NULL){
        printf("文件打开失败");
        return;
    }
    if(fgetc(fp) == -1){
        for(int i = 1;i <= 10;i++){
            fprintf(fp,"%s","*************************************\n");
            fprintf(fp,"%s","-------------------------------------\n");
        }
        fseek(fp,0,SEEK_SET);
    }
    fseek(fp,0,SEEK_SET);
    printf("请选择要管理的科室:\n");
    printf("1.心血管内科\n2.呼吸内科\n3.消化内科\n4.神经内科\n5.普通外科\n6.骨科\n7.妇产科\n8.儿科\n9.眼科\n10.急诊科\n");
    int opt;
    scanf("%d",&opt);
    system("cls");
    printf("1.现有医生查看\n");
    printf("2.删除医生\n");
    printf("3.增加医生\n");
    int t;scanf("%d",&t);
    system("cls");
    if(t == 1){
        char str[200];
        int cnt = 0;
        for(int j = 0;j < opt;){
            fgets(str,200,fp);
            if(str[0] == '-')j++;
            if(j == opt - 1){
                if(str[0] == '-')continue;
                if(str[0] == '*')break;
                cnt++;
                printf("%s",str);
            }
        }
        fclose(fp);
        printf("点击返回至主界面\n");
        system("pause");
        logadmin();
    }
    else if(t == 2){
        printf("该科室现有医生为:\n");
        char str[200];
        int cnt = 0,cho;
        long arr[20],arr1[20];
        for(int j = 0;j < opt;){
            fgets(str,200,fp);
            //if(opt == 1)arr[cnt] = ftell(fp);
            if(str[0] == '-')j++;
            if(j == opt - 1){
                if(str[0] == '-'){
                    arr[cnt] = ftell(fp);
                    continue;
                }
                if(str[0] == '*'){
                    if(cnt == 0){
                        printf("该科室暂无医生\n");
                        fclose(fp);
                        system("pause");
                        doctor();
                        return;
                    }
                    for(int i = 0;i < cnt;i++){
                        fgets(str,200,fp);
                        arr1[i] = ftell(fp);
                    }
                    break;
                }
                arr[cnt] = ftell(fp);
                cnt++;
                printf("%s",str);
            }
        }
        printf("请输入要删除的医生的序号:");
        scanf("%d",&cho);
        fclose(fp);
        doctormanage(arr,arr1,cho,1);
    }
    else if(t == 3){
        char str[200];
        int cnt = 0;
        long arr[20],arr1[20];
        for(int j = 0;j < opt;){
            fgets(str,200,fp);
            //if(opt == 1)arr[cnt] = ftell(fp);
            if(str[0] == '-')j++;
            if(j == opt - 1){
                if(str[0] == '-'){
                    arr[cnt] = ftell(fp);
                    continue;
                }
                if(cnt == 0){
                    arr[0] = ftell(fp);
                    fgets(str,200,fp);
                    arr1[0] = ftell(fp);
                    break;
                }
                if(str[0] == '*'){
                    for(int i = 0;i < cnt;i++){
                        fgets(str,200,fp);
                        arr1[i] = ftell(fp);
                    }
                    break;
                }
                arr[cnt] = ftell(fp);
                cnt++;
                //printf("%s",str);
            }
        }
        fclose(fp);
        doctormanage(arr,arr1,cnt,2);
    }
}
//医生管理文件操作
void doctormanage(long *x,long *y,int cho,int mode){
    system("cls");
    if(mode == 1){
        FILE *fp,*fp_tmp;
        fp = fopen("doctor.txt","ab+");
        fp_tmp = fopen("tmp.txt", "wb");
        if (fp == NULL){
            printf("文件打开失败");
            return;
        }
        if (fp_tmp == NULL){
            printf("文件打开失败");
            return;
        }
        char line[200] = {};
        int sqort = 0;
        fseek(fp,0,SEEK_SET);
        // 逐行读取原文件，跳过第n行
        do{
            if(ftell(fp) == x[cho - 1] || ftell(fp) == y[cho - 1]){
                sqort++;
                continue;
            }
            if(sqort == 1){
                if(line[0] >= '1' && line[0] <= '9' && line[1] == '.')line[0] -= 1;
            }
            fputs(line, fp_tmp);          // 写入其他行到临时文件
        }while(fgets(line, sizeof(line), fp));
        // 关闭文件并清理
        fclose(fp);
        fclose(fp_tmp);
        
        // 删除原文件，重命名临时文件
        if (remove("doctor.txt") != 0){ 
            perror("删除原文件失败"); 
            return; 
        }
        if (rename("tmp.txt","doctor.txt") != 0){ 
            perror("重命名失败"); 
            return; 
        }
        fclose(fp);
        fclose(fp_tmp);
        printf("删除成功!");
    }
    else if(mode == 2){
        docter doc;
        int arr[20],t = cho,sum = 0;
        if(cho == 0)t = 1;
        printf("请输入医生姓名:");
        scanf("%s",doc.name);
        printf("请输入医生职称:");
        scanf("%s",doc.jobtitle);
        printf("请输入医生当天的总号数:");
        scanf("%d",&doc.num);
        system("cls");
        printf("请输入每个时间段分配的号数:\n");
        printf("1.8:30-9:00:  __\n2.9:00-9:30:  __\n3.9:30-10:00: __\n4.10:00-10:30: __\n5.10:30-11:00: __\n6.11:00-11:30: __\n7.14:00-14:30: __\n8.14:30-15:00: __\n9.15:00-15:30: __\n10.15:30-16:00:__\n11.16:00-16:30:__\n");
        for(int i = 0,j = 1,k = 14;i < 11;i++,j++){
            if(i == 3)k++;
            set_cursor_pos(k,j);
            scanf("%d",&arr[i]);
            sum += arr[i];
        }
        if(sum != doc.num){
            printf("号数有误，请重新输入\n");
            system("pause");
            doctormanage(x,y,cho,2);
        }
        FILE *fp,*fp_tmp;
        fp = fopen("doctor.txt","ab+");
        fp_tmp = fopen("tmp.txt", "wb");
        if (fp == NULL){
            printf("文件打开失败");
            return;
        }
        if (fp_tmp == NULL){
            printf("文件打开失败");
            return;
        }
        char line[200] = {};
        fseek(fp,0,SEEK_SET);
        // 逐行读取原文件，跳过第n行
        do{
            if(ftell(fp) == x[t - 1]){
                if(cho == 0){
                    fprintf(fp_tmp,"%d.%s,%s,剩余号数:%d\n",cho + 1,doc.name,doc.jobtitle,doc.num);
                    fputs(line, fp_tmp);
                    continue;
                }
                fputs(line, fp_tmp);
                fprintf(fp_tmp,"%d.%s,%s,剩余号数:%d\n",cho + 1,doc.name,doc.jobtitle,doc.num);
                continue;
            }
            if(ftell(fp) == y[t - 1]){
                if(cho == 0){
                    fprintf(fp_tmp,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",arr[0],arr[1],arr[2],arr[3],arr[4],arr[5],arr[6],arr[7],arr[8],arr[9],arr[10]);
                    fputs(line, fp_tmp);
                    continue;
                }
                fputs(line, fp_tmp);
                fprintf(fp_tmp,"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",arr[0],arr[1],arr[2],arr[3],arr[4],arr[5],arr[6],arr[7],arr[8],arr[9],arr[10]);
                continue;
            }
            fputs(line, fp_tmp);          // 写入其他行到临时文件
        }while(fgets(line, sizeof(line), fp));
        // 关闭文件并清理
        fclose(fp);
        fclose(fp_tmp);
        
        // 删除原文件，重命名临时文件
        if (remove("doctor.txt") != 0){ 
            perror("删除原文件失败"); 
            return; 
        }
        if (rename("tmp.txt","doctor.txt") != 0){ 
            perror("重命名失败"); 
            return; 
        }
        fclose(fp);
        fclose(fp_tmp);
        printf("增加成功!");
    }
    printf("点击返回至主界面\n");
    system("pause");
    logadmin();
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
