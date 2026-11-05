/* NPC item converter (SUBWND CNOS, retail beNDMWShopCtrl40) through the normal prepared Central hub
 * runtime. Headless. The Digi-Elf is reached by the live Cross probe and the original script chain
 * (hit_n_digilfm -> n_digilfm_02 -> prompt -> SUBWND GENERATE CNOS); the list, dialogs and conversion
 * run the native windows over the original text, models and the retail coweapon/coarmor tables.
 * Fixtures are limited to BIT, LEVEL and the DEVICEFOLDER item list. The reroll draw comes from the
 * hub's own shared MT19937 stream, so results are checked as members of the authored table row set;
 * exact draws are pinned by tools/test_playerinit.c. */
#include "hubtest.h"
enum {UP=1,RIGHT=2,DOWN=4,LEFT=8};
static void enter_cnos(dw4_hubruntime *h)
{
    const dw4_modelctrl *npc=find(dw4_hubruntime_models(h),"n_digilfm",2);assert(npc);
    assert(talk_to(h,npc));
    unsigned k=0;
    for(;k<3000 && !(has_text(h,"TALKFONT02","font01") && has_text(h,"TALKFONT02","font02"));k++)step(h,0,k%45==44?0x4000:0);
    assert(k<3000);
    idle(h,60);press(h,0x4000); /* first entry: use the converter */
    assert(wait_text(h,"STWINFONT29","font100",900)); /* the 1450 prompt in the box state 0 prepared */
    assert(dw4_hubruntime_status_active(h));
    idle(h,60);
}
static void fixture(dw4_property_folder *f,const dw4_item_record *items,size_t n,int32_t bit,int32_t level)
{
    static const int32_t none[5]={-1,-1,-1,-1,-1};
    assert(!dw4_property_set_items(f,"DEVICEFOLDER",items,n));
    assert(!dw4_property_set_array(f,"POWERSOCKETREF",none,3) && !dw4_property_set_array(f,"POWERPOCKETREF",none,5) &&
           !dw4_property_set_array(f,"MAINSLOTREF",none,1) && !dw4_property_set_array(f,"MAINPOCKETREF",none,5) &&
           !dw4_property_set_array(f,"SUBSLOTREF",none,1));
    assert(!dw4_property_set_number(f,"BIT",bit) && !dw4_property_set_number(f,"LEVEL",level));
}
static int32_t tier_of(int32_t level){return level<41?1:level<101?2:level<201?3:level<301?4:level<401?5:6;}
/* The record is either unchanged (a miss) or one of the tier's authored result IDs. */
static int allowed(const dw4_databases *db,int kind,int32_t level,int32_t before,int32_t after)
{
    static const char *const names[3]={"coweapon","coarmor1","coarmor2"};
    const dw4_database *d=dw4_databases_get(db,names[kind]);assert(d);
    int32_t tier=tier_of(level),count=0;assert(dw4_database_number(d,tier*100,"ID",&count)>=0 && count>0);
    if(after==before)return 1;
    for(int32_t i=1;i<=count;i++){int32_t id;assert(dw4_database_number(d,tier*100+i,"ID",&id)>=0);if(id==after)return 1;}
    return 0;
}
static size_t count_of(dw4_property_folder *f){size_t n;assert(!dw4_property_item_count(f,"DEVICEFOLDER",&n));return n;}
static int32_t record_at(dw4_property_folder *f,size_t i){size_t n;const dw4_item_record *it=dw4_property_items(f,"DEVICEFOLDER",&n);assert(it && i<n);return it[i].record;}
/* One tap on the vertical stick; the selector's move latch swallows the first tap after a move. */
static int latched;
static void move_down(dw4_hubruntime *h){if(latched){step(h,DOWN,0);idle(h,70);}step(h,DOWN,0);idle(h,70);latched=1;}

/* kind/record of the item under test; filler rows come first so the row can be reached by moving down. */
static void convert(dw4_mount *mount,const dw4_hubruntime_source *source,const char *label,int kind,int32_t record,
    size_t filler,int32_t bit,int32_t level,int answer,const char *shot)
{
    dw4_hubruntime *h=boot_central(mount,source);
    dw4_property_folder *f=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);
    dw4_item_record items[4];size_t n=0;
    for(size_t i=0;i<filler;i++)items[n++]=(dw4_item_record){.kind=0,.record=1+(int32_t)i};
    items[n++]=(dw4_item_record){.kind=kind,.record=record};
    fixture(f,items,n,bit,level);
    int32_t before=record_at(f,filler);
    enter_cnos(h);
    latched=0;for(size_t i=0;i<filler;i++)move_down(h);
    idle(h,60);if(shot)draw_frame(h,shot);
    press(h,0x4000); /* choose the unknown item */
    if(bit<DW4_CNOS_PRICE) {
        assert(wait_text(h,"STWINFONT29","font000",900)); /* the insufficient-BIT notice (1451) */
        assert(number(f,"BIT")==bit && record_at(f,filler)==before);
        idle(h,60);press(h,0x4000);
        assert(wait_gone(h,"STWINFONT29","font000",600));idle(h,60);
        assert(number(f,"BIT")==bit && record_at(f,filler)==before);
        leave_service(h);
        printf("hub CNOS %s: insufficient BIT notice refuses without charging or changing the item\n",label);
        dw4_hubruntime_close(h);return;
    }
    assert(wait_text(h,"STWINFONT29","font000",900) && !has_text(h,"STWINFONT29","font001")); /* confirmation (1452) */
    assert(wait_gone(h,"STWINFONT29","font100",120)); /* the list prompt is hidden */
    assert(number(f,"BIT")==bit && record_at(f,filler)==before); /* asking spends nothing */
    idle(h,60);press(h,0x4000);
    assert(wait_text(h,"STWINFONT29","font001",900)); /* yes / no (1453) */
    idle(h,60);
    if(answer)down(h);
    press(h,0x4000);
    if(!answer) {
        unsigned k=0;for(;k<600 && number(f,"BIT")==bit;k++)step(h,0,0);
        assert(k<600 && number(f,"BIT")==bit-DW4_CNOS_PRICE);
        assert(allowed(dw4_hubruntime_databases(h),kind,level,before,record_at(f,filler)));
        assert(count_of(f)==n);
        printf("hub CNOS %s: record %d -> %d for tier %d, BIT %d -> %d\n",label,before,record_at(f,filler),tier_of(level),bit,number(f,"BIT"));
    }else {
        idle(h,200);
        assert(number(f,"BIT")==bit && record_at(f,filler)==before);
        printf("hub CNOS %s: declining leaves BIT and the item unchanged\n",label);
    }
    /* Either answer returns to the list; cancelling it closes the service and restores control. */
    assert(wait_text(h,"STWINFONT14","font000",900));idle(h,90);
    leave_service(h);
    assert(number(f,"BIT")==(answer?bit:bit-DW4_CNOS_PRICE));
    dw4_hubruntime_close(h);
}
/* A disabled row is not selectable and an empty list can only be cancelled. */
static void unselectable(dw4_mount *mount,const dw4_hubruntime_source *source,const char *label,size_t n)
{
    dw4_hubruntime *h=boot_central(mount,source);
    dw4_property_folder *f=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);
    const dw4_item_record items[2]={{.kind=0,.record=1},{.kind=3,.record=1}};
    fixture(f,items,n,1000,150);
    enter_cnos(h);
    idle(h,60);press(h,0x4000); /* Cross on a disabled row (or nothing) does nothing */
    idle(h,200);
    assert(!has_text(h,"STWINFONT29","font001") && !has_text(h,"TALKFONT02",NULL)); /* no yes/no dialog opened */
    assert(number(f,"BIT")==1000 && count_of(f)==n);
    if(n)assert(record_at(f,0)==1);
    leave_service(h);
    assert(number(f,"BIT")==1000 && count_of(f)==n);
    printf("hub CNOS %s: nothing selectable, Cross does nothing and cancel restores control\n",label);
    dw4_hubruntime_close(h);
}
int main(int argc,char **argv)
{
    capture_dir=argc>2?argv[2]:NULL;(void)text_value;
    dw4_mount mount;assert(!dw4_mount_open(&mount,argc>1?argv[1]:"../local/extracted"));
    dw4_playerrecords *players=dw4_playerrecords_open();dw4_be_state state;dw4_be_init(&state);
    struct boot host={players,dw4_scriptservices_open()};assert(players && host.sd);
    assert(dw4_scriptservices_register(host.sd,0,"GAMERAM",NULL,-1,1,dw4_playerrecords_service,players));
    dw4_scriptengine *e=dw4_scriptengine_open(&state,binding,&host);dw4_filelist *f=dw4_filelist_open(&mount);assert(e && f);
    dw4_scriptengine_filelist(e,f);
    assert(!dw4_filelist_begin(f,e,"stagIS10",1));assert(!dw4_filelist_shared(f));
    dw4_stageobjects *objects=dw4_stageobjects_open();assert(objects);
    assert(!dw4_filelist_route_assets(f,dw4_stageobjects_route,objects));assert(!dw4_filelist_bind_layers(f,dw4_stageobjects_bind_layers,objects));
    char error[512];dw4_databases *db=dw4_databases_open(objects,error,sizeof error);assert(db);
    assert(!dw4_playerrecords_create(players,db,0,"p_dorumon","HubCnos",error,sizeof error));
    dw4_hubruntime_source initial={players,&state,NULL,0};
    frame=0;convert(&mount,&initial,"weapon",0,276,0,1000,150,0,"cnos-list");
    frame=0;convert(&mount,&initial,"weapon (declined)",0,276,0,1000,150,1,NULL);
    frame=0;convert(&mount,&initial,"armor1 (second row)",1,31,1,600,450,0,NULL);
    frame=0;convert(&mount,&initial,"armor2",2,44,0,300,5,0,NULL);
    frame=0;convert(&mount,&initial,"weapon (BIT 299)",0,276,0,299,150,0,NULL);
    frame=0;unselectable(&mount,&initial,"ordinary equipment and a chip",2);
    frame=0;unselectable(&mount,&initial,"empty inventory",0);
    dw4_databases_close(db);dw4_stageobjects_close(objects);dw4_scriptengine_close(e);dw4_filelist_close(f);
    dw4_scriptservices_close(host.sd);dw4_playerrecords_close(players);dw4_mount_close(&mount);
    puts("hub cnos: NPC reach, item list, confirmation, 300 BIT conversion, refusals and restored control pass");
    return 0;
}
