#define _GNU_SOURCE
/* Developer aid: list the classes of an igb (pack, named file, `s <stage>` for a stage's world pack, `p <stage>` to list its scene/support packs, `m <substring>` to list manifest paths, `w <name> <file>` to write a named file's bytes); with a name, #id or class+x, dump matching records. */
#include "dw4/igfile.h"
#include "dw4/igb.h"
#include "dw4/object.h"
#include "dw4/mount.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
int main(int argc,char **argv){
    dw4_mount m;assert(!dw4_mount_open(&m,"../../local/extracted"));
    if(argv[1][0]=='m'){for(uint32_t i=0;i<m.man.nfiles;i++)if(!argv[2][0]||strcasestr(m.man.files[i].path,argv[2]))printf("%s\n",m.man.files[i].path);return 0;}
    if(argv[1][0]=='w'){dw4_igfile q={0};assert(!dw4_igfile_open_named(&q,&m,argv[2]));FILE *o=fopen(argv[3],"wb");assert(o && fwrite(q.data,1,q.len,o)==q.len);fclose(o);return 0;}
    if(argv[1][0]=='p'){for(int sup=0;sup<2;sup++)for(unsigned i=0;i<16;i++){dw4_igfile q={0};if(dw4_igfile_open_stage_pack(&q,&m,argv[2],sup,i))continue;printf("%s row %u: %u bytes\n",sup?"support":"scene",i,q.len);}return 0;}
    uint32_t size;const uint8_t *blob;dw4_igfile gf={0};if(argv[1][0]=='s' || argv[1][0]=='S'){assert(!dw4_igfile_open_stage_pack(&gf,&m,argv[2],argv[1][0]=='S',0));blob=gf.data;size=gf.len;}else if(argv[1][0]=='n'){assert(!dw4_igfile_open_named(&gf,&m,argv[2]));blob=gf.data;size=gf.len;}else{blob=dw4_mount_entry(&m,atoi(argv[1]),atoi(argv[2]),&size,NULL);}assert(blob);
    dw4_igb g={0};assert(!dw4_igb_open(&g,blob,size,0)&&!dw4_igb_refs_open(&g));
    printf("table %u\n",g.table_n);
    struct {char n[64];int c;} cls[256];int nc=0;
    for(uint32_t id=0;id<g.table_n;id++){ if(g.id_kind[id]!=2)continue;
        dw4_igb_record r={0};if(!dw4_igb_decode(&g,g.id_off[id],&r))continue;
        int k;for(k=0;k<nc;k++)if(!strcmp(cls[k].n,r.class_name))break;
        if(k==nc&&nc<256){snprintf(cls[nc].n,64,"%s",r.class_name);cls[nc++].c=0;}
        cls[k].c++;
        if(!strcmp(r.class_name,"beDBManagerInfo")) printf("DB %s id=%u\n",r.name?r.name:"-",id);
        if(argc>4 && !strcmp(r.class_name,argv[3])){printf("%s id=%u name=%s:",r.class_name,id,r.name?r.name:"-");for(unsigned v=0;v<r.nvalues;v++){unsigned o=r.values[v].ordinal;if(r.values[v].vsize==12){float f[3];memcpy(f,g.data+r.values[v].voff,12);printf(" o%u=(%g,%g,%g)",o,f[0],f[1],f[2]);}else{float fl;uint32_t rw=r.values[v].raw;memcpy(&fl,&rw,4);printf(" o%u=%u/%g",o,rw,fl);}}printf("\n");}
        if(argc==4 && ((argv[3][0]=='#' && (uint32_t)atoi(argv[3]+1)==id) || (r.name && !strcmp(r.name,argv[3])))){printf("%s id=%u class=%s\n",r.name,id,r.class_name);for(unsigned v=0;v<r.nvalues;v++)printf("  ord %u type %u raw 0x%x vsize %u\n",r.values[v].ordinal,r.values[v].type,r.values[v].raw,r.values[v].vsize);}
        dw4_igb_record_free(&r);}
    for(int k=0;k<nc;k++)printf("%5d %s\n",cls[k].c,cls[k].n);
    return 0;}
