#include <stdio.h>
#include <string.h> 
#include <direct.h>

#define MAX_IDS 1000
#define LONGEST_LINE 10000
#define PATH "D:/Programs/VSCode/code_field/code_c/c_multiple/script/project_mc/order.txt"

void writer_root(const char* json, const char* name, const char type, int count, char (*ids)[64]);

void order(void)
{
    char class[8]={0}, order[1600]={0}, json[256]={0};
    char name[256]={0}, ids[MAX_IDS][64]={0}, tmp[LONGEST_LINE]={0}, tmp2[LONGEST_LINE]={0}, *p=NULL;
    int count=0;

    FILE* fp=fopen(PATH,"r");
    if(fp == NULL) {
        printf("无法打开文件啊\n");
        return;
    }
    //读取每一行文本，起始为z的存入class，起始为一个\t的存入order，起始为两个\t的存入family，起始为三个\t的存入name
    while(fgets(tmp,LONGEST_LINE,fp)!=NULL){
        if(tmp[0]!='\t'){
            //处理纲
            sscanf(tmp,"%s",class);
        }
        else{
                    //处理目
                    sscanf(tmp,"%s %s %s",order,name,tmp2);
                    //将tmp2中的逗号为分隔符，将分割后的字符串存入ids
                    p=strtok(tmp2,",");
                    while(p!=NULL){
                        strcpy(ids[count++],p);
                        p=strtok(NULL,",");
                    }
                    sprintf(json,"D:/Programs/VSCode/code_field/code_c/c_multiple/script/project_mc/advancements/%s/%s/root.json",class,order);
                    writer_root(json,name,'o',count,ids);
                    count=0;           
        }
    }
    return;
}