#include <stdio.h>
#include <string.h>

void writer_root(const char* json, const char* name, const char type, int count, char (*ids)[64])
{
    char criteria[500000]={0}, requirements[50000]={0}, tmp[500000]={0}, icon[63]={0}, *id=NULL;
   
    if('a'==type){
        id=ids[0];
        strcpy(icon, id);
        sprintf(criteria,
                "\n\"%s\":{\"trigger\":\"minecraft:inventory_changed\",\"conditions\":{\"items\":"
                "[{\"items\":[\"%s\"]}]}}",id,id);            
        sprintf(requirements,"\n[\"%s\"]",id);
    
        for(int i=1;i<count;++i){
            id=ids[i];
            strcat(criteria,",\n");
            sprintf(tmp,"%s\"%s\":{\"trigger\":\"minecraft:inventory_changed\",\"conditions\":{\"items\":[{\"items\":[\"%s\"]}]}}",criteria,id,id);
            strcpy(criteria,tmp);
            strcat(requirements,",\n");
            sprintf(tmp,"%s[\"%s\"]",requirements,id);
            strcpy(requirements,tmp);
        }
    }
    else{
        // Code for type 'o'
        id=ids[0];
        strcpy(icon, id);
        sprintf(criteria,
                "\n\"%s\":{\"trigger\":\"minecraft:inventory_changed\",\"conditions\":{\"items\":"
                "[{\"items\":[\"%s\"]}]}}",id,id);             
        sprintf(requirements,"\n[\"%s\"",id);

        for(int i=1;i<count;++i){
            id=ids[i];
            strcat(criteria,",\n");
            sprintf(tmp,"%s\"%s\":{\"trigger\":\"minecraft:inventory_changed\",\"conditions\":{\"items\":[{\"items\":[\"%s\"]}]}}",criteria,id,id);
            strcpy(criteria,tmp);
            strcat(requirements,",\n");
            sprintf(tmp,"%s\"%s\"",requirements,id);
            strcpy(requirements,tmp);
        }
        strcat(requirements,"]");
    }

    FILE* fp=fopen(json,"w");
    if(fp == NULL) {
        printf("无法打开文件\n");
        return;
    }

    fprintf(fp,"\
		{\"display\":{\"icon\":{\"item\":\n\
\"%s\"\n\
		},\"title\":\n\
\"%s\",\n\
		\"description\":\"\",\"frame\":\"challenge\",\"background\":\"minecraft:textures/gui/advancements/backgrounds/stone.png\",\n\
        \"show_toast\":true,\"announce_to_chat\":true,\"hidden\":false},\"criteria\":{\n\
%s\n\n\
		},\"requirements\":[\n\
%s\n\
		]}\n\
",icon,name,criteria,requirements);
    fclose(fp);
}
