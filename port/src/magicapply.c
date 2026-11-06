#include <string.h>
#include "dw4/magicapply.h"
int dw4_magic_area_collect(const dw4_magic_group *g,int32_t excluded,const float center[3],int32_t out[4])
{
    int n=0;
    if(!g || !center || !out)return -1;
    for(int i=0;i<4;i++){
        if(!g->member[i] || i==excluded)continue;
        float dx=g->pos[i][0]-center[0],dy=g->pos[i][1]-center[1],dz=g->pos[i][2]-center[2];
        if(!(dx*dx+dy*dy+dz*dz<DW4_MAGIC_AREA_RADIUS_SQ))continue;
        if(g->answer[i])out[n++]=i;
    }
    return n;
}
int dw4_magic_player_group(dw4_playerrecords *r,const int joined[4],const float pos[4][3],dw4_magic_group *out)
{
    if(!r || !joined || !pos || !out)return -1;
    memset(out,0,sizeof *out);
    for(int i=0;i<4;i++){
        int32_t hp=0;
        out->member[i]=joined[i]!=0;
        memcpy(out->pos[i],pos[i],sizeof out->pos[i]);
        if(out->member[i]){dw4_property_folder *p=dw4_playerrecords_get(r,"GETPLAYER",i);if(!p || dw4_property_number(p,"HP",&hp))return -1;}
        out->answer[i]=hp!=0;
    }
    return 0;
}
int dw4_magic_apply_heal(dw4_playerrecords *r,const dw4_magic *m,int32_t caster,const dw4_magic_group *g,int applied[4])
{
    int32_t list[4];int n,rc;
    if(!r || !m || !g || !applied || m->kind!=DW4_MAGIC_HEAL || caster<0 || caster>3)return -1;
    memset(applied,0,4*sizeof *applied);
    rc=dw4_fight_apply_hp(dw4_playerrecords_get(r,"GETPLAYER",caster),m->v[0]);
    if(rc<0)return -1;
    applied[caster]=rc==1;
    if(!m->area)return 0;
    n=dw4_magic_area_collect(g,caster,g->pos[caster],list);
    for(int i=0;i<n;i++){
        rc=dw4_fight_apply_hp(dw4_playerrecords_get(r,"GETPLAYER",list[i]),m->v[0]);
        if(rc<0)return -1;
        applied[list[i]]=rc==1;
    }
    return n;
}
int dw4_magic_apply_cure(const dw4_fight_ctx *c,const dw4_magic *m,int32_t caster,const dw4_magic_group *g,const int poisoned[4],const int32_t endurance[4],int cured[4])
{
    int32_t list[4];int n=0,draws=0;
    if(!c || !m || !g || !poisoned || !endurance || !cured || m->kind!=DW4_MAGIC_CURE || caster<0 || caster>3)return -1;
    memset(cured,0,4*sizeof *cured);
    if(poisoned[caster]){if(dw4_fight_p2p_cure_poison(c,m,endurance[caster],&cured[caster]))return -1;draws++;}
    if(m->area)n=dw4_magic_area_collect(g,caster,g->pos[caster],list);
    for(int i=0;i<n;i++)if(poisoned[list[i]]){
        if(dw4_fight_p2p_cure_poison(c,m,endurance[list[i]],&cured[list[i]]))return -1;
        draws++;
    }
    return draws;
}
int dw4_magic_apply_raise(dw4_playerrecords *r,const dw4_magic *m,const dw4_magic_group *g,const float caster_pos[3],const int running[4],int32_t targets[4],int32_t exp_percent[4])
{
    int n;
    if(!r || !m || !g || !caster_pos || !running || !targets || !exp_percent || m->kind!=DW4_MAGIC_RAISE || m->nv!=2)return -1;
    n=dw4_magic_area_collect(g,-1,caster_pos,targets);
    for(int i=0;i<n;i++){
        exp_percent[i]=m->v[0];
        if(!running[targets[i]] && dw4_property_set_number(dw4_playerrecords_get(r,"GETPLAYER",targets[i]),"HP",m->v[1]))return -1;
    }
    return n;
}
int dw4_magic_buff_targets(const dw4_magic_group *g,int32_t caster,int32_t out[4])
{
    int n;
    if(!g || !out || caster<0 || caster>3)return -1;
    n=dw4_magic_area_collect(g,caster,g->pos[caster],out);
    if(n<0)return -1;
    out[n++]=caster;   /* RecoveryList::append of the caster, after the area members */
    return n;
}
int dw4_magic_apply_raise_refund(dw4_playerrecords *r,int32_t slot,int32_t percent)
{
    dw4_property_folder *common=dw4_playerrecords_get(r,"GETCOMMON",0),*p=dw4_playerrecords_get(r,"GETPLAYER",slot);
    size_t nd=0;const int32_t *data=common?dw4_property_array(common,"BKCHIPDATA",&nd):NULL;
    int32_t bit,exp,list[8];const char *stage[4],*name[4];
    if(!common || !p || slot<0 || slot>3 || !data || nd!=8 || dw4_property_number(p,"BIT",&bit) || dw4_property_number(p,"EXP",&exp))return -1;
    memcpy(list,data,sizeof list);
    for(int i=0;i<4;i++){stage[i]=dw4_property_string_at(common,"BKCHIPSTAGE",(size_t)i);name[i]=dw4_property_string_at(common,"BKCHIPNAME",(size_t)i);}
    bit+=list[2*slot];list[2*slot]=0;
    const char *mine=dw4_property_string(p,"DIGIMONNAME");
    if(mine && name[slot] && !strcmp(mine,name[slot])){exp+=(int32_t)((int64_t)list[2*slot+1]*percent/100);list[2*slot+1]=0;}
    stage[slot]=NULL;
    if(dw4_property_set_number(p,"BIT",bit) || dw4_property_set_number(p,"EXP",exp) || dw4_property_set_array(common,"BKCHIPDATA",list,8) ||
       dw4_property_set_strings(common,"BKCHIPSTAGE",stage,4))return -1;
    return 0;
}

/* ---- the death side of the bank-chip stash: GAMERAM BKCHIPBITEXP, DEADRESTART and the capsule's start ------------------------------------------------ */
/* DW4Curve::g(d,x) of the matched source (vfunc_34, ~line 303): the cumulative EXP curve. g(L-1,L) = 200(L-1) + (L+139)(L-1)^2 is the NEXTEXP of level L-1,
 * i.e. the EXP at which level L starts (playerstats.c computes the same NEXTEXP as 200L + (L+140)L^2). */
static int32_t exp_curve(int32_t d,int32_t x){return d*0xC8+(x+0x8B)*(d*d);}
int dw4_magic_bkchip_bitexp(dw4_playerrecords *r,int32_t slot)
{
    dw4_property_folder *common=dw4_playerrecords_get(r,"GETCOMMON",0),*p=dw4_playerrecords_get(r,"GETPLAYER",slot);
    size_t nd=0;const int32_t *data=common?dw4_property_array(common,"BKCHIPDATA",&nd):NULL;
    int32_t bit,exp,level,list[8];const char *name[4];
    if(!common || !p || slot<0 || slot>3 || !data || nd!=8 || dw4_property_number(p,"BIT",&bit) || dw4_property_number(p,"EXP",&exp) ||
       dw4_property_number(p,"LEVEL",&level))return -1;
    memcpy(list,data,sizeof list);
    for(int i=0;i<4;i++)name[i]=dw4_property_string_at(common,"BKCHIPNAME",(size_t)i);
    name[slot]=dw4_property_string(p,"DIGIMONNAME");   /* NULL stays NULL (the retail list slot is then set to an empty string reference) */
    list[2*slot]=bit;bit=0;
    if(level!=1 && level!=999){
        /* The loss is 2/10 of the level span g(L-1,L) - g(L-2,L-1), but the EXP never drops below the level's base g(L-1,L). */
        int32_t base=exp_curve(level-1,level),kept=exp-(base-exp_curve(level-2,level-1))*2/10;
        if(kept<base)kept=base;
        list[2*slot+1]=exp-kept;exp=kept;
    }   /* levels 1 and 999 leave the loss entry untouched (it keeps whatever a previous death stashed) */
    if(dw4_property_set_number(p,"BIT",bit) || dw4_property_set_number(p,"EXP",exp) || dw4_property_set_array(common,"BKCHIPDATA",list,8) ||
       dw4_property_set_strings(common,"BKCHIPNAME",name,4))return -1;
    return 0;
}
int dw4_magic_dead_restart(dw4_playerrecords *r)
{
    if(!r)return -1;
    for(int i=0;i<4;i++){
        dw4_property_folder *p=dw4_playerrecords_get(r,"GETPLAYER",i);
        int32_t use,mhp,mmp;
        if(!p || dw4_property_number(p,"ISUSE",&use))return -1;
        if(!(uint8_t)use)continue;
        if(dw4_property_number(p,"MHP",&mhp) || dw4_property_number(p,"MMP",&mmp) || dw4_property_set_number(p,"HP",mhp) || dw4_property_set_number(p,"MP",mmp))return -1;
    }
    return 0;
}
int dw4_magic_capsule_start(dw4_playerrecords *r,int32_t slot,const char *stage,const float pos[3])
{
    dw4_property_folder *common=dw4_playerrecords_get(r,"GETCOMMON",0);
    size_t nf=0;const float *fp=common?dw4_property_floats(common,"BKCHIPPOS",&nf):NULL;
    const char *names[4];float list[12];
    if(!common || slot<0 || slot>3 || !stage || !pos || !fp || nf!=12)return -1;
    memcpy(list,fp,sizeof list);
    for(int i=0;i<4;i++)names[i]=dw4_property_string_at(common,"BKCHIPSTAGE",(size_t)i);
    names[slot]=stage;memcpy(list+3*slot,pos,3*sizeof *pos);
    if(dw4_property_set_strings(common,"BKCHIPSTAGE",names,4) || dw4_property_set_floats(common,"BKCHIPPOS",list,12))return -1;
    return 0;
}
