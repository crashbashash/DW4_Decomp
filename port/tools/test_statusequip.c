#include "dw4/statusequip.h"
#include "dw4/playerinit.h"
#include "dw4/scriptengine.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
static int binding(void *u,const char *m,const dw4_script_value *a,size_t n,dw4_script_value *r,char *e,size_t c)
{(void)u;(void)e;(void)c;*r=(dw4_script_value){DW4_SCRIPT_NUMBER,0,NULL,0};
 if(!strcmp(m,"SYSgetLightMode"))r->number=1;
 else if(!strcmp(m,"SYSisJoinPlayer"))r->number=n==1 && a[0].number==0;
 else if(!strcmp(m,"SYSgetPlayerName"))*r=(dw4_script_value){DW4_SCRIPT_STRING,0,"m_agumon",8};
 else if(!strcmp(m,"SYSgetWeaponName"))*r=(dw4_script_value){DW4_SCRIPT_STRING,0,"w_axe01",7};
 return 0;}
struct host {dw4_menu_window *w;int fail,close,finish;int32_t candidate;};
static int child(dw4_menu_window *w,char *e,size_t n)
{(void)e;(void)n;if(dw4_menu_window_data(w)->_st0==2)dw4_menu_window_data(w)->_isRun=0;return 0;}
static int view(void *u,dw4_statusequip *s,int op,int32_t value)
{
    struct host *h=u;(void)s;(void)value;
    if(h->fail)return -1;
    if(op==DW4_EQUIP_SELECTOR){dw4_menu_window *w=dw4_menu_window_open(child,NULL,NULL);assert(w);assert(!dw4_menu_window_add(h->w,w));}
    if(op==DW4_EQUIP_CLOSE_MODELS)h->close++;
    return op==DW4_EQUIP_FINISHED?h->finish:0;
}
static int candidate(void *u,dw4_statusequip *c,int chip,int32_t *out)
{(void)c;(void)chip;*out=((struct host *)u)->candidate;return 0;}
struct preview {int calls,fail;int32_t first;};
static int inspect(void *u,dw4_property_folder *f)
{
    struct preview *p=u;size_t n;const int32_t *r=dw4_property_array(f,"POWERSOCKETREF",&n);assert(r && n==3);
    p->calls++;p->first=r[0];int32_t hp;assert(!dw4_property_number(f,"MHP",&hp));
    return p->fail?-1:0;
}
struct removal {const char *key;int calls;};
static int remove_preview(void *u,dw4_property_folder *f)
{struct removal *p=u;size_t n;const int32_t *r=dw4_property_array(f,p->key,&n);assert(r && n==1 && r[0]==-1);p->calls++;return 0;}
static int no_inventory(void *u,dw4_statusequip *c,int chip,int32_t *out)
{(void)u;(void)c;(void)chip;(void)out;assert(0);return -1;}
int main(int argc,char **argv)
{
    dw4_mount mount;assert(!dw4_mount_open(&mount,argc>1?argv[1]:"../../local/extracted"));
    dw4_be_state state;dw4_be_init(&state);
    dw4_scriptengine *engine=dw4_scriptengine_open(&state,binding,NULL);assert(engine);
    dw4_filelist *files=dw4_filelist_open(&mount);assert(files);dw4_scriptengine_filelist(engine,files);
    assert(!dw4_filelist_begin(files,engine,"stagML11",7) && !dw4_filelist_shared(files));
    dw4_stageobjects *objects=dw4_stageobjects_open();assert(objects);
    assert(!dw4_filelist_route_assets(files,dw4_stageobjects_route,objects));
    char error[256];dw4_databases *db=dw4_databases_open(objects,error,sizeof error);assert(db);
    dw4_playerrecords *players=dw4_playerrecords_open();assert(players);
    const char *species[]={"p_dorumon","p_agumon","p_vmon","p_girumon"};
    for(int cycle=0;cycle<32;cycle++)for(int player=0;player<4;player++){
        assert(!dw4_playerrecords_create(players,db,player,species[player],"John",error,sizeof error));
        dw4_property_folder *f=dw4_playerrecords_get(players,"GETPLAYER",player);size_t n;
        const dw4_item_record *items=dw4_property_items(f,"DEVICEFOLDER",&n);assert(n==3);
        int32_t rows[36];size_t count;assert(!dw4_statusequip_candidates(players,player,0,rows,36,&count) && count==3);
        assert(rows[0]==0 && rows[1]==1 && rows[2]==2);
        assert(dw4_statusequip_candidates(players,player,0,rows,2,&count)==-1);
        struct preview p={0};const dw4_item_record *before=items;
        assert(!dw4_statusequip_swap(players,player,0,2,db,1,inspect,&p));assert(p.calls==1 && p.first==2);
        assert(dw4_property_items(f,"DEVICEFOLDER",&n)==before);
        assert(!dw4_statusequip_swap(players,player,0,2,db,0,NULL,NULL));
        const int32_t *refs=dw4_property_array(f,"POWERSOCKETREF",&n);assert(refs[0]==2 && refs[2]==0);
        p.fail=1;before=dw4_property_items(f,"DEVICEFOLDER",&n);
        assert(dw4_statusequip_preview(players,player,0,0,-1,db,inspect,&p)==-1);
        assert(dw4_property_items(f,"DEVICEFOLDER",&n)==before);
        assert(!dw4_statusequip_accept(players,player,0,0,-1,db));refs=dw4_property_array(f,"POWERSOCKETREF",&n);assert(refs[0]==-1);
        assert(dw4_statusequip_swap(players,player,0,1,db,1,inspect,&p)==1);
        assert(dw4_statusequip_accept(players,player,0,3,0,db)==-1);
        /* Signed armor level eligibility refuses a real item until level meets it. */
        int result;assert(!dw4_playertransactions_device(players,player,DW4_DEVICE_SET,1,0,0,0,&result) && result);
        assert(!dw4_property_set_number(f,"LEVEL",-1));int eligible;
        assert(!dw4_statusequip_eligible(players,player,3,db,&eligible) && !eligible);
        before=dw4_property_items(f,"DEVICEFOLDER",&n);assert(dw4_statusequip_accept(players,player,1,0,3,db)==-1);
        assert(dw4_property_items(f,"DEVICEFOLDER",&n)==before);
        assert(!dw4_property_set_number(f,"LEVEL",999));
        assert(!dw4_statusequip_accept(players,player,1,0,3,db));
        refs=dw4_property_array(f,"MAINSLOTREF",&n);assert(refs[0]==3);
        /* Install a real chip, then accepting the main board clears every pocket
         * and publishes its item flag/stat changes in the same transaction. */
        int32_t chip=-1;
        for(int row=0;row<128;row++){
            dw4_item_record item={.kind=3,.record=row};int32_t v;
            if(!dw4_playerstats_item_attribute(db,&item,"TSUYOSA",&v) && v>0){chip=row;break;}
        }
        assert(chip>=0);
        assert(!dw4_playertransactions_device(players,player,DW4_DEVICE_SET,3,chip,0,0,&result) && result);
        assert(!dw4_statusequip_accept(players,player,4,0,4,db));
        refs=dw4_property_array(f,"MAINPOCKETREF",&n);assert(refs[0]==4);
        assert(!dw4_statusequip_accept(players,player,1,0,3,db));
        refs=dw4_property_array(f,"MAINPOCKETREF",&n);for(size_t j=0;j<n;j++)assert(refs[j]==-1);
        items=dw4_property_items(f,"DEVICEFOLDER",&n);assert(!items[4].equipped);
        assert(!dw4_statusequip_accept(players,player,1,0,3,db));
        /* Route an accepted selector result through the real transaction IO. */
        struct host h={.candidate=3};p.fail=0;
        dw4_statusequip_context context={players,db,player,1,view,&h,candidate,inspect,&p};
        dw4_statusequip c={.window={.selection=0},.slot=0};
        assert(dw4_statusequip_transaction_io(&context,&c,130,0)==1);
        before=dw4_property_items(f,"DEVICEFOLDER",&n);int calls=p.calls;
        assert(!dw4_property_set_number(f,"LEVEL",-1));
        assert(!dw4_statusequip_transaction_io(&context,&c,132,0) && p.calls==calls);
        assert(dw4_property_items(f,"DEVICEFOLDER",&n)==before);
        assert(!dw4_property_set_number(f,"LEVEL",999));
        assert(!dw4_statusequip_transaction_io(&context,&c,131,0));
        refs=dw4_property_array(f,"MAINSLOTREF",&n);assert(refs[0]==-1); /* same identity toggles */
        context.candidate=NULL;assert(dw4_statusequip_transaction_io(&context,&c,131,0)==-1);
        context.candidate=candidate;
        assert(!dw4_statusequip_accept(players,player,1,0,3,db));
        assert(!dw4_playertransactions_device(players,player,DW4_DEVICE_SET,2,0,0,0,&result) && result);
        assert(!dw4_statusequip_accept(players,player,2,0,5,db));
        /* Remove-action previews do not ask an absent inventory view for a
         * candidate. Main/Sub stage an empty slot; Power intentionally ignores
         * -1. Failed or successful previews never publish session records. */
        for(int kind=0;kind<3;kind++){
            struct removal removal={kind==1?"MAINSLOTREF":"SUBSLOTREF",0};
            dw4_statusequip_context clear=context;clear.kind=kind;clear.candidate=no_inventory;
            clear.preview=remove_preview;clear.preview_user=&removal;
            c=(dw4_statusequip){.window={.sub=1,.selection=2},.slot=0};
            before=dw4_property_items(f,"DEVICEFOLDER",&n);
            int32_t original=-1;
            if(kind){const int32_t *live=dw4_property_array(f,removal.key,&n);assert(live && n==1 && live[0]>=0);original=live[0];}
            assert(!dw4_statusequip_transaction_io(&clear,&c,DW4_EQUIP_VIRTUAL+32,-1));
            assert(removal.calls==(kind!=0) && dw4_property_items(f,"DEVICEFOLDER",&n)==before);
            if(kind){const int32_t *live=dw4_property_array(f,removal.key,&n);assert(live[0]==original);}
        }
        for(int kind=0;kind<3;kind++)for(int mode=0;mode<2;mode++){
            context.kind=kind;c=(dw4_statusequip){.window={.selection=0},.mode=mode};
            assert(!dw4_statusequip_transaction_io(&context,&c,125,0) && c.window.sub==1);
            dw4_statusequip_actions actions;
            assert(!dw4_statusequip_action_rows(players,player,kind,mode,0,0,&actions));
            assert(actions.rows==(kind==0 && !mode?2:3) && actions.enabled[0]);
            assert(!dw4_statusequip_transaction_io(&context,&c,128,0));
            assert(c.window.sub==(kind==0 && !mode?3:4));
            c.window.selection=1;
            if(kind==2)assert(dw4_statusequip_transaction_io(&context,&c,128,0)==-1);
            else assert(!dw4_statusequip_transaction_io(&context,&c,128,0) && c.window.sub==2);
        }
        /* Owned close waits for actual descendants and the view's model hold. */
        h.w=dw4_statusequip_window_open(0,3,view,&h);assert(h.w);
        assert(!dw4_menu_window_tick(h.w,error,sizeof error) && dw4_menu_window_count(h.w)==1);
        dw4_menu_window_remove(h.w);assert(!dw4_menu_window_tick(h.w,error,sizeof error));
        assert(dw4_menu_window_data(h.w)->_st0==3 && dw4_menu_window_data(h.w)->_isRun && !dw4_menu_window_count(h.w) && h.close==1);
        assert(!dw4_menu_window_tick(h.w,error,sizeof error) && dw4_menu_window_data(h.w)->_isRun);
        h.finish=1;assert(!dw4_menu_window_tick(h.w,error,sizeof error) && !dw4_menu_window_data(h.w)->_isRun);dw4_menu_window_close(h.w);
        h.fail=1;h.w=dw4_statusequip_window_open(0,3,view,&h);assert(h.w);
        assert(dw4_menu_window_tick(h.w,error,sizeof error)==-1 && dw4_menu_window_data(h.w)->_isRun);dw4_menu_window_close(h.w);
    }
    dw4_playerrecords_close(players);dw4_databases_close(db);dw4_stageobjects_close(objects);
    dw4_filelist_close(files);dw4_scriptengine_close(engine);dw4_mount_close(&mount);
    puts("equipment: 128 four-player/species record cycles, filtered identities, private/failed previews, socket swaps, signed eligibility, accepted IO routing and owned-tree close/failure holds pass");return 0;
}
