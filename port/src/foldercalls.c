#include "dw4/playertransactions.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>
/* Engine calls SYSctlDiskFolder(op, player, record, amount) and SYSctlDeviceFolder(op, player, kind, record,
 * revision, pocket): the messenger GAMERAM CTRLITEM receiver (3fca10) with the group DISK or DEVICE. Operation
 * names are SET/CLR/IS/ISMAX/ISEQUIP/GET/ADD; an operation the group does not implement answers false and
 * leaves the folder alone. The answer is a number (0 or 1). Returns 1 for any other method. */
/* SYSctlFlagFolder(op, index): the same receiver's FLAG group over the session FLAGFOLDER (twelve bytes, not the
 * per-player BASE_FLAGFOLDER). SET stores 1 and answers true only when the byte was 0, CLR stores 0 and answers true
 * only when it was set, IS answers the byte itself (retail passes it unchanged). An index outside the folder is refused (retail checks only writes). */
static int flag_folder_call(void *players,const dw4_script_value *a,size_t n,dw4_script_value *r)
{
    if(n!=2 || a[0].type!=DW4_SCRIPT_STRING || !a[0].string || a[1].type!=DW4_SCRIPT_NUMBER || !isfinite(a[1].number) ||
        floor(a[1].number)!=a[1].number)return -1;
    dw4_property_folder *common=dw4_playerrecords_get(players,"GETCOMMON",0);size_t count;
    const uint8_t *bytes=common?dw4_property_bytes(common,"FLAGFOLDER",&count):NULL;
    if(!bytes || a[1].number<0 || a[1].number>=(double)count)return -1;
    size_t i=(size_t)a[1].number;int answer;int raw=-1;
    uint8_t copy[64];if(count>sizeof copy)return -1;
    memcpy(copy,bytes,count);
    if(a[0].length==3 && !memcmp(a[0].string,"SET",3)){answer=copy[i]==0;if(answer)copy[i]=1;}
    else if(a[0].length==3 && !memcmp(a[0].string,"CLR",3)){answer=copy[i]!=0;if(answer)copy[i]=0;}
    else if(a[0].length==2 && !memcmp(a[0].string,"IS",2)){answer=copy[i]!=0;raw=copy[i];}
    else return -1;
    if(memcmp(copy,bytes,count) && dw4_property_set_bytes(common,"FLAGFOLDER",copy,count))return -1;
    *r=(dw4_script_value){DW4_SCRIPT_NUMBER,raw>=0?raw:answer!=0,NULL,0};return 0;
}
int dw4_playertransactions_folder_call(void *players,const char *method,const dw4_script_value *a,size_t n,
    dw4_script_value *r,char *error,size_t cap)
{
    if(!strcmp(method,"SYSctlFlagFolder")){
        if(!flag_folder_call(players,a,n,r))return 0;
        snprintf(error,cap,"%s: folder request is not valid for the session records",method);return -1;
    }
    int disk=!strcmp(method,"SYSctlDiskFolder");
    if(!disk && strcmp(method,"SYSctlDeviceFolder"))return 1;
    static const char *const ops[]={"SET","CLR","IS","ISMAX","ISEQUIP","GET","ADD"};
    if(n!=(disk?4:6) || a[0].type!=DW4_SCRIPT_STRING || !a[0].string || a[1].type!=DW4_SCRIPT_NUMBER)goto bad;
    int op=-1;for(unsigned i=0;i<7;i++)if(strlen(ops[i])==a[0].length && !memcmp(a[0].string,ops[i],a[0].length))op=(int)i;
    for(size_t i=1;i<n;i++)if(i!=2 || disk)if(a[i].type!=DW4_SCRIPT_NUMBER || !isfinite(a[i].number) ||
        floor(a[i].number)!=a[i].number || a[i].number<INT32_MIN || a[i].number>INT32_MAX)goto bad;
    if(a[1].number<0 || a[1].number>3 || op<0)goto bad;
    int answer=0;int32_t player=(int32_t)a[1].number;
    if(disk) {
        if(op<=DW4_DISK_ISMAX && dw4_playertransactions_disk_folder(players,player,(dw4_disk_operation)op,(int32_t)a[2].number,(int32_t)a[3].number,&answer))goto bad;
    }else if(op<=DW4_DEVICE_ISEQUIP) {
        static const char *const kinds[]={"weapon","armor1","armor2","abChip"};
        int kind=op==DW4_DEVICE_ISMAX?0:-1; /* ISMAX ignores the kind name */
        if(kind<0 && a[2].type==DW4_SCRIPT_STRING && a[2].string)
            for(int i=0;i<4;i++)if(strlen(kinds[i])==a[2].length && !memcmp(a[2].string,kinds[i],a[2].length))kind=i;
        if(kind>=0 && dw4_playertransactions_device(players,player,(dw4_device_operation)op,kind,
            (int32_t)a[3].number,(int32_t)a[4].number,(int32_t)a[5].number,&answer))goto bad;
    }
    *r=(dw4_script_value){DW4_SCRIPT_NUMBER,answer!=0,NULL,0};return 0;
bad:
    snprintf(error,cap,"%s: folder request is not valid for the session records",method);return -1;
}
