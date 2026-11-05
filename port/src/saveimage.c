#include "dw4/saveimage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/* Deliver-struct offsets (struct base = file +8), from serializer 3ee6d0 / loader 3ef5d0. */
enum {S=8,O_ISUSE=0x00,O_UNIQUE=0x04,O_MODEL=0x08,O_NAMEMARK=0x28,O_NAME=0x2A,O_LEVEL=0x48,O_HP=0x4C,O_MHP=0x50,O_MP=0x54,
    O_MMP=0x58,O_XDATA=0x5C,O_BIT=0x60,O_DEVICE=0x64,O_DISK=0xF4,O_CARD=0x124,O_BANK=0x158,O_BANKBIT=0x2D8,O_REF=0x2DC,
    O_FLAG=0x318,O_FLAGFOLDER=0x718,O_COUNTER=0x724,O_BASEUSE=0x764,O_BASELEVEL=0x774,O_BASEEXP=0x7B4,O_SKILL=0x7F4,O_UPCNT=0xA34};
/* DEVICEFOLDER/DISKFOLDER/BANKDEVICE capacities and the five equipment lists (POWERSOCKET, POWERPOCKET, MAINSLOT,
 * MAINPOCKET, SUBSLOT) with their reference offsets and lengths. */
enum {NDEVICE=36,NDISK=12,NBANK=96,NCARD=50,NFLAG=1024,NFOLDER=12};
static const char *const equipment[]={"POWERSOCKET","POWERPOCKET","MAINSLOT","MAINPOCKET","SUBSLOT"};
static const char *const refkeys[]={"POWERSOCKETREF","POWERPOCKETREF","MAINSLOTREF","MAINPOCKETREF","SUBSLOTREF"};
static const unsigned refoff[]={O_REF,0x2E8,0x2FC,0x300,0x314},reflen[]={3,5,1,5,1};
static uint32_t rd(const uint8_t *b,unsigned o){uint32_t v;memcpy(&v,b+o,4);return v;}
static void wr(uint8_t *b,unsigned o,uint32_t v){memcpy(b+o,&v,4);}
int dw4_saveimage_item_encode(const dw4_item_record *it,uint32_t *out)
{
    if(!it || !out)return -1;
    if(it->kind<0){*out=0xFFFFFFFFu;return 0;}
    if(it->kind>4 || it->record<0 || it->record>0x3FF || it->revision<0 || it->pocket<0)return -1;
    uint32_t id=(uint32_t)it->record|((uint8_t)it->equipped?0x400u:0)|(uint32_t)it->kind<<12;
    switch(it->kind){
    case 0:case 1:if(it->pocket>0xF || it->revision>0x7FF)return -1;id|=(uint32_t)it->pocket<<16|(uint32_t)it->revision<<20;break;
    case 2:if(it->pocket || it->revision>0x7FF)return -1;id|=(uint32_t)it->revision<<20;break;
    case 3:if(it->pocket || it->revision)return -1;break;
    default:if(it->pocket || it->revision>0xF)return -1;id|=(uint32_t)it->revision<<16;
    }
    *out=id;return 0;
}
int dw4_saveimage_item_decode(uint32_t id,dw4_item_record *it)
{
    if(!it)return -1;
    uint32_t kind=id>>12&0xF;
    if(kind>4){*it=(dw4_item_record){.kind=-1};return 0;}
    *it=(dw4_item_record){.kind=(int32_t)kind,.record=(int32_t)(id&0x3FF),.equipped=!!(id&0x400)};
    if(kind<2){it->pocket=(int32_t)(id>>16&0xF);it->revision=(int32_t)(id>>20&0x7FF);}
    else if(kind==2)it->revision=(int32_t)(id>>20&0x7FF);
    else if(kind==4)it->revision=(int32_t)(id>>16&0xF);
    return 0;
}
static uint32_t checksum(const uint8_t *block)
{uint32_t s=0;for(unsigned o=4;o<DW4_SAVE_BLOCK_SIZE;o+=4)s+=rd(block,o);return s;}
int dw4_saveimage_verify(const uint8_t *image,size_t size,const char **why)
{
    const char *dummy;if(!why)why=&dummy;
    if(!image || size!=DW4_SAVE_IMAGE_SIZE){*why="a save file is exactly 81920 bytes";return -1;}
    for(unsigned b=0;b<2;b++){
        const uint8_t *p=image+b*DW4_SAVE_BLOCK_SIZE;
        if(rd(p,4)!=DW4_SAVE_VERSION){*why="unsupported save version";return -1;}
        if(rd(p,0)!=checksum(p)){*why="save checksum mismatch";return -1;}
    }
    if(memcmp(image,image+DW4_SAVE_BLOCK_SIZE,DW4_SAVE_BLOCK_SIZE)){*why="the second block does not mirror the first";return -1;}
    return 0;
}
/* ---- records -> image ---- */
static int number(dw4_property_folder *f,const char *key,uint8_t *b,unsigned o)
{int32_t v;if(dw4_property_number(f,key,&v))return -1;wr(b,S+o,(uint32_t)v);return 0;}
/* A folder of items padded with -1 up to cap; more than cap are truncated as retail's ObjectList_ResizeRetained does
 * for the device folder (0x24 and 0xC), so callers needing losslessness check counts themselves. */
static int items(dw4_property_folder *f,const char *key,uint8_t *b,unsigned o,unsigned cap)
{
    size_t n;const dw4_item_record *it=dw4_property_items(f,key,&n);
    if(dw4_property_item_count(f,key,&n))return -1;
    it=dw4_property_items(f,key,&n);
    if(n>cap || (n && !it))return -1;
    for(unsigned i=0;i<cap;i++){
        uint32_t id=0xFFFFFFFFu;
        if(i<n && dw4_saveimage_item_encode(it+i,&id))return -1;
        wr(b,S+o+4*i,id);
    }
    return 0;
}
static int ints(dw4_property_folder *f,const char *key,uint8_t *b,unsigned o,size_t cap,int bytes)
{
    size_t n;const int32_t *v=dw4_property_array(f,key,&n);
    if(!v || n>cap)return -1;
    for(size_t i=0;i<n;i++){
        if(bytes){if(v[i]<0 || v[i]>255)return -1;b[S+o+i]=(uint8_t)v[i];}
        else wr(b,S+o+4*(unsigned)i,(uint32_t)v[i]);
    }
    return 0;
}
static int raw(dw4_property_folder *f,const char *key,uint8_t *b,unsigned o,size_t cap)
{size_t n;const uint8_t *v=dw4_property_bytes(f,key,&n);if(!v || n>cap)return -1;memcpy(b+S+o,v,n);return 0;}
void dw4_saveimage_init(uint8_t image[DW4_SAVE_IMAGE_SIZE])
{
    memset(image,0,DW4_SAVE_IMAGE_SIZE);
    for(unsigned k=0;k<2;k++){uint8_t *p=image+k*DW4_SAVE_BLOCK_SIZE;wr(p,4,DW4_SAVE_VERSION);wr(p,0,checksum(p));}
}
int dw4_saveimage_slot_used(const uint8_t *image,int32_t slot)
{return image && slot>=0 && slot<DW4_SAVE_SLOTS && image[S+(unsigned)slot*DW4_SAVE_SLOT_STRIDE]!=0;}
int dw4_saveimage_store(dw4_playerrecords *players,int32_t player,int32_t slot,uint8_t image[DW4_SAVE_IMAGE_SIZE])
{
    dw4_property_folder *f=dw4_playerrecords_get(players,"GETPLAYER",player);
    if(!f || !image || slot<0 || slot>=DW4_SAVE_SLOTS || dw4_saveimage_verify(image,DW4_SAVE_IMAGE_SIZE,NULL))return -1;
    uint8_t *blk=malloc(DW4_SAVE_BLOCK_SIZE);if(!blk)return -1;
    memcpy(blk,image,DW4_SAVE_BLOCK_SIZE);
    uint8_t *b=blk+(unsigned)slot*DW4_SAVE_SLOT_STRIDE;memset(b+S,0,DW4_SAVE_SLOT_STRIDE);
    int32_t v;const char *model=dw4_property_string(f,"DIGIMONNAME");
    dw4_unicode_object name;size_t ndev;
    if(dw4_property_number(f,"ISUSE",&v))goto bad;
    b[S+O_ISUSE]=(uint8_t)v;
    if(number(f,"UNIQUE",b,O_UNIQUE) || number(f,"LEVEL",b,O_LEVEL) || number(f,"HP",b,O_HP) || number(f,"MHP",b,O_MHP) ||
       number(f,"MP",b,O_MP) || number(f,"MMP",b,O_MMP) || number(f,"XDATA",b,O_XDATA) || number(f,"BIT",b,O_BIT) ||
       number(f,"BANKBIT",b,O_BANKBIT))goto bad;
    if(model){size_t len=strlen(model);if(len>=O_NAMEMARK-O_MODEL)goto bad;memcpy(b+S+O_MODEL,model,len);}
    if(dw4_property_unicode_object(f,"PLAYERNAME",0,&name))goto bad;
    if(name.present && name.count){
        if(name.count>8 || !name.codes)goto bad;
        uint16_t mark=0xFFFF;memcpy(b+S+O_NAMEMARK,&mark,2);
        for(size_t i=0;i<name.count;i++)memcpy(b+S+O_NAME+2*i,&name.codes[i],2);
    }
    if(items(f,"DEVICEFOLDER",b,O_DEVICE,NDEVICE) || items(f,"DISKFOLDER",b,O_DISK,NDISK) ||
       items(f,"BANKDEVICE",b,O_BANK,NBANK) || raw(f,"CARDLIST",b,O_CARD,NCARD))goto bad;
    if(dw4_property_item_count(f,"DEVICEFOLDER",&ndev))goto bad;
    /* Equipment: the references index DEVICEFOLDER (host identity, retail compares object identity). */
    for(unsigned k=0;k<5;k++){
        size_t n;const int32_t *r=dw4_property_array(f,refkeys[k],&n);
        if(!r || n!=reflen[k])goto bad;
        for(unsigned i=0;i<n;i++){
            if(r[i]<-1 || (r[i]>=0 && (size_t)r[i]>=ndev))goto bad;
            wr(b,S+refoff[k]+4*i,(uint32_t)r[i]);
        }
    }
    if(raw(f,"BASE_FLAG",b,O_FLAG,NFLAG) || raw(f,"BASE_FLAGFOLDER",b,O_FLAGFOLDER,NFOLDER) ||
       ints(f,"BASE_COUNTER",b,O_COUNTER,16,0) || ints(f,"BASE_ISUSE",b,O_BASEUSE,16,1) ||
       ints(f,"BASE_LEVEL",b,O_BASELEVEL,16,0) || ints(f,"BASE_EXP",b,O_BASEEXP,16,0) ||
       ints(f,"BASE_SKILL",b,O_SKILL,144,0) || ints(f,"BASE_UPCNT",b,O_UPCNT,176,0))goto bad;
    wr(blk,0,checksum(blk));
    memcpy(image,blk,DW4_SAVE_BLOCK_SIZE);memcpy(image+DW4_SAVE_BLOCK_SIZE,blk,DW4_SAVE_BLOCK_SIZE);
    free(blk);return 0;
bad:free(blk);return -1;
}
/* ---- image -> records ---- */
static int put_items(dw4_property_folder *s,const char *key,const uint8_t *b,unsigned o,unsigned cap,dw4_item_record *keep)
{
    dw4_item_record list[96];size_t n=0;
    for(unsigned i=0;i<cap;i++){
        uint32_t id=rd(b,S+o+4*i);if(id==0xFFFFFFFFu)continue;
        dw4_item_record it;
        if(dw4_saveimage_item_decode(id,&it) || it.kind<0)return -1; /* retail appends NULL for an unknown kind; refuse */
        list[n++]=it;
    }
    if(keep)memcpy(keep,list,n*sizeof *list);
    return dw4_property_set_items(s,key,list,n)?-1:(int)n;
}
static int put_ints(dw4_property_folder *s,const char *key,const uint8_t *b,unsigned o,size_t n,int bytes)
{
    int32_t v[176];
    for(size_t i=0;i<n;i++)v[i]=bytes?b[S+o+i]:(int32_t)rd(b,S+o+4*(unsigned)i);
    return dw4_property_set_array(s,key,v,n);
}
int dw4_saveimage_load(dw4_playerrecords *players,int32_t player,int32_t slot,const uint8_t *image,size_t size)
{
    dw4_property_folder *f=dw4_playerrecords_get(players,"GETPLAYER",player);
    if(!f || slot<0 || slot>=DW4_SAVE_SLOTS || dw4_saveimage_verify(image,size,NULL))return -1;
    const uint8_t *b=image+(unsigned)slot*DW4_SAVE_SLOT_STRIDE;
    uint16_t mark;memcpy(&mark,b+S+O_NAMEMARK,2);
    /* A save without the 0xFFFF marker stores a narrow name for converter 382eb0 (US table 4c8880); not recovered. */
    if(mark!=0xFFFF && mark)return -1;
    dw4_playerrecords *owner=dw4_playerrecords_open();if(!owner)return -1;
    dw4_property_folder *s=dw4_playerrecords_get(owner,"GETPLAYER",0);
    if(dw4_property_copy_values(s,f))goto bad;
    char model[O_NAMEMARK-O_MODEL+1]={0};memcpy(model,b+S+O_MODEL,O_NAMEMARK-O_MODEL);
    uint16_t codes[9]={0};unsigned ncode=0;
    if(mark==0xFFFF){for(;ncode<8;ncode++){memcpy(&codes[ncode],b+S+O_NAME+2*ncode,2);if(!codes[ncode])break;}}
    /* 3ef5d0 allocates the name object with eight codes (FUN_003843c0 size 8) and zero-pads the converted text. */
    dw4_unicode_object name={codes,8,1};
    if(dw4_property_set_number(s,"ISUSE",b[S+O_ISUSE]) || dw4_property_set_number(s,"UNIQUE",(int32_t)rd(b,S+O_UNIQUE)) ||
       dw4_property_set_number(s,"LEVEL",(int32_t)rd(b,S+O_LEVEL)) || dw4_property_set_number(s,"HP",(int32_t)rd(b,S+O_HP)) ||
       dw4_property_set_number(s,"MHP",(int32_t)rd(b,S+O_MHP)) || dw4_property_set_number(s,"MP",(int32_t)rd(b,S+O_MP)) ||
       dw4_property_set_number(s,"MMP",(int32_t)rd(b,S+O_MMP)) || dw4_property_set_number(s,"XDATA",(int32_t)rd(b,S+O_XDATA)) ||
       dw4_property_set_number(s,"BIT",(int32_t)rd(b,S+O_BIT)) || dw4_property_set_number(s,"BANKBIT",(int32_t)rd(b,S+O_BANKBIT)) ||
       dw4_property_set_string(s,"DIGIMONNAME",model) || dw4_property_set_unicode_objects(s,"PLAYERNAME",&name,1))goto bad;
    dw4_item_record device[NDEVICE];
    int ndev=put_items(s,"DEVICEFOLDER",b,O_DEVICE,NDEVICE,device);
    if(ndev<0 || put_items(s,"DISKFOLDER",b,O_DISK,NDISK,NULL)<0 || put_items(s,"BANKDEVICE",b,O_BANK,NBANK,NULL)<0 ||
       dw4_property_set_bytes(s,"CARDLIST",b+S+O_CARD,NCARD))goto bad;
    for(unsigned k=0;k<5;k++){
        int32_t refs[5];dw4_item_record list[5];
        for(unsigned i=0;i<reflen[k];i++){
            refs[i]=(int32_t)rd(b,S+refoff[k]+4*i);
            if(refs[i]<-1 || refs[i]>=ndev)goto bad;
            list[i]=refs[i]<0?(dw4_item_record){.kind=-1}:device[refs[i]];
        }
        if(dw4_property_set_array(s,refkeys[k],refs,reflen[k]) || dw4_property_set_items(s,equipment[k],list,reflen[k]))goto bad;
    }
    if(dw4_property_set_bytes(s,"BASE_FLAG",b+S+O_FLAG,NFLAG) || dw4_property_set_bytes(s,"BASE_FLAGFOLDER",b+S+O_FLAGFOLDER,NFOLDER) ||
       put_ints(s,"BASE_COUNTER",b,O_COUNTER,16,0) || put_ints(s,"BASE_ISUSE",b,O_BASEUSE,16,1) ||
       put_ints(s,"BASE_LEVEL",b,O_BASELEVEL,16,0) || put_ints(s,"BASE_EXP",b,O_BASEEXP,16,0) ||
       put_ints(s,"BASE_SKILL",b,O_SKILL,144,0) || put_ints(s,"BASE_UPCNT",b,O_UPCNT,176,0))goto bad;
    if(dw4_property_commit_values(f,s))goto bad;
    dw4_playerrecords_close(owner);return 0;
bad:dw4_playerrecords_close(owner);return -1;
}
/* ---- files ---- */
int dw4_savefile_read(const char *path,uint8_t image[DW4_SAVE_IMAGE_SIZE])
{
    FILE *f=fopen(path,"rb");if(!f)return -1;
    uint8_t *tmp=malloc(DW4_SAVE_IMAGE_SIZE+1);if(!tmp){fclose(f);return -1;}
    size_t n=fread(tmp,1,DW4_SAVE_IMAGE_SIZE+1,f);int bad=ferror(f);fclose(f);
    int rc=bad || dw4_saveimage_verify(tmp,n,NULL)?-1:0;
    if(!rc)memcpy(image,tmp,DW4_SAVE_IMAGE_SIZE);
    free(tmp);return rc;
}
int dw4_savefile_write(const char *path,const uint8_t image[DW4_SAVE_IMAGE_SIZE])
{
    if(!path || dw4_saveimage_verify(image,DW4_SAVE_IMAGE_SIZE,NULL))return -1;
    char tmp[1024];if(snprintf(tmp,sizeof tmp,"%s.tmp",path)>=(int)sizeof tmp)return -1;
    FILE *f=fopen(tmp,"wb");if(!f)return -1;
    int ok=fwrite(image,1,DW4_SAVE_IMAGE_SIZE,f)==DW4_SAVE_IMAGE_SIZE && fflush(f)==0;
    ok=fclose(f)==0 && ok;
    uint8_t *back=ok?malloc(DW4_SAVE_IMAGE_SIZE):NULL;
    if(ok)ok=back && !dw4_savefile_read(tmp,back) && !memcmp(back,image,DW4_SAVE_IMAGE_SIZE);
    free(back);
    if(!ok || rename(tmp,path)){remove(tmp);return -1;}
    return 0;
}
