#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<windows.h>
#include <stdlib.h>
#include<time.h>
#define MAX_LINE 10
#define MAX_NAME 100

//�û���Ϣ�ṹ��
typedef struct Person
{
    char name[50];
    char account[20];
    char id[19];
    char psw[20];
    int cardnum;
}User;
//ҽ����Ϣ�ṹ��
typedef struct Doctor
{
    char name[50];
    char jobtitle[20];
    int num;
}docter;
//ģʽö��
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

//���ù��λ��
void set_cursor_pos(int x, int y) {
    // ��ȡ��׼����������������̨�ĺ��Ľӿڣ�
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    // ��֤�����Ч�Բ������쳣����
    if (h == INVALID_HANDLE_VALUE) {
        perror("��ȡ����̨���ʧ��");
        exit(1);
    }
    // ����COORD�ṹ�岢���ù��λ��
    COORD pos = {(short int)x, (short int)y};
    // ���ù��λ��
    SetConsoleCursorPosition(h, pos);
}
//�����˵�¼ 
void Login()
{
    int t = 0;
    char sec[120],insec[50];
    system("cls");
    int num = 0;
    printf("������������ƿ���:");
    scanf("%d",&num);
    FILE *fp = fopen("users.txt","r");
    if (fp == NULL) {
        printf("�ļ���ʧ��\n");
        return;
    }
    fseek(fp,-(int)sizeof(int),SEEK_END);
    fscanf(fp, "%08d", &t);
    if(num > t){
        printf("�����ƿ��Ų�����,��ע�����������\n");
        Sleep(3000);
        patientLo();
        return;
    }
    printf("����������:");
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
                    printf("������������ԡ�\n");
                    Sleep(2000);
                    Login();
                    return;
                }    
            }
            printf("��½�ɹ���");
            Sleep(250);
            patient(num);
            break;
        }
    }
}
//�����˵�½�ɹ�
void patient(int record_id)
{
    system("cls");
    system("color E0");
    printf("\t\t\t\t��");
    Sleep(300);
    printf("  ӭ");
    Sleep(300);
    printf("  ��");
    Sleep(300);
    printf("  ��");
    Sleep(300);
    printf("  X");
    Sleep(300);
    printf("  X");
    Sleep(300);
    printf("  ҽ");
    Sleep(300);
    printf("  Ժ");
    Sleep(300);
    printf("  Ԥ");
    Sleep(300);
    printf("  Լ");
    Sleep(300);
    printf("  ��");
    Sleep(300);
    printf("  ��");
    Sleep(300);
    printf("  ϵ");
    Sleep(300);
    printf("  ͳ\n");
    Sleep(300);
    printf("\t\t\t\t\t        ----------------------\n");
    printf("\t\t\t\t\t\t|1.ԤԼ�Һ�          |\n");
    printf("\t\t\t\t\t\t|2.��¼��ѯ          |\n");
    printf("\t\t\t\t\t\t|3.�˳�ϵͳ          |\n");
    printf("\t\t\t\t\t        ----------------------\n");
    int opt;
    scanf("%d",&opt);
    system("cls");
    if(opt == 1){
        printf("��ѡ����ҪԤԼ�Ŀ��ң�\n");
        printf("1.��Ѫ���ڿ�\n2.�����ڿ�\n3.�����ڿ�\n4.���ڿ�\n5.��ͨ���\n6.�ǿ�\n7.������\n8.����\n9.�ۿ�\n10.�����\n");
        int cho;
        scanf("%d",&cho);
        char str[200];
        int arr[50][20];
        if(cho == 1){
            int cnt = 0;
            char d[120]="��Ѫ���ڿ�";
            char names[MAX_LINE][MAX_NAME];
            system("cls");
            printf("��ѡ��ҽ����\n");
            FILE *fp = fopen("doctor.txt","rb");
            if (fp == NULL) { // ������Ӵ˼��
                printf("�ļ���ʧ��");
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
                            printf("�ÿ�������ҽ��\n");
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
            char d[120]="�����ڿ�";
            char names[MAX_LINE][MAX_NAME];
            system("cls");
            printf("��ѡ��ҽ����\n");
            FILE *fp = fopen("doctor.txt","rb");
            if (fp == NULL) { // ������Ӵ˼��
                printf("�ļ���ʧ��");
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
                            printf("�ÿ�������ҽ��\n");
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
            char d[120]="�����ڿ�";
            char names[MAX_LINE][MAX_NAME];
            //        chodoc(d);
            system("cls");
            printf("��ѡ��ҽ����\n");
            FILE *fp = fopen("doctor.txt","rb");
            if (fp == NULL) { // ������Ӵ˼��
                printf("�ļ���ʧ��");
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
                            printf("�ÿ�������ҽ��\n");
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
            char d[120]="���ڿ�";
            char names[MAX_LINE][MAX_NAME];
            system("cls");
            printf("��ѡ��ҽ����\n");
            FILE *fp = fopen("doctor.txt","rb");
            if (fp == NULL) { // ������Ӵ˼��
                printf("�ļ���ʧ��");
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
                            printf("�ÿ�������ҽ��\n");
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
            printf("��ѡ��ҽ����\n");
            int cnt = 0;
            char d[120]="��ͨ���";
            char names[MAX_LINE][MAX_NAME];
            FILE *fp = fopen("doctor.txt","rb");
            if (fp == NULL) { // ������Ӵ˼��
                printf("�ļ���ʧ��");
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
                            printf("�ÿ�������ҽ��\n");
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
            char d[120]="�ǿ�";
            char names[MAX_LINE][MAX_NAME];
            system("cls");
            printf("��ѡ��ҽ����\n");
            FILE *fp = fopen("doctor.txt","rb");
            if (fp == NULL) { // ������Ӵ˼��
                printf("�ļ���ʧ��");
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
                            printf("�ÿ�������ҽ��\n");
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
            char d[120]="������";
            char names[MAX_LINE][MAX_NAME];
            system("cls");
            printf("��ѡ��ҽ����\n");
            FILE *fp = fopen("doctor.txt","rb");
            if (fp == NULL) { // ������Ӵ˼��
                printf("�ļ���ʧ��");
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
                            printf("�ÿ�������ҽ��\n");
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
            char d[120]="����";
            char names[MAX_LINE][MAX_NAME];
            system("cls");
            printf("��ѡ��ҽ����\n");
            FILE *fp = fopen("doctor.txt","rb");
            if (fp == NULL) { // ������Ӵ˼��
                printf("�ļ���ʧ��");
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
                            printf("�ÿ�������ҽ��\n");
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
            char d[120]="�ۿ�";
            char names[MAX_LINE][MAX_NAME];
            system("cls");
            printf("��ѡ��ҽ����\n");
            FILE *fp = fopen("doctor.txt","rb");
            if (fp == NULL) { // ������Ӵ˼��
                printf("�ļ���ʧ��");
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
                            printf("�ÿ�������ҽ��\n");
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
            char d[120]="�����";
            char names[MAX_LINE][MAX_NAME];
            system("cls");
            printf("��ѡ��ҽ����\n");
            FILE *fp = fopen("doctor.txt","rb");
            if (fp == NULL) { // ������Ӵ˼��
                printf("�ļ���ʧ��");
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
                            printf("�ÿ�������ҽ��\n");
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
        if(MessageBox(NULL,TEXT("�������տ�����"),TEXT("��лʹ��!"),MB_OK|MB_ICONASTERISK) == IDOK) {
            exit(0);
        }
    }
}
//ѡ��ԤԼʱ�䲢�޸��ļ�
void chodoc(int arr[][20],int cho,int t,int cid,char dep[],char optdor[])
{
    system("cls");
    char str[200],str1[200],s[200];
    long fd,fd1;
    t--;
    //    search(cid);
    printf("��ѡ��ԤԼʱ��Σ�\n");
    printf("1.8:30-9:00ʣ�����:%d\n2.9:00-9:30ʣ�����:%d\n3.9:30-10:00ʣ�����:%d\n4.10:00-10:30ʣ�����:%d\n5.10:30-11:00ʣ�����:%d\n6.11:00-11:30ʣ�����:%d\n7.14:00-14:30ʣ�����:%d\n8.14:30-15:00ʣ�����:%d\n9.15:00-15:30ʣ�����:%d\n10.15:30-16:00ʣ�����:%d\n11.16:00-16:30ʣ�����:%d\n",
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
            printf("�ļ���ʧ��");
            return;
        }
        fprintf(fp,"%08d,%s,%s,%s\n",cid,dep,optdor,s);
        fclose(fp);
        fp = fopen("doctor.txt","rb+");
        if (fp == NULL) { // ������Ӵ˼��
            printf("�ļ���ʧ��");
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
        //����Ϊ��������
        // for(int i = 0;i < t;i++){
        //     fgets(str,200,fp);
        // }
        // for(int i = 0,j;i < a - 1;i++){
        //     fscanf(fp,"%d",&j);
        //     fseek(fp,1,SEEK_CUR);
        //     //printf("%ld",ftell(fp));
        // }
        // fprintf(fp,"%02d,",arr[t][a - 1] - 1);
        printf("ԤԼ�ɹ���");
        fclose(fp);
        printf("����������������\n");
        system("pause");
        patient(cid);
}
//ע���ѡ���¼
void patientLo()
    {
        system("cls");
        int opt;
        printf("1.ע���˻�\n");
        printf("2.��¼�˻�\n");
        scanf("%d", &opt);
        //ע���û� 
        if (opt == 1) {
            system("cls");
            int cnt;
            User new_user;
            FILE* fp;
            printf("--------------------�û�ע��-------------------------\n");
            printf("������������");
            scanf("%49s", new_user.name);
            printf("�������ֻ��ţ�");
            scanf("%19s", new_user.account);
            printf("���������֤�ţ�");
            scanf("%18s", new_user.id);
            printf("���������룻");
            scanf("%19s", new_user.psw);
            //���û���Ϣ�洢���ļ����Ա��ѯ 
            fp = fopen("users.txt", "a+");
            if (fp == NULL) {
                printf("�ļ���ʧ��\n");
                return;
            }
            fseek(fp,-(int)sizeof(int), SEEK_END);
            fscanf(fp,"%d",&cnt);
            new_user.cardnum = ++cnt;
            fseek(fp,0, SEEK_END);
            fprintf(fp,"%s,%s,%s,%s,%08d\n", new_user.name, new_user.account, new_user.id, new_user.psw,new_user.cardnum);
            fclose(fp);
            printf("\nע��ɹ�!\n");
            printf("���ľ��￨��Ϊ%08d���ÿ��Ž�������¼ԤԼ�Һ�ϵͳ������μǡ�\n",cnt);
            printf("--------------------------------------------------\n");
            printf("���������ת����¼����\n");
            system("pause");
            Login();
        }
        //��¼�û� 
        else if (opt == 2) {
            Login();
        }
    }
//�Һż�¼��ѯ
void search(int reid)
{
    printf("��ѯ��.");
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

    time(&rawtime);  // ��ȡ����ʱ���ֵ
    time_info = localtime(&rawtime);  // ��ʱ��ת��Ϊ����ʱ��

    // ��ӡ��ʽ�����ʱ����Ϣ
    printf("��ǰʱ��Ϊ��%d��%d��%d�� %02d:%02d:%02d\n�������ԤԼ��¼Ϊ:\n",
        time_info->tm_year + 1900,  // ��
        time_info->tm_mon + 1,      // ��
        time_info->tm_mday,         // ��
        time_info->tm_hour,         // ʱ
        time_info->tm_min,          // ��
        time_info->tm_sec           // ��
       );
    //system("color E0");
    FILE *fp=fopen("record.txt","rb");
    if (fp == NULL) {
        printf("�ļ���ʧ��");
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
            printf("��¼%d:\n",cnt);
            for(int i = 0,j = 0,k = 0;i < (int)strlen(line);i++,k++){
                if(line[i] == ','){
                    j++;
                    if(j == 1)printf("ԤԼ����:%s\n",str);
                    if(j == 2)printf("ԤԼҽ��:%s\n",str);
                    memset(str, 0, sizeof(str));
                    k = -1;
                }
                else{
                    str[k] = line[i];
                }
            }
            printf("ԤԼʱ���:%s\n",str);
            memset(str, 0, sizeof(str));
        }
        else fgets(line,200,fp);
        if(fgetc(fp) == -1)break;
        else fseek(fp,-1,SEEK_CUR);
    }
    if(!cnt){
        printf("δ�ҵ�����Ϊ%08d�ĹҺż�¼\n",reid);
    }
    fclose(fp);
    printf("���������������\n");
    system("pause");
    patient(reid);
}
//����Աע���ѡ���¼
void admin()
{
    system("cls");
    int opt;
    printf("1.��������Ա\n");
    printf("2.��¼\n");
    scanf("%d", &opt);
    //ע�����Ա 
    if (opt == 1) {
        system("cls");
        typedef struct Ad 
        {
            char account[20];
            char psw[20];	
        }Admin;
        Admin new_admin;
        FILE* fp;
        printf("--------------------����Աע��-------------------------\n");
        printf("�������ֻ��ţ�");
        scanf("%19s", new_admin.account);
        printf("���������룻");
        scanf("%19s", new_admin.psw);
        //�洢����Ա��Ϣ 
        fp = fopen("admins.txt", "ab+");
        if (fp == NULL) {
            printf("�ļ���ʧ��\n");
            return;
        }
        fprintf(fp, "%s,%s\n", new_admin.account, new_admin.psw);
        fclose(fp);
        printf("\nע��ɹ�!\n");
        printf("--------------------------------------------------\n");
        printf("���������ת����¼����\n");
        system("pause");
        Login1();
    }
    else if (opt == 2) {
        Login1();
    }
}
//����Ա��¼
void Login1()
{
    system("cls");
    printf("�������˺����룺\n");
    printf("�˺�(�ֻ���):");
    int t = 0;
    char username[20],phone[20],sec[50],insec[50],tmp[50];
    scanf("%s",username);
    FILE *fp = fopen("admins.txt","ab+");
    fseek(fp,0,SEEK_SET);
    if (fp == NULL) {
        printf("�ļ���ʧ��\n");
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
        printf("�û������ڣ���ע�����������\n");
        system("pause");
        admin();
        return;
    }
    printf("����������:");
    scanf("%s",insec);
    if(!strcmp(sec,insec)){
        printf("��½�ɹ���");
        Sleep(250);
        logadmin();
    }
    else{
        printf("�������������\n");
        system("pause");
        Login1();
    }
}
//����Ա��ѯ
void search_record(SearchMode mode)
{
    system("cls");
	FILE *fp=fopen("record.txt","ab+");
    if (fp == NULL){
        printf("�ļ���ʧ��");
        return;
    }
	if(mode == SEARCH_CARD){
        int cid;
        printf("������Ҫ��ѯ�Ŀ���:");
        scanf("%d",&cid);
        system("cls");
        time_t rawtime;
        struct tm * time_info;

        time(&rawtime);  // ��ȡ����ʱ���ֵ
        time_info = localtime(&rawtime);  // ��ʱ��ת��Ϊ����ʱ��

        // ��ӡ��ʽ�����ʱ����Ϣ
        printf("��ǰʱ��Ϊ��%d��%d��%d�� %02d:%02d:%02d\n�����û�%08d��ԤԼ��¼Ϊ:\n",
        time_info->tm_year + 1900,  // ��
        time_info->tm_mon + 1,      // ��
        time_info->tm_mday,         // ��
        time_info->tm_hour,         // ʱ
        time_info->tm_min,          // ��
        time_info->tm_sec,          // ��
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
                printf("��¼%d:\n",cnt);
                for(int i = 0,j = 0,k = 0;i < (int)strlen(line);i++,k++){
                    if(line[i] == ','){
                        j++;
                        if(j == 1)printf("ԤԼ����:%s\n",str);
                        if(j == 2)printf("ԤԼҽ��:%s\n",str);
                        memset(str, 0, sizeof(str));
                        k = -1;
                    }
                    else{
                        str[k] = line[i];
                    }
                }
                printf("ԤԼʱ���:%s\n",str);
                memset(str, 0, sizeof(str));
            }
            else fgets(line,200,fp);
            if(fgetc(fp) == -1)break;
            else fseek(fp,-1,SEEK_CUR);
        }
        if(!cnt){
            printf("δ�ҵ�����Ϊ%08d�ĹҺż�¼\n",cid);
        }
        fclose(fp);
        printf("���������������\n");
        system("pause");
        logadmin();
    }
	else if(mode == SEARCH_DOC){
        char name[100];
        printf("������Ҫ��ѯ��ҽ��:");
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
                printf("��¼%d:\n",cnt);
                printf("���˿���:%s\n",str[0]);
                printf("��������:%s\n",str[1]);
                printf("ԤԼʱ���:%s\n",str[3]);
                memset(str, 0, sizeof(str));
            }
            if(fgetc(fp) == -1)break;
            else fseek(fp,-1,SEEK_CUR);
        }
        if(!cnt){
            printf("δ�ҵ�ҽ��%s�ĹҺ���Ϣ\n",name);
        }
        printf("���������������\n");
        fclose(fp);
        system("pause");
        logadmin();
    } 
}    
//����Ա��¼�ɹ�
void logadmin()
{
    system("cls");
    FILE *fp=fopen("record.txt","ab+");
    if (fp == NULL){
        printf("�ļ���ʧ��");
        return;
    }
    int opt;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 10);
    printf("\t\t\t\t\t\t    ��ӭ�㣬����Ա\n");
    printf("\t\t\t\t\t        ----------------------\n");
    printf("\t\t\t\t\t\t|1.�Һ���Ϣ          |\n");
    printf("\t\t\t\t\t\t|2.ҽ������          |\n");
    printf("\t\t\t\t\t\t|3.�˳�ϵͳ          |\n");
    printf("\t\t\t\t\t        ----------------------\n");
    scanf("%d", &opt);
    system("cls");
    if(opt == 1){
        int choice;
        printf("��ѡ���ѯ��ʽ��\n");
        printf("1.�����Ų�ѯ:\n");
        printf("2.��ҽ����ѯ:\n");
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
        if(MessageBox(NULL,TEXT("ף��������죡"),TEXT("��лʹ��!"),MB_OK|MB_ICONASTERISK) == IDOK) {
            exit(0);
        }
    }
}
//ҽ������
void doctor()
{
    system("cls");
    FILE *fp = fopen("doctor.txt","ab+");
    if (fp == NULL){
        printf("�ļ���ʧ��");
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
    printf("��ѡ��Ҫ����Ŀ���:\n");
    printf("1.��Ѫ���ڿ�\n2.�����ڿ�\n3.�����ڿ�\n4.���ڿ�\n5.��ͨ���\n6.�ǿ�\n7.������\n8.����\n9.�ۿ�\n10.�����\n");
    int opt;
    scanf("%d",&opt);
    system("cls");
    printf("1.����ҽ���鿴\n");
    printf("2.ɾ��ҽ��\n");
    printf("3.����ҽ��\n");
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
        printf("���������������\n");
        system("pause");
        logadmin();
    }
    else if(t == 2){
        printf("�ÿ�������ҽ��Ϊ:\n");
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
                        printf("�ÿ�������ҽ��\n");
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
        printf("������Ҫɾ����ҽ�������:");
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
//ҽ�������ļ�����
void doctormanage(long *x,long *y,int cho,int mode){
    system("cls");
    if(mode == 1){
        FILE *fp,*fp_tmp;
        fp = fopen("doctor.txt","ab+");
        fp_tmp = fopen("tmp.txt", "wb");
        if (fp == NULL){
            printf("�ļ���ʧ��");
            return;
        }
        if (fp_tmp == NULL){
            printf("�ļ���ʧ��");
            return;
        }
        char line[200] = {};
        int sqort = 0;
        fseek(fp,0,SEEK_SET);
        // ���ж�ȡԭ�ļ���������n��
        do{
            if(ftell(fp) == x[cho - 1] || ftell(fp) == y[cho - 1]){
                sqort++;
                continue;
            }
            if(sqort == 1){
                if(line[0] >= '1' && line[0] <= '9' && line[1] == '.')line[0] -= 1;
            }
            fputs(line, fp_tmp);          // д�������е���ʱ�ļ�
        }while(fgets(line, sizeof(line), fp));
        // �ر��ļ�������
        fclose(fp);
        fclose(fp_tmp);
        
        // ɾ��ԭ�ļ�����������ʱ�ļ�
        if (remove("doctor.txt") != 0){ 
            perror("ɾ��ԭ�ļ�ʧ��"); 
            return; 
        }
        if (rename("tmp.txt","doctor.txt") != 0){ 
            perror("������ʧ��"); 
            return; 
        }
        fclose(fp);
        fclose(fp_tmp);
        printf("ɾ���ɹ�!");
    }
    else if(mode == 2){
        docter doc;
        int arr[20],t = cho,sum = 0;
        if(cho == 0)t = 1;
        printf("������ҽ������:");
        scanf("%s",doc.name);
        printf("������ҽ��ְ��:");
        scanf("%s",doc.jobtitle);
        printf("������ҽ��������ܺ���:");
        scanf("%d",&doc.num);
        system("cls");
        printf("������ÿ��ʱ��η���ĺ���:\n");
        printf("1.8:30-9:00:  __\n2.9:00-9:30:  __\n3.9:30-10:00: __\n4.10:00-10:30: __\n5.10:30-11:00: __\n6.11:00-11:30: __\n7.14:00-14:30: __\n8.14:30-15:00: __\n9.15:00-15:30: __\n10.15:30-16:00:__\n11.16:00-16:30:__\n");
        for(int i = 0,j = 1,k = 14;i < 11;i++,j++){
            if(i == 3)k++;
            set_cursor_pos(k,j);
            scanf("%d",&arr[i]);
            sum += arr[i];
        }
        if(sum != doc.num){
            printf("������������������\n");
            system("pause");
            doctormanage(x,y,cho,2);
        }
        FILE *fp,*fp_tmp;
        fp = fopen("doctor.txt","ab+");
        fp_tmp = fopen("tmp.txt", "wb");
        if (fp == NULL){
            printf("�ļ���ʧ��");
            return;
        }
        if (fp_tmp == NULL){
            printf("�ļ���ʧ��");
            return;
        }
        char line[200] = {};
        fseek(fp,0,SEEK_SET);
        // ���ж�ȡԭ�ļ���������n��
        do{
            if(ftell(fp) == x[t - 1]){
                if(cho == 0){
                    fprintf(fp_tmp,"%d.%s,%s,ʣ�����:%d\n",cho + 1,doc.name,doc.jobtitle,doc.num);
                    fputs(line, fp_tmp);
                    continue;
                }
                fputs(line, fp_tmp);
                fprintf(fp_tmp,"%d.%s,%s,ʣ�����:%d\n",cho + 1,doc.name,doc.jobtitle,doc.num);
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
            fputs(line, fp_tmp);          // д�������е���ʱ�ļ�
        }while(fgets(line, sizeof(line), fp));
        // �ر��ļ�������
        fclose(fp);
        fclose(fp_tmp);
        
        // ɾ��ԭ�ļ�����������ʱ�ļ�
        if (remove("doctor.txt") != 0){ 
            perror("ɾ��ԭ�ļ�ʧ��"); 
            return; 
        }
        if (rename("tmp.txt","doctor.txt") != 0){ 
            perror("������ʧ��"); 
            return; 
        }
        fclose(fp);
        fclose(fp_tmp);
        printf("���ӳɹ�!");
    }
    printf("���������������\n");
    system("pause");
    logadmin();
}
//������
int main()
{
    int opt;
    printf("\t\t\t\t\t        ------------------------\n");
    printf("\t\t\t\t\t\t|��ӭ����ԤԼ�Һ�ϵͳ��|\n");
    printf("\t\t\t\t\t\t|��ѡ��������ݣ�      |\n");
    printf("\t\t\t\t\t\t|1.�����˵�¼          |\n");
    printf("\t\t\t\t\t\t|2.����Ա��¼          |\n");
    printf("\t\t\t\t\t        ------------------------\n");
    scanf("%d", &opt);
    if (opt == 1) patientLo();
    else if (opt == 2)admin();
    return 0;
}
