/* Retail STATUS 3d60e0 freeze, 3d8740 caps and 3d59b0 entry/restore order.
 * Scene and ADDHP/ADDMP publication require the owning service sink. */
#include "dw4/statusscene.h"
#include <stdio.h>
static int send(dw4_statusscene *s,int op,const char *category,const char *name,const char *key,const char *value,char *e,size_t n)
{
    dw4_statusscene_command c={.op=op,.category=category,.name=name,.key=key,.value=value};
    if(s->io(s->user,&c,e,n)){s->failed=1;return -1;}return 0;
}
static int valid(dw4_statusscene *s,int phase,char *e,size_t n)
{
    if(!s || !s->players || !s->io || s->failed || s->phase!=phase){snprintf(e,n,"STATUS scene lifecycle unavailable or out of order");return -1;}return 0;
}
#define SEND(cat,name,key,value) do {if(send(s,DW4_STATUSSCENE_COMMAND,cat,name,key,value,e,n))return -1;} while(0)
int dw4_statusscene_freeze(dw4_statusscene *s,char *e,size_t n)
{
    if(valid(s,0,e,n))return -1;
    SEND("MODELCTRL",NULL,"ONFREEZE",NULL);SEND("GENERATER",NULL,"ONFREEZE",NULL);
    if(send(s,DW4_STATUSSCENE_HOLD,NULL,NULL,NULL,"1",e,n))return -1;
    SEND("SOUND",NULL,"ONFREEZE",NULL);s->phase=1;return 0;
}
int dw4_statusscene_enter(dw4_statusscene *s,char *e,size_t n)
{
    if(valid(s,1,e,n))return -1;
    int32_t use[4],bit[4],xdata[4];
    /* Validate all record dependencies before any mutation or scene commands. */
    for(int i=0;i<4;i++){
        dw4_property_folder *f=dw4_playerrecords_get(s->players,"GETPLAYER",i);
        if(dw4_property_number(f,"ISUSE",use+i) || ((uint8_t)use[i] &&
           (dw4_property_number(f,"BIT",bit+i) || dw4_property_number(f,"XDATA",xdata+i)))){
            snprintf(e,n,"STATUS entry requires player %d ISUSE/BIT/XDATA",i);s->failed=1;return -1;}
    }
    for(int i=0;i<4;i++)if((uint8_t)use[i]){
        dw4_property_folder *f=dw4_playerrecords_get(s->players,"GETPLAYER",i);
        if((bit[i]>9999999 && dw4_property_set_number(f,"BIT",9999999)) ||
           (xdata[i]>9999 && dw4_property_set_number(f,"XDATA",9999))){s->failed=1;return -1;}
    }
    SEND("STAGECTL",NULL,"PADINPUT","ENABLE");
    SEND("LAYERCTL","WN01","SWITCH","DISPOFF");SEND("LAYERCTL","WN00","SWITCH","DISPOFF");
    s->phase=2;return 0;
}
int dw4_statusscene_restore(dw4_statusscene *s,char *e,size_t n)
{
    if(valid(s,2,e,n))return -1;
    dw4_statusscene_command health[4];int32_t use[4];
    for(int i=0;i<4;i++){
        dw4_property_folder *f=dw4_playerrecords_get(s->players,"GETPLAYER",i);
        health[i]=(dw4_statusscene_command){.op=DW4_STATUSSCENE_HEALTH,.category="GAMERAM",.player=i};
        if(dw4_property_number(f,"ISUSE",use+i) || ((uint8_t)use[i] &&
           (dw4_property_number(f,"HP",&health[i].hp) || dw4_property_number(f,"MP",&health[i].mp) ||
            dw4_property_number(f,"MHP",&health[i].max_hp) || dw4_property_number(f,"MMP",&health[i].max_mp)))){
            snprintf(e,n,"STATUS restore requires player %d HP/MP owner records",i);s->failed=1;return -1;}
    }
    SEND("SOUND",NULL,"OFFREEZE",NULL);SEND("GENERATER",NULL,"OFFREEZE",NULL);SEND("MODELCTRL",NULL,"OFFREEZE",NULL);
    if(send(s,DW4_STATUSSCENE_HOLD,NULL,NULL,NULL,"0",e,n))return -1;
    for(int i=0;i<4;i++)if((uint8_t)use[i])if(s->io(s->user,health+i,e,n)){s->failed=1;return -1;}
    SEND("LAYERCTL","WN01","SWITCH","DISPON");SEND("LAYERCTL","WN00","SWITCH","DISPON");
    s->phase=0;return 0;
}
