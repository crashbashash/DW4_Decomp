#include "dw4/fieldhud.h"
#include "dw4/hudmeter.h"
#include "dw4/igb.h"
#include "dw4/igfile.h"
#include "dw4/hudnumber.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define DW4_FIELDHUD_POPUPS 16
struct plate {uint32_t geometry,max,mode,count;float offset;int32_t value;struct {uint32_t vertex,place,kind;} map[48];};
struct dw4_fieldhud {
    struct plate plate[3][4];unsigned have_plate[3];
    struct plate popup[4][DW4_FIELDHUD_POPUPS];unsigned npopup[4];unsigned popup_hits;   /* floating numbers: damage, exp, player damage, bit; one plate per RAM slot */
    dw4_hudmeter meter[3][4];   /* gauge 0 HP, 1 MP per player; gauge 2 slot 0 the boss gauge (bshp10) */
    uint32_t node[3][4];
    uint32_t child[3][4][8];unsigned nchild[3][4];   /* the scene nodes of the gauge (the meter node's _childList) */
    unsigned have[3];   /* bit s: slot s's gauge was found */
};
static int dw4_igb_record_at(const dw4_igb *g,uint32_t id,dw4_igb_record *r)
{return id<g->table_n && g->id_kind[id]==2 && dw4_igb_decode(g,g->id_off[id],r);}
static uint32_t slot_of(const dw4_igb_record *r,unsigned ord)
{
    for(unsigned i=0;i<r->nvalues;i++)if(r->values[i].ordinal==ord)return r->values[i].raw;
    return UINT32_MAX;
}
static const uint8_t *field_of(const dw4_igb *g,const dw4_igb_record *r,unsigned ord)
{
    for(unsigned i=0;i<r->nvalues;i++)if(r->values[i].ordinal==ord)return g->data+r->values[i].voff;
    return NULL;
}
/* One beNumberCtrlInfoRam: its geometry, digit count and the vertices of each digit (`pl->geometry` stays 0 when the record is incomplete). */
static int load_plate(const dw4_igb *g,const dw4_igb_record *r,struct plate *pl,uint32_t *geometry_id,char *geometry_name,size_t name_cap)
{
    dw4_igb_record geometry={0};int ok=0;
    if(!dw4_igb_record_at(g,slot_of(r,11),&geometry))return 0;
    snprintf(geometry_name,name_cap,"%s",geometry.name?geometry.name:"");
    *geometry_id=slot_of(r,11);
    pl->geometry=*geometry_id;pl->max=slot_of(r,13);pl->mode=slot_of(r,14);pl->count=0;
    uint32_t raw=slot_of(r,12);memcpy(&pl->offset,&raw,4);
    dw4_igb_record digits={0};uint32_t bytes=0;const uint8_t *data=NULL;
    if(dw4_igb_record_at(g,slot_of(r,15),&digits))data=dw4_igb_block(g,slot_of(&digits,4),&bytes);
    if(data && bytes && !(bytes%4) && bytes/4<=8) {
        ok=1;
        for(unsigned digit=0;digit<bytes/4 && ok;digit++){
            uint32_t id;memcpy(&id,data+4*digit,4);dw4_igb_record dr={0},vertices={0};uint32_t vb=0;
            const uint8_t *vd=NULL;
            if(!dw4_igb_record_at(g,id,&dr) || !dw4_igb_record_at(g,slot_of(&dr,3),&vertices)){dw4_igb_record_free(&vertices);dw4_igb_record_free(&dr);ok=0;break;}
            vd=dw4_igb_block(g,slot_of(&vertices,4),&vb);
            if(!vd || vb!=24){ok=0;}
            for(unsigned q=0;ok && q<vb/4;q++){
                uint32_t vid;memcpy(&vid,vd+4*q,4);dw4_igb_record vr={0};
                if(!dw4_igb_record_at(g,vid,&vr) || slot_of(&vr,3)>3 || pl->count>=48){dw4_igb_record_free(&vr);ok=0;break;}
                pl->map[pl->count].vertex=slot_of(&vr,2);pl->map[pl->count].kind=slot_of(&vr,3);pl->map[pl->count].place=digit;pl->count++;
                dw4_igb_record_free(&vr);
            }
            dw4_igb_record_free(&vertices);dw4_igb_record_free(&dr);
        }
        if(!ok)pl->count=0;
    }
    dw4_igb_record_free(&digits);dw4_igb_record_free(&geometry);
    return ok;
}
/* One beMeterCtrlOneData: the recovered meter state, its beMeterCtrlNode and that node's child scene nodes (the gauge's graph nodes). */
static int load_meter(const dw4_igb *g,const dw4_igb_record *r,dw4_hudmeter *m,uint32_t *node,uint32_t child[8],unsigned *nchild)
{
    uint32_t raw=slot_of(r,4);float maximum;memcpy(&maximum,&raw,4);
    const uint8_t *nz=field_of(g,r,9),*nm=field_of(g,r,10);int64_t nonzero,nonmax;
    if(!nz || !nm)return -1;
    memcpy(&nonzero,nz,8);memcpy(&nonmax,nm,8);
    if(dw4_hudmeter_init(m,maximum,slot_of(r,14)!=0,nonzero,nonmax))return -1;
    *node=slot_of(r,3);*nchild=0;
    dw4_igb_record mn={0},list={0};
    if(*node<g->table_n && g->id_kind[*node]==2 && dw4_igb_decode(g,g->id_off[*node],&mn)) {
        uint32_t lid=slot_of(&mn,7);
        if(lid<g->table_n && g->id_kind[lid]==2 && dw4_igb_decode(g,g->id_off[lid],&list)) {
            uint32_t count=slot_of(&list,2),len;const uint8_t *ids=dw4_igb_block(g,slot_of(&list,4),&len);
            for(uint32_t k=0;ids && k<count && k<8 && 4*(k+1)<=len;k++)memcpy(&child[(*nchild)++],ids+4*k,4);
        }
        dw4_igb_record_free(&list);
    }
    dw4_igb_record_free(&mn);
    dw4_hudmeter_percent(m,100);
    return 0;
}
dw4_fieldhud *dw4_fieldhud_open(dw4_mount *mount,const char *stage)
{
    dw4_igfile file={0};dw4_igb g={0};dw4_fieldhud *f=calloc(1,sizeof *f);
    if(!f || dw4_igfile_open_stage_pack(&file,mount,stage,0,0) || dw4_igb_open(&g,file.data,file.len,0) || dw4_igb_refs_open(&g))goto fail;
    for(uint32_t id=0;id<g.table_n;id++) {
        dw4_igb_record r={0};
        if(g.id_kind[id]!=2 || !dw4_igb_decode(&g,g.id_off[id],&r))continue;
        if(!strcmp(r.class_name,"beMeterCtrlOneData") && r.name && (!strncmp(r.name,"hpmt",4) || !strncmp(r.name,"mpmt",4)) &&
           r.name[4]>='1' && r.name[4]<='4' && !r.name[5]) {
            unsigned gauge=r.name[0]=='m',s=(unsigned)(r.name[4]-'1');
            if(load_meter(&g,&r,&f->meter[gauge][s],&f->node[gauge][s],f->child[gauge][s],&f->nchild[gauge][s])){dw4_igb_record_free(&r);goto fail;}
            f->have[gauge]|=1u<<s;
        }
        if(!strcmp(r.class_name,"beMeterCtrlInfo") && r.name && !strncmp(r.name,"bshp1",5) && r.name[5]>='0' && r.name[5]<='9' && !r.name[6]) {   /* bshp10 (Blossomon), bshp11 (Mammothmon) */   /* the boss gauge: the info's first one-data */
            dw4_igb_record list={0};
            if(dw4_igb_record_at(&g,slot_of(&r,7),&list)) {
                uint32_t len;const uint8_t *ids=dw4_igb_block(&g,slot_of(&list,4),&len);
                dw4_igb_record od={0};uint32_t oid;
                if(ids && len>=4 && (memcpy(&oid,ids,4),dw4_igb_record_at(&g,oid,&od)) && !load_meter(&g,&od,&f->meter[2][0],&f->node[2][0],f->child[2][0],&f->nchild[2][0]))f->have[2]=1;
                dw4_igb_record_free(&od);
            }
            dw4_igb_record_free(&list);
        }
        if(!strcmp(r.class_name,"beNumberCtrlInfoRam")) {   /* a digit plate: its geometry, digit count and the vertices of each digit */
            struct plate pl={0};uint32_t gid;char gname[16];
            if(load_plate(&g,&r,&pl,&gid,gname,sizeof gname) && strlen(gname)==5 && gname[4]>='1' && gname[4]<='4' &&
               (!strncmp(gname,"lvnm",4) || !strncmp(gname,"hpnm",4) || !strncmp(gname,"mpnm",4))) {
                unsigned kind=gname[0]=='l'?0:gname[0]=='h'?1:2,s=(unsigned)(gname[4]-'1');
                f->plate[kind][s]=pl;f->have_plate[kind]|=1u<<s;
            }
        }
        if(!strcmp(r.class_name,"beNumberCtrlInfo") && r.name) {   /* the floating numbers: one digit plate per instance (RAM slot) of the model */
            static const char *const names[4]={"dmgnm0","expnm0","dmgnm1","bitnum0"};
            for(unsigned k=0;k<4;k++) {
                if(strcmp(r.name,names[k]))continue;
                dw4_igb_record list={0};
                if(dw4_igb_record_at(&g,slot_of(&r,6),&list)) {
                    uint32_t count=slot_of(&list,2),len;const uint8_t *ids=dw4_igb_block(&g,slot_of(&list,4),&len);
                    for(uint32_t q=0;ids && q<count && q<DW4_FIELDHUD_POPUPS && 4*(q+1)<=len;q++) {
                        uint32_t rid;memcpy(&rid,ids+4*q,4);dw4_igb_record ram={0};uint32_t gid;char gname[16];
                        if(dw4_igb_record_at(&g,rid,&ram) && load_plate(&g,&ram,&f->popup[k][q],&gid,gname,sizeof gname)){f->popup[k][q].value=0;f->npopup[k]=q+1;}
                        dw4_igb_record_free(&ram);
                    }
                }
                dw4_igb_record_free(&list);
            }
        }
        dw4_igb_record_free(&r);
    }
    if(f->have[0]!=15 || f->have[1]!=15)goto fail;
    dw4_igb_close(&g);dw4_igfile_close(&file);return f;
fail:
    dw4_igb_close(&g);dw4_igfile_close(&file);free(f);return NULL;
}
void dw4_fieldhud_close(dw4_fieldhud *f){free(f);}
void dw4_fieldhud_percent(dw4_fieldhud *f,unsigned gauge,unsigned slot,float percent)
{if(f && gauge<2 && slot<4)dw4_hudmeter_percent(&f->meter[gauge][slot],percent);}
void dw4_fieldhud_tick(dw4_fieldhud *f)
{if(f)for(unsigned g=0;g<3;g++)for(unsigned s=0;s<4;s++)dw4_hudmeter_tick(&f->meter[g][s]);}
int dw4_fieldhud_time(const dw4_fieldhud *f,uint32_t node_id,int32_t slot,int64_t *time)
{
    for(unsigned g=0;f && g<3;g++)for(unsigned s=0;s<4;s++){
        if(g==2 && (s || !f->have[2]))break;
        if(g<2 && slot>=0 && slot<4 && s!=(unsigned)slot)continue;   /* the panel graphs of the four slots share transforms (a node id appears under several meters' child lists): the instance's slot picks its meters */
        int hit=f->node[g][s]==node_id;
        for(unsigned k=0;k<f->nchild[g][s];k++)hit|=f->child[g][s][k]==node_id;
        if(hit){*time=f->meter[g][s].time;return 1;}
    }
    return 0;
}
void dw4_fieldhud_number(dw4_fieldhud *f,unsigned kind,unsigned slot,int32_t value){if(f && kind<3 && slot<4)f->plate[kind][slot].value=value;}
int dw4_fieldhud_uv(const dw4_fieldhud *f,uint32_t node_id,uint32_t geometry_id,uint32_t vertex,float uv[2])
{
    for(unsigned k=0;f && k<3;k++)for(unsigned s=0;s<4;s++) {
        const struct plate *pl=&f->plate[k][s];
        if(!(f->have_plate[k]&(1u<<s)) || (node_id!=pl->geometry && geometry_id!=pl->geometry))continue;
        int32_t value=pl->value;if(value<0)value=0;if((uint32_t)value>pl->max)value=(int32_t)pl->max;
        for(unsigned n=0;n<pl->count;n++)if(pl->map[n].vertex==vertex){dw4_hudnumber_uv(dw4_hudnumber_digit(value,pl->mode,pl->map[n].place),pl->map[n].kind,pl->offset,uv);return 1;}
    }
    return 0;
}
void dw4_fieldhud_boss_percent(dw4_fieldhud *f,float percent){if(f && f->have[2])dw4_hudmeter_percent(&f->meter[2][0],percent);}
void dw4_fieldhud_popup_value(dw4_fieldhud *f,unsigned kind,unsigned slot,int32_t value)
{if(f && kind<4 && slot<f->npopup[kind])f->popup[kind][slot].value=value;}
unsigned dw4_fieldhud_popup_hits(const dw4_fieldhud *f){return f?f->popup_hits:0;}
int dw4_fieldhud_popup_uv(dw4_fieldhud *f,uint32_t node_id,uint32_t geometry_id,uint32_t vertex,float uv[2])
{
    for(unsigned k=0;f && k<4;k++)for(unsigned s=0;s<f->npopup[k];s++) {
        const struct plate *pl=&f->popup[k][s];
        if(node_id!=pl->geometry && geometry_id!=pl->geometry)continue;
        int32_t value=pl->value;if(value<0)value=0;if((uint32_t)value>pl->max)value=(int32_t)pl->max;
        for(unsigned n=0;n<pl->count;n++)if(pl->map[n].vertex==vertex){dw4_hudnumber_uv(dw4_hudnumber_digit(value,pl->mode,pl->map[n].place),pl->map[n].kind,pl->offset,uv);f->popup_hits++;return 1;}
    }
    return 0;
}
