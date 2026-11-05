#include "dw4/statusequip.h"
#include <string.h>
static const char *const keys[]={"POWERSOCKET","MAINSLOT","SUBSLOT","POWERPOCKET","MAINPOCKET"};
static const char *const refs[]={"POWERSOCKETREF","MAINSLOTREF","SUBSLOTREF","POWERPOCKETREF","MAINPOCKETREF"};
int dw4_statusequip_candidates(dw4_playerrecords *p,int32_t player,int kind,int32_t *rows,size_t cap,size_t *out)
{
    dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",player);size_t n,total=0;
    if(!f || kind<0 || kind>3 || !out || dw4_property_item_count(f,"DEVICEFOLDER",&n) || n>36)return -1;
    const dw4_item_record *items=dw4_property_items(f,"DEVICEFOLDER",&n);
    for(size_t i=0;i<n;i++)if(items[i].kind==kind)total++;
    if(total>cap || (total && !rows))return -1;
    total=0;for(size_t i=0;i<n;i++)if(items[i].kind==kind)rows[total++]=(int32_t)i;
    *out=total;return 0;
}
int dw4_statusequip_action_rows(dw4_playerrecords *p,int32_t player,int kind,
    int mode,int32_t slot,int32_t latch,dw4_statusequip_actions *out)
{
    dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",player);size_t n;
    if(!f || !out || kind<0 || kind>2 || mode<0 || mode>1 || slot<0)return -1;
    const dw4_item_record *items=dw4_property_items(f,keys[kind],&n);
    if(!items || (size_t)slot>=n)return -1;
    *out=(dw4_statusequip_actions){.callno=kind!=0?120:mode?46:124,.rows=kind!=0 || mode?3:2,.enabled={1,0,0}};
    out->enabled[1]=kind!=2 && latch==0 && items[0].kind!=-1 && items[0].pocket>0;
    out->enabled[2]=slot!=0 && items[slot].kind!=-1;
    if(kind!=0)out->enabled[2]=items[slot].kind!=-1;
    return 0;
}
int dw4_statusequip_eligible(dw4_playerrecords *p,int32_t player,int32_t candidate,const dw4_databases *db,int *out)
{
    dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",player);size_t n;
    if(!f || !db || !out || dw4_property_item_count(f,"DEVICEFOLDER",&n) || n>36 || candidate<0 || (size_t)candidate>=n)return -1;
    const dw4_item_record *item=dw4_property_items(f,"DEVICEFOLDER",&n)+candidate;
    int32_t species,mask,skill,threshold,level;
    if(item->kind==3){*out=1;return 0;}
    if(item->kind==0){
        if(dw4_property_number(f,"DIGIMONNO",&species) || dw4_playerstats_item_attribute((void *)db,item,"SOUBI",&mask) ||
            dw4_playerstats_item_attribute((void *)db,item,"SKILL",&skill) || dw4_playerstats_item_attribute((void *)db,item,"SKILLPOINT",&threshold))return -1;
        const int32_t *skills=dw4_property_array(f,"SKILL",&n);if(!skills || n!=9)return -1;
        *out=dw4_weapon_eligible(species,skills,(uint32_t)mask,skill,threshold);return 0;
    }
    if(item->kind!=1 && item->kind!=2)return -1;
    if(dw4_property_number(f,"LEVEL",&level) || dw4_playerstats_item_attribute((void *)db,item,"LVPOINT",&threshold))return -1;
    *out=threshold<=level;return 0;
}
static int clear_pockets(dw4_property_folder *f,int kind)
{
    const char *key=keys[kind+3],*ref=refs[kind+3];size_t n,len;
    const int32_t *v=dw4_property_array(f,ref,&len);
    const dw4_item_record *src=dw4_property_items(f,"DEVICEFOLDER",&n);
    if(!v || len!=5 || dw4_property_item_count(f,"DEVICEFOLDER",&n) || n>36)return -1;
    dw4_item_record items[36],empty[5];int32_t links[5];if(n)memcpy(items,src,n*sizeof *items);
    for(size_t i=0;i<5;i++){
        if(v[i]<-1 || (v[i]>=0 && (size_t)v[i]>=n))return -1;
        if(v[i]>=0)items[v[i]].equipped=0;
        links[i]=-1;empty[i]=(dw4_item_record){.kind=-1};
    }
    return dw4_property_set_items(f,"DEVICEFOLDER",items,n) || dw4_property_set_array(f,ref,links,5) || dw4_property_set_items(f,key,empty,5)?-1:0;
}
static int transaction(dw4_playerrecords *p,int32_t player,int kind,size_t pos,int32_t candidate,
    const dw4_databases *db,int preview,dw4_player_recalculate sink,void *user)
{
    dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",player);int eligible;
    if(!f || !db || kind<0 || kind>4 || (preview && !sink))return -1;
    if(candidate>=0 && (dw4_statusequip_eligible(p,player,candidate,db,&eligible) || !eligible))return -1;
    dw4_playerrecords *stage=dw4_playerrecords_open();if(!stage)return -1;
    dw4_property_folder *s=dw4_playerrecords_get(stage,"GETPLAYER",0);int rc=-1;
    if(dw4_property_copy_values(s,f))goto done;
    /* Retail virtual 31 clears chips after accepting the first weapon/board. */
    if(kind<2 && !pos && (!preview || kind==1) && clear_pockets(s,kind))goto done;
    if(dw4_playertransactions_equip_database(stage,0,keys[kind],pos,candidate,db))goto done;
    rc=preview?sink(user,s):dw4_property_commit_values(f,s);
done:dw4_playerrecords_close(stage);return rc;
}
int dw4_statusequip_accept(dw4_playerrecords *p,int32_t player,int kind,size_t pos,int32_t candidate,const dw4_databases *db)
{return transaction(p,player,kind,pos,candidate,db,0,NULL,NULL);}
int dw4_statusequip_preview(dw4_playerrecords *p,int32_t player,int kind,size_t pos,int32_t candidate,
    const dw4_databases *db,dw4_player_recalculate sink,void *user)
{return transaction(p,player,kind,pos,candidate,db,1,sink,user);}
int dw4_statusequip_swap(dw4_playerrecords *p,int32_t player,size_t a,size_t b,const dw4_databases *db,
    int preview,dw4_player_recalculate sink,void *user)
{
    dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",player);size_t n;
    if(!f || !db || a>=3 || b>=3 || (preview && !sink))return -1;
    const int32_t *r=dw4_property_array(f,"POWERSOCKETREF",&n);if(!r || n!=3)return -1;
    if(preview && (a==b || ((!a || !b) && (r[a]<0 || r[b]<0))))return 1;
    int32_t links[3];memcpy(links,r,sizeof links);int32_t temp=links[a];links[a]=links[b];links[b]=temp;
    const dw4_item_record *items=dw4_property_items(f,"DEVICEFOLDER",&n);
    if(dw4_property_item_count(f,"DEVICEFOLDER",&n) || n>36)return -1;
    dw4_item_record values[3];
    for(size_t i=0;i<3;i++){if(links[i]<-1 || (links[i]>=0 && (size_t)links[i]>=n))return -1;
        values[i]=links[i]<0?(dw4_item_record){.kind=-1}:items[links[i]];}
    dw4_playerrecords *stage=dw4_playerrecords_open();if(!stage)return -1;
    dw4_property_folder *s=dw4_playerrecords_get(stage,"GETPLAYER",0);int rc=-1;
    if(dw4_property_copy_values(s,f) || dw4_property_set_array(s,"POWERSOCKETREF",links,3) ||
        dw4_property_set_items(s,"POWERSOCKET",values,3) ||
        (!preview && (!a || !b) && clear_pockets(s,0)) || dw4_playerstats_recalculate((void *)db,s))goto done;
    rc=preview?sink(user,s):dw4_property_commit_values(f,s);
done:dw4_playerrecords_close(stage);return rc;
}
int dw4_statusequip_transaction_io(void *user,dw4_statusequip *c,int op,int32_t value)
{
    dw4_statusequip_context *b=user;int32_t candidate;int rc,eligible;
    if(!b || !c || !b->view || !b->candidate || !b->preview || !b->players || !b->databases || b->kind<0 || b->kind>2)return -1;
    /* 40fd68 leaves a1=-1 for the remove-action v32 call. Main/Sub preview a
     * private clear; Power's v32 ignores it. This path owns no inventory cursor. */
    if(op==DW4_EQUIP_VIRTUAL+32 && value==-1){
        return b->kind==0?0:dw4_statusequip_preview(b->players,b->player,b->kind,(size_t)c->slot,-1,b->databases,b->preview,b->preview_user);
    }
    if(op==DW4_EQUIP_VIRTUAL+39 && value==-1){
        return b->kind==2?0:dw4_statusequip_preview(b->players,b->player,b->kind+3,(size_t)c->pocket,-1,b->databases,b->preview,b->preview_user);
    }
    if(op==DW4_EQUIP_VIRTUAL+25){
        c->window.sub=1;c->window.delay=0;c->window.latch=b->kind==0 && c->window.selection!=0?1:0;return 0;
    }
    if(op==DW4_EQUIP_VIRTUAL+28){
        if(c->window.selection==0){c->window.sub=b->kind==0 && !c->mode?3:4;}
        else if(c->window.selection==1){if(b->kind==2)return -1;c->window.sub=2;}
        else if(c->window.selection==2){
            if(dw4_statusequip_accept(b->players,b->player,b->kind,(size_t)c->slot,-1,b->databases))return -1;
            c->window.selection=c->slot;
            if(b->view(b->user,c,DW4_EQUIP_VIRTUAL+24,0)<0 || b->view(b->user,c,DW4_EQUIP_REFRESH,0)<0)return -1;
            c->window.state=0;c->window.sub=1;
        }else return -1;
        c->window.delay=c->window.latch=0;return 0;
    }
    if(op==DW4_EQUIP_PREPARE){
        dw4_property_folder *f=dw4_playerrecords_get(b->players,"GETPLAYER",b->player);size_t n;
        if(!f)return -1;
        const size_t counts[]={3,1,1,5,5};
        for(unsigned k=0;k<5;k++)if(!dw4_property_array(f,refs[k],&n) || n!=counts[k] || dw4_property_item_count(f,keys[k],&n) || n!=counts[k])return -1;
        if(dw4_property_item_count(f,"DEVICEFOLDER",&n) || n>36)return -1;
    }
    if(op==DW4_EQUIP_VIRTUAL+30 || op==DW4_EQUIP_VIRTUAL+31 || op==DW4_EQUIP_VIRTUAL+37 || op==DW4_EQUIP_VIRTUAL+32 || op==DW4_EQUIP_VIRTUAL+39){
        int chip=op==DW4_EQUIP_VIRTUAL+37 || op==DW4_EQUIP_VIRTUAL+39;
        int preview=op==DW4_EQUIP_VIRTUAL+32 || op==DW4_EQUIP_VIRTUAL+39;
        int kind=chip?b->kind+3:b->kind;
        if(kind>4)return -1;
        candidate=-1;
        if(c->window.selection!=-1){
            rc=b->candidate(b->user,c,chip,&candidate);
            if(rc<0 || (!preview && rc>0))return -1;
            if(rc==2)return b->view(b->user,c,DW4_EQUIP_PREVIEW_OFF,0);
            if(rc>0)return 0;
            if(candidate<0)return -1;
        }
        if(op==DW4_EQUIP_VIRTUAL+30){
            if(candidate<0)return 0;
            return dw4_statusequip_eligible(b->players,b->player,candidate,b->databases,&eligible)?-1:eligible;
        }
        if(preview && candidate>=0){
            if(dw4_statusequip_eligible(b->players,b->player,candidate,b->databases,&eligible))return -1;
            if(!eligible)return b->view(b->user,c,DW4_EQUIP_PREVIEW_OFF,0);
        }
        if(preview)return dw4_statusequip_preview(b->players,b->player,kind,chip?(size_t)c->pocket:(size_t)c->slot,candidate,b->databases,b->preview,b->preview_user);
        return dw4_statusequip_accept(b->players,b->player,kind,chip?(size_t)c->pocket:(size_t)c->slot,candidate,b->databases);
    }
    /* Accepted weapon/swap publication already cleared pockets atomically. */
    if(op==DW4_EQUIP_VIRTUAL+38)return 0;
    if(op==DW4_EQUIP_SWAP || op==DW4_EQUIP_SWAP_PREVIEW){
        if(b->kind!=0)return -1;
        rc=dw4_statusequip_swap(b->players,b->player,(size_t)c->slot,(size_t)c->window.selection,b->databases,
            op==DW4_EQUIP_SWAP_PREVIEW,b->preview,b->preview_user);
        if(rc<0)return rc;
        /* A suppressed comparison restores the baseline text through the view. */
        return rc?b->view(b->user,c,DW4_EQUIP_PREVIEW_OFF,0):0;
    }
    return b->view(b->user,c,op,value);
}
