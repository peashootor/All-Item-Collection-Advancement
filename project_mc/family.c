#include <stdio.h>
#include <string.h> 
#include <direct.h>

#define MAX_IDS 128
#define LONGEST_LINE 4096
#define PATH "D:/Programs/VSCode/code_field/code_c/c_multiple/script/project_mc/family.txt"

void writer(const char* json, const char* parent, const char* name, const char type, int count, char (*ids)[64]);

void family(void)
{
    char class[8]={0}, order[1600]={0}, family[16]={0}, json[1024]={0}, parent[1024]={0};
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
            count=0;
        }
        else{
            if(tmp[1]=='\t'){
                    //处理科
                    sscanf(tmp,"%s %s %s",family,name,tmp2);
                    //将tmp2中的逗号为分隔符，将分割后的字符串存入ids
                    p=strtok(tmp2,",");
                    while(p!=NULL){
                        strcpy(ids[count++],p);
                        p=strtok(NULL,",");
                    }
                    sprintf(json,"D:/Programs/VSCode/code_field/code_c/c_multiple/script/project_mc/advancements/%s/%s/%s/_family.json",class,order,family);
                    sprintf(parent,"all_item:%s/%s/root",class,order);
                    writer(json,parent,name,'o',count,ids);
                    count=0;                          
            }
            else{
                //处理目
                sscanf(tmp,"%s",order);
                count=0;
            }
        }
    }
    return;
}