#include<cstdio>
#include<cstdlib>
#include<windows.h>
const int max_l = 120;
const int sleep_me = 10; 
//static int:仅能在本文件使用
//const：常量 
//枚举常量 
int main() {
    char ch[max_l];
    int i = 0;
    ch[i] = getchar();
    i ++;
    while((ch[i] = getchar()) != EOF) {
        if(ch[i] == '\n')
            break;
        i += 1;
    }
    ch[i] = '\0';
    printf("%s",ch);
    int j = i;
    while(1) {
        for(;j <= max_l;j ++) {
            system("cls");
            //			printf("7");
            for(int k = 0;k < j - i;k ++)
                printf(" ");
            printf("%s",ch);
            Sleep(sleep_me);
        }
        for(;j > i;j --) {
            system("cls");
            for(int k = 0;k < j - i - 1;k ++)
                printf(" ");
            printf("%s",ch);
            Sleep(sleep_me);
        }
    }/**/
    return 0;
}

