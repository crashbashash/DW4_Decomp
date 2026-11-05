#include "dw4/statusview.h"
#include "arenalist.h"
#include "dw4/statusui.h"
#include "dw4/playertransactions.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>
static int emit(dw4_statusview_io io,void *u,int op,const char *g,const char *n,
    const char *k,const char *v,int32_t slot)
{dw4_statusview_command c={op,g,n,k,v,slot};return io(u,&c);}
static const char *const datafonts[]={"font000","font001","font010","font011",
    "font040","font041","font042","font043","font044","font045","font046",
    "font047","font048","font049","font070","font071"};
static const char *const labels[]={"font030","font031","font032","font033","font034",
    "font035","font036","font037","font038","font039","font060","font061"};
static int track(dw4_statusview_io io,void *u,const char *group,const char *name)
{return emit(io,u,DW4_VIEW_TRACK_TEXT,group,name,NULL,NULL,0);}
/* Title01's refresh (425430: SUBWND UPDATE and the i_stdigiface portrait at (-410,240,0)) and its base: the full panel
 * (425e60: i_stbase SQ_LOPEN, the 28 STWINFONT06 rows and STWINFONT04/font001 shown) or the compact shop base (425fb0:
 * j_shbase SQ_OPEN, those rows hidden). */
static int title01_base(dw4_statusview_io io,void *u,int variant,int32_t player,int32_t digimon)
{
    static const char *const face[]={"SQ_agumonOPEN","SQ_vmonOPEN","SQ_girumonOPEN",
        "SQ_dorumonOPEN","SQ_weregaruOPEN","SQ_hekabutOPEN","SQ_wargreyOPEN",
        "SQ_angelrOPEN","SQ_beelzebOPEN","SQ_alphaOPEN","SQ_bwargreyOPEN",
        "SQ_impdrafmOPEN","SQ_impdrapmOPEN","SQ_metalgaruOPEN","SQ_dukecrimOPEN","SQ_susanooOPEN"};
    char positioned[80];snprintf(positioned,sizeof positioned,"%s/V<-410,240,0>",face[digimon>=0 && digimon<16?digimon:0]);
    if(emit(io,u,DW4_VIEW_REFRESH,NULL,NULL,NULL,NULL,player) ||
       emit(io,u,DW4_VIEW_MODEL,NULL,"i_stdigiface",positioned,"SQ_CLOSE",player) ||
       emit(io,u,DW4_VIEW_MODEL,NULL,variant?"j_shbase":"i_stbase",variant?"SQ_OPEN":"SQ_LOPEN","SQ_CLOSE",player))return -1;
    for(size_t i=0;i<28;i++)if(emit(io,u,DW4_VIEW_SWITCH,"STWINFONT06",i<12?labels[i]:datafonts[i-12],NULL,variant?"DISPOFF":"DISPON",0))return -1;
    return emit(io,u,DW4_VIEW_SWITCH,"STWINFONT04","font001",NULL,variant?"DISPOFF":"DISPON",0);
}
/* 43dc10 row counts by entry code; 0 for the unimplemented player chooser and unknown codes. */
static int talk_rows(int32_t code)
{
    switch(code){case 1:return 3;case 2:case 3:case 4:return 4;case 1262:case 1268:case 2003:case 2005:case 2008:return 2;default:return 0;}
}
/* The row count of a talk menu: the fixed codes, or the caller's player count for the chooser (callno -1). */
static int talk_rows_for(int32_t code,int32_t rows){return code==-1?rows:talk_rows(code);}
int dw4_statusview_setup(int kind,int variant,int32_t player,int32_t digimon,
    int32_t callno,dw4_statusview_io io,void *u)
{
    if(!io || player<0 || player>3)return -1;
    if(kind==DW4_STATUS_TITLE00){
        if(emit(io,u,DW4_VIEW_MODEL,NULL,"i_stback","SQ_OPEN","SQ_CLOSE",0) ||
           emit(io,u,DW4_VIEW_MODEL,NULL,"i_bgclear","SQ_OPEN","SQ_CLOSE",0))return -1;
    }else if(kind==DW4_STATUS_TITLE01){
        for(size_t i=0;i<12;i++)if(track(io,u,"STWINFONT06",labels[i]))return -1;
        if(emit(io,u,DW4_VIEW_TEXT,"STWINFONT02","font000","LEFT"," ",0) ||
           emit(io,u,DW4_VIEW_TEXT,"STWINFONT04","font000","CENTER"," ",0) ||
           emit(io,u,DW4_VIEW_TEXT,"STWINFONT04","font001","LEFT"," ",0))return -1;
        for(size_t i=0;i<16;i++)if(emit(io,u,DW4_VIEW_TEXT,"STWINFONT06",datafonts[i],"RIGHT"," ",0))return -1;
        if(emit(io,u,DW4_VIEW_SCRIPT,NULL,"txt_status.lua",NULL,NULL,3) || title01_base(io,u,variant,player,digimon))return -1;
    }else if(kind==DW4_STATUS_TITLE02){
        if(emit(io,u,DW4_VIEW_MODEL,NULL,"i_messwn","SQ_STOPEN","SQ_STCLOSE",0))return -1;
    }else if(kind==DW4_STATUS_TITLE03 || kind==DW4_STATUS_TITLE04 || kind==DW4_STATUS_SELECT00){
        const char *group=kind==DW4_STATUS_TITLE03?"STWINFONT34":kind==DW4_STATUS_TITLE04?"STWINFONT12":"STWINFONT08";
        const char *model=kind==DW4_STATUS_TITLE03?"i_staccount":kind==DW4_STATUS_TITLE04?"i_sttitle":"i_stmenu01";
        const char *open=kind==DW4_STATUS_SELECT00?"SQ_3LINEUPOPEN":"SQ_OPEN";
        if(emit(io,u,DW4_VIEW_MODEL,NULL,model,open,"SQ_CLOSE",0))return -1;
        unsigned count=kind==DW4_STATUS_TITLE04?1:3;
        for(unsigned i=0;i<count;i++){char font[16];snprintf(font,sizeof font,"font%03u",i);if(track(io,u,group,font))return -1;}
        int32_t textcall=kind==DW4_STATUS_TITLE03?0:kind==DW4_STATUS_SELECT00?15:callno;
        if(emit(io,u,DW4_VIEW_SCRIPT,NULL,"txt_status.lua",NULL,NULL,textcall))return -1;
    }else if(kind==DW4_STATUS_SELECT01 || kind==DW4_STATUS_SELECTE0 || kind==DW4_STATUS_SELECTE1){
        if(kind==DW4_STATUS_SELECT01){
            const char *open=callno==61?"SQ_4LINEOPEN":"SQ_3LINEDOWNOPEN";
            if(callno!=31 && callno!=61 && callno!=91)return -1;
            if(emit(io,u,DW4_VIEW_MODEL,NULL,"i_stmenu01",open,"SQ_CLOSE",0))return -1;
        }
        if(kind!=DW4_STATUS_SELECTE1){
            if(emit(io,u,DW4_VIEW_TEXT,"STWINFONT29","font100","LEFT"," ",0))return -1;
            int count=kind==DW4_STATUS_SELECT01?4:3;
            for(int i=0;i<count;i++){char font[16];snprintf(font,sizeof font,"font%03d",i);
                if(emit(io,u,DW4_VIEW_TEXT,kind==DW4_STATUS_SELECT01?"STWINFONT09":"STWINFONT29",font,"LEFT"," ",0))return -1;}
            if(callno>0 && emit(io,u,DW4_VIEW_SCRIPT,NULL,"txt_status.lua",NULL,NULL,callno))return -1;
        }
    }else if(kind==DW4_STATUS_SHOPSELECT00){
        /* variant 1: the caller-provided _fontName font100 (XDATA chip's empty-list notice). */
        if(callno>0 && (track(io,u,"STWINFONT29",variant==1?"font100":"font000") ||
           emit(io,u,DW4_VIEW_SCRIPT,NULL,"txt_shop.lua",NULL,NULL,callno)))return -1;
    }else if(kind==DW4_STATUS_SHOPSELECT34){
        for(unsigned i=0;i<7;i++){
            char font[16];snprintf(font,sizeof font,"font%03u",i);
            const char *g=variant==3?"STWINFONT28":"STWINFONT25";
            if(emit(io,u,DW4_VIEW_ALIGN,g,font,NULL,"CENTER",0))return -1;
            if(variant!=3)for(unsigned j=1;j<=2;j++){
                snprintf(font,sizeof font,"font0%u%u",j,i);
                if(emit(io,u,DW4_VIEW_ALIGN,g,font,NULL,"CENTER",0))return -1;
            }
        }
    }else if(kind==DW4_STATUS_TALKSELECT03){
        if(callno>0 && (track(io,u,"TALKFONT01","font00") || emit(io,u,DW4_VIEW_SCRIPT,NULL,"txt_shop.lua",NULL,NULL,callno)))return -1;
    }else if(kind==DW4_STATUS_TALKSELECT02){
        if(callno==-1){
            /* 43dc10 case -1: the species line (TALKFONT04) is tracked beside the name; rows is the joined-player count. */
            if(variant<1 || variant>4)return -1;
            for(int i=1;i<=variant;i++){char font[16];snprintf(font,sizeof font,"font%02d",i);
                if(track(io,u,"TALKFONT01",font) || track(io,u,"TALKFONT04",font))return -1;}
            return 0;
        }
        int rows=talk_rows(callno);
        if(rows<2)return -1;
        for(int i=1;i<=rows;i++){char font[16];snprintf(font,sizeof font,"font%02d",i);if(track(io,u,"TALKFONT01",font))return -1;}
        if(emit(io,u,DW4_VIEW_SCRIPT,NULL,"txt_shop.lua",NULL,NULL,callno==1?0x7F2:callno>=2 && callno<=4?0x7EE:callno))return -1;
    }else if(kind==DW4_STATUS_CARDPAGE){
        /* 440670: the album window opens, STWINFONT34 font000/font001 are tracked and filled by txt_shop 0x7D1, and the
         * page counter (STWINFONT33 font000 / font001) starts blank and centred. */
        if(emit(io,u,DW4_VIEW_MODEL,NULL,"j_shcardwin","SQ_OPEN","SQ_CLOSE",0) || track(io,u,"STWINFONT34","font000") ||
           track(io,u,"STWINFONT34","font001") || emit(io,u,DW4_VIEW_SCRIPT,NULL,"txt_shop.lua",NULL,NULL,0x7D1) ||
           emit(io,u,DW4_VIEW_TEXT,"STWINFONT33","font000","CENTER"," ",0) || emit(io,u,DW4_VIEW_TEXT,"STWINFONT33","font001","CENTER"," ",0))return -1;
    }else if(kind!=DW4_STATUS_SHOPSELECT52 && kind!=DW4_STATUS_XDATAMENU && kind!=DW4_STATUS_XDATASTAT && kind!=DW4_STATUS_SHOPSELECTB0)return -1;
    return 0;
}
struct view {
    dw4_statusview_context c;int kind;
    dw4_menu_window *self;
    char error[256];
    int failed;
};
static int selection_kind(int kind)
{return kind==DW4_STATUS_SELECT00 || (kind>=DW4_STATUS_SELECT01 && kind<=DW4_STATUS_SELECTE1) || (kind>=DW4_STATUS_SHOPSELECT00 && kind<=DW4_STATUS_CARDPAGE);}
static beNDMWWindowSelect *selector_data(const struct view *v)
{return DW4_ARENA_OBJ(v->self->arena,beNDMWWindowSelect,v->self->object);}
static const uint8_t *selector_flags(const struct view *v)
{return selection_kind(v->kind)?al_data(v->self->arena,selector_data(v)->_decideList,1):NULL;}
static float selector_position(const struct view *v,int axis)
{float f;memcpy(&f,selector_data(v)->_offsetPos+axis,4);return f;}
static int view_variant(const struct view *v)
{
    if(v->kind==DW4_STATUS_TITLE01 || v->kind==DW4_STATUS_SHOPSELECT34 || v->kind==DW4_STATUS_SHOPSELECT52)return dw4_menu_window_data(v->self)->_entCode;
    if(v->kind==DW4_STATUS_SHOPSELECT00){const beNDMWShopSelect00 *d=DW4_ARENA_OBJ(v->self->arena,beNDMWShopSelect00,v->self->object);
        const char *s=al_text(v->self->arena,d->_panelName);return s && !strcmp(s,"font100");}
    if(v->kind==DW4_STATUS_TALKSELECT02 && dw4_menu_window_data(v->self)->_entCode==-1)return selector_data(v)->_selectMax;
    return 0;
}
static const char *selection_cursor(const struct view *v,const char *name)
{if(v->self && selection_kind(v->kind)){const char *s=al_text(v->self->arena,selector_data(v)->_infoName);if(s)return s;}
 return v->kind==DW4_STATUS_SELECTE0?"i_stmesscr":v->kind==DW4_STATUS_SELECTE1?"i_stcursor01":v->kind==DW4_STATUS_SHOPSELECT00?"i_stmessky":v->kind==DW4_STATUS_SHOPSELECT34?"i_stcursor03":v->kind==DW4_STATUS_SHOPSELECT52?"i_stcursor05":v->kind==DW4_STATUS_XDATAMENU || v->kind==DW4_STATUS_SHOPSELECTB0?"i_stmesscr":v->kind==DW4_STATUS_XDATASTAT?"i_stcursor01":v->kind==DW4_STATUS_TALKSELECT03?"i_messky":v->kind==DW4_STATUS_TALKSELECT02?"i_messcr":v->kind==DW4_STATUS_CARDPAGE?"j_shcardcursor":name;}
static dw4_script_value str(const char *s){return (dw4_script_value){DW4_SCRIPT_STRING,0,s,strlen(s)};}
static int sd(struct view *v,int query,const char *category,const char *name,int32_t slot,
    const char *key,const char *value)
{
    dw4_script_value a[]={str(category),name?str(name):(dw4_script_value){0},
        {DW4_SCRIPT_NUMBER,slot,NULL,0},str(key),{0}},r={0};
    if(value)a[4]=str(value);
    if(dw4_scriptservices_call(v->c.sd,query?"querySD":"sd",a,value?5:4,&r,v->error,sizeof v->error))return -2;
    if(query){
        if(r.type!=DW4_SCRIPT_NUMBER || !isfinite(r.number) || r.number<INT32_MIN || r.number>INT32_MAX || floor(r.number)!=r.number){
            snprintf(v->error,sizeof v->error,"STATUS %s query %s unavailable",name,key);return -2;}
        return (int32_t)r.number;
    }
    return 0;
}
static int textcommand(struct view *v,const char *group,const char *name,const char *key,const char *value)
{char encoded[8192];int n=snprintf(encoded,sizeof encoded,"%s/%s/%s",group,name,value);
 if(n<0 || (size_t)n>=sizeof encoded)return -1;
 return sd(v,0,"TEXTCTL",NULL,-1,key,encoded);}
/* Recovered close-list fields: PresentModel/ClearQueuedText/PlayQueuedModelClose.
 * Preserve the native adapter's deduplication and close/poll order. */
static int model_track(struct view *v,const char *name,int32_t slot,const char *close)
{
    dw4_arena *a=v->self->arena;beNDMWWindow *w=dw4_menu_window_data(v->self);
    int n=al_count(a,w->_modelCloseInfoNameList),i;
    int32_t *names=al_words(a,w->_modelCloseInfoNameList),*slots=al_words(a,w->_modelCloseRamNoList);
    for(i=0;i<n;i++)if(slots[i]==slot && !strcmp(al_text(a,names[i]),name))break;
    if(i==n && n==4)return -1;
    int32_t c=al_string(a,close),nm=i==n?al_string(a,name):0;
    if(!c || (i==n && !nm)){al_free(a,c);al_free(a,nm);return -1;}
    if(i==n && (al_reserve(a,w->_modelCloseInfoNameList,4,n+1) || al_reserve(a,w->_modelCloseRamNoList,4,n+1) || al_reserve(a,w->_modelCloseSeqNameList,4,n+1))){
        al_free(a,c);al_free(a,nm);return -1;
    }
    int32_t *closes=al_list(a,w->_modelCloseSeqNameList)->_capacity?dw4_arena_at(a,al_handle(al_list(a,w->_modelCloseSeqNameList)->_data),(uint32_t)al_list(a,w->_modelCloseSeqNameList)->_capacity*4):NULL;
    if(i<n){al_free(a,closes[i]);closes[i]=c;return 0;}
    ((int32_t *)dw4_arena_at(a,al_handle(al_list(a,w->_modelCloseInfoNameList)->_data),(uint32_t)(n+1)*4))[n]=nm;
    ((int32_t *)dw4_arena_at(a,al_handle(al_list(a,w->_modelCloseRamNoList)->_data),(uint32_t)(n+1)*4))[n]=slot;
    closes[n]=c;
    al_list(a,w->_modelCloseInfoNameList)->_count=al_list(a,w->_modelCloseRamNoList)->_count=al_list(a,w->_modelCloseSeqNameList)->_count=n+1;
    return 0;
}
static int text_track(struct view *v,const char *group,const char *name)
{
    dw4_arena *a=v->self->arena;beNDMWWindow *w=dw4_menu_window_data(v->self);
    int n=al_count(a,w->_textCloseTypeList);int32_t *groups=al_words(a,w->_textCloseTypeList),*names=al_words(a,w->_textCloseNameList);
    for(int i=0;i<n;i++)if(!strcmp(al_text(a,groups[i]),group) && !strcmp(al_text(a,names[i]),name))return 0;
    if(n==64)return -1;
    int32_t g=al_string(a,group),nm=al_string(a,name);
    if(!g || !nm || al_reserve(a,w->_textCloseTypeList,4,n+1) || al_reserve(a,w->_textCloseNameList,4,n+1)){
        al_free(a,g);al_free(a,nm);return -1;
    }
    ((int32_t *)dw4_arena_at(a,al_handle(al_list(a,w->_textCloseTypeList)->_data),(uint32_t)(n+1)*4))[n]=g;
    ((int32_t *)dw4_arena_at(a,al_handle(al_list(a,w->_textCloseNameList)->_data),(uint32_t)(n+1)*4))[n]=nm;
    al_list(a,w->_textCloseTypeList)->_count=al_list(a,w->_textCloseNameList)->_count=n+1;return 0;
}
static int native_emit(void *u,const dw4_statusview_command *c)
{
    struct view *v=u;
    if(c->op==DW4_VIEW_MODEL){
        if(model_track(v,c->name,c->slot,c->value))return -1;
        const char *position=strstr(c->key,"/V<");
        if(position){
            char sequence[128];size_t n=(size_t)(position-c->key);float x,y,z;int used=0;
            if(n>=sizeof sequence || sscanf(position,"/V<%f,%f,%f>%n",&x,&y,&z,&used)!=3 || position[used])return -1;
            memcpy(sequence,c->key,n);sequence[n]=0;
            return dw4_statusui_positioned(&v->c,c->name,c->slot,sequence,x,y,z,v->error,sizeof v->error);
        }
        return sd(v,0,"MODELCTRL",c->name,c->slot,"GENERATE",c->key);
    }
    if(c->op==DW4_VIEW_TRACK_TEXT || c->op==DW4_VIEW_TEXT){
        if(text_track(v,c->group,c->name))return -1;
        if(c->op==DW4_VIEW_TEXT){
            if(textcommand(v,c->group,c->name,"ALIGN",c->key) || textcommand(v,c->group,c->name,"TEXTSET",c->value))return -1;
            return textcommand(v,c->group,c->name,"SWITCH","DISPON");
        }
        return 0;
    }
    if(c->op==DW4_VIEW_SCRIPT){
        int rc=dw4_scriptengine_text_event(v->c.engine,v->c.scope,c->name,c->slot);
        if(rc)snprintf(v->error,sizeof v->error,"%s",dw4_scriptengine_error(v->c.engine));
        return rc;
    }
    if(c->op==DW4_VIEW_SWITCH)return textcommand(v,c->group,c->name,"SWITCH",c->value);
    if(c->op==DW4_VIEW_COLOR)return textcommand(v,c->group,c->name,c->key,c->value?c->value:"");
    if(c->op==DW4_VIEW_SET_TEXT)return textcommand(v,c->group,c->name,"TEXTSET",c->value);
    if(c->op==DW4_VIEW_ALIGN)return textcommand(v,c->group,c->name,"ALIGN",c->value);
    if(c->op==DW4_VIEW_REFRESH){
        if(!v->c.refresh){snprintf(v->error,sizeof v->error,"STATUS Title01 requires a native stat refresh owner");return -1;}
        return v->c.refresh(v->c.user,c->slot,v->error,sizeof v->error);
    }
    return -1;
}
static int close_models(struct view *v)
{
    dw4_arena *a=v->self->arena;beNDMWWindow *w=dw4_menu_window_data(v->self);
    int n=al_count(a,w->_modelCloseInfoNameList);
    for(int i=0;i<n;i++)if(sd(v,0,"MODELCTRL",al_text(a,al_words(a,w->_modelCloseInfoNameList)[i]),al_words(a,w->_modelCloseRamNoList)[i],al_text(a,al_words(a,w->_modelCloseSeqNameList)[i]),NULL))return -1;
    return 0;
}
static int clear_text(struct view *v)
{
    dw4_arena *a=v->self->arena;beNDMWWindow *w=dw4_menu_window_data(v->self);
    int n=al_count(a,w->_textCloseTypeList);
    for(int i=0;i<n;i++)if(textcommand(v,al_text(a,al_words(a,w->_textCloseTypeList)[i]),al_text(a,al_words(a,w->_textCloseNameList)[i]),"SWITCH","DISPOFF"))return -1;
    return 0;
}
static int finished(struct view *v)
{
    dw4_arena *a=v->self->arena;beNDMWWindow *w=dw4_menu_window_data(v->self);
    int n=al_count(a,w->_modelCloseInfoNameList);
    for(int i=0;i<n;i++){int q=sd(v,1,"MODELCTRL",al_text(a,al_words(a,w->_modelCloseInfoNameList)[i]),al_words(a,w->_modelCloseRamNoList)[i],"ISRUN",NULL);if(q<0)return -1;if((uint8_t)q)return 0;}
    return 1;
}
static void release(void *u)
{
    struct view *v=u;dw4_arena *a=v->self->arena;beNDMWWindow *w=dw4_menu_window_data(v->self);
    al_strings_drop(a,&w->_textCloseTypeList);al_strings_drop(a,&w->_textCloseNameList);
    if(selection_kind(v->kind)){
        beNDMWWindowSelect *d=selector_data(v);al_drop(a,&d->_decideList);al_free(a,d->_infoName);
        if(v->kind==DW4_STATUS_SHOPSELECT00)al_free(a,DW4_ARENA_OBJ(a,beNDMWShopSelect00,v->self->object)->_panelName);
    }
    al_strings_drop(a,&w->_modelCloseInfoNameList);al_strings_drop(a,&w->_modelCloseSeqNameList);al_drop(a,&w->_modelCloseRamNoList);free(v);
}
/* 43d450 classification: recognized entry codes fix the choice count. */
static int xdata_menu_rows(int32_t code,int fallback)
{
    static const int32_t triples[]={0x79e,0x73a,0x6d6,0x672,0x60e,0x546,0x47e};
    static const int32_t pairs[]={0x7aa,0x5ad,0x61a,0x740,0x6dc,0x678,0x614,0x54b,0x4f8,0x4ea,0x4e7,0x493,0x48e,0x48b};
    for(size_t i=0;i<sizeof triples/sizeof *triples;i++)if(triples[i]==code)return 3;
    for(size_t i=0;i<sizeof pairs/sizeof *pairs;i++)if(pairs[i]==code)return 2;
    return fallback;
}
static int xdata_menu_setup(struct view *v)
{
    int rows=xdata_menu_rows(dw4_menu_window_data(v->self)->_entCode,0);
    for(int i=0;i<rows;i++){char font[16];snprintf(font,sizeof font,"font%03d",i);
        if(track(native_emit,v,"STWINFONT29",font))return -1;}
    return rows && emit(native_emit,v,DW4_VIEW_SCRIPT,NULL,"txt_shop.lua",NULL,NULL,dw4_menu_window_data(v->self)->_entCode)?-1:0;
}
/* 43fb70: price and colour per stat; capped stats show ---- in the exact retail colour. */
static int xdata_costs(struct view *v)
{
    static const char *const fonts[]={"font000","font001","font002","font003","font004","font005","font006"};
    dw4_property_folder *f=dw4_playerrecords_get(v->c.players,"GETPLAYER",v->c.player);
    for(int i=0;i<7;i++){
        const char *key;int32_t limit,stat;
        if(!f || dw4_xdata_stat(i,&key,&limit,NULL) || dw4_property_number(f,key,&stat)){
            snprintf(v->error,sizeof v->error,"XDATA stat %d record unavailable",i);return -1;}
        char text[16];
        if(stat<limit)snprintf(text,sizeof text,"%d",dw4_xdata_price(stat));else snprintf(text,sizeof text,"----");
        if(emit(native_emit,v,DW4_VIEW_SET_TEXT,"STWINFONT19",fonts[i],NULL,text,0))return -1;
        if(stat<limit){if(emit(native_emit,v,DW4_VIEW_COLOR,"STWINFONT14",fonts[i],"DEFAULTCOLOR",NULL,0))return -1;}
        else {
            char color[64];uint32_t bits[3]={0x3f666666,0x3ecccccd,0x3e4ccccd};float c[3];memcpy(c,bits,sizeof c);
            snprintf(color,sizeof color,"V<%.9g,%.9g,%.9g>",(double)c[0],(double)c[1],(double)c[2]);
            if(emit(native_emit,v,DW4_VIEW_COLOR,"STWINFONT14",fonts[i],"COLOR",color,0))return -1;
        }
    }
    return 0;
}
static int xdata_stat_setup(struct view *v)
{
    static const char *const fonts[]={"font000","font001","font002","font003","font004","font005","font006"};
    if(emit(native_emit,v,DW4_VIEW_MODEL,NULL,"j_shwin","SQ_XDATASTATUSOPEN","SQ_CLOSE",0))return -1;
    if(track(native_emit,v,"STWINFONT29","font100") || emit(native_emit,v,DW4_VIEW_SCRIPT,NULL,"txt_shop.lua",NULL,NULL,1153) ||
       track(native_emit,v,"STWINFONT13","font000") || track(native_emit,v,"STWINFONT35","font001") ||
       emit(native_emit,v,DW4_VIEW_SCRIPT,NULL,"txt_shop.lua",NULL,NULL,1101))return -1;
    for(int i=0;i<7;i++)if(track(native_emit,v,"STWINFONT14",fonts[i]))return -1;
    if(emit(native_emit,v,DW4_VIEW_SCRIPT,NULL,"txt_shop.lua",NULL,NULL,1103))return -1;
    for(int i=0;i<7;i++)if(emit(native_emit,v,DW4_VIEW_TEXT,"STWINFONT19",fonts[i],"RIGHT"," ",0))return -1;
    if(emit(native_emit,v,DW4_VIEW_TEXT,"STWINFONT29","font000","LEFT"," ",0))return -1;
    /* RECALCPLAYER with an explicit false: prices use stats without equipment bonuses. */
    dw4_script_value a[]={str("GAMERAM"),{0},{DW4_SCRIPT_NUMBER,v->c.player,NULL,0},str("RECALCPLAYER"),str("FALSE")},r={0};
    if(dw4_scriptservices_call(v->c.sd,"sd",a,5,&r,v->error,sizeof v->error))return -1;
    if(xdata_costs(v))return -1;
    return emit(native_emit,v,DW4_VIEW_SCRIPT,NULL,"txt_shop.lua",NULL,NULL,1154+selector_data(v)->_startPoint);
}
static int select_io(void *u,int op,const char *name,const char *key,int32_t value)
{
    struct view *v=u;
    if(op==DW4_STATUS_SELECT_INIT){
        if(dw4_statusview_setup(v->kind,view_variant(v),v->c.player,0,dw4_menu_window_data(v->self)->_entCode,native_emit,v))return -1;
        if(v->c.selection_initialize && v->c.selection_initialize(v->c.user,native_emit,v))return -1;
        if(v->kind==DW4_STATUS_XDATAMENU && xdata_menu_setup(v))return -1;
        if(v->kind==DW4_STATUS_XDATASTAT && xdata_stat_setup(v))return -1;
        if(v->kind==DW4_STATUS_SHOPSELECTB0) {
            /* 440a20: font100 prompt and both row fonts are tracked, then txt_shop 0x625 fills the rows; each
             * row is coloured from the decide list (CANCELCOLOR for a disabled row; the Sell controller resets both to
             * DEFAULTCOLOR after the menu closes, so a menu without a list shows both rows normally). */
            if(track(native_emit,v,"STWINFONT29","font100") || track(native_emit,v,"STWINFONT29","font000") ||
               track(native_emit,v,"STWINFONT29","font001") ||
               emit(native_emit,v,DW4_VIEW_SCRIPT,NULL,"txt_shop.lua",NULL,NULL,0x625))return -1;
            for(int i=0;i<2;i++){char font[16];snprintf(font,sizeof font,"font%03d",i);
                if(emit(native_emit,v,DW4_VIEW_COLOR,"STWINFONT29",font,!selector_flags(v) || selector_flags(v)[i]?"DEFAULTCOLOR":"CANCELCOLOR",NULL,0))return -1;}
        }
        if(v->kind==DW4_STATUS_SELECTE0 && selector_flags(v))for(int i=0;i<selector_data(v)->_selectMax;i++){
            char font[16];snprintf(font,sizeof font,"font%03d",i);
            if(emit(native_emit,v,DW4_VIEW_COLOR,"STWINFONT29",font,selector_flags(v)[i]?"DEFAULTCOLOR":"CANCELCOLOR",NULL,0))return -1;
        }
        int rows=v->kind==DW4_STATUS_SELECT00?3:v->kind==DW4_STATUS_SELECT01?(dw4_menu_window_data(v->self)->_entCode==61?4:3):selector_data(v)->_selectMax;
        int selected=v->kind<=DW4_STATUS_SELECT00?value:selector_data(v)->_startPoint;
        float x=-83,y=v->kind==DW4_STATUS_SELECT00?209:172,z=0;
        if(v->kind>=DW4_STATUS_SELECTE0){x=selector_position(v,0);y=selector_position(v,1);z=selector_position(v,2);}
        if(v->kind==DW4_STATUS_SHOPSELECT34){rows=7;selected=6;x=view_variant(v)==3?147:-20;y=view_variant(v)==3?-2:view_variant(v)==1?-1:138;z=0;}
        if(v->kind==DW4_STATUS_SHOPSELECT52){rows=view_variant(v);selected=rows-1;}
        if(v->kind==DW4_STATUS_XDATAMENU){rows=xdata_menu_rows(dw4_menu_window_data(v->self)->_entCode,selector_data(v)->_selectMax);selected=selector_data(v)->_startPoint;x=y=z=0;}
        if(v->kind==DW4_STATUS_SHOPSELECTB0){rows=2;selected=selector_data(v)->_startPoint;x=y=z=0;}
        if(v->kind==DW4_STATUS_TALKSELECT03){rows=1;selected=0;x=y=z=0;}
        if(v->kind==DW4_STATUS_TALKSELECT02){rows=talk_rows_for(dw4_menu_window_data(v->self)->_entCode,selector_data(v)->_selectMax);selected=selector_data(v)->_startPoint;x=y=z=0;}
        if(v->kind==DW4_STATUS_CARDPAGE){rows=9;selected=selector_data(v)->_startPoint;x=y=z=0;}
        if(v->kind==DW4_STATUS_XDATASTAT){rows=7;selected=selector_data(v)->_startPoint;x=-121;y=128;z=0;}
        beNDMWWindowSelect *d=selector_data(v);d->_selectMax=rows;d->_startPoint=selected;
        float position[3]={x,y,z};memcpy(d->_offsetPos,position,sizeof position);
        char args[2048];int len=snprintf(args,sizeof args,"I<%d,%d>/V<%.9g,%.9g,%.9g>",rows,selected,x,y,z);
        if(selector_flags(v))for(int i=0;i<rows;i++)len+=snprintf(args+len,sizeof args-(size_t)len,"/%s",selector_flags(v)[i]?"TRUE":"FALSE");
        return sd(v,0,"SELECTCTRL",selection_cursor(v,name),v->c.player,"GENERATE",args);
    }
    if(op==DW4_STATUS_CLOSE_MODELS)return close_models(v);
    if(op==DW4_STATUS_CLEAR_TEXT)return clear_text(v);
    if(op==DW4_STATUS_FINISHED)return finished(v);
    const char *cursor=selection_cursor(v,name);
    if(op==DW4_STATUS_SELECT_TOP && v->kind>=DW4_STATUS_SELECTE0){
        char args[2048];int len=snprintf(args,sizeof args,"I<%d>",selector_data(v)->_selectMax);
        if(selector_flags(v))for(int i=0;i<selector_data(v)->_selectMax;i++)len+=snprintf(args+len,sizeof args-(size_t)len,"/%s",selector_flags(v)[i]?"TRUE":"FALSE");
        return sd(v,0,"SELECTCTRL",cursor,v->c.player,key,args);
    }
    int q=sd(v,op!=DW4_STATUS_SELECT_TOP,"SELECTCTRL",cursor,v->c.player,key,NULL);
    if(op==DW4_STATUS_SELECT_GET && q>=-1 && v->c.parent_window && !v->c.parent)
        dw4_menu_window_data(v->c.parent_window)->_retCode=q;
    /* 423700 returns !ISFO2TOP: the window's state-four route runs only
     * when the underlying selector is at its input top. */
    return op==DW4_STATUS_SELECT_IS_TOP && q>=0?!q:q;
}
static int update(dw4_menu_window *w,char *error,size_t cap)
{
    struct view *v=w->user;int rc=0;
    if(v->failed){snprintf(error,cap,"STATUS view failed; scene reset required");return -1;}
    if(selection_kind(v->kind)){
        dw4_statusctrl state,parent;dw4_statusctrl_load(w,&state);
        dw4_statusctrl *target=v->c.parent;
        if(v->c.parent_window && !v->c.parent){dw4_statusctrl_load(v->c.parent_window,&parent);target=&parent;}
        rc=dw4_statusselect_tick(&state,target,select_io,v);dw4_statusctrl_store(w,&state);
    }else if(dw4_menu_window_data(w)->_st0==0){
        int32_t digimon=0;
        if(v->kind==DW4_STATUS_TITLE01 && dw4_property_number(dw4_playerrecords_get(v->c.players,"GETPLAYER",v->c.player),"DIGIMONNO",&digimon)){
            snprintf(v->error,sizeof v->error,"STATUS Title01 requires DIGIMONNO");rc=-1;
        }else rc=v->kind==DW4_STATUS_CONTENT?v->c.initialize(v->c.user,native_emit,v):
            dw4_statusview_setup(v->kind,view_variant(v),v->c.player,digimon,dw4_menu_window_data(v->self)->_entCode,native_emit,v);
        if(!rc){dw4_menu_window_data(w)->_st0=1;dw4_menu_window_data(w)->_st1=dw4_menu_window_data(w)->_st2=dw4_menu_window_data(w)->_st3=0;}
    }else if(dw4_menu_window_data(w)->_st0==2){
        rc=close_models(v);if(!rc)rc=clear_text(v);
        if(!rc){dw4_menu_window_data(w)->_st0=3;dw4_menu_window_data(w)->_st1=dw4_menu_window_data(w)->_st2=dw4_menu_window_data(w)->_st3=0;}
    }else if(dw4_menu_window_data(w)->_st0==3){int q=finished(v);if(q<0)rc=-1;else if(q && !dw4_menu_window_count(w))dw4_menu_window_data(w)->_isRun=0;}
    if(rc){v->failed=1;snprintf(error,cap,"STATUS view %d: %s",v->kind,v->error[0]?v->error:"setup failed");}
    return rc;
}
dw4_menu_window *dw4_statusview_window_open(int kind,const dw4_statusview_context *c)
{
    if(!c || !c->sd || !c->engine || c->player<0 || c->player>3 || kind<DW4_STATUS_TITLE00 || (kind>DW4_STATUS_SELECT00 && (kind<DW4_STATUS_SELECT01 || kind>DW4_STATUS_CARDPAGE)) ||
       (selection_kind(kind) && !c->parent && !c->parent_window) ||
       (kind==DW4_STATUS_CONTENT && !c->initialize) || (kind==DW4_STATUS_TITLE01 && (!c->players || !c->refresh)))return NULL;
    if(kind==DW4_STATUS_SELECT01 && c->callno!=31 && c->callno!=61 && c->callno!=91)return NULL;
    if((kind==DW4_STATUS_SELECTE0 || kind==DW4_STATUS_SELECTE1 || kind==DW4_STATUS_SHOPSELECT00) && (c->rows<1 || c->rows>256 || c->selected<0 || c->selected>=c->rows))return NULL;
    if((kind==DW4_STATUS_SELECTE0 && c->rows>3) || (kind==DW4_STATUS_SHOPSELECT00 && c->rows!=1))return NULL;
    if(kind==DW4_STATUS_SHOPSELECT52 && (c->variant<1 || c->variant>9))return NULL;
    if(kind==DW4_STATUS_SHOPSELECTB0 && (c->rows!=2 || c->selected<0 || c->selected>=2))return NULL;
    if(kind==DW4_STATUS_TALKSELECT03 && (c->rows!=1 || c->selected!=0 || c->callno<=0))return NULL;
    if(kind==DW4_STATUS_TALKSELECT02 && c->callno==-1){if(c->rows<1 || c->rows>4 || c->variant!=c->rows || c->selected<0 || c->selected>=c->rows)return NULL;}
    else if(kind==DW4_STATUS_TALKSELECT02 && (talk_rows(c->callno)<2 || c->rows!=talk_rows(c->callno) || c->selected<0 || c->selected>=c->rows))return NULL;
    if(kind==DW4_STATUS_CARDPAGE && (c->rows!=9 || c->selected<0 || c->selected>=9))return NULL;
    if(kind==DW4_STATUS_XDATAMENU){int rows=xdata_menu_rows(c->callno,c->rows);if(rows<1 || rows>256 || c->selected<0 || c->selected>=rows || c->callno<=0)return NULL;}
    if(kind==DW4_STATUS_XDATASTAT && (c->selected<0 || c->selected>6 || !c->players))return NULL;
    for(int i=0;selection_kind(kind) && i<3;i++)if(!isfinite(c->position[i]))return NULL;
    struct view *v=calloc(1,sizeof(*v));if(!v)return NULL;
    v->c=*c;v->kind=kind;
    const char *name="beNDMWWindowTitle";
    static const char *const classes[]={"beNDMWStatusTitle00","beNDMWStatusTitle01","beNDMWStatusTitle02","beNDMWStatusTitle03","beNDMWStatusTitle04","beNDMWStatusSelect00"};
    if(kind<=DW4_STATUS_SELECT00)name=classes[kind];
    else if(selection_kind(kind)){
        static const char *const selectors[]={"beNDMWStatusSelect01","beNDMWStatusSelectE0","beNDMWStatusSelectE1",NULL,"beNDMWShopSelect00","beNDMWShopSelect34","beNDMWShopSelect52","beNDMWShopSelect01","beNDMWShopSelect11","beNDMWShopSelectB0","beNDMWShopSelect03","beNDMWShopSelect02","beNDMWShopSelectA0"};
        name=selectors[kind-DW4_STATUS_SELECT01];
    }
    dw4_menu_window *w=dw4_menu_window_open_class(name,update,v,release);if(!w){free(v);return NULL;}
    v->self=w;beNDMWWindow *data=dw4_menu_window_data(w);
    data->_textCloseTypeList=al_new(w->arena,"igStringRefList",4,0,NULL);
    data->_textCloseNameList=al_new(w->arena,"igStringRefList",4,0,NULL);
    data->_modelCloseInfoNameList=al_new(w->arena,"igStringRefList",4,0,NULL);
    data->_modelCloseRamNoList=al_new(w->arena,"igIntList",4,0,NULL);
    data->_modelCloseSeqNameList=al_new(w->arena,"igStringRefList",4,0,NULL);
    if(!data->_textCloseTypeList || !data->_textCloseNameList || !data->_modelCloseInfoNameList || !data->_modelCloseRamNoList || !data->_modelCloseSeqNameList){dw4_menu_window_close(w);return NULL;}
    dw4_statusctrl state={.active=1,.selection=-1};
    if(c->parent)state.last_selection=c->parent->last_selection;
    else if(c->parent_window){dw4_statusctrl parent;dw4_statusctrl_load(c->parent_window,&parent);state.last_selection=parent.last_selection;}
    dw4_statusctrl_store(w,&state);data->_playerNo=c->player;
    data->_entCode=kind==DW4_STATUS_TITLE01 || kind==DW4_STATUS_SHOPSELECT34 || kind==DW4_STATUS_SHOPSELECT52?c->variant:c->callno;
    if(selection_kind(kind)){
        beNDMWWindowSelect *d=selector_data(v);d->_selectMax=c->rows;
        if(kind!=DW4_STATUS_SELECT00)d->_startPoint=c->selected;
        memcpy(d->_offsetPos,c->position,12);
        int rows=kind==DW4_STATUS_SELECT01?(c->callno==61?4:3):c->rows;
        d->_decideList=al_new(w->arena,"igBoolList",1,c->enabled?rows:0,c->enabled);
        d->_infoName=al_string(w->arena,selection_cursor(v,"i_stcursor02"));
        if(!d->_decideList || !d->_infoName){dw4_menu_window_close(w);return NULL;}
        if(kind==DW4_STATUS_SHOPSELECT00){beNDMWShopSelect00 *shop=DW4_ARENA_OBJ(w->arena,beNDMWShopSelect00,w->object);
            shop->_panelName=al_string(w->arena,c->variant==1?"font100":"font000");
            if(!shop->_panelName){dw4_menu_window_close(w);return NULL;}}
    }
    /* The public context is construction input; mutable view parameters are recovered fields. */
    v->c.rows=v->c.selected=v->c.callno=v->c.variant=0;memset(v->c.position,0,sizeof v->c.position);v->c.enabled=NULL;
    return w;
}
int dw4_statusview_window_emit(void *user,const dw4_statusview_command *c)
{
    dw4_menu_window *w=user;
    if(!w || w->update!=update || !c || !dw4_menu_window_data(w)->_isRun || dw4_menu_window_data(w)->_st0!=1)return -1;
    struct view *v=w->user;if(v->kind!=DW4_STATUS_CONTENT || v->failed)return -1;
    int rc=native_emit(v,c);if(rc)v->failed=1;return rc;
}
int dw4_statusview_window_title_variant(dw4_menu_window *w,int variant)
{
    if(!w || w->update!=update || !dw4_menu_window_data(w)->_isRun || dw4_menu_window_data(w)->_st0!=1 || (variant!=0 && variant!=1))return -1;
    struct view *v=w->user;int32_t digimon=0;
    if(v->failed || v->kind!=DW4_STATUS_TITLE01)return -1;
    if(dw4_property_number(dw4_playerrecords_get(v->c.players,"GETPLAYER",v->c.player),"DIGIMONNO",&digimon)){v->failed=1;return -1;}
    dw4_menu_window_data(w)->_entCode=variant;
    /* The other base closes when this one is presented (the retail lab menu shows only the compact base after the check). */
    dw4_statusview_command close={DW4_VIEW_MODEL,NULL,variant?"i_stbase":"j_shbase","SQ_CLOSE","SQ_CLOSE",v->c.player};
    int rc=native_emit(v,&close);
    if(!rc)rc=title01_base(native_emit,v,variant,v->c.player,digimon);
    if(rc)v->failed=1;
    return rc;
}
int dw4_statusview_window_prepare(dw4_menu_window *w,
    int (*initialize)(void *,dw4_statusview_io,void *),void *user)
{
    if(!w || w->update!=update || !initialize || !dw4_menu_window_data(w)->_isRun || dw4_menu_window_data(w)->_st0)return -1;
    struct view *v=w->user;
    if(v->failed || !selection_kind(v->kind))return -1;
    int rc=initialize(user,native_emit,v);if(rc)v->failed=1;return rc;
}
int dw4_statusview_window_clear_text(dw4_menu_window *w)
{
    if(!w || w->update!=update || !dw4_menu_window_data(w)->_isRun || dw4_menu_window_data(w)->_st0!=1)return -1;
    struct view *v=w->user;if(v->failed || v->kind!=DW4_STATUS_CONTENT)return -1;
    int rc=clear_text(v);if(rc)v->failed=1;return rc;
}
int dw4_statusview_selector_ready(dw4_menu_window *w)
{
    if(!w || w->update!=update || !dw4_menu_window_data(w)->_isRun)return -1;
    struct view *v=w->user;
    if(v->failed || !selection_kind(v->kind))return -1;
    if(dw4_menu_window_data(w)->_st0!=1)return 0;
    int q=select_io(v,DW4_STATUS_SELECT_IS_TOP,"i_stcursor02","ISFO2TOP",0);
    if(q<0){v->failed=1;return -1;}return q;
}
int dw4_statusview_selector_repage(dw4_menu_window *w,int rows)
{
    if(!w || w->update!=update || ((struct view *)w->user)->c.enabled)return -1;
    return dw4_statusview_selector_restart(w,rows,NULL);
}
int dw4_statusview_selector_restart(dw4_menu_window *w,int rows,const uint8_t *enabled)
{
    if(rows<1 || rows>256 || dw4_statusview_selector_ready(w)!=1)return -1;
    struct view *v=w->user;if(v->kind!=DW4_STATUS_SELECTE1)return -1;
    int32_t list=al_new(w->arena,"igBoolList",1,enabled?rows:0,enabled);if(!list)return -1;
    beNDMWWindowSelect *d=selector_data(v);al_drop(w->arena,&d->_decideList);d->_decideList=list;
    d->_selectMax=rows;d->_startPoint=0;
    dw4_menu_window_data(w)->_st0=4;dw4_menu_window_data(w)->_st1=dw4_menu_window_data(w)->_st2=dw4_menu_window_data(w)->_st3=0;return 0;
}
