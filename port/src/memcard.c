#include "dw4/memcard.h"
#include "dw4/playerinit.h"
#include "dw4/playerstats.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

struct dw4_memcard {char directory[400];};
static int path(const dw4_memcard *c,char *out,size_t cap)
{int n=snprintf(out,cap,"%s/%s",c->directory,DW4_MEMCARD_FILE);return n<0 || (size_t)n>=cap?-1:0;}
static void fail(char *error,size_t cap,const char *text){if(error && cap)snprintf(error,cap,"%s",text);}
dw4_memcard *dw4_memcard_open(const char *directory)
{
    if(!directory || strlen(directory)>=sizeof((dw4_memcard *)0)->directory)return NULL;
    dw4_memcard *c=calloc(1,sizeof *c);if(!c)return NULL;
    snprintf(c->directory,sizeof c->directory,"%s",directory);return c;
}
void dw4_memcard_close(dw4_memcard *c){free(c);}
int dw4_memcard_ready(const dw4_memcard *c)
{struct stat s;return c && !stat(c->directory,&s) && S_ISDIR(s.st_mode) && !access(c->directory,W_OK|X_OK);}
/* Returns 1 with the verified image, 0 when there is no file, -1 when it is unreadable or damaged. */
static int read_image(const dw4_memcard *c,uint8_t image[DW4_SAVE_IMAGE_SIZE],char *error,size_t cap)
{
    char file[512];struct stat s;
    if(!dw4_memcard_ready(c)){fail(error,cap,"memory card directory is not available");return -1;}
    if(path(c,file,sizeof file)){fail(error,cap,"memory card path is too long");return -1;}
    if(stat(file,&s))return 0;
    const char *why=NULL;
    if(dw4_savefile_read(file,image) || dw4_saveimage_verify(image,DW4_SAVE_IMAGE_SIZE,&why)){
        if(error && cap)snprintf(error,cap,"memory card save file is damaged%s%s",why?": ":"",why?why:"");
        return -1;
    }
    return 1;
}
int dw4_memcard_scan(const dw4_memcard *c,int present[DW4_SAVE_SLOTS],int *used,char *error,size_t cap)
{
    uint8_t image[DW4_SAVE_IMAGE_SIZE];int r=read_image(c,image,error,cap);
    if(r<0)return -1;
    int count=0;
    for(int s=0;s<DW4_SAVE_SLOTS;s++){int p=r==1 && dw4_saveimage_slot_used(image,s);present[s]=p;count+=p;}
    if(used)*used=count;
    return 0;
}
/* Keep the previous valid file as <file>.bak (a copy, so the original stays in place until the atomic rename). */
static int backup(const char *file)
{
    char bak[560];FILE *in=fopen(file,"rb");if(!in)return 0;
    if(snprintf(bak,sizeof bak,"%s.bak",file)>=(int)sizeof bak){fclose(in);return -1;}
    FILE *out=fopen(bak,"wb");if(!out){fclose(in);return -1;}
    char buf[8192];size_t n;int bad=0;
    while((n=fread(buf,1,sizeof buf,in))>0)if(fwrite(buf,1,n,out)!=n){bad=1;break;}
    bad|=ferror(in);fclose(in);if(fclose(out))bad=1;
    if(bad)remove(bak);
    return bad?-1:0;
}
int dw4_memcard_save(dw4_memcard *c,dw4_playerrecords *players,const int32_t player_for_slot[DW4_SAVE_SLOTS],char *error,size_t cap)
{
    uint8_t image[DW4_SAVE_IMAGE_SIZE];char file[512];int r=read_image(c,image,error,cap),stored=0;
    if(r<0)return -1;
    if(!r)dw4_saveimage_init(image);
    for(int s=0;s<DW4_SAVE_SLOTS;s++){
        if(player_for_slot[s]<0)continue;
        if(dw4_saveimage_store(players,player_for_slot[s],s,image)){fail(error,cap,"a character could not be stored in the save image");return -1;}
        stored++;
    }
    if(!stored){fail(error,cap,"no character was selected for saving");return -1;}
    if(path(c,file,sizeof file)){fail(error,cap,"the save file could not be written");return -1;}
    if(r==1 && backup(file)){fail(error,cap,"the previous save file could not be backed up");return -1;}
    if(dw4_savefile_write(file,image)){fail(error,cap,"the save file could not be written");return -1;}
    return 0;
}
int dw4_memcard_load(const dw4_memcard *c,dw4_playerrecords *players,int32_t player,int32_t slot,char *error,size_t cap)
{
    uint8_t image[DW4_SAVE_IMAGE_SIZE];int r=read_image(c,image,error,cap);
    if(r<0)return -1;
    if(!r){fail(error,cap,"the memory card has no save file");return -1;}
    if(slot<0 || slot>=DW4_SAVE_SLOTS || !dw4_saveimage_slot_used(image,slot)){fail(error,cap,"the slot holds no character");return -1;}
    if(dw4_saveimage_load(players,player,slot,image,sizeof image)){fail(error,cap,"the slot could not be loaded");return -1;}
    return 0;
}
size_t dw4_memcard_needed(const dw4_memcard *c)
{
    char file[512];struct stat s;
    return path(c,file,sizeof file)==0 && !stat(file,&s)?0:DW4_SAVE_IMAGE_SIZE;
}
int dw4_memcard_make(dw4_memcard *c,char *error,size_t cap)
{
    uint8_t image[DW4_SAVE_IMAGE_SIZE];char file[512];int r=read_image(c,image,error,cap);
    if(r<0)return -1;
    if(r==1)return 0;
    dw4_saveimage_init(image);
    if(path(c,file,sizeof file) || dw4_savefile_write(file,image)){fail(error,cap,"the save file could not be created");return -1;}
    return 0;
}
int dw4_memcard_summaries(const dw4_memcard *c,dw4_memcard_summary out[DW4_SAVE_SLOTS],char *error,size_t cap)
{
    uint8_t image[DW4_SAVE_IMAGE_SIZE];int r=read_image(c,image,error,cap);
    if(r<0)return -1;
    memset(out,0,sizeof *out*DW4_SAVE_SLOTS);
    if(r!=1)return 0;
    for(int s=0;s<DW4_SAVE_SLOTS;s++){
        const uint8_t *b=image+8+(size_t)s*DW4_SAVE_SLOT_STRIDE;dw4_memcard_summary *o=&out[s];
        int32_t v;
        o->used=b[0];if(!o->used)continue;
        memcpy(&v,b+4,4);o->unique=v;memcpy(o->model,b+8,32);o->model[32]=0;
        for(int i=0;i<8;i++){uint16_t u;memcpy(&u,b+0x2A+2*i,2);o->name[i]=u;if(!u)break;}
        memcpy(&v,b+0x48,4);o->level=v;memcpy(&v,b+0x4C,4);o->hp=v;memcpy(&v,b+0x50,4);o->mhp=v;
        memcpy(&v,b+0x54,4);o->mp=v;memcpy(&v,b+0x58,4);o->mmp=v;
    }
    return 0;
}
static int make_dir(const char *p)
{
    if(!mkdir(p,0700)||errno==EEXIST)return 0;
    return -1;
}
int dw4_memcard_default_directory(char *out,size_t cap,int create)
{
    const char *xdg=getenv("XDG_DATA_HOME"),*home=getenv("HOME");char base[420];
    if(xdg&&*xdg)snprintf(base,sizeof base,"%s",xdg);
    else if(home&&*home)snprintf(base,sizeof base,"%s/.local/share",home);
    else return -1;
    int n=snprintf(out,cap,"%s/dw4/saves",base);if(n<0||(size_t)n>=cap)return -1;
    if(create){
        char step[460];
        snprintf(step,sizeof step,"%s",base);if(make_dir(step))return -1;
        snprintf(step,sizeof step,"%s/dw4",base);if(make_dir(step))return -1;
        if(make_dir(out))return -1;
    }
    return 0;
}
static const char *species_model(void *u,int32_t row){return dw4_database_string(dw4_databases_get(u,"shinka"),row,"MODEL_NAME");}
int dw4_memcard_restore(const dw4_memcard *c,dw4_playerrecords *players,const dw4_databases *db,int32_t player,int32_t slot,
    char *error,size_t cap)
{
    dw4_memcard_summary sum[DW4_SAVE_SLOTS];
    if(!c || !players || !db || slot<0 || slot>=DW4_SAVE_SLOTS){fail(error,cap,"invalid restore request");return -1;}
    if(dw4_memcard_summaries(c,sum,error,cap))return -1;
    if(!sum[slot].used){fail(error,cap,"the slot holds no character");return -1;}
    /* A fresh record supplies the keys a save does not store; the stored keys then replace it, BASE2CURRENT rebuilds the species'
     * level, EXP and skills and RECALCPLAYER the stats and the weapon model, as retail does after 3ef5d0. */
    if(dw4_playerrecords_create(players,db,player,"p_dorumon","Load",error,cap))return -1;   /* any starter: the stored keys and BASE2CURRENT replace the species */
    if(dw4_memcard_load(c,players,player,slot,error,cap))return -1;
    if(dw4_playertransactions_base_to_current(players,player,species_model,(void *)db,dw4_playerstats_recalculate,(void *)db)){
        fail(error,cap,"the loaded character could not be rebuilt from its saved species");return -1;
    }
    return 0;
}
