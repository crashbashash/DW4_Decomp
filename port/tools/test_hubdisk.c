/* Digi-Disk shop (SUBWND DISK, retail beNDMWShopCtrl50 and its sell branch) through the normal prepared Shop
 * hub runtime. Headless. The Digi-Elf is reached by the live Cross probe and the original script chain
 * (hit_n_digilff -> n_digilff_00 -> prompt -> diskshop.lua -> SUBWND GENERATE DISK); menus, lists and the
 * quantity selector run the native windows over the original text and models. Fixtures are limited to the
 * BIT balance, DISKFOLDER quantities and the DEVICEFOLDER item list. */
#include "hubtest.h"
static int latched;
enum {UP=1,RIGHT=2,DOWN=4,LEFT=8};
/* A tap is one stick edge; the selector keeps a move latch that clears on an input frame after the cursor
 * animation, so the first cursor tap after a move is consumed (faithful to retail). */
static void tap(dw4_hubruntime *h,uint32_t analog){step(h,analog,0);idle(h,70);}
static void move_cursor(dw4_hubruntime *h,uint32_t dir){if(latched)tap(h,dir);tap(h,dir);latched=1;}
static dw4_databases *db;
static dw4_hubruntime *boot_shop(dw4_mount *mount,const dw4_hubruntime_source *source)
{
    char error[512];
    dw4_hubruntime *h=dw4_hubruntime_prepare(mount,source,"stagML13",0,1,error,sizeof error);
    if(!h){fprintf(stderr,"prepare Shop: %s\n",error);assert(0);}
    unsigned t=0;
    for(;t<2600;t++){step(h,0,t%10==0?0x4000:0);if(t>30 && control(h) && dw4_lobby_intro_done(dw4_hubruntime_world(h)))break;}
    assert(t<2600);idle(h,60);latched=0;return h;
}
static void enter_disk(dw4_hubruntime *h)
{
    const dw4_modelctrl *npc=find(dw4_hubruntime_models(h),"n_digilff",0);assert(npc);
    assert(talk_to(h,npc));
    unsigned k=0;
    for(;k<3000 && !(has_text(h,"TALKFONT02","font01") && has_text(h,"TALKFONT02","font02"));k++)step(h,0,k%45==44?0x4000:0);
    assert(k<3000);
    idle(h,60);press(h,0x4000);
    assert(wait_text(h,"STWINFONT29","font002",900) && dw4_hubruntime_status_active(h)>0);
    idle(h,60);latched=0;
}
static void pick(dw4_hubruntime *h,unsigned entry)
{idle(h,60);for(unsigned i=0;i<entry;i++){down(h);}press(h,0x4000);idle(h,90);}
static const dw4_database *con(void){return dw4_databases_get(db,"conItem");}
static int32_t hanbai(int row){int32_t v;assert(dw4_database_number(con(),row,"HANBAI",&v)>=0);return v;}
static int32_t kaitori(int row){int32_t v;assert(dw4_database_number(con(),row,"KAITORI",&v)>=0);return v;}
static dw4_property_folder *folder(dw4_hubruntime *h){return dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);}
static void set_bit(dw4_hubruntime *h,int32_t v){assert(!dw4_property_set_number(folder(h),"BIT",v));}
static int32_t bit(dw4_hubruntime *h){return number(folder(h),"BIT");}
static void set_disk(dw4_hubruntime *h,int row,int32_t quantity)
{
    size_t n;const dw4_item_record *v=dw4_property_items(folder(h),"DISKFOLDER",&n);assert(v && n==12);
    dw4_item_record out[12];memcpy(out,v,sizeof out);out[row].revision=quantity;
    assert(!dw4_property_set_items(folder(h),"DISKFOLDER",out,12));
}
static int32_t disk(dw4_hubruntime *h,int row)
{size_t n;const dw4_item_record *v=dw4_property_items(folder(h),"DISKFOLDER",&n);assert(v && n==12);return v[row].revision;}
static void zero_disks(dw4_hubruntime *h){for(int i=0;i<12;i++)set_disk(h,i,0);}
static void set_devices(dw4_hubruntime *h,const dw4_item_record *items,size_t n)
{
    static const int32_t none[5]={-1,-1,-1,-1,-1};
    dw4_property_folder *f=folder(h);
    assert(!dw4_property_set_items(f,"DEVICEFOLDER",items,n));
    assert(!dw4_property_set_array(f,"POWERSOCKETREF",none,3) && !dw4_property_set_array(f,"POWERPOCKETREF",none,5) &&
           !dw4_property_set_array(f,"MAINSLOTREF",none,1) && !dw4_property_set_array(f,"MAINPOCKETREF",none,5) &&
           !dw4_property_set_array(f,"SUBSLOTREF",none,1));
}
static size_t devices(dw4_hubruntime *h){size_t n;assert(!dw4_property_item_count(folder(h),"DEVICEFOLDER",&n));return n;}
static void leave(dw4_hubruntime *h)
{
    idle(h,60);press(h,0x2000);
    unsigned k=0;for(;k<900 && dw4_hubruntime_status_active(h);k++)step(h,0,0);
    assert(k<900 && !dw4_hubruntime_status_active(h));
    unsigned e=0;for(;e<200 && (!control(h) || dw4_hubruntime_input_state(h)->disabled);e++)step(h,0,0);
    assert(e<200 && control(h) && !dw4_hubruntime_travel(h)->pending);
}
/* text_value reuses one buffer, so copy each result. Names are compared over their leading ASCII run (the
 * database strings continue with double-byte glyphs that the text layer stores as glyph codes). */
static void value(dw4_hubruntime *h,const char *group,const char *name,char out[64])
{const char *v=text_value(h,group,name);snprintf(out,64,"%s",v?v:"");}
static void expect_list(dw4_hubruntime *h)
{
    assert(wait_text(h,"STWINFONT17","font009",900));idle(h,70);
    for(int i=0;i<10;i++) {
        char font[16],price[16],shown[64],cost[64];snprintf(font,sizeof font,"font%03d",i);snprintf(price,sizeof price,"%d",hanbai(i));
        const char *name=dw4_database_string(con(),i,"NAME");
        value(h,"STWINFONT14",font,shown);value(h,"STWINFONT17",font,cost);
        size_t ascii=0;while(((unsigned char)name[ascii])>0 && ((unsigned char)name[ascii])<0x80)ascii++;
        if(strncmp(shown,name,ascii) || strcmp(cost,price))
            fprintf(stderr,"row %d shows '%s' '%s', want '%s' '%s'\n",i,shown,cost,name,price);
        assert(!strncmp(shown,name,ascii) && !strcmp(cost,price) && ascii>0);
    }
    assert(has_text(h,"STWINFONT13","font000"));
}
/* ---- buy ---- */
static void buy_flow(dw4_mount *mount,const dw4_hubruntime_source *source,const char *capture)
{
    dw4_hubruntime *h=boot_shop(mount,source);
    assert(hanbai(0)>0);
    zero_disks(h);set_bit(h,10000);
    int32_t price=hanbai(0);
    enter_disk(h);
    pick(h,0);expect_list(h);
    if(capture)draw_frame(h,"disklist");
    /* Accept a quantity of two. */
    pick(h,0);
    assert(wait_text(h,"STWINFONT32","font010",600));idle(h,70);
    assert(!strcmp(text_value(h,"STWINFONT32","font010"),"1"));
    char want[16];snprintf(want,sizeof want,"%d",price);
    assert(!strcmp(text_value(h,"STWINFONT32","font021"),want));
    move_cursor(h,UP);
    assert(!strcmp(text_value(h,"STWINFONT32","font010"),"2"));
    snprintf(want,sizeof want,"%d",2*price);
    assert(!strcmp(text_value(h,"STWINFONT32","font021"),want));
    assert(bit(h)==10000 && disk(h,0)==0);
    if(capture)draw_frame(h,"diskquantity");
    pick(h,0);   /* quantity */
    pick(h,0);   /* confirm prompt */
    if(capture)draw_frame(h,"diskconfirm");
    pick(h,0);   /* yes */
    assert(bit(h)==10000-2*price && disk(h,0)==2);
    latched=0;
    /* Decline: quantity one, answer no. */
    assert(wait_text(h,"STWINFONT17","font009",600));
    pick(h,0);assert(wait_text(h,"STWINFONT32","font010",600));
    pick(h,0);pick(h,0);pick(h,1);
    assert(bit(h)==10000-2*price && disk(h,0)==2);
    /* Insufficient balance: notice, nothing changes. */
    set_bit(h,price-1);
    assert(wait_text(h,"STWINFONT17","font009",600));
    pick(h,0);assert(wait_text(h,"STWINFONT32","font010",600));
    pick(h,0);idle(h,90);
    assert(bit(h)==price-1 && disk(h,0)==2);
    pick(h,0); /* acknowledge */
    assert(wait_text(h,"STWINFONT17","font009",600));
    /* Nine held: notice before any quantity. */
    set_bit(h,10000);set_disk(h,0,9);
    pick(h,0);idle(h,90);pick(h,0);
    assert(bit(h)==10000 && disk(h,0)==9);
    assert(wait_text(h,"STWINFONT17","font009",600));
    /* Cancel the list, then the menu. */
    idle(h,60);press(h,0x2000);
    assert(wait_text(h,"STWINFONT29","font002",900));
    leave(h);
    assert(bit(h)==10000 && disk(h,0)==9);
    dw4_hubruntime_close(h);
    puts("hub DISK buy: price list, quantity, confirm, charge, decline, insufficient balance, nine held and restored control pass");
}
/* ---- sell ---- */
static int find_chip(int32_t *a,int32_t *b)
{
    const dw4_database *d=dw4_databases_get(db,"abChip");size_t rows=dw4_database_string_rows(d);int found=0;
    for(size_t r=0;r<rows && found<2;r++) {
        int32_t k;dw4_item_record it={.kind=3,.record=(int32_t)r};
        if(!dw4_statuscontent_item_string(db,&it,"NAME") || dw4_statuscontent_kaitori(db,&it,&k) || k<=0)continue;
        if(found==0)*a=(int32_t)r;else *b=(int32_t)r;found++;
    }
    return found==2;
}
static void sell_flow(dw4_mount *mount,const dw4_hubruntime_source *source,const char *capture)
{
    dw4_hubruntime *h=boot_shop(mount,source);
    int32_t ca,cb;assert(find_chip(&ca,&cb));
    int32_t pa,pb;dw4_item_record ia={.kind=3,.record=ca},ib={.kind=3,.record=cb};
    assert(!dw4_statuscontent_kaitori(db,&ia,&pa) && !dw4_statuscontent_kaitori(db,&ib,&pb));
    dw4_item_record items[2]={ia,ib};
    zero_disks(h);set_devices(h,items,2);set_bit(h,1000);
    enter_disk(h);
    pick(h,1);   /* sell */
    /* Only devices: the disk row is disabled, the device row is chosen. */
    idle(h,90);pick(h,0);
    assert(wait_text(h,"STWINFONT14","font000",900) && wait_text(h,"STWINFONT17","font000",100));idle(h,70);
    char want[16];snprintf(want,sizeof want,"%d",pa);
    assert(!strcmp(text_value(h,"STWINFONT17","font000"),want));
    if(capture)draw_frame(h,"disksell");
    pick(h,0);pick(h,0);pick(h,0); /* chip, notice, yes */
    assert(bit(h)==1000+pa && devices(h)==1);
    size_t n;const dw4_item_record *left=dw4_property_items(folder(h),"DEVICEFOLDER",&n);assert(n==1 && left[0].record==cb);
    latched=0;
    /* Give the player disks first: once the last chip is sold the sell menu reopens, with the device row disabled. */
    set_disk(h,0,3);
    pick(h,0);pick(h,0);pick(h,0); /* the other chip */
    assert(bit(h)==1000+pa+pb && devices(h)==0);
    idle(h,200);
    assert(wait_text(h,"STWINFONT29","font001",900));
    pick(h,1);   /* the disk list */
    assert(wait_text(h,"STWINFONT14","font000",900) && wait_text(h,"STWINFONT15","font000",100));idle(h,70);
    assert(!strcmp(text_value(h,"STWINFONT15","font000"),"3"));
    int32_t before=bit(h),unit=kaitori(0);
    pick(h,0);   /* disk 0 -> quantity */
    assert(wait_text(h,"STWINFONT30","font010",600));idle(h,70);
    assert(!strcmp(text_value(h,"STWINFONT30","font010"),"1"));
    move_cursor(h,UP);
    assert(!strcmp(text_value(h,"STWINFONT30","font010"),"2"));
    snprintf(want,sizeof want,"%d",2*unit);
    assert(!strcmp(text_value(h,"STWINFONT30","font021"),want));
    pick(h,0);pick(h,0);pick(h,0); /* quantity, notice, yes */
    assert(bit(h)==before+2*unit && disk(h,0)==1);
    /* Leave the disk list, the sell menu and the shop. */
    latched=0;idle(h,120);press(h,0x2000);idle(h,200);
    press(h,0x2000);idle(h,200);
    leave(h);
    assert(devices(h)==0 && disk(h,0)==1);
    dw4_hubruntime_close(h);
    puts("hub DISK sell: device list, KAITORI credit, item removal, disk quantity, credit and restored control pass");
}
static void nothing_to_sell(dw4_mount *mount,const dw4_hubruntime_source *source)
{
    dw4_hubruntime *h=boot_shop(mount,source);
    zero_disks(h);set_devices(h,NULL,0);set_bit(h,321);
    enter_disk(h);
    pick(h,1);   /* sell: the nothing-to-sell notice (0x628) */
    idle(h,200);pick(h,0);
    assert(wait_text(h,"STWINFONT29","font002",900)); /* back at the buy/sell menu */
    leave(h);
    assert(bit(h)==321);
    dw4_hubruntime_close(h);
    puts("hub DISK sell: empty inventory and disks show the notice and return to the menu");
}
int main(int argc,char **argv)
{
    capture_dir=argc>2?argv[2]:NULL;
    dw4_mount mount;assert(!dw4_mount_open(&mount,argc>1?argv[1]:"../local/extracted"));
    dw4_playerrecords *players=dw4_playerrecords_open();dw4_be_state state;dw4_be_init(&state);
    struct boot host={players,dw4_scriptservices_open()};assert(players && host.sd);
    assert(dw4_scriptservices_register(host.sd,0,"GAMERAM",NULL,-1,1,dw4_playerrecords_service,players));
    dw4_scriptengine *e=dw4_scriptengine_open(&state,binding,&host);dw4_filelist *f=dw4_filelist_open(&mount);assert(e && f);
    dw4_scriptengine_filelist(e,f);
    assert(!dw4_filelist_begin(f,e,"stagIS10",1));assert(!dw4_filelist_shared(f));
    dw4_stageobjects *objects=dw4_stageobjects_open();assert(objects);
    assert(!dw4_filelist_route_assets(f,dw4_stageobjects_route,objects));assert(!dw4_filelist_bind_layers(f,dw4_stageobjects_bind_layers,objects));
    char error[512];db=dw4_databases_open(objects,error,sizeof error);assert(db);
    assert(!dw4_playerrecords_create(players,db,0,"p_dorumon","HubDisk",error,sizeof error));
    dw4_hubruntime_source initial={players,&state,NULL,0};
    frame=0;buy_flow(&mount,&initial,capture_dir);
    frame=0;sell_flow(&mount,&initial,capture_dir);
    frame=0;nothing_to_sell(&mount,&initial);
    dw4_databases_close(db);dw4_stageobjects_close(objects);dw4_scriptengine_close(e);dw4_filelist_close(f);
    dw4_scriptservices_close(host.sd);dw4_playerrecords_close(players);dw4_mount_close(&mount);
    puts("hub disk: NPC reach, buy and sell windows, refusals and restored control pass");
    return 0;
}
