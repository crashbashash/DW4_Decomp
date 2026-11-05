/* NPC bank (SUBWND BANK, retail beNDMWShopCtrl30 / ShopCtrlEditBit) through the normal prepared
 * Central hub runtime. Headless. The Digi-Elf is reached by the live Cross probe and the original
 * script chain (hit_n_digilff -> n_digilff_00 -> prompt -> bankshop.lua -> SUBWND GENERATE BANK);
 * menus, digit editing and the item list run the native windows over the original text and models.
 * Fixtures are limited to BIT/BANKBIT balances and the DEVICEFOLDER/BANKDEVICE item lists. */
#include "hubtest.h"
/* A tap is one stick edge. The selector keeps a move latch that only clears on an input frame after
 * the cursor animation, so the first cursor tap after a move is consumed (faithful to retail). */
static int latched;
static void tap(dw4_hubruntime *h,uint32_t analog){step(h,analog,0);idle(h,analog==8 || analog==2?70:8);}
enum {UP=1,RIGHT=2,DOWN=4,LEFT=8};
static void move_cursor(dw4_hubruntime *h,uint32_t dir){if(latched)tap(h,dir);tap(h,dir);latched=1;}
static void edit_tap(dw4_hubruntime *h,uint32_t dir){tap(h,dir);latched=0;}
/* Talk to Central's bank Digi-Elf, accept the first prompt entry and wait for the first menu. */
static void enter_bank(dw4_hubruntime *h)
{
    const dw4_modelctrl *npc=find(dw4_hubruntime_models(h),"n_digilff",0);assert(npc);
    assert(talk_to(h,npc));
    unsigned k=0;
    for(;k<3000 && !(has_text(h,"TALKFONT02","font01") && has_text(h,"TALKFONT02","font02"));k++)step(h,0,k%45==44?0x4000:0);
    assert(k<3000);
    idle(h,60);press(h,0x4000);
    assert(wait_text(h,"STWINFONT29","font002",900) && dw4_hubruntime_status_active(h)==2);
    idle(h,60);
}
/* Choose a row of the current menu. */
static void pick(dw4_hubruntime *h,unsigned entry)
{
    idle(h,60);for(unsigned i=0;i<entry;i++)down(h);press(h,0x4000);idle(h,90);
}
static void fixture_items(dw4_property_folder *f,const dw4_item_record *items,size_t n)
{
    static const int32_t none[5]={-1,-1,-1,-1,-1};
    assert(!dw4_property_set_items(f,"DEVICEFOLDER",items,n));
    assert(!dw4_property_set_array(f,"POWERSOCKETREF",none,3) && !dw4_property_set_array(f,"POWERPOCKETREF",none,5) &&
           !dw4_property_set_array(f,"MAINSLOTREF",none,1) && !dw4_property_set_array(f,"MAINPOCKETREF",none,5) &&
           !dw4_property_set_array(f,"SUBSLOTREF",none,1));
}
static size_t count(dw4_property_folder *f,const char *key){size_t n;assert(!dw4_property_item_count(f,key,&n));return n;}
static void expect_digits(dw4_hubruntime *h,const char *font_format,const char *want)
{
    /* want is most-significant first; font index 0 is the ones place. */
    size_t n=strlen(want);
    for(size_t i=0;i<7;i++) {
        char font[16];snprintf(font,sizeof font,font_format,(int)i);
        if(i<n) {
            const char *v=text_value(h,"STWINFONT25",font);
            if(!v || v[0]!=want[n-1-i] || v[1]) {
                fprintf(stderr,"digit %s expected '%c' got '%s'; shown:",font,want[n-1-i],v?v:"(hidden)");
                for(int k=0;k<7;k++){char g[16];snprintf(g,sizeof g,font_format,k);const char *t=text_value(h,"STWINFONT25",g);fprintf(stderr," %s=%s",g,t?t:"-");}
                fputc('\n',stderr);
            }
            assert(v && v[0]==want[n-1-i] && !v[1]);
        }else assert(!has_text(h,"STWINFONT25",font));
    }
}
/* Open the money editor: withdraw selects the second first-menu entry. */
static dw4_hubruntime *open_editor(dw4_mount *mount,const dw4_hubruntime_source *source,int withdraw,int32_t bit,int32_t bank)
{
    dw4_hubruntime *h=boot_central(mount,source);
    dw4_property_folder *f=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);
    assert(!dw4_property_set_number(f,"BIT",bit) && !dw4_property_set_number(f,"BANKBIT",bank));
    enter_bank(h);
    pick(h,withdraw);pick(h,1);
    assert(wait_text(h,"STWINFONT25","font000",900) && wait_text(h,"STWINFONT36","font000",100) && wait_text(h,"STWINFONT36","font001",100));
    assert(has_text(h,"STWINFONT36","font002")==withdraw && has_text(h,"STWINFONT29","font100"));
    latched=0;idle(h,150);return h;
}
static void to_first_menu(dw4_hubruntime *h)
{
    assert(wait_text(h,"STWINFONT29","font002",900) && !has_text(h,"STWINFONT25","font000") && !has_text(h,"STWINFONT36","font000"));
    idle(h,60);
}
static void money_deposit(dw4_mount *mount,const dw4_hubruntime_source *source)
{
    dw4_hubruntime *h=open_editor(mount,source,0,5000,200);
    dw4_property_folder *f=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);
    expect_digits(h,"font%03d","0");expect_digits(h,"font01%d","200");assert(!has_text(h,"STWINFONT25","font020"));
    draw_frame(h,"bank-editor");
    for(int i=0;i<3;i++)edit_tap(h,UP);
    expect_digits(h,"font%03d","3");
    move_cursor(h,LEFT);expect_digits(h,"font%03d","03");
    edit_tap(h,UP);edit_tap(h,UP);expect_digits(h,"font%03d","23");
    move_cursor(h,LEFT);edit_tap(h,UP);expect_digits(h,"font%03d","123");
    edit_tap(h,DOWN);expect_digits(h,"font%03d","023");edit_tap(h,UP);expect_digits(h,"font%03d","123");
    assert(number(f,"BIT")==5000 && number(f,"BANKBIT")==200); /* editing spends nothing */
    press(h,0x4000);
    assert(wait_text(h,"STWINFONT29","font000",600) && !has_text(h,"STWINFONT25","font100"));
    assert(number(f,"BIT")==5000 && number(f,"BANKBIT")==200); /* the acknowledgement precedes the transfer */
    idle(h,60);press(h,0x4000);
    to_first_menu(h);
    assert(number(f,"BIT")==4877 && number(f,"BANKBIT")==323);
    leave_service(h);
    assert(number(f,"BIT")==4877 && number(f,"BANKBIT")==323);
    printf("hub BANK money: deposit digit editing, acknowledgement, atomic transfer, menu return and restored control pass\n");
    dw4_hubruntime_close(h);
}
static void money_withdraw(dw4_mount *mount,const dw4_hubruntime_source *source)
{
    dw4_hubruntime *h=open_editor(mount,source,1,9999900,500);
    dw4_property_folder *f=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);
    expect_digits(h,"font01%d","0");expect_digits(h,"font%03d","9999900");expect_digits(h,"font02%d","500");
    move_cursor(h,LEFT);move_cursor(h,LEFT);edit_tap(h,UP); /* +100 is clamped to min(bank, 9,999,999 - wallet) = 99 */
    expect_digits(h,"font01%d","099");
    edit_tap(h,UP);expect_digits(h,"font01%d","099");
    draw_frame(h,"bank-withdraw");
    press(h,0x4000);assert(wait_text(h,"STWINFONT29","font000",600));idle(h,60);press(h,0x4000);
    to_first_menu(h);
    assert(number(f,"BIT")==9999999 && number(f,"BANKBIT")==401);
    leave_service(h);
    printf("hub BANK money: withdraw is clamped by the bank balance and wallet room, then transfers and restores control\n");
    dw4_hubruntime_close(h);
}
static void money_clamp_cancel(dw4_mount *mount,const dw4_hubruntime_source *source)
{
    /* Deposit limit is the wallet (50); Circle and a zero amount both leave the balances alone. */
    dw4_hubruntime *h=open_editor(mount,source,0,50,0);
    dw4_property_folder *f=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);
    for(int i=0;i<6;i++)move_cursor(h,LEFT); /* leftmost digit */
    edit_tap(h,UP);expect_digits(h,"font%03d","0000050");
    edit_tap(h,DOWN);expect_digits(h,"font%03d","0000000");
    press(h,0x2000); /* cancel */
    to_first_menu(h);assert(number(f,"BIT")==50 && number(f,"BANKBIT")==0);
    pick(h,0);pick(h,1);assert(wait_text(h,"STWINFONT25","font000",900));idle(h,40);
    press(h,0x4000); /* confirm a zero amount: treated as cancel */
    to_first_menu(h);assert(number(f,"BIT")==50 && number(f,"BANKBIT")==0);
    leave_service(h);
    printf("hub BANK money: limit clamp, cancel and zero-amount confirmation change nothing\n");
    dw4_hubruntime_close(h);
}
/* ---- items ---- */
static dw4_hubruntime *open_items(dw4_mount *mount,const dw4_hubruntime_source *source,int withdraw,
    const dw4_item_record *inv,size_t ninv,const dw4_item_record *bank,size_t nbank,dw4_property_folder **out)
{
    dw4_hubruntime *h=boot_central(mount,source);
    dw4_property_folder *f=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);
    fixture_items(f,inv,ninv);assert(!dw4_property_set_items(f,"BANKDEVICE",bank,nbank));
    enter_bank(h);pick(h,withdraw);pick(h,0);*out=f;return h;
}
static void items_flow(dw4_mount *mount,const dw4_hubruntime_source *source)
{
    const dw4_item_record chips[2]={{.kind=3,.record=1},{.kind=3,.record=2}};
    dw4_property_folder *f;
    dw4_hubruntime *h=open_items(mount,source,0,chips,2,NULL,0,&f);
    assert(wait_text(h,"STWINFONT14","font000",900) && wait_text(h,"STWINFONT14","font001",100) && has_text(h,"STWINFONT29","font100"));
    assert(has_text(h,"STWINFONT13","font000") && !has_text(h,"STWINFONT14","font002"));
    idle(h,60);draw_frame(h,"bank-items");
    press(h,0x4000); /* deposit the first chip */
    unsigned k=0;for(;k<600 && count(f,"BANKDEVICE")==0;k++)step(h,0,0);
    assert(k<600 && count(f,"DEVICEFOLDER")==1 && count(f,"BANKDEVICE")==1);
    size_t n;assert(dw4_property_items(f,"BANKDEVICE",&n)[0].record==1 && dw4_property_items(f,"DEVICEFOLDER",&n)[0].record==2);
    assert(wait_gone(h,"STWINFONT14","font001",600) && has_text(h,"STWINFONT14","font000"));idle(h,90);
    press(h,0x2000); /* cancel the list */
    to_first_menu(h);assert(!has_text(h,"STWINFONT29","font100") && !has_text(h,"STWINFONT14","font000"));
    /* Withdraw it again; emptying the bank shows the original notice before the list closes. */
    pick(h,1);pick(h,0);
    assert(wait_text(h,"STWINFONT14","font000",900));idle(h,60);
    press(h,0x4000);
    k=0;for(;k<600 && count(f,"BANKDEVICE")!=0;k++)step(h,0,0);
    assert(k<600 && count(f,"DEVICEFOLDER")==2 && dw4_property_items(f,"DEVICEFOLDER",&n)[1].record==1);
    assert(wait_gone(h,"STWINFONT29","font100",600));idle(h,120); /* prompt hidden, notice shown */
    press(h,0x4000);
    to_first_menu(h);assert(!has_text(h,"STWINFONT14","font000"));
    leave_service(h);
    printf("hub BANK items: deposit, cancel, withdraw to empty, notice and restored control pass\n");
    dw4_hubruntime_close(h);
}
static void items_refusals(dw4_mount *mount,const dw4_hubruntime_source *source)
{
    dw4_property_folder *f;dw4_item_record fill[96];size_t n;
    for(unsigned i=0;i<96;i++)fill[i]=(dw4_item_record){.kind=3,.record=1+(int32_t)(i%3)};
    /* Empty bank: withdrawing shows the notice immediately and returns to the first menu. */
    dw4_hubruntime *h=boot_central(mount,source);
    f=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);
    fixture_items(f,fill,2);assert(!dw4_property_set_items(f,"BANKDEVICE",NULL,0));
    enter_bank(h);pick(h,1);pick(h,0);
    assert(wait_text(h,"STWINFONT29","font000",900) && !has_text(h,"STWINFONT14","font000"));
    idle(h,60);press(h,0x4000);to_first_menu(h);
    assert(count(f,"DEVICEFOLDER")==2 && count(f,"BANKDEVICE")==0);
    leave_service(h);dw4_hubruntime_close(h);
    /* Full bank: the deposit is refused with its notice and nothing moves. */
    frame=0;h=open_items(mount,source,0,fill,2,fill,96,&f);
    assert(wait_text(h,"STWINFONT14","font000",900));idle(h,60);press(h,0x4000);
    assert(wait_gone(h,"STWINFONT29","font100",600));idle(h,120);
    assert(count(f,"DEVICEFOLDER")==2 && count(f,"BANKDEVICE")==96);
    press(h,0x4000);to_first_menu(h);
    leave_service(h);dw4_hubruntime_close(h);
    /* Full inventory: the withdrawal is refused with its notice and nothing moves. */
    frame=0;h=open_items(mount,source,1,fill,36,fill,2,&f);
    assert(wait_text(h,"STWINFONT14","font000",900));idle(h,60);press(h,0x4000);
    assert(wait_gone(h,"STWINFONT29","font100",600));idle(h,120);
    assert(count(f,"DEVICEFOLDER")==36 && count(f,"BANKDEVICE")==2 && dw4_property_items(f,"BANKDEVICE",&n)[0].record==1);
    press(h,0x4000);to_first_menu(h);
    leave_service(h);dw4_hubruntime_close(h);
    printf("hub BANK items: empty bank, full bank and full inventory notices refuse without changing records\n");
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
    char error[512];dw4_databases *db=dw4_databases_open(objects,error,sizeof error);assert(db);
    assert(!dw4_playerrecords_create(players,db,0,"p_dorumon","HubBank",error,sizeof error));
    dw4_hubruntime_source initial={players,&state,NULL,0};
    frame=0;money_deposit(&mount,&initial);
    frame=0;money_withdraw(&mount,&initial);
    frame=0;money_clamp_cancel(&mount,&initial);
    frame=0;items_flow(&mount,&initial);
    frame=0;items_refusals(&mount,&initial);
    dw4_databases_close(db);dw4_stageobjects_close(objects);dw4_scriptengine_close(e);dw4_filelist_close(f);
    dw4_scriptservices_close(host.sd);dw4_playerrecords_close(players);dw4_mount_close(&mount);
    puts("hub bank: NPC reach, menus, money editor, item list, capacity refusals and restored control pass");
    return 0;
}
