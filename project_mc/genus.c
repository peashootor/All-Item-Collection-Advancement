#include <stdio.h>
#include <string.h> 
#include <direct.h>

#define MAX_IDS 128
#define LONGEST_LINE 2048
#define PATH "D:/Programs/VSCode/code_field/code_c/c_multiple/script/project_mc/genus.txt"

void writer(const char* json, const char* parent, const char* name, const char type, int count, char (*ids)[64]);

void genus(void)
{
    char class[8]={0}, order[16]={0}, family[16]={0}, json[256]={0}, parent[256]={0};
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
            sprintf(json,"D:/Programs/VSCode/code_field/code_c/c_multiple/script/project_mc/advancements/%s/",class);
            if(_mkdir(json) == -1)
                perror("无法创建目录");
            count=0;
        }
        else{
            if(tmp[1]=='\t'){
                if(tmp[2]=='\t'){
                    //处理属
                    sscanf(tmp,"%s %s",name,tmp2);
                    //将tmp2中的逗号为分隔符，将分割后的字符串存入ids
                    p=strtok(tmp2,",");
                    while(p!=NULL){
                        strcpy(ids[count++],p);
                        p=strtok(NULL,",");
                    }
                    //将ids[0]中:后的字符串存入tmp2并保留ids[0]不变
                    strcpy(tmp2,ids[0]);
                    p=strtok(tmp2,":");
                    p=strtok(NULL,":");

                    sprintf(tmp,"%s%s.json",json,p);
                    writer(tmp,parent,name,'a',count,ids);
                    count=0;
                }
                else{
                    //处理科
                    sscanf(tmp,"%s",family);
                    sprintf(json,"D:/Programs/VSCode/code_field/code_c/c_multiple/script/project_mc/advancements/%s/%s/%s/",class,order,family);
                    if(_mkdir(json) == -1)
                        perror("无法创建目录");
                    sprintf(parent,"all_item:%s/%s/%s/_family",class,order,family);
                    count=0;
                }
            }
            else{
                //处理目
                sscanf(tmp,"%s",order);
                sprintf(json,"D:/Programs/VSCode/code_field/code_c/c_multiple/script/project_mc/advancements/%s/%s/",class,order);
                if(_mkdir(json) == -1)
                    perror("无法创建目录");
                count=0;
            }
        }
    }
    return;
}