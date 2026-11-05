#include "dw4/statuscontent.h"
#include "dw4/playerstats.h"
#include <stdio.h>
#include <string.h>
static int emit(dw4_statusview_io io,void *u,int op,const char *g,const char *n,const char *k,const char *v,int32_t call)
{dw4_statusview_command c={op,g,n,k,v,call};return io(u,&c);}
static int set(dw4_statusview_io io,void *u,const char *g,const char *n,const char *v)
{return emit(io,u,DW4_VIEW_SET_TEXT,g,n,NULL,v,0);}
static int visible(dw4_statusview_io io,void *u,const char *g,const char *n,int on)
{return emit(io,u,DW4_VIEW_SWITCH,g,n,NULL,on?"DISPON":"DISPOFF",0);}
static int script(dw4_statusview_io io,void *u,int call)
{return emit(io,u,DW4_VIEW_SCRIPT,NULL,"txt_status.lua",NULL,NULL,call);}
static int color(dw4_statusview_io io,void *u,const char *g,const char *n,const float *v)
{char s[80];snprintf(s,sizeof s,"V<%.9g,%.9g,%.9g>",v[0],v[1],v[2]);return emit(io,u,DW4_VIEW_COLOR,g,n,"COLOR",s,0);}
static int preflight(void *u,const dw4_statusview_command *c){(void)u;(void)c;return 0;}
int dw4_statuscontent_number(int variant,int32_t value,int width,dw4_statusview_io io,void *u)
{
    if(!io || value<0 || value>9999999 || width<0 || width>7)return -1;
    const char *g=variant==3?"STWINFONT28":"STWINFONT25";char number[8];
    if(width)snprintf(number,sizeof number,"%0*d",width,value);
    for(unsigned i=0;i<7;i++){char font[16];snprintf(font,sizeof font,"font%03u",i);if(visible(io,u,g,font,0))return -1;}
    if(width){size_t n=strlen(number);for(size_t i=n;i>0;i--){
        char font[16],digit[2]={number[n-i],0};snprintf(font,sizeof font,"font%03u",(unsigned)i-1);
        if(set(io,u,g,font,digit) || visible(io,u,g,font,1))return -1;
    }}return 0;
}
/* ShopCtrlEditBit 4402e0/440110 over STWINFONT25 (shop variants 0/1). Seven fonts named by
 * `family` (0 "font%03d", 1 "font01%d", 2 "font02%d") are hidden, then the zero-padded value
 * (width 1..7, 1 meaning plain %d) is written right-aligned from font index 0. A width outside
 * 1..7 only hides, as retail's switch falls through. */
int dw4_statuscontent_digits(int family,int32_t value,int width,dw4_statusview_io io,void *u)
{
    static const char *const formats[]={"font%03d","font01%d","font02%d"};
    if(!io || family<0 || family>2 || value<0 || value>9999999)return -1;
    char font[16],number[16];
    for(int i=0;i<7;i++){snprintf(font,sizeof font,formats[family],i);if(visible(io,u,"STWINFONT25",font,0))return -1;}
    if(width<1 || width>7)return 0;
    snprintf(number,sizeof number,"%0*d",width,value);
    size_t n=strlen(number);
    for(size_t j=n;j>0;j--){
        char digit[2]={number[n-j],0};snprintf(font,sizeof font,formats[family],(int)j-1);
        if(set(io,u,"STWINFONT25",font,digit) || visible(io,u,"STWINFONT25",font,1))return -1;
    }
    return 0;
}
int dw4_statuscontent_flag(const dw4_databases *db,const int32_t *indices,size_t count,
    int selected,int rows,int description,dw4_statusview_io io,void *u)
{
    if(!db || !io || count>12 || (count && !indices))return -1;
    const dw4_database *items=dw4_databases_get(db,"impItem");
    const char *names[12],*txt=NULL;
    for(size_t i=0;rows && i<count;i++)if(!(names[i]=dw4_database_string(items,indices[i],"NAME")))return -1;
    if(description && count){
        if(selected<0 || (size_t)selected>=count || !(txt=dw4_database_string(items,indices[selected],"TXT")))return -1;
    }
    if(rows)for(unsigned i=0;i<12;i++){
        char font[16];snprintf(font,sizeof font,"font%03u",i);
        if(i<count){if(set(io,u,"STWINFONT14",font,names[i]))return -1;}
        else if(visible(io,u,"STWINFONT14",font,0))return -1;
    }
    return txt?set(io,u,"STWINFONT29","font000",txt):0;
}
const char *dw4_statuscontent_item_string(const dw4_databases *db,const dw4_item_record *i,const char *key)
{
    static const char *const names[]={"weapon","armor1","armor2","abChip"};
    const char *name=i && i->kind>=0 && i->kind<4?names[i->kind]:i && i->kind==4?"conItem":i && i->kind==9?"pcTech":NULL;
    return name && key?dw4_database_string(dw4_databases_get(db,name),i->record,key):NULL;
}
void dw4_statuscontent_item_color(const dw4_item_record *i,float out[3])
{
    out[0]=out[1]=out[2]=.9f;
    if(!i || (i->kind>=3 && i->kind<=6) || (i->kind==0 && i->record==276) ||
       (i->kind==1 && i->record==31) || (i->kind==2 && i->record==44))return;
    int v=i->revision;
    if(v>=1000){out[0]=1;out[1]=0;out[2]=.9f;}
    else if(v>=501){out[0]=1;out[1]=.6f;out[2]=.1f;}
    else if(v>=101){out[0]=.9f;out[1]=.8f;out[2]=.1f;}
    else if(v>=31){out[0]=.4f;out[1]=1;out[2]=.6f;}
    else if(v>0){out[0]=.1f;out[1]=.9f;out[2]=1;}
}
static int description_text(const dw4_databases *db,const dw4_item_record *i,int pocket,char *out,size_t cap)
{
    const char *s=dw4_statuscontent_item_string(db,i,"TXT");if(!s)return -1;
    char suffix[2]={(char)((uint32_t)i->pocket+'0'),0};
    int n=snprintf(out,cap,"%s%s",s,pocket?suffix:"");return n<0 || (size_t)n>=cap?-1:0;
}
int dw4_statuscontent_equipment(dw4_playerrecords *p,const dw4_databases *db,int32_t player,
    int kind,int32_t selected,int description,dw4_statusview_io io,void *u)
{
    static const char *const keys[]={"POWERSOCKET","MAINSLOT","SUBSLOT"};
    if(!io || !db || kind<0 || kind>2)return -1;
    dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",player);size_t n;
    const dw4_item_record *items=dw4_property_items(f,keys[kind],&n);
    if(!items || n!=(kind?1u:3u) || selected< -1 || (selected>=0 && (size_t)selected>=n))return -1;
    const char *names[3]={0};char txt[8192];
    if(description){if(selected>=0 && items[selected].kind!=-1 && description_text(db,items+selected,kind!=2,txt,sizeof txt))return -1;}
    else for(size_t i=0;i<n;i++)if(items[i].kind!=-1 && !(names[i]=dw4_statuscontent_item_string(db,items+i,"NAME")))return -1;
    if(!description && kind!=2 && dw4_statuscontent_pockets(p,db,player,kind,preflight,NULL))return -1;
    if(description){
        int on=selected>=0 && items[selected].kind!=-1;
        if(on && set(io,u,"STWINFONT29","font000",txt))return -1;
        return visible(io,u,"STWINFONT29","font000",on);
    }
    if(script(io,u,kind?137:136) || script(io,u,38+kind*2))return -1;
    for(size_t i=0;i<n;i++){
        char font[16];snprintf(font,sizeof font,"font%03u",(unsigned)i);
        if(names[i]){float rgb[3];dw4_statuscontent_item_color(items+i,rgb);
            if(set(io,u,"STWINFONT11",font,names[i]) || color(io,u,"STWINFONT11",font,rgb))return -1;}
        if(visible(io,u,"STWINFONT11",font,names[i]!=NULL))return -1;
    }
    return kind==2?0:dw4_statuscontent_pockets(p,db,player,kind,io,u);
}
int dw4_statuscontent_pockets(dw4_playerrecords *p,const dw4_databases *db,int32_t player,int kind,dw4_statusview_io io,void *u)
{
    if(!io || !db || kind<0 || kind>2)return -1;
    if(kind==2){for(unsigned i=0;i<5;i++)for(unsigned j=0;j<2;j++){
        char font[16];snprintf(font,sizeof font,"font%03u",(j?200:100)+i);
        if(visible(io,u,"STWINFONT11",font,0))return -1;}return 0;}
    dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",player);size_t n;
    const dw4_item_record *base=dw4_property_items(f,kind?"MAINSLOT":"POWERSOCKET",&n);
    if(!base || n!=(kind?1u:3u))return -1;
    int pocket=base[0].kind==-1?-1:base[0].pocket;
    const dw4_item_record *items=dw4_property_items(f,kind?"MAINPOCKET":"POWERPOCKET",&n);
    if(!items || n!=5)return -1;
    const char *names[5];for(size_t i=0;i<5;i++){names[i]=items[i].kind==-1?NULL:dw4_statuscontent_item_string(db,items+i,"NAME");if(items[i].kind!=-1 && !names[i])return -1;}
    char sequence[32];snprintf(sequence,sizeof sequence,"SQ_%dLINEOPEN",pocket>=1 && pocket<=5?pocket:0);
    if(emit(io,u,DW4_VIEW_MODEL,NULL,"i_stpocket",sequence,"SQ_CLOSE",0))return -1;
    for(unsigned i=0;i<5;i++){char font[16];snprintf(font,sizeof font,"font%03u",100+i);
        if(names[i] && set(io,u,"STWINFONT11",font,names[i]))return -1;
        if(visible(io,u,"STWINFONT11",font,names[i]!=NULL))return -1;}
    return 0;
}
int dw4_statuscontent_device(const dw4_databases *db,const dw4_item_record *items,size_t count,
    const uint8_t enabled[12],int page,int pages,int selected,int bank,int rows,int description,dw4_statusview_io io,void *u)
{
    if(!db || !io || (count && !items) || count>96 || page<0 || page>7 || pages<1 || pages>8 || page>=pages || selected<0 || selected>=12)return -1;
    const char *names[12]={0};char txt[8192];size_t start=(size_t)page*12,index=start+(size_t)selected;
    if(rows)for(unsigned i=0;i<12 && start+i<count;i++){names[i]=dw4_statuscontent_item_string(db,items+start+i,"NAME");if(!names[i])return -1;}
    if(description && index<count){const dw4_item_record *i=items+index;
        int pocket=(i->kind==0 && i->record!=276) || (i->kind==1 && i->record!=31);
        if(description_text(db,i,pocket,txt,sizeof txt))return -1;}
    if(rows){for(unsigned i=0;i<12;i++){
        char font[16];snprintf(font,sizeof font,"font%03u",i);
        if(names[i]){
            /* Retail prefixes these exact two-byte markers; conversion to
             * glyph codes belongs to the original text service boundary. */
            char name[8192];int n=snprintf(name,sizeof name,"%s%s",items[start+i].equipped?"\x81\xba":"\x8a\x71",names[i]);
            if(n<0 || (size_t)n>=sizeof name || set(io,u,"STWINFONT14",font,name))return -1;
            float rgb[3];dw4_statuscontent_item_color(items+start+i,rgb);
            if(enabled && !enabled[i]){if(emit(io,u,DW4_VIEW_COLOR,"STWINFONT14",font,"CANCELCOLOR",NULL,0))return -1;}
            else if(color(io,u,"STWINFONT14",font,rgb))return -1;
            if(set(io,u,"STWINFONT16",font," "))return -1;
        }
        if(visible(io,u,"STWINFONT14",font,names[i]!=NULL) || visible(io,u,"STWINFONT16",font,names[i]!=NULL))return -1;
    }
    char value[2]={(char)('1'+page),0};const char *g=bank?"STWINFONT40":"STWINFONT23";
    if(set(io,u,g,"font000",value))return -1;
    value[0]=(char)('0'+pages);if(set(io,u,g,"font001",value))return -1;}
    if(description){if(index<count && set(io,u,"STWINFONT29","font000",txt))return -1;
        return visible(io,u,"STWINFONT29","font000",index<count);}
    return 0;
}
int dw4_statuscontent_xdata_chip(const dw4_databases *db,const dw4_item_record *items,size_t count,
    int page,int pages,int selected,int rows,int description,dw4_statusview_io io,void *u)
{
    if(!db || !io || (count && !items) || count>36 || page<0 || pages<1 || pages>3 || page>=pages)return -1;
    if(rows) {
        for(unsigned i=0;i<12;i++) {
            char font[16];snprintf(font,sizeof font,"font%03u",i);
            size_t index=(size_t)page*12+i;
            if(index<count) {
                const char *name=dw4_statuscontent_item_string(db,items+index,"NAME");int32_t next;
                if(!name || dw4_playerstats_item_attribute((void *)db,items+index,"NEXTX",&next))return -1;
                char value[16];
                if(next<1)snprintf(value,sizeof value,"----");else snprintf(value,sizeof value,"%d",next);
                if(set(io,u,"STWINFONT14",font,name) || set(io,u,"STWINFONT17",font,value) ||
                   visible(io,u,"STWINFONT14",font,1) || visible(io,u,"STWINFONT17",font,1))return -1;
            }else if(visible(io,u,"STWINFONT14",font,0) || visible(io,u,"STWINFONT17",font,0))return -1;
        }
        /* Single characters, as retail: page+'1' and pages+'0'. */
        char label[2]={(char)('1'+page),0};
        if(set(io,u,"STWINFONT30","font000",label))return -1;
        label[0]=(char)('0'+pages);
        if(set(io,u,"STWINFONT30","font001",label))return -1;
    }
    if(description && selected>=0) {
        size_t index=(size_t)page*12+(size_t)selected;
        if(index<count) {
            const char *txt=dw4_statuscontent_item_string(db,items+index,"TXT");
            if(!txt || set(io,u,"STWINFONT29","font000",txt) || visible(io,u,"STWINFONT29","font000",1))return -1;
        }
    }
    return 0;
}
/* KAITORI (shop buy-back price) for a DEVICEFOLDER item (kinds 0..3) or a DISKFOLDER disk (kind 4, conItem). */
int dw4_statuscontent_kaitori(const dw4_databases *db,const dw4_item_record *i,int32_t *out)
{
    if(!db || !i || !out)return -1;
    if(i->kind==4)return dw4_database_number(dw4_databases_get(db,"conItem"),i->record,"KAITORI",out)<0?-1:0;
    return dw4_playerstats_item_price((void *)db,i,1,out)?-1:0;
}
/* 436060: DeviceSell rows (equipped marker + NAME, KAITORI, item colour, row enable flags as
 * DEFAULTCOLOR/CANCELCOLOR on the price), page labels in STWINFONT30 and the selected row's description. */
int dw4_statuscontent_sell_device(const dw4_databases *db,const dw4_item_record *items,size_t count,
    const uint8_t enabled[12],int page,int pages,int selected,int rows,int description,dw4_statusview_io io,void *u)
{
    if(!db || !io || !enabled || (count && !items) || count>36 || page<0 || pages<1 || pages>3 || page>=pages)return -1;
    if(rows) {
        for(unsigned i=0;i<12;i++) {
            char font[16];snprintf(font,sizeof font,"font%03u",i);
            size_t index=(size_t)page*12+i;
            if(index<count) {
                const char *name=dw4_statuscontent_item_string(db,items+index,"NAME");int32_t price;
                if(!name || dw4_statuscontent_kaitori(db,items+index,&price))return -1;
                char label[8192],value[16];
                int n=snprintf(label,sizeof label,"%s%s",items[index].equipped?"\x81\xba":"\x8a\x71",name);
                if(n<0 || (size_t)n>=sizeof label)return -1;
                snprintf(value,sizeof value,"%d",price);
                float rgb[3];dw4_statuscontent_item_color(items+index,rgb);
                if(set(io,u,"STWINFONT14",font,label) || set(io,u,"STWINFONT17",font,value) || color(io,u,"STWINFONT14",font,rgb) ||
                   emit(io,u,DW4_VIEW_COLOR,"STWINFONT17",font,enabled[i]?"DEFAULTCOLOR":"CANCELCOLOR",NULL,0) ||
                   visible(io,u,"STWINFONT14",font,1) || visible(io,u,"STWINFONT17",font,1))return -1;
            }else if(visible(io,u,"STWINFONT14",font,0) || visible(io,u,"STWINFONT17",font,0))return -1;
        }
        char label[2]={(char)('1'+page),0};
        if(set(io,u,"STWINFONT30","font000",label))return -1;
        label[0]=(char)('0'+pages);
        if(set(io,u,"STWINFONT30","font001",label))return -1;
    }
    if(description && selected>=0) {
        size_t index=(size_t)page*12+(size_t)selected;
        if(index<count) {
            const dw4_item_record *i=items+index;char txt[8192];
            int pocket=(i->kind==0 && i->record!=276) || (i->kind==1 && i->record!=31);
            if(description_text(db,i,pocket,txt,sizeof txt) || set(io,u,"STWINFONT29","font000",txt))return -1;
        }
        return visible(io,u,"STWINFONT29","font000",index<count);
    }
    return 0;
}
/* 4393e0: ShopCtrlSales rows for services 6..9 (NAME, item colour and the HANBAI price or "----" for a
 * sold-out chip in STWINFONT14/17 fonts 0..11, a null slot hidden), the page labels in STWINFONT30 and, for
 * the highlighted slot, the TXT (plus the pocket count of weapons and blue armor) in STWINFONT29. Slots are
 * the 36-entry stock list; a slot of kind -1 is null. */
int dw4_statuscontent_sales(const dw4_databases *db,const dw4_item_record *items,size_t count,int page,int pages,
    int selected,int rows,int description,dw4_statusview_io io,void *u)
{
    /* An empty junk stock has 0 pages and one disabled row; the page label then reads 0. */
    if(!db || !io || (count && !items) || count>36 || page<0 || pages<0 || pages>3 || (pages && page>=pages))return -1;
    if(rows) {
        for(unsigned i=0;i<12;i++) {
            char font[16];snprintf(font,sizeof font,"font%03u",i);
            size_t index=(size_t)page*12+i;
            const dw4_item_record *it=index<count && items[index].kind>=0?items+index:NULL;
            if(it) {
                const char *name=dw4_statuscontent_item_string(db,it,"NAME");int32_t price;char value[16];
                if(!name)return -1;
                if(it->kind==3 && it->record==0xB9)snprintf(value,sizeof value,"----");
                else {
                    if(dw4_playerstats_item_price((void *)db,it,0,&price))return -1;
                    snprintf(value,sizeof value,"%d",price);
                }
                float rgb[3];dw4_statuscontent_item_color(it,rgb);
                if(set(io,u,"STWINFONT14",font,name) || color(io,u,"STWINFONT14",font,rgb) || set(io,u,"STWINFONT17",font,value))return -1;
            }
            if(visible(io,u,"STWINFONT14",font,it!=NULL) || visible(io,u,"STWINFONT17",font,it!=NULL))return -1;
        }
        char label[2]={(char)('1'+page),0};
        if(set(io,u,"STWINFONT30","font000",label))return -1;
        label[0]=(char)('0'+pages);
        if(set(io,u,"STWINFONT30","font001",label))return -1;
    }
    if(description) {
        size_t index=selected>=0?(size_t)page*12+(size_t)selected:count;
        const dw4_item_record *it=index<count && items[index].kind>=0?items+index:NULL;
        if(it) {
            char txt[8192];
            if(description_text(db,it,it->kind==0 || it->kind==1,txt,sizeof txt) || set(io,u,"STWINFONT29","font000",txt))return -1;
        }
        return visible(io,u,"STWINFONT29","font000",it!=NULL);
    }
    return 0;
}
/* 437ae0: DiskSell rows (NAME, held count digit, KAITORI) for all twelve DISKFOLDER entries and the
 * selected disk's TXT; *unit receives the selected disk's KAITORI (retail stores it at +64). */
int dw4_statuscontent_sell_disk(const dw4_databases *db,const dw4_item_record *disks,size_t count,
    int selected,int rows,int description,int32_t *unit,dw4_statusview_io io,void *u)
{
    if(!db || !io || !disks || count!=12)return -1;
    if(rows)for(unsigned i=0;i<12;i++) {
        char font[16],digit[2]={(char)('0'+disks[i].revision),0},value[16];int32_t price;
        snprintf(font,sizeof font,"font%03u",i);
        const char *name=dw4_statuscontent_item_string(db,disks+i,"NAME");
        if(!name || dw4_statuscontent_kaitori(db,disks+i,&price) || disks[i].revision<0 || disks[i].revision>9)return -1;
        snprintf(value,sizeof value,"%d",price);
        if(set(io,u,"STWINFONT14",font,name) || set(io,u,"STWINFONT15",font,digit) || set(io,u,"STWINFONT17",font,value) ||
           visible(io,u,"STWINFONT14",font,1) || visible(io,u,"STWINFONT15",font,1) || visible(io,u,"STWINFONT17",font,1))return -1;
    }
    if(description) {
        if(selected<0 || (size_t)selected>=count)return visible(io,u,"STWINFONT29","font000",0);
        const char *txt=dw4_statuscontent_item_string(db,disks+selected,"TXT");
        if(!txt || !unit || dw4_statuscontent_kaitori(db,disks+selected,unit) ||
           set(io,u,"STWINFONT29","font000",txt) || visible(io,u,"STWINFONT29","font000",1))return -1;
    }
    return 0;
}
int dw4_statuscontent_skill_list(dw4_playerrecords *p,const dw4_databases *db,int32_t player,dw4_status_skillrow out[16],size_t *count)
{
    if(!out || !count)return -1;
    dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",player);size_t n;
    const int32_t *used=dw4_property_array(f,"BASE_ISUSE",&n);if(!used || n!=16)return -1;
    const int32_t *level=dw4_property_array(f,"BASE_LEVEL",&n);if(!level || n!=16)return -1;
    dw4_status_skillrow staged[16];size_t total=0;
    for(int i=0;i<16;i++)if((uint8_t)used[i]){
        const char *name=dw4_databases_shinka_name((void *)db,i);if(!name)return -1;
        if(i==3){memmove(staged+1,staged,total*sizeof *staged);staged[0]=(dw4_status_skillrow){i,level[i],name};}
        else staged[total]=(dw4_status_skillrow){i,level[i],name};
        total++;
    }
    memcpy(out,staged,total*sizeof *staged);*count=total;return 0;
}
int dw4_statuscontent_skill(dw4_playerrecords *p,const dw4_databases *db,int32_t player,int mode,int page,int pages,int selected,
    int rows,int description,dw4_statusview_io io,void *u)
{
    if(!db || !io || mode<0 || mode>2 || page<0 || page>1 || pages<1 || pages>2 || page>=pages || selected< -1)return -1;
    if(selected==-1)return 0;
    if(rows && mode!=0)return -1;
    dw4_status_skillrow list[16];size_t n=0;const char *txt=NULL;
    if(mode==0){if(dw4_statuscontent_skill_list(p,db,player,list,&n) || selected>=8)return -1;
        size_t i=(size_t)page*8+(size_t)selected;
        if(description && i<n){txt=dw4_database_string(dw4_databases_get(db,"shinka"),list[i].species,"EXPLANATION");if(!txt)return -1;}
    }else if(mode==1){if(selected>=9)return -1;}
    else if(description){dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",player);
        const dw4_item_record *items=dw4_property_items(f,"WAZALIST",&n);
        if(dw4_property_item_count(f,"WAZALIST",&n) || (size_t)selected>=n || !(txt=dw4_statuscontent_item_string(db,items+selected,"TXT")))return -1;}
    if(rows){for(unsigned i=0;i<8;i++){
        char font[16];snprintf(font,sizeof font,"font%03u",i);size_t index=(size_t)page*8+i;
        if(index<n){char value[32];snprintf(value,sizeof value,"%d",list[index].level);
            if(set(io,u,"STWINFONT14",font,list[index].name) || set(io,u,"STWINFONT42",font,"Lv") || set(io,u,"STWINFONT18",font,value))return -1;}
        const char *groups[]={"STWINFONT14","STWINFONT42","STWINFONT18"};
        for(unsigned g=0;g<3;g++)if(visible(io,u,groups[g],font,index<n))return -1;
    }
    if(pages>1){char value[2]={(char)('1'+page),0};if(set(io,u,"STWINFONT24","font000",value))return -1;
        value[0]=(char)('0'+pages);if(set(io,u,"STWINFONT24","font001",value))return -1;}}
    if(description){if(mode==1)return script(io,u,selected+111);if(txt)return set(io,u,"STWINFONT29","font000",txt);}
    return 0;
}
int dw4_statuscontent_skill_setup(dw4_playerrecords *p,const dw4_databases *db,int32_t player,int mode,int pages,int *out,dw4_statusview_io io,void *u)
{
    if(!io || !out || mode<0 || mode>2 || pages<1 || pages>2)return -1;
    dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",player);size_t n=0;int count;
    const int32_t *skills=NULL;const dw4_item_record *waza=NULL;const char *names[6]={0};int32_t limit=0;
    if(mode==0){dw4_status_skillrow list[16];if(dw4_statuscontent_skill_list(p,db,player,list,&n))return -1;count=pages>1?8:n?(int)n:2;}
    else if(mode==1){int32_t level;if(dw4_property_number(f,"LEVEL",&level))return -1;
        skills=dw4_property_array(f,"SKILL",&n);if(!skills || n!=9)return -1;
        uint32_t value=level<37?(uint32_t)level*30:level<108?(uint32_t)level*20+360:level<228?(uint32_t)level*10+1430:(uint32_t)level*8+1884;
        memcpy(&limit,&value,4);count=9;
    }else {waza=dw4_property_items(f,"WAZALIST",&n);if(dw4_property_item_count(f,"WAZALIST",&n) || n>6)return -1;
        for(size_t i=0;i<n;i++)if(!(names[i]=dw4_statuscontent_item_string(db,waza+i,"NAME")))return -1;
        count=n?(int)n:1;}
    const char *seq=mode==2?"SQ_WAZAOPEN":mode==1 || pages<2?"SQ_BWINOFFOPEN":"SQ_BWINONOPEN";
    if(emit(io,u,DW4_VIEW_MODEL,NULL,"i_stfolder",seq,"SQ_CLOSE",0) ||
       emit(io,u,DW4_VIEW_TRACK_TEXT,"STWINFONT13","font000",NULL,NULL,0) || script(io,u,95+mode))return -1;
    if(mode==0){
        if(pages>1)for(unsigned i=0;i<2;i++){char font[16];snprintf(font,sizeof font,"font%03u",i);if(emit(io,u,DW4_VIEW_TEXT,"STWINFONT24",font,"CENTER"," ",0))return -1;}
        for(int i=0;i<count;i++){char font[16];snprintf(font,sizeof font,"font%03d",i);
            if(emit(io,u,DW4_VIEW_TEXT,"STWINFONT14",font,"LEFT"," ",0) || emit(io,u,DW4_VIEW_TEXT,"STWINFONT42",font,"LEFT"," ",0) || emit(io,u,DW4_VIEW_TEXT,"STWINFONT18",font,"RIGHT"," ",0))return -1;}
        if(dw4_statuscontent_skill(p,db,player,0,0,pages,0,1,0,io,u))return -1;
    }else if(mode==1){
        for(unsigned i=0;i<9;i++){char font[16],value[32];snprintf(font,sizeof font,"font%03u",i);snprintf(value,sizeof value,"%d",skills[i]);
            if(emit(io,u,DW4_VIEW_TRACK_TEXT,"STWINFONT14",font,NULL,NULL,0) || emit(io,u,DW4_VIEW_TEXT,"STWINFONT18",font,"RIGHT",value,0))return -1;
            float rgb[]={.9f,.4f,.2f};if(skills[i]>=limit){if(color(io,u,"STWINFONT14",font,rgb))return -1;}
            else if(emit(io,u,DW4_VIEW_COLOR,"STWINFONT14",font,"DEFAULTCOLOR",NULL,0))return -1;}
        if(script(io,u,101))return -1;
    }else for(size_t i=0;i<n;i++){char font[16];snprintf(font,sizeof font,"font%03u",(unsigned)i);if(emit(io,u,DW4_VIEW_TEXT,"STWINFONT14",font,"LEFT",names[i],0))return -1;}
    if(emit(io,u,DW4_VIEW_TEXT,"STWINFONT29","font000","LEFT"," ",0))return -1;
    *out=count;return 0;
}
int dw4_statuscontent_skill_clear_colors(dw4_statusview_io io,void *u)
{
    if(!io)return -1;
    for(unsigned i=0;i<9;i++){char font[16];snprintf(font,sizeof font,"font%03u",i);
        if(emit(io,u,DW4_VIEW_COLOR,"STWINFONT14",font,"DEFAULTCOLOR",NULL,0))return -1;}
    return 0;
}
int dw4_statuscontent_labo(dw4_playerrecords *p,const dw4_databases *db,int32_t player,int page,int pages,int selected,
    int rows,int detail,dw4_statusview_io io,void *u)
{
    static const char *const values[16]={"font030","font031","font040","font041","font042","font043","font044",
        "font050","font051","font052","font053","font054","font055","font056","font057","font058"};
    if(!db || !io || page<0 || pages<1 || pages>2 || page>=pages || selected<-1 || selected>=8)return -1;
    dw4_status_skillrow list[16];size_t n=0;
    if(dw4_statuscontent_skill_list(p,db,player,list,&n))return -1;
    if(rows) {
        static const char *const groups[3]={"STWINFONT20","STWINFONT43","STWINFONT21"};
        for(unsigned i=0;i<8;i++) {
            char font[16];snprintf(font,sizeof font,"font%03u",i);size_t index=(size_t)page*8+i;
            if(index<n){char level[16];snprintf(level,sizeof level,"%d",list[index].level);
                if(set(io,u,groups[0],font,list[index].name) || set(io,u,groups[1],font,"Lv") || set(io,u,groups[2],font,level))return -1;}
            for(unsigned g=0;g<3;g++)if(visible(io,u,groups[g],font,index<n))return -1;
        }
        if(pages>=2){char a[2]={(char)('1'+page),0},b[2]={(char)('0'+pages),0};
            if(set(io,u,"STWINFONT31","font000",a) || set(io,u,"STWINFONT31","font001",b))return -1;}
    }
    if(detail && selected>=0) {
        size_t index=(size_t)page*8+(size_t)selected;
        if(index>=n)return 0;
        int32_t form[16];dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",player);
        if(!f || dw4_playerstats_form(db,f,list[index].species,form))return -1;
        for(unsigned i=0;i<16;i++){char text[16];snprintf(text,sizeof text,"%d",form[i]);if(set(io,u,"STWINFONT22",values[i],text))return -1;}
        const char *txt=dw4_database_string(dw4_databases_get(db,"shinka"),list[index].species,"EXPLANATION");
        if(!txt || set(io,u,"STWINFONT29","font000",txt) || visible(io,u,"STWINFONT29","font000",1))return -1;
    }
    return 0;
}
