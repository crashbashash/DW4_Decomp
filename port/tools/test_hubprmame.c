/* The disk-collector Prmame (Central n_prmame[0], stagML12) through the normal prepared hub runtime.
 * Headless. The NPC is reached by the live Cross probe and runs the original script chain
 * (hit_n_prmame -> n_prmame_00). It calls SYSctlDiskFolder("ISMAX") on the disk-11 stack, and once
 * that stack is full and the player accepts its prompt (bML01055 -> the prize script) it clears nine
 * disks with SYSctlDiskFolder("CLR") and adds equipment with SYSctlDeviceFolder("SET"). Both engine
 * calls are native services over the same transactions as the shops. Fixtures: the disk-11 count
 * (DISKFOLDER) and the progress flags the script itself would have set earlier. */
#include "hubtest.h"
static int flag(dw4_playerrecords *p,int32_t n)
{
    dw4_script_value a={DW4_SCRIPT_NUMBER,n,NULL,0},r;char e[256];
    assert(!dw4_playerrecords_call(p,"FLGisOn",&a,1,&r,e,sizeof e));return (int)r.number;
}
static void set_flag(dw4_playerrecords *p,int32_t n,int32_t v)
{
    dw4_script_value a[2]={{DW4_SCRIPT_NUMBER,n,NULL,0},{DW4_SCRIPT_NUMBER,v,NULL,0}},r;char e[256];
    assert(!dw4_playerrecords_call(p,"FLGset",a,2,&r,e,sizeof e));
}
static int32_t disk_count(dw4_property_folder *f,int32_t record)
{
    size_t n;const dw4_item_record *v=dw4_property_items(f,"DISKFOLDER",&n);assert(v && n==12);
    for(size_t i=0;i<n;i++)if(v[i].record==record)return v[i].revision;
    assert(0);return -1;
}
static void set_disk(dw4_property_folder *f,int32_t record,int32_t count)
{
    size_t n;const dw4_item_record *v=dw4_property_items(f,"DISKFOLDER",&n);assert(v && n==12);
    dw4_item_record out[12];memcpy(out,v,sizeof out);
    for(size_t i=0;i<12;i++)if(out[i].record==record)out[i].revision=count;
    assert(!dw4_property_set_items(f,"DISKFOLDER",out,12));
}
static int has_dialogue(dw4_hubruntime *h)
{return has_text(h,"TALKFONT01",NULL) || has_text(h,"TALKFONT02",NULL) || has_text(h,"TALKFONT03",NULL);}
/* Talk to the NPC and advance its pages with Cross (only while control is withheld) until the
 * dialogue is over and control is back. Returns 1 when a dialogue ran to its end. */
static int talk_through(dw4_hubruntime *h,const dw4_modelctrl *npc)
{
    assert(talk_to(h,npc));
    unsigned quiet=0;int talked=0;
    for(unsigned k=0;k<4500;k++){
        step(h,0,(!control(h) && k%45==44)?0x4000:0);
        if(has_dialogue(h))talked=1;
        quiet=(talked && control(h) && !has_dialogue(h))?quiet+1:0;
        if(quiet>150)return 1;
    }
    return 0;
}
static size_t device_count(dw4_property_folder *f){size_t n;assert(!dw4_property_item_count(f,"DEVICEFOLDER",&n));return n;}
static dw4_item_record device_at(dw4_property_folder *f,size_t i)
{size_t n;const dw4_item_record *v=dw4_property_items(f,"DEVICEFOLDER",&n);assert(v && i<n);return v[i];}
static void fill_inventory(dw4_property_folder *f,size_t count)
{
    static const int32_t none[5]={-1,-1,-1,-1,-1};dw4_item_record items[36];
    for(size_t i=0;i<count;i++)items[i]=(dw4_item_record){0,269,0,0,0};
    assert(!dw4_property_set_items(f,"DEVICEFOLDER",items,count));
    assert(!dw4_property_set_array(f,"POWERSOCKETREF",none,3) && !dw4_property_set_array(f,"POWERPOCKETREF",none,5) &&
           !dw4_property_set_array(f,"MAINSLOTREF",none,1) && !dw4_property_set_array(f,"MAINPOCKETREF",none,5) &&
           !dw4_property_set_array(f,"SUBSLOTREF",none,1));
}
struct kit {dw4_mount *mount;const dw4_hubruntime_source *source;};
/* One fresh Central visit. Fixtures are only the stack count and the progress flags the script itself
 * would have set earlier; everything else is produced by the running script. */
static dw4_hubruntime *visit(struct kit *k,int32_t disk,int32_t f392,int32_t f393,int32_t f405,size_t inventory,
    dw4_playerrecords **records,dw4_property_folder **pf,const dw4_modelctrl **npc)
{
    frame=0;dw4_hubruntime *h=boot_central(k->mount,k->source);
    *records=dw4_hubruntime_records(h);*pf=dw4_playerrecords_get(*records,"GETPLAYER",0);
    *npc=find(dw4_hubruntime_models(h),"n_prmame",0);assert(*npc);
    set_flag(*records,392,f392);set_flag(*records,393,f393);set_flag(*records,405,f405);
    set_disk(*pf,11,disk);if(inventory)fill_inventory(*pf,inventory);
    return h;
}
int main(int argc,char **argv)
{
    capture_dir=argc>2?argv[2]:NULL;(void)text_value;(void)draw_frame;
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
    assert(!dw4_playerrecords_create(players,db,0,"p_dorumon","HubPrm",error,sizeof error));
    dw4_hubruntime_source initial={players,&state,NULL,0};
    struct kit kit={&mount,&initial};dw4_playerrecords *r;dw4_property_folder *pf;const dw4_modelctrl *npc;dw4_hubruntime *h;
    /* First meeting: the introduction runs and sets flag 405; nothing is given or taken. */
    h=visit(&kit,5,0,0,0,0,&r,&pf,&npc);size_t before=device_count(pf);
    assert(flag(r,405)==0 && flag(r,935)==1 && talk_through(h,npc));
    assert(flag(r,405)==1 && flag(r,392)==0 && disk_count(pf,11)==5 && device_count(pf)==before && control(h));
    dw4_hubruntime_close(h);
    printf("hub Prmame: first meeting sets 405 and changes nothing\n");
    /* Stack not full: ISMAX answers false, the not-full speech runs and the folder is untouched. */
    h=visit(&kit,8,0,0,1,0,&r,&pf,&npc);before=device_count(pf);
    assert(talk_through(h,npc) && flag(r,921)==0 && flag(r,392)==0 && disk_count(pf,11)==8 && device_count(pf)==before && control(h));
    dw4_hubruntime_close(h);
    printf("hub Prmame: a stack of eight is refused, nothing changes\n");
    /* Full stack: ISMAX true, then CLR 9 and a weapon (200, revision 10, pocket 1) is added. */
    h=visit(&kit,9,0,0,1,0,&r,&pf,&npc);before=device_count(pf);
    assert(talk_through(h,npc));
    assert(flag(r,921)==1 && flag(r,392)==1 && flag(r,393)==0 && disk_count(pf,11)==0 && device_count(pf)==before+1 && control(h));
    dw4_item_record gift=device_at(pf,before);
    assert(gift.kind==0 && gift.record==200 && gift.revision==10 && gift.pocket==1 && !gift.equipped);
    dw4_hubruntime_close(h);
    printf("hub Prmame: full stack is cleared (9 disks) and weapon 200 rev 10 pocket 1 is added\n");
    /* Second prize of the chain: flag 392 already set -> armor1 10, revision 20, pocket 1. */
    h=visit(&kit,9,1,0,1,0,&r,&pf,&npc);before=device_count(pf);
    assert(talk_through(h,npc));
    assert(flag(r,393)==1 && flag(r,394)==0 && disk_count(pf,11)==0 && device_count(pf)==before+1);
    gift=device_at(pf,before);assert(gift.kind==1 && gift.record==10 && gift.revision==20 && gift.pocket==1);
    dw4_hubruntime_close(h);
    printf("hub Prmame: second prize armor1 10 rev 20 pocket 1\n");
    /* A full device folder: SYSctlDeviceFolder ISMAX answers true, so no prize and no CLR. */
    h=visit(&kit,9,0,0,1,36,&r,&pf,&npc);
    assert(device_count(pf)==36 && talk_through(h,npc));
    assert(flag(r,392)==0 && disk_count(pf,11)==9 && device_count(pf)==36 && control(h));
    dw4_hubruntime_close(h);
    printf("hub Prmame: a full device folder blocks the prize and keeps the disks\n");
    printf("hub Prmame: SYSctlDiskFolder/SYSctlDeviceFolder services, original dialogue, prizes and restored control pass\n");
    dw4_databases_close(db);dw4_stageobjects_close(objects);dw4_scriptengine_close(e);dw4_filelist_close(f);
    dw4_scriptservices_close(host.sd);dw4_playerrecords_close(players);dw4_mount_close(&mount);
    return 0;
}
