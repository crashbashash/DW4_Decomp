/* Live Cross interaction through the normal prepared Central hub runtime. Headless.
 * Movement is real stick input from the authored arrival point; probe geometry,
 * dialogue, choices, stage requests and the XDATA service run original bytecode and
 * native services. Record fixtures are limited to the character's XDATA balance and
 * UPCNT counters; everything else is produced by the running game. */
#include "hubtest.h"
/* Waypoints from the arrival pocket around the walls to the west Digi-Elf, found by
 * breadth-first search over the real movement and collision code, the last three moved to the middle of the corridor for the retail wall query. */
static const char *const xdata_route="-104,-40;-106,5;-108,29;-128,32;-131,52;-152,56;-155,77;-176,80;-179,100;"
    "-200,104;-296,104;-299,84;-321,81;-324,59;-345,57;-348,35;-369,33;-380,11;-382,-13;-380,-36";
static void walk_route(dw4_hubruntime *h,const char *route)
{
    char copy[512];snprintf(copy,sizeof copy,"%s",route);
    for(char *tok=strtok(copy,";");tok;tok=strtok(NULL,";")){float x,z;assert(sscanf(tok,"%f,%f",&x,&z)==2);assert(walk_to(h,x,z,6));}
}
/* second: move to the second prompt entry before confirming. */
static void scenario(dw4_mount *mount,const dw4_hubruntime_source *source,int second)
{
    dw4_hubruntime *h=boot_central(mount,source);
    const dw4_controllers *models=dw4_hubruntime_models(h);
    /* Registration came with the accepted rows; ungenerated Work is not eligible. */
    assert(dw4_controllers_talk_count(models)==44);
    const dw4_modelctrl *npc=find(models,"n_digilfm",0),*dormant=find(models,"n_digilfm",3);
    assert(npc && dormant && dw4_modelctrl_active(npc) && !dw4_modelctrl_active(dormant));
    /* Cross away from any receiver does nothing and leaves control alone. */
    press(h,0x4000);idle(h,6);
    assert(dw4_lobby_talk_result(dw4_hubruntime_world(h))==0 && control(h) && !has_text(h,"TALKFONT02",NULL));
    assert(approach(h,npc,9));
    step(h,0,0x4000);
    assert(dw4_lobby_talk_result(dw4_hubruntime_world(h))==1 && !strcmp(dw4_modelctrl_sequence(npc),"SQ_TALK"));
    step(h,0,0);assert(!control(h));
    unsigned k=0,chosen=0;
    unsigned shot=0;
    for(;k<3000;k++) {
        if(!second && capture_dir && !shot && k>40 && has_text(h,"TALKFONT02","font00")){shot=1;idle(h,30);draw_frame(h,"talk");}
        if(has_text(h,"TALKFONT02","font01") && has_text(h,"TALKFONT02","font02")) {
            /* Two-entry prompt: the original selector reads the stick/Cross itself. */
            idle(h,60);
            if(second)down(h);
            step(h,0,0x4000);chosen=1;idle(h,400);
            break;
        }
        step(h,0,k%45==44?0x4000:0);
    }
    assert(chosen);
    const dw4_stagetravel *travel=dw4_hubruntime_travel(h);
    if(second) {
        unsigned r=0;for(;r<900 && !(control(h) && !strcmp(dw4_modelctrl_sequence(npc),"SQ_WAIT"));r++)step(h,0,r%45==44?0x4000:0);
        assert(r<900 && !travel->pending && !has_text(h,"TALKFONT02",NULL) && !has_text(h,"TALKFONT03",NULL));
        unsigned e=0;for(;e<60 && dw4_hubruntime_input_state(h)->disabled;e++)step(h,0,0);
        assert(e<60 && control(h)); /* original PADINPUT ENABLE with its 15-frame delay */
        /* The NPC can be addressed again after control returns. */
        assert(approach(h,npc,9));step(h,0,0x4000);
        assert(dw4_lobby_talk_result(dw4_hubruntime_world(h))==1);
        printf("hub talk Central n_digilfm: Cross probe, original dialogue, second choice, close and restored control pass\n");
    }else {
        unsigned r=0;for(;r<900 && !travel->pending;r++)step(h,0,0);
        assert(travel->pending && !strcasecmp(travel->destination,"stagIS12") && !control(h));
        printf("hub talk Central n_digilfm: Cross probe, original dialogue, accepted choice and stage request %s pass\n",travel->destination);
    }
    dw4_hubruntime_close(h);
}
/* ---- XDATA service ---- */
static int32_t upcnt(dw4_property_folder *f,unsigned index)
{size_t n;const int32_t *a=dw4_property_array(f,"UPCNT",&n);assert(a && n==11);return a[index];}
/* Talk to the XDATA Digi-Elf, accept its prompt and wait for the main menu. */
static void enter_xdata(dw4_hubruntime *h)
{
    const dw4_modelctrl *npc=find(dw4_hubruntime_models(h),"n_digilfm",1);assert(npc);
    walk_route(h,xdata_route);assert(approach(h,npc,9));
    step(h,0,0x4000);assert(dw4_lobby_talk_result(dw4_hubruntime_world(h))==1);
    unsigned k=0;
    for(;k<3000 && !(has_text(h,"TALKFONT02","font01") && has_text(h,"TALKFONT02","font02"));k++)step(h,0,k%45==44?0x4000:0);
    assert(k<3000);
    idle(h,60);press(h,0x4000); /* first entry: use XDATA */
    assert(wait_text(h,"STWINFONT29","font002",600) && dw4_hubruntime_status_active(h)==2);
}
/* Main-menu entry 0 opens the stat list; wait for its cost column. */
static void open_stats(dw4_hubruntime *h)
{
    idle(h,60);press(h,0x4000);
    assert(wait_text(h,"STWINFONT19","font000",600) && wait_text(h,"STWINFONT14","font006",100));idle(h,70);
}
static void check_costs(dw4_hubruntime *h,dw4_property_folder *f)
{
    static const char *const fonts[]={"font000","font001","font002","font003","font004","font005","font006"};
    for(int i=0;i<7;i++){
        const char *key;int32_t limit;assert(!dw4_xdata_stat(i,&key,&limit,NULL));
        int32_t stat=number(f,key);char want[16];
        if(stat<limit)snprintf(want,sizeof want,"%d",dw4_xdata_price(stat));else snprintf(want,sizeof want,"----");
        const char *got=text_value(h,"STWINFONT19",fonts[i]);
        if(!got || strcmp(got,want))fprintf(stderr,"cost %s: shown '%s' expected '%s' (stat %d)\n",key,got?got:"(none)",want,stat);
        assert(got && !strcmp(got,want));
    }
}
/* accept: 1 buys TSUYOSA once, 0 declines at the confirmation. */
static void xdata_buy(dw4_mount *mount,const dw4_hubruntime_source *source,int accept)
{
    dw4_hubruntime *h=boot_central(mount,source);
    dw4_property_folder *f=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);
    assert(!dw4_property_set_number(f,"XDATA",500));
    int32_t total_before=number(f,"TSUYOSA"),up_before=upcnt(f,2);
    enter_xdata(h);
    assert(has_text(h,"STWINFONT29","font000") && has_text(h,"STWINFONT29","font001") && has_text(h,"STWINFONT29","font002"));
    open_stats(h);
    /* RECALCPLAYER(false) published equipment-free stats; the column shows their retail prices. */
    int32_t base=number(f,"TSUYOSA");assert(base<=total_before);
    check_costs(h,f);
    if(accept){draw_frame(h,"stats");}
    int32_t price=dw4_xdata_price(base);
    press(h,0x4000); /* TSUYOSA */
    assert(wait_text(h,"STWINFONT41","font011",600));
    char remaining[16];snprintf(remaining,sizeof remaining,"%d",500-price);
    assert(!strcmp(text_value(h,"STWINFONT41","font011"),"+1") && !strcmp(text_value(h,"STWINFONT41","font012"),remaining));
    assert(number(f,"XDATA")==500 && upcnt(f,2)==up_before); /* quoting spends nothing */
    if(accept){draw_frame(h,"quote");}
    idle(h,60);press(h,0x4000); /* acknowledge the quote */
    assert(wait_gone(h,"STWINFONT41","font011",300) && wait_text(h,"STWINFONT29","font001",600));
    idle(h,60);
    if(!accept)down(h);
    press(h,0x4000);
    if(accept) {
        unsigned k=0;for(;k<600 && number(f,"XDATA")==500;k++)step(h,0,0);
        assert(k<600 && number(f,"XDATA")==500-price && upcnt(f,2)==up_before+1);
        assert(number(f,"TSUYOSA")==total_before+1); /* recalculated with equipment */
        assert(number(f,"HP")==number(f,"MHP") && number(f,"MP")==number(f,"MMP"));
        assert(wait_text(h,"STWINFONT29","font000",600));idle(h,60);press(h,0x4000); /* success notice */
        assert(wait_text(h,"STWINFONT29","font001",600));idle(h,60);down(h);press(h,0x4000); /* do not continue */
        assert(wait_text(h,"STWINFONT29","font002",600)); /* back at the main menu */
        leave_service(h);
        assert(number(f,"XDATA")==500-price && number(f,"TSUYOSA")==total_before+1);
        printf("hub XDATA Central: browse, quote %d, accept, charge, UPCNT, recalculation, close and restored control pass\n",price);
    }else {
        assert(wait_text(h,"STWINFONT19","font000",600));idle(h,70);
        assert(number(f,"XDATA")==500 && upcnt(f,2)==up_before);
        press(h,0x2000); /* cancel the list */
        assert(wait_text(h,"STWINFONT29","font002",600));
        leave_service(h);
        assert(number(f,"XDATA")==500 && upcnt(f,2)==up_before && number(f,"TSUYOSA")==total_before);
        printf("hub XDATA Central: decline leaves XDATA/UPCNT/stats unchanged and returns to normal play\n");
    }
    dw4_hubruntime_close(h);
}
/* Balance too small, or the stat already at its cap: an error notice, no charge. */
static void xdata_refuse(dw4_mount *mount,const dw4_hubruntime_source *source,int capped)
{
    dw4_hubruntime *h=boot_central(mount,source);
    dw4_property_folder *f=dw4_playerrecords_get(dw4_hubruntime_records(h),"GETPLAYER",0);
    int32_t counts[11];size_t n;const int32_t *up=dw4_property_array(f,"UPCNT",&n);assert(up && n==11);memcpy(counts,up,sizeof counts);
    assert(!dw4_property_set_number(f,"XDATA",capped?500:0));
    if(capped){counts[2]=20000;assert(!dw4_property_set_array(f,"UPCNT",counts,11));}
    enter_xdata(h);open_stats(h);
    const char *shown=text_value(h,"STWINFONT19","font000");assert(shown);
    if(capped && strcmp(shown,"----"))fprintf(stderr,"capped column shows '%s', TSUYOSA=%d UPCNT[2]=%d\n",shown,number(f,"TSUYOSA"),upcnt(f,2));
    if(capped)assert(!strcmp(shown,"----"));
    press(h,0x4000); /* TSUYOSA */
    assert(wait_text(h,"STWINFONT29","font000",600) && !has_text(h,"STWINFONT41","font011"));
    assert(number(f,"XDATA")==(capped?500:0) && upcnt(f,2)==counts[2]);
    idle(h,60);press(h,0x4000);
    assert(wait_text(h,"STWINFONT19","font000",600));idle(h,70);
    assert(number(f,"XDATA")==(capped?500:0) && upcnt(f,2)==counts[2]);
    press(h,0x2000);assert(wait_text(h,"STWINFONT29","font002",600));
    leave_service(h);
    printf("hub XDATA Central: %s notice refuses without charging and gameplay is restored\n",capped?"capped-stat":"insufficient-balance");
    dw4_hubruntime_close(h);
}
/* The bottom panel (i_stpnl06, single-player slot 4) is generated into an empty SQ_WAIT: no ACTION
 * runs, so its nodes keep their authored pose. Sampling the raw clock instead clamped its embedded
 * animation to the opened pose and drew an extra line and chevrons that retail does not show. */
static void idle_panel(dw4_mount *mount,const dw4_hubruntime_source *source)
{
    dw4_hubruntime *h=boot_central(mount,source);idle(h,300);
    const dw4_modelctrl *panel=find(dw4_hubruntime_models(h),"i_stpnl06",4),*npc=find(dw4_hubruntime_models(h),"n_digilfm",0);
    assert(panel && npc && dw4_modelctrl_active(panel) && dw4_modelctrl_drawable(panel));
    assert(!strcmp(dw4_modelctrl_sequence(panel),"SQ_WAIT") && dw4_modelctrl_time(panel)==0);
    assert(dw4_modelctrl_time(npc)>0); /* a running action keeps advancing */
    draw_frame(h,"idle");
    printf("hub idle panel: action-less bottom panel stays in its authored pose while running actions advance\n");
    dw4_hubruntime_close(h);
}
/* ---- XDATA chip branch ---- */
static dw4_databases *chip_db;
/* A catalogue row with a payable next level, or the first row whose NEXTX is -1 (fully upgraded). */
static int find_chip(int maxed,int32_t *record,int32_t *cost)
{
    const dw4_database *d=dw4_databases_get(chip_db,"abChip");size_t rows=dw4_database_string_rows(d);
    for(size_t r=0;r+1<rows;r++){
        int32_t next,price;
        if(dw4_database_number(d,(int32_t)r,"NEXTX",&next)<0)continue;
        if(maxed?next==-1:next>0){
            const char *name=dw4_statuscontent_item_string(chip_db,&(dw4_item_record){.kind=3,.record=(int32_t)r},"NAME");
            const char *after=dw4_statuscontent_item_string(chip_db,&(dw4_item_record){.kind=3,.record=(int32_t)r+1},"NAME");
            if(!name || !*name || (!maxed && (!after || !*after)))continue;
            price=next;*record=(int32_t)r;*cost=price;return 1;
        }
    }
    return 0;
}
/* The left player panel's stat numbers (STWINFONT06) as the quote shows them: value and whether the text is tinted. */
typedef struct {int32_t value;int tinted;int present;} panel_stat;
static void panel_stats(const dw4_hubruntime *h,panel_stat out[11],panel_stat *xdata)
{
    static const char *const fonts[]={"font010","font011","font040","font041","font042","font043","font044","font045","font046","font047","font048"};
    const dw4_dialogue *d=dw4_hubruntime_dialogue(h);
    memset(out,0,11*sizeof *out);memset(xdata,0,sizeof *xdata);
    for(size_t i=0;i<dw4_dialogue_text_count(d);i++){
        const dw4_dialogue_text *t=dw4_dialogue_text_at(d,i);
        if(!t->visible || !t->count || strcmp(t->group,"STWINFONT06"))continue;
        int32_t v=0;for(size_t k=0;k<t->count;k++)if(t->codes[k]>='0' && t->codes[k]<='9')v=v*10+(int32_t)(t->codes[k]-'0');
        int tint=t->color[0]<.6f && t->color[2]>.8f; /* cyan: red low, blue high (default stat text is white) */
        for(unsigned f=0;f<11;f++)if(!strcmp(t->name,fonts[f]))out[f]=(panel_stat){v,tint,1};
        if(!strcmp(t->name,"font049"))*xdata=(panel_stat){v,tint,1};
    }
}
static void add_chip(dw4_playerrecords *p,int32_t record,int equip)
{
    int result;dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",0);size_t before;
    assert(!dw4_property_item_count(f,"DEVICEFOLDER",&before));
    assert(!dw4_playertransactions_device(p,0,DW4_DEVICE_SET,3,record,0,0,&result) && result);
    if(equip)assert(!dw4_playertransactions_equip_database(p,0,"POWERPOCKET",0,(int32_t)before,chip_db));
}
static int32_t chip_record(dw4_property_folder *f,size_t chip_index)
{size_t n;const dw4_item_record *it=dw4_property_items(f,"DEVICEFOLDER",&n);assert(it && chip_index<n);return it[chip_index].record;}
static int32_t retail_wisdom_preview;
static int retail_visit(void *u,dw4_property_folder *f){(void)u;return dw4_property_number(f,"KASHIKOSA",&retail_wisdom_preview);}
/* Retail reference (2026-10-17): a Dorumon Lv 40 (current stats rebuilt from its saved record) with a Wisdom chip (upgrade cost 2400,
 * +120 step) equipped shows Wisdom 600 -> 720 in cyan on the Data Keeper quote, every other stat and the X Data row unchanged. */
static void chip_projection(dw4_databases *db)
{
    dw4_playerrecords *p=dw4_playerrecords_open();char error[256];assert(p);
    assert(!dw4_playerrecords_create(p,db,0,"p_dorumon","ChipTest",error,sizeof error));
    dw4_property_folder *f=dw4_playerrecords_get(p,"GETPLAYER",0);
    assert(!dw4_property_set_number(f,"LEVEL",40) && !dw4_property_set_number(f,"EXP",4000));
    assert(!dw4_playerstats_recalculate((void *)db,f));
    const dw4_database *d=dw4_databases_get(db,"abChip");int32_t record=-1;
    for(size_t r=0;r+1<dw4_database_string_rows(d) && record<0;r++){
        int32_t next;if(dw4_database_number(d,(int32_t)r,"NEXTX",&next)<0 || next!=2400)continue;
        const char *name=dw4_statuscontent_item_string(db,&(dw4_item_record){.kind=3,.record=(int32_t)r},"NAME");
        if(name && strstr(name,"Wisdom") && !strchr(name,'+'))record=(int32_t)r;
    }
    assert(record>=0);size_t before;int added;assert(!dw4_property_item_count(f,"DEVICEFOLDER",&before));
    assert(!dw4_playertransactions_device(p,0,DW4_DEVICE_SET,3,record,0,0,&added) && added);
    assert(!dw4_playertransactions_equip_database(p,0,"POWERPOCKET",0,(int32_t)before,db));
    int32_t now=0,mhp=0,tsu=0;assert(!dw4_property_number(f,"KASHIKOSA",&now) && !dw4_property_number(f,"MHP",&mhp) && !dw4_property_number(f,"TSUYOSA",&tsu));
    assert(now==600 && mhp==3074 && tsu==418); /* the retail panel: Wisdom 600, HP 3074, Strength 418 */
    assert(!dw4_playertransactions_chip_preview(p,0,before,dw4_playerstats_recalculate,(void *)db,retail_visit,NULL));
    assert(retail_wisdom_preview==720); /* the retail quote: Wisdom 720 (cyan) */
    int32_t after=0;assert(!dw4_property_number(f,"KASHIKOSA",&after) && after==600); /* nothing published by the preview */
    printf("XDATA chip: Dorumon Lv 40 Wisdom 600 -> 720 with the equipped chip matches the retail quote (3074 HP, 418 Strength)\n");
    dw4_playerrecords_close(p);
}
/* mode: 0 buy (equipped), 1 decline, 2 insufficient balance, 3 maxed chip, 4 no chips */
static void xdata_chip(dw4_mount *mount,const dw4_hubruntime_source *source,int mode)
{
    dw4_hubruntime *h=boot_central(mount,source);
    dw4_playerrecords *records=dw4_hubruntime_records(h);dw4_property_folder *f=dw4_playerrecords_get(records,"GETPLAYER",0);
    int32_t record=0,cost=0;size_t before;assert(!dw4_property_item_count(f,"DEVICEFOLDER",&before));
    if(mode!=4){assert(find_chip(mode==3,&record,&cost));add_chip(records,record,mode==0);}
    assert(!dw4_property_set_number(f,"XDATA",mode==2?cost-1:500));
    int32_t xdata=number(f,"XDATA");
    static const char *const stat_keys[11]={"MHP","MMP","TSUYOSA","MAMORI","KASHIKOSA","SEISHIN","SUBAYASA","HONOOTEIKO","KOORITEIKO","KAMINARITEIKO","YAMITEIKO"};
    int32_t stats_before[11];for(unsigned k=0;k<11;k++)stats_before[k]=number(f,stat_keys[k]);
    enter_xdata(h);
    idle(h,60);down(h);press(h,0x4000); /* main-menu entry 1: chips */
    if(mode==4) {
        assert(wait_text(h,"STWINFONT29",NULL,600)); /* the empty-list notice (1169) */
        idle(h,60);press(h,0x4000);
        assert(wait_gone(h,"STWINFONT29","font100",300));
        assert(wait_text(h,"STWINFONT29","font002",600)); /* back at the XDATA menu */
        leave_service(h);
        printf("hub XDATA chip: empty inventory shows its notice and returns to the menu\n");
        dw4_hubruntime_close(h);return;
    }
    assert(wait_text(h,"STWINFONT14","font000",600) && wait_text(h,"STWINFONT17","font000",100));idle(h,70);
    char want[16];snprintf(want,sizeof want,"%d",mode==3?0:cost);
    if(mode==3)snprintf(want,sizeof want,"----");
    const char *shown=text_value(h,"STWINFONT17","font000");
    if(!shown || strcmp(shown,want))fprintf(stderr,"chip NEXTX shown '%s' expected '%s'\n",shown?shown:"(none)",want);
    assert(shown && !strcmp(shown,want));
    assert(!strcmp(text_value(h,"STWINFONT30","font000"),"1") && !strcmp(text_value(h,"STWINFONT30","font001"),"1"));
    assert(text_value(h,"STWINFONT14","font000") && !has_text(h,"STWINFONT14","font001"));
    assert(has_text(h,"STWINFONT29","font000")); /* description of the highlighted chip */
    if(mode==0){draw_frame(h,"chips");}
    press(h,0x4000); /* the chip */
    if(mode==2 || mode==3) {
        assert(wait_text(h,"STWINFONT29","font000",600) && !has_text(h,"STWINFONT41","font012"));
        assert(number(f,"XDATA")==xdata && chip_record(f,before)==record);
        idle(h,60);press(h,0x4000);
        assert(wait_text(h,"STWINFONT14","font000",600));idle(h,70);
        press(h,0x2000);assert(wait_text(h,"STWINFONT29","font002",600));
        leave_service(h);
        assert(number(f,"XDATA")==xdata && chip_record(f,before)==record);
        printf("hub XDATA chip: %s refusal leaves XDATA and the chip unchanged\n",mode==2?"insufficient-balance":"fully-upgraded");
        dw4_hubruntime_close(h);return;
    }
    assert(wait_text(h,"STWINFONT41","font012",600));
    char remaining[16];snprintf(remaining,sizeof remaining,"%d",xdata-cost);
    assert(!strcmp(text_value(h,"STWINFONT41","font012"),remaining));
    assert(number(f,"XDATA")==xdata && chip_record(f,before)==record); /* quoting spends nothing */
    panel_stat quoted[11],quoted_xdata;
    if(mode==0){draw_frame(h,"chipquote");panel_stats(h,quoted,&quoted_xdata);}
    idle(h,60);press(h,0x4000); /* acknowledge the quote */
    assert(wait_gone(h,"STWINFONT41","font012",300) && wait_text(h,"STWINFONT29","font001",600));
    idle(h,60);
    if(mode==1)down(h);
    press(h,0x4000);
    if(mode==0) {
        unsigned k=0;for(;k<600 && number(f,"XDATA")==xdata;k++)step(h,0,0);
        assert(k<600 && number(f,"XDATA")==xdata-cost && chip_record(f,before)==record+1);
        /* The quote's left panel previewed the record after the upgrade: every stat that the commit changes shows its new value
         * tinted, every other stat keeps its value untinted, and the X Data row is not previewed (retail chip quote). */
        unsigned changed=0;
        for(unsigned s=0;s<11;s++){
            int32_t after=number(f,stat_keys[s]);
            assert(quoted[s].present && quoted[s].value==after);
            assert(quoted[s].tinted==(after!=stats_before[s]));
            changed+=after!=stats_before[s];
        }
        assert(changed && quoted_xdata.present && quoted_xdata.value==xdata && !quoted_xdata.tinted);
        size_t n;const dw4_item_record *pocket=dw4_property_items(f,"POWERPOCKET",&n);
        assert(pocket && n==5 && pocket[0].kind==3 && pocket[0].record==record+1); /* equipped copy follows the chip */
        assert(wait_text(h,"STWINFONT14","font000",600));idle(h,70);
        press(h,0x2000);assert(wait_text(h,"STWINFONT29","font002",600));
        leave_service(h);
        assert(number(f,"XDATA")==xdata-cost && chip_record(f,before)==record+1);
        printf("hub XDATA chip: browse, quote, equipped preview, accept, charge, record+1, projection and restored control pass\n");
    }else {
        assert(wait_text(h,"STWINFONT14","font000",600));idle(h,70);
        assert(number(f,"XDATA")==xdata && chip_record(f,before)==record);
        press(h,0x2000);assert(wait_text(h,"STWINFONT29","font002",600));
        leave_service(h);
        assert(number(f,"XDATA")==xdata && chip_record(f,before)==record);
        printf("hub XDATA chip: decline leaves XDATA and the chip unchanged\n");
    }
    dw4_hubruntime_close(h);
}
/* The label band (i_stpnl06, WN01) over the HUD panels (i_stpnl00, also WN01) and the name text (FONT) over the band: the left
 * chevrons draw their texels unshaded (retail frame: brightest (202,202,255), about (131,107,236) mean) and the name glyphs are
 * not under the band's plate (they were at about 43% brightness, each in turn, with the HUD or the text drawn over the band). */
static void label_band_brightness(dw4_hubruntime *h)
{
    dw4_fb fb;assert(!dw4_fb_init(&fb,640,448));assert(dw4_hubruntime_draw(h,&fb,NULL)>0);
    unsigned chevron[3]={0},glyph=0,lit=0;double mean[3]={0};
    for(int y=398;y<425;y++)for(int x=180;x<270;x++){
        const uint8_t *p=fb.rgba+4*((size_t)y*fb.w+x);
        if((unsigned)(p[0]+p[1]+p[2])>chevron[0]+chevron[1]+chevron[2])for(int c=0;c<3;c++)chevron[c]=p[c];
        if(p[2]>200){lit++;for(int c=0;c<3;c++)mean[c]+=p[c];}
    }
    for(int y=400;y<422;y++)for(int x=320;x<500;x++){const uint8_t *p=fb.rgba+4*((size_t)y*fb.w+x);if(p[1]>glyph && p[1]>p[0]+30)glyph=p[1];}
    printf("hub label band: left chevron max (%u,%u,%u), mean of %u lit pixels (%.0f,%.0f,%.0f); name glyph green %u\n",
        chevron[0],chevron[1],chevron[2],lit,lit?mean[0]/lit:0,lit?mean[1]/lit:0,lit?mean[2]/lit:0,glyph);
    assert(chevron[0]>=190 && chevron[1]>=190 && chevron[2]>=245 && lit>=500 && mean[2]/lit>=230 && glyph>=140);
    dw4_fb_free(&fb);
}
/* The matf* regions run the stage's PintmessOpen labels: the name in the bottom band (POINTFONT00/font04) and the arrow (i_pointcur,
 * instance 4 for the single player); both go away when the player leaves the region. Names are the retail texts. */
/* The HUD region of a 640x448 frame (the ring and digits, bottom left) as RGB bytes, to compare against another frame. */
static void hud_region(dw4_hubruntime *h,uint8_t out[3*140*90])
{
    dw4_fb fb;assert(!dw4_fb_init(&fb,640,448));assert(dw4_hubruntime_draw(h,&fb,NULL)>0);
    for(unsigned y=0;y<90;y++)for(unsigned x=0;x<140;x++)for(unsigned c=0;c<3;c++)out[3*(140*y+x)+c]=fb.rgba[4*((358+y)*640+x)+c];
    dw4_fb_free(&fb);
}
static double hud_diff(const uint8_t *a,const uint8_t *b){double d=0;for(unsigned i=0;i<3*140*90;i++)d+=abs((int)a[i]-(int)b[i]);return d;}
static void point_labels(dw4_mount *mount,const dw4_hubruntime_source *source)
{
    static const struct {const char *stage;const char *name;float x,z;const char *text;} cases[]={
        {"stagML11","Gate to Outside World",5,-95,"Gate to Outside World"},{"stagML11","Gate to Commander Room",30,40,"Gate to Commander Room"},
        {"stagML11","Emergency Gate",180,80,"Emergency Gate"},{"stagML11","Heal Circle",115,-120,"Heal Circle"},{"stagML11","Call Keeper",255,65,"Call Keeper"},
        {"stagML12","Save Keeper",-115,-40,"Save Keeper"},{"stagML12","Bank Keeper",-240,85,"Bank Keeper"},{"stagML12","Digi-Lab",-330,60,"Digi-Lab"},
        {"stagML12","Data Keeper",-365,-40,"Data Keeper"},{"stagML12","Card Keeper",-240,-165,"Card Keeper"},{"stagML12","Appraisal Keeper",-210,230,"Appraisal Keeper"},
        {"stagML13","Disk Shop",60,145,"Disk Shop"},{"stagML13","Weapon Shop",-55,260,"Weapon Shop"},{"stagML13","Armor Shop",60,375,"Armor Shop"},
        {"stagML13","Chip Shop",175,260,"Chip Shop"},{"stagML13","Junk Shop",380,310,"Junk Shop"},{"stagML13","Bank Keeper (shop)",175,145,"Bank Keeper"}};
    const char *stage="";dw4_hubruntime *h=NULL;
    for(unsigned i=0;i<sizeof cases/sizeof *cases;i++){
        if(strcmp(stage,cases[i].stage)){
            if(h)dw4_hubruntime_close(h);
            char err[512];h=dw4_hubruntime_prepare(mount,source,cases[i].stage,0,1,err,sizeof err);assert(h);stage=cases[i].stage;frame=0;
            unsigned t=0;for(;t<6000;t++){step(h,0,t%45==44?0x4000:0);if(t>30 && control(h) && dw4_lobby_intro_done(dw4_hubruntime_world(h)))break;}
            assert(t<6000);
        }
        dw4_lobby_place_player(dw4_hubruntime_world(h),60,10,-30,0);idle(h,90);
        assert(!has_text(h,"POINTFONT00",NULL)); /* outside every region: no label */
        assert(!dw4_lobby_place_player(dw4_hubruntime_world(h),cases[i].x,cases[i].x>300?90:40 /* the Junk Shop stands on a raised platform */,cases[i].z,0));idle(h,120);
        const char *shown=has_text(h,"POINTFONT00","font04")?text_value(h,"POINTFONT00","font04"):NULL;
        if(!shown || !strstr(shown,cases[i].text)){fprintf(stderr,"label %s: shows '%s'\n",cases[i].name,shown?shown:"(none)");assert(0);}
        if(i==0)label_band_brightness(h);
        if(capture_dir){char tag[64];snprintf(tag,sizeof tag,"label-%u",i);draw_frame(h,tag);}
        if(!strcmp(cases[i].name,"Save Keeper")){ /* talking closes the label and the HUD (retail frames of any NPC message) */
            const dw4_modelctrl *el=find(dw4_hubruntime_models(h),"n_digilfm",0);dw4_modelctrl_actor ea={0};assert(el);dw4_modelctrl_actor_state(el,&ea);
            assert(!dw4_lobby_place_player(dw4_hubruntime_world(h),ea.position[0]+(float)(12*sin(ea.rotation[1]*0.0174533)),40,ea.position[2]+(float)(12*cos(ea.rotation[1]*0.0174533)),ea.rotation[1]+180));
            idle(h,60);assert(!dw4_dialogue_talk_open(dw4_hubruntime_dialogue(h)));
            /* retail frames, one apart: the HUD and label are gone within a frame of the press, before the window has opened and long
             * before any text shows (the text appears about 20 frames later) */
            step(h,0,0x4000);unsigned hidden_at=0,text_at=0;
            for(unsigned t=1;t<=150 && !text_at;t++){step(h,0,0);if(!hidden_at && dw4_lobby_talk_open(dw4_hubruntime_world(h)))hidden_at=t;if(dw4_dialogue_talk_open(dw4_hubruntime_dialogue(h)))text_at=t;}
            if(!hidden_at || !text_at || hidden_at>3 || hidden_at+10>text_at){fprintf(stderr,"talk: HUD hidden at tick %u, text at %u\n",hidden_at,text_at);assert(0);}
            idle(h,150);assert(dw4_dialogue_talk_open(dw4_hubruntime_dialogue(h)));
            {   /* the close: retail frames bring the HUD back about 11 frames after the window starts closing (its authored range is 16), while the window is still collapsing */
                int hidden=1;unsigned last=0,close_at=0,back_at=0;int still_active=0;static uint8_t ref[3*140*90],f1[3*140*90],f2[3*140*90],f3[3*140*90];int hud_ref_ok=1;(void)hud_ref_ok;
                for(unsigned k=0;k<500 && !back_at;k++){
                    if((k%100==50 && k<=350) && k!=250){step(h,0,0x4000);last=k;}else if(k==230)step(h,4,0);else if(k==250){step(h,0,0x4000);last=k;}else step(h,0,0);   /* page through, move to the last choice (leave, not save) and confirm */
                    const dw4_modelctrl *tw=dw4_lobby_window_model(dw4_hubruntime_world(h),1);
                    if(!close_at && tw && dw4_modelctrl_active(tw) && !strcmp(dw4_modelctrl_sequence(tw),"SQ_CLOSEL"))close_at=k;
                    int now=dw4_lobby_talk_open(dw4_hubruntime_world(h));
                    if(hidden && !now && close_at){back_at=k;still_active=tw && dw4_modelctrl_active(tw);}
                    if(!back_at && !now)hud_ref_ok=0;
                    if(!back_at && now && k>=close_at && close_at)hud_region(h,ref);   /* the last frame with the HUD hidden */
                    hidden=now;(void)last;
                }
                /* the fade-in: the HUD returns at 1/3, 2/3 and full strength over three ticks (retail frames 34, 35, 36 after the press). The reference is a frame
                 * with the HUD hidden; the difference from it grows with the HUD's strength. */
                hud_region(h,f1);step(h,0,0);hud_region(h,f2);step(h,0,0);hud_region(h,f3);
                {double d1=hud_diff(ref,f1),d2=hud_diff(ref,f2),d3=hud_diff(ref,f3);
                 if(!(d1>0 && d1<.7*d3 && d2>d1 && d2<d3*1.02)){fprintf(stderr,"HUD fade-in: differences from the hidden frame %.0f %.0f %.0f\n",d1,d2,d3);assert(0);}}
                idle(h,240);assert(!dw4_dialogue_talk_open(dw4_hubruntime_dialogue(h)));   /* the message is over and control is back before the next case */
                if(!close_at || !back_at || !still_active || back_at-close_at<10 || back_at-close_at>13){
                    fprintf(stderr,"talk close: window closing from tick %u, HUD back at %u (window still active %d)\n",close_at,back_at,still_active);assert(0);}
            }
        }
        const dw4_modelctrl *cursor=find(dw4_hubruntime_models(h),"i_pointcur",4);
        assert(cursor && dw4_modelctrl_active(cursor) && !strcmp(dw4_modelctrl_sequence(cursor),"SQ_OPEN4"));
    }
    if(h)dw4_hubruntime_close(h);
    printf("hub labels: %zu gate, pad, keeper and shop names with their arrow appear in the Terminal, Central and Shop Area and close on leaving\n",sizeof cases/sizeof *cases);
}
/* Walking into a gate with the stick held: when the travel prompt opens, control is off and the player must stand idle (waitS)
 * instead of running in place, however long the stick stays held. */
static void gate_prompt_stops_walking(dw4_mount *mount,const dw4_hubruntime_source *source)
{
    dw4_hubruntime *h=boot_central(mount,source);
    float tx=20,tz=-40;dw4_lobby_walk_state w;int prompt=0;unsigned held=0;
    for(unsigned t=0;t<1500 && held<240;t++){
        dw4_lobby_control_state c;assert(!dw4_lobby_control(dw4_hubruntime_world(h),&c));
        assert(!dw4_lobby_walk(dw4_hubruntime_world(h),&w));
        float yaw=atan2f(tx-w.position[0],tz-w.position[2])-atan2f(c.camera_world[8],c.camera_world[10]);
        dw4_hubruntime_input(h,sinf(yaw),-cosf(yaw),0,0,0); /* the stick stays held the whole time */
        assert(!dw4_hubruntime_tick(h,frame++*1000000000ULL/60));
        if(has_text(h,"STCHGFONT00",NULL))prompt=1;
        if(prompt){held++;if(held>20)assert(!c.player_control && w.motion && !strncmp(w.motion,"wait",4));}
    }
    assert(prompt && held>=240);
    dw4_hubruntime_close(h);
    printf("hub gate: the player stands idle while the travel prompt is open with the stick held\n");
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
    assert(!dw4_playerrecords_create(players,db,0,"p_dorumon","HubTalk",error,sizeof error));
    dw4_hubruntime_source initial={players,&state,NULL,0};
    if(getenv("DW4_READY_SHOT")){dw4_hubruntime *h=boot_central(&mount,&initial);idle(h,120);draw_frame(h,"ready");return 0;}
    idle_panel(&mount,&initial);
    frame=0;gate_prompt_stops_walking(&mount,&initial);
    point_labels(&mount,&initial);
    frame=0;scenario(&mount,&initial,1);
    frame=0;scenario(&mount,&initial,0);
    frame=0;xdata_buy(&mount,&initial,1);
    frame=0;xdata_buy(&mount,&initial,0);
    frame=0;xdata_refuse(&mount,&initial,0);
    frame=0;xdata_refuse(&mount,&initial,1);
    chip_db=db;
    chip_projection(db);
    for(int mode=0;mode<5;mode++){frame=0;xdata_chip(&mount,&initial,mode);}
    dw4_databases_close(db);dw4_stageobjects_close(objects);dw4_scriptengine_close(e);dw4_filelist_close(f);
    dw4_scriptservices_close(host.sd);dw4_playerrecords_close(players);dw4_mount_close(&mount);
    printf("hub GPU: %u service frames match the CPU oracle within tolerance (%u skipped without a GPU context)\n",gpu_checked,gpu_skipped);
    puts("hub talk: registered receivers, live Cross, original dialogue/choices, XDATA service and restored control pass");
    return 0;
}
