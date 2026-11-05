/* Weapon / armor / chip / junk shops (SUBWND WPU, APU, CHIP, JUNK: retail beNDMWShopDevice, beNDMWShopJunk and
 * beNDMWShopCtrlSales) through the normal prepared Shop hub runtime. Headless. Each NPC is reached by the live Cross
 * probe and the original script chain; menus, goods lists, confirmations and the sell branch run the native windows
 * over the original text and models. Fixtures are limited to BIT, XDATA, the DEVICEFOLDER list and the common
 * investment counter; the stock itself is produced by the retail selection from the hub's own tables. */
#include "hubtest.h"
#include "dw4/shopstock.h"
#include "dw4/equipshop.h"
static int latched;
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
enum {UP=1,RIGHT=2,DOWN=4,LEFT=8};
/* A tap is one stick edge; the selector keeps a move latch that clears on an input frame after the cursor
 * animation, so the first cursor tap after a move is consumed (faithful to retail). */
static void tap(dw4_hubruntime *h,uint32_t analog){step(h,analog,0);idle(h,70);}
static void move_cursor(dw4_hubruntime *h,uint32_t dir){if(latched)tap(h,dir);tap(h,dir);latched=1;}
static void edit_tap(dw4_hubruntime *h,uint32_t dir){tap(h,dir);latched=0;}
static void pick(dw4_hubruntime *h,unsigned entry)
{idle(h,60);for(unsigned i=0;i<entry;i++){down(h);}press(h,0x4000);idle(h,90);latched=0;}
static dw4_property_folder *folder(dw4_hubruntime *h){return dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);}
static dw4_property_folder *common(dw4_hubruntime *h){return dw4_playerrecords_get(dw4_hubruntime_records(h),"GETCOMMON",0);}
static void set_bit(dw4_hubruntime *h,int32_t v){assert(!dw4_property_set_number(folder(h),"BIT",v));}
static int32_t bit(dw4_hubruntime *h){return number(folder(h),"BIT");}
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
static const dw4_item_record *device(dw4_hubruntime *h,size_t i)
{size_t n;const dw4_item_record *v=dw4_property_items(folder(h),"DEVICEFOLDER",&n);assert(v && i<n);return v+i;}
static void set_investment(dw4_hubruntime *h,int32_t v)
{
    int32_t counters[16];size_t n;memcpy(counters,dw4_property_array(common(h),"COUNTER",&n),sizeof counters);assert(n==16);
    counters[1]=v;assert(!dw4_property_set_array(common(h),"COUNTER",counters,16));
}
static int32_t investment(dw4_hubruntime *h){size_t n;return dw4_property_array(common(h),"COUNTER",&n)[1];}
static void leave(dw4_hubruntime *h)
{
    idle(h,60);press(h,0x2000);
    unsigned k=0;for(;k<900 && dw4_hubruntime_status_active(h);k++)step(h,0,0);
    assert(k<900 && !dw4_hubruntime_status_active(h));
    unsigned e=0;for(;e<200 && (!control(h) || dw4_hubruntime_input_state(h)->disabled);e++)step(h,0,0);
    assert(e<200 && control(h) && !dw4_hubruntime_travel(h)->pending);
}
/* Reach a Digi-Elf by the live Cross probe and take its first answer; the main menu then lists three entries. */
static void enter(dw4_hubruntime *h,const char *name,int slot)
{
    const dw4_modelctrl *npc=find(dw4_hubruntime_models(h),name,slot);assert(npc);
    assert(talk_to(h,npc));
    unsigned k=0;
    for(;k<3000 && !(has_text(h,"TALKFONT02","font01") && has_text(h,"TALKFONT02","font02"));k++)step(h,0,k%45==44?0x4000:0);
    assert(k<3000);
    idle(h,60);press(h,0x4000);
    assert(wait_text(h,"STWINFONT29","font002",900) && dw4_hubruntime_status_active(h)>0);
    idle(h,60);latched=0;
}
/* text_value reuses one buffer, so copy each result. Names are compared over their leading ASCII run (the database
 * strings continue with double-byte glyphs that the text layer stores as glyph codes). */
static void value(dw4_hubruntime *h,const char *group,const char *name,char out[64])
{const char *v=text_value(h,group,name);snprintf(out,64,"%s",v?v:"");}
static int32_t price_of(dw4_hubruntime *h,const dw4_item_record *i)
{int32_t p;assert(!dw4_playerstats_item_price((void *)dw4_hubruntime_databases(h),i,0,&p));return p;}
static int32_t sell_of(dw4_hubruntime *h,const dw4_item_record *i)
{int32_t p;assert(!dw4_playerstats_item_price((void *)dw4_hubruntime_databases(h),i,1,&p));return p;}
static void expect_name(dw4_hubruntime *h,const char *font,const dw4_item_record *it)
{
    const char *name=dw4_statuscontent_item_string(dw4_hubruntime_databases(h),it,"NAME");assert(name);
    char shown[64],run[64];value(h,"STWINFONT14",font,shown);
    /* Equipment names start with a double-byte icon glyph; the shown text stores glyph codes, so compare the first
     * ASCII run of the database name inside the shown text. */
    size_t start=0;while(name[start] && ((unsigned char)name[start])>=0x80)start++;
    size_t n=0;while(name[start+n] && ((unsigned char)name[start+n])<0x80 && n+1<sizeof run){run[n]=name[start+n];n++;}
    run[n]=0;
    if(!n || !strstr(shown,run))fprintf(stderr,"\n%s shows '%s', want '%s'\n",font,shown,run);
    assert(n>0 && strstr(shown,run));
}
/* The goods list of one page: NAME and price per present slot, hidden rows past the list, page labels. */
static void expect_page(dw4_hubruntime *h,int mode,int page,int pages)
{
    dw4_shopstock *st=dw4_hubruntime_shopstock(h);size_t count;const dw4_item_record *list=dw4_shopstock_list(st,mode,&count);
    assert(list && wait_text(h,"STWINFONT17","font000",900));idle(h,70);
    for(int i=0;i<12;i++) {
        char font[16],cost[64];snprintf(font,sizeof font,"font%03d",i);
        size_t index=(size_t)page*12+i;
        int present=index<count && list[index].kind>=0;
        int rows=0;for(size_t j=0;j<12 && (size_t)page*12+j<count && list[(size_t)page*12+j].kind>=0;j++)rows++;
        if(i<rows){
            assert(present && has_text(h,"STWINFONT14",font));
            expect_name(h,font,list+index);
            char want[16];
            if(list[index].kind==3 && list[index].record==DW4_SHOPSTOCK_SOLD_OUT)snprintf(want,sizeof want,"----");
            else snprintf(want,sizeof want,"%d",price_of(h,list+index));
            value(h,"STWINFONT17",font,cost);
            if(strcmp(cost,want))fprintf(stderr,"page %d row %d price '%s', want '%s'\n",page,i,cost,want);
            assert(!strcmp(cost,want));
        }
    }
    char label[64];
    value(h,"STWINFONT30","font000",label);{char want[2]={(char)('1'+page),0};assert(!strcmp(label,want));}
    value(h,"STWINFONT30","font001",label);{char want[2]={(char)('0'+pages),0};assert(!strcmp(label,want));}
}
/* ---- shared helpers for the goods-list flows ---- */
/* Select the highlighted row, acknowledge the notice and answer the yes/no question (answer 0 = yes). */
static void buy_row(dw4_hubruntime *h,unsigned answer)
{pick(h,0);pick(h,0);pick(h,answer);}
static void expect_back_at_list(dw4_hubruntime *h){assert(wait_text(h,"STWINFONT17","font000",900));idle(h,70);}
static void cancel_list(dw4_hubruntime *h)
{idle(h,60);press(h,0x2000);assert(wait_text(h,"STWINFONT29","font002",900));latched=0;}

/* ---- WPU ---- */
static void wpu_flow(dw4_mount *mount,const dw4_hubruntime_source *source,const char *capture)
{
    dw4_hubruntime *h=boot_shop(mount,source);
    dw4_shopstock *st=dw4_hubruntime_shopstock(h);
    set_bit(h,100000);set_devices(h,NULL,0);
    enter(h,"n_digilfm",0);
    pick(h,0); /* Buy */
    expect_page(h,6,0,2); /* 24 present slots: two pages */
    assert(has_text(h,"STWINFONT13","font000"));
    if(capture)draw_frame(h,"wpu-list");
    dw4_item_record first=dw4_shopstock_list(st,6,NULL)[0];assert(first.kind==0);
    int32_t price=price_of(h,&first);assert(price>0);
    /* Decline at the question: nothing changes and the list returns. */
    buy_row(h,1);expect_back_at_list(h);
    assert(bit(h)==100000 && devices(h)==0 && dw4_shopstock_list(st,6,NULL)[0].kind==0);
    /* Not enough BIT: the notice refuses and the list returns. */
    set_bit(h,price-1);
    pick(h,0);pick(h,0);expect_back_at_list(h);
    assert(bit(h)==price-1 && devices(h)==0);
    /* A full DEVICEFOLDER refuses first. */
    set_bit(h,100000);
    {dw4_item_record full[36];for(int i=0;i<36;i++)full[i]=(dw4_item_record){.kind=3,.record=i};set_devices(h,full,36);}
    pick(h,0);pick(h,0);expect_back_at_list(h);
    assert(bit(h)==100000 && devices(h)==36 && dw4_shopstock_list(st,6,NULL)[0].kind==0);
    set_devices(h,NULL,0);
    /* Buy: the item object joins DEVICEFOLDER, the slot is sold out. */
    if(capture)draw_frame(h,"wpu-list-before-buy");
    pick(h,0);
    if(capture)draw_frame(h,"wpu-notice");
    pick(h,0);
    if(capture)draw_frame(h,"wpu-confirm");
    pick(h,0);
    assert(bit(h)==100000-price && devices(h)==1);
    const dw4_item_record *got=device(h,0);
    assert(got->kind==0 && got->record==first.record && got->revision==first.revision && got->pocket==first.pocket && !got->equipped);
    assert(dw4_shopstock_list(st,6,NULL)[0].kind==3 && dw4_shopstock_list(st,6,NULL)[0].record==DW4_SHOPSTOCK_SOLD_OUT);
    expect_back_at_list(h);
    assert(!strcmp(text_value(h,"STWINFONT17","font000"),"----"));
    cancel_list(h);
    /* Cancel the menu and the shop. */
    leave(h);
    assert(bit(h)==100000-price && devices(h)==1);
    dw4_hubruntime_close(h);
    puts("hub WPU buy: stock rows, decline, insufficient balance, full folder, purchase, sold-out slot and restored control pass");
}
static void wpu_sell(dw4_mount *mount,const dw4_hubruntime_source *source,const char *capture)
{
    dw4_hubruntime *h=boot_shop(mount,source);
    /* A weapon with an enhancement and a pocket grade sells for its KAITORI plus both surcharges. */
    dw4_item_record weapon={.kind=0,.record=0,.revision=2,.pocket=3};
    const dw4_database *wd=dw4_databases_get(dw4_hubruntime_databases(h),"weapon");int32_t k=0;
    for(int32_t r=0;r<300;r++)if(dw4_database_number(wd,r,"KAITORI",&k)==0 && k>0){weapon.record=r;break;}
    assert(k>0);
    int32_t base;assert(!dw4_playerstats_item_attribute((void *)dw4_hubruntime_databases(h),&weapon,"KAITORI",&base));
    int32_t want=sell_of(h,&weapon);assert(want==base+2*25+3000);
    dw4_item_record items[2]={weapon,{.kind=3,.record=1}};
    set_devices(h,items,2);set_bit(h,1000);
    enter(h,"n_digilfm",0);
    pick(h,1); /* Sell Item in Folder */
    idle(h,90);pick(h,0); /* devices (no disks to sell) */
    assert(wait_text(h,"STWINFONT14","font000",900) && wait_text(h,"STWINFONT17","font000",100));idle(h,70);
    char shown[64],cost[16];value(h,"STWINFONT17","font000",shown);snprintf(cost,sizeof cost,"%d",want);
    assert(!strcmp(shown,cost));
    if(capture)draw_frame(h,"wpu-sell");
    pick(h,0);pick(h,0);pick(h,0); /* item, notice, yes */
    assert(bit(h)==1000+want && devices(h)==1 && device(h,0)->kind==3);
    latched=0;idle(h,120);press(h,0x2000);idle(h,200); /* leave the device list */
    press(h,0x2000);idle(h,200); /* leave the sell menu */
    leave(h);
    assert(bit(h)==1000+want && devices(h)==1);
    dw4_hubruntime_close(h);
    puts("hub WPU sell: the shared sell branch credits KAITORI with enhancement and grade surcharges and restores control");
}

/* ---- APU ---- */
static void apu_flow(dw4_mount *mount,const dw4_hubruntime_source *source,const char *capture)
{
    dw4_hubruntime *h=boot_shop(mount,source);
    dw4_shopstock *st=dw4_hubruntime_shopstock(h);
    set_bit(h,100000);set_devices(h,NULL,0);
    enter(h,"n_digilff",1);
    pick(h,0);
    expect_page(h,7,0,2); /* blue armor in slots 0..11, yellow armor from 12; 21 present slots */
    if(capture)draw_frame(h,"apu-list");
    /* Turn to page two and back with the stick; the page label and the rows follow. */
    step(h,RIGHT,0);idle(h,90);
    expect_page(h,7,1,2);
    if(capture)draw_frame(h,"apu-page2");
    /* Buy the first yellow armor of page two. */
    dw4_item_record yellow=dw4_shopstock_list(st,7,NULL)[12];assert(yellow.kind==2);
    int32_t price=price_of(h,&yellow);
    buy_row(h,0);
    assert(bit(h)==100000-price && devices(h)==1);
    const dw4_item_record *got=device(h,0);
    assert(got->kind==2 && got->record==yellow.record && got->revision==yellow.revision && !got->equipped);
    assert(dw4_shopstock_list(st,7,NULL)[12].kind==3 && dw4_shopstock_list(st,7,NULL)[12].record==DW4_SHOPSTOCK_SOLD_OUT);
    expect_back_at_list(h);
    expect_page(h,7,1,2); /* the list returns to the page it was on, the bought slot now "Sold Out" */
    assert(!strcmp(text_value(h,"STWINFONT17","font000"),"----"));
    cancel_list(h);
    leave(h);
    dw4_hubruntime_close(h);
    puts("hub APU buy: blue/yellow armor stock, page turn, page label, purchase and sold-out slot pass");
}
/* ---- CHIP ---- */
static void chip_flow(dw4_mount *mount,const dw4_hubruntime_source *source,const char *capture)
{
    dw4_hubruntime *h=boot_shop(mount,source);
    dw4_shopstock *st=dw4_hubruntime_shopstock(h);
    set_bit(h,100000);set_devices(h,NULL,0);
    enter(h,"n_digilfm",1);
    pick(h,0);
    expect_page(h,8,0,2); /* ten chips, a gap, then five more on page two */
    assert(!has_text(h,"STWINFONT14","font010") && !has_text(h,"STWINFONT14","font011"));
    if(capture)draw_frame(h,"chip-list");
    dw4_item_record chip=dw4_shopstock_list(st,8,NULL)[0];assert(chip.kind==3);
    int32_t price=price_of(h,&chip);
    buy_row(h,0);
    assert(bit(h)==100000-price && devices(h)==1);
    const dw4_item_record *got=device(h,0);
    assert(got->kind==3 && got->record==chip.record && !got->equipped);
    assert(dw4_shopstock_list(st,8,NULL)[0].kind==3 && dw4_shopstock_list(st,8,NULL)[0].record==DW4_SHOPSTOCK_SOLD_OUT);
    expect_back_at_list(h);
    assert(!strcmp(text_value(h,"STWINFONT17","font000"),"----"));
    cancel_list(h);
    leave(h);
    dw4_hubruntime_close(h);
    puts("hub CHIP buy: chip stock with its gap, rows, purchase and sold-out slot pass");
}

/* ---- JUNK ---- */
static void expect_digits(dw4_hubruntime *h,const char *want)
{
    size_t n=strlen(want);
    for(size_t i=0;i<7;i++) {
        char font[16];snprintf(font,sizeof font,"font%03d",(int)i);
        if(i<n) {
            const char *v=text_value(h,"STWINFONT25",font);
            if(!v || v[0]!=want[n-1-i] || v[1])fprintf(stderr,"\ndigit %s expected '%c' got '%s'\n",font,want[n-1-i],v?v:"(hidden)");
            assert(v && v[0]==want[n-1-i] && !v[1]);
        }else assert(!has_text(h,"STWINFONT25",font));
    }
}
static void wait_menu(dw4_hubruntime *h){assert(wait_text(h,"STWINFONT29","font002",900));idle(h,60);latched=0;}
/* Open the donation editor: the junk menu's first entry. */
static void open_donation(dw4_hubruntime *h)
{
    pick(h,0);
    assert(wait_text(h,"STWINFONT25","font000",900));idle(h,70);latched=0;
    expect_digits(h,"0");
}
static void junk_donate(dw4_mount *mount,const dw4_hubruntime_source *source,const char *capture)
{
    dw4_hubruntime *h=boot_shop(mount,source);
    set_bit(h,5000);set_investment(h,0);
    enter(h,"n_metete",0);
    /* Cancel the editor: nothing changes and the menu returns. */
    open_donation(h);
    edit_tap(h,UP);expect_digits(h,"1");
    if(capture)draw_frame(h,"junk-editor");
    idle(h,60);press(h,0x2000);wait_menu(h);
    assert(bit(h)==5000 && investment(h)==0);
    /* Donate 500 and decline the question: nothing changes. */
    open_donation(h);
    move_cursor(h,LEFT);move_cursor(h,LEFT);
    for(int i=0;i<5;i++)edit_tap(h,UP);
    expect_digits(h,"500");
    press(h,0x4000);assert(wait_text(h,"STWINFONT29","font000",600));idle(h,60);
    assert(bit(h)==5000 && investment(h)==0); /* the acknowledgement precedes any change */
    press(h,0x4000);
    pick(h,1); /* No */
    wait_menu(h);
    assert(bit(h)==5000 && investment(h)==0);
    /* Donate 500: below the first tier, the menu returns. */
    open_donation(h);
    move_cursor(h,LEFT);move_cursor(h,LEFT);
    for(int i=0;i<5;i++)edit_tap(h,UP);
    press(h,0x4000);assert(wait_text(h,"STWINFONT29","font000",600));idle(h,60);press(h,0x4000);
    pick(h,0); /* Yes */
    wait_menu(h);
    assert(bit(h)==4500 && investment(h)==500);
    /* Another 500 crosses 1000: junkexit.lua runs, the notice is shown and the shop closes. */
    open_donation(h);
    move_cursor(h,LEFT);move_cursor(h,LEFT);
    for(int i=0;i<5;i++)edit_tap(h,UP);
    press(h,0x4000);assert(wait_text(h,"STWINFONT29","font000",600));idle(h,60);press(h,0x4000);
    if(capture)draw_frame(h,"junk-confirm");
    pick(h,0); /* Yes */
    assert(bit(h)==4000 && investment(h)==1000);
    assert(wait_text(h,"STWINFONT29","font000",900));idle(h,60); /* the tier notice (0x7B2) */
    if(capture)draw_frame(h,"junk-tier-notice");
    press(h,0x4000);
    unsigned k=0;for(;k<1200 && dw4_hubruntime_status_active(h);k++)step(h,0,0);
    assert(k<1200 && !dw4_hubruntime_status_active(h));
    unsigned e=0;for(;e<400 && (!control(h) || dw4_hubruntime_input_state(h)->disabled);e++)step(h,0,0);
    assert(e<400 && control(h) && !dw4_hubruntime_travel(h)->pending);
    assert(bit(h)==4000 && investment(h)==1000);
    dw4_hubruntime_close(h);
    puts("hub JUNK donate: editor digits, cancel, decline, confirmed donation, tier threshold notice and restored control pass");
}
static void junk_empty_then_buy(dw4_mount *mount,const dw4_hubruntime_source *source,const char *capture)
{
    dw4_hubruntime *h=boot_shop(mount,source);
    dw4_shopstock *st=dw4_hubruntime_shopstock(h);
    set_bit(h,100000);set_devices(h,NULL,0);set_investment(h,0);
    enter(h,"n_metete",0);
    /* Below the first tier the stock is empty: one disabled row and a zero page count. */
    pick(h,1);
    assert(wait_text(h,"STWINFONT30","font001",900));idle(h,70);
    assert(!strcmp(text_value(h,"STWINFONT30","font001"),"0") && dw4_shopstock_count(st,9)==0 && dw4_shopstock_gift(st)==0);
    if(capture)draw_frame(h,"junk-empty");
    idle(h,60);press(h,0x4000);idle(h,90); /* Cross on the disabled row does nothing */
    assert(bit(h)==100000 && devices(h)==0);
    idle(h,60);press(h,0x2000);wait_menu(h);
    leave(h);
    dw4_hubruntime_close(h);
    /* A fresh visit with an investment of 1000 stocks the first tier; the list persists and buys like the others. */
    h=boot_shop(mount,source);
    st=dw4_hubruntime_shopstock(h);
    set_bit(h,100000);set_devices(h,NULL,0);set_investment(h,1000);
    enter(h,"n_metete",0);
    pick(h,1);
    assert(dw4_shopstock_gift(st)==1000 && dw4_shopstock_count(st,9)>0);
    expect_page(h,9,0,(int)(dw4_shopstock_count(st,9)/12+(dw4_shopstock_count(st,9)%12!=0)));
    if(capture)draw_frame(h,"junk-list");
    dw4_item_record first=dw4_shopstock_list(st,9,NULL)[0];assert(first.kind>=0);
    int32_t price=price_of(h,&first);
    buy_row(h,0);
    assert(bit(h)==100000-price && devices(h)==1);
    const dw4_item_record *got=device(h,0);
    assert(got->kind==first.kind && got->record==first.record && got->revision==first.revision && got->pocket==first.pocket);
    assert(dw4_shopstock_list(st,9,NULL)[0].kind==3 && dw4_shopstock_list(st,9,NULL)[0].record==DW4_SHOPSTOCK_SOLD_OUT);
    expect_back_at_list(h);
    cancel_list(h);
    leave(h);
    dw4_hubruntime_close(h);
    puts("hub JUNK buy: empty stock below the first tier, then the tier's stock, purchase and sold-out slot pass");
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
    assert(!dw4_playerrecords_create(players,db,0,"p_dorumon","HubShops",error,sizeof error));
    dw4_hubruntime_source initial={players,&state,NULL,0};
    frame=0;wpu_flow(&mount,&initial,capture_dir);
    frame=0;wpu_sell(&mount,&initial,capture_dir);
    frame=0;apu_flow(&mount,&initial,capture_dir);
    frame=0;chip_flow(&mount,&initial,capture_dir);
    frame=0;junk_donate(&mount,&initial,capture_dir);
    frame=0;junk_empty_then_buy(&mount,&initial,capture_dir);
    dw4_databases_close(db);dw4_stageobjects_close(objects);dw4_scriptengine_close(e);dw4_filelist_close(f);
    dw4_scriptservices_close(host.sd);dw4_playerrecords_close(players);dw4_mount_close(&mount);
    puts("hub shops: NPC reach, menus, goods lists, purchases, refusals and restored control pass");
    return 0;
}
