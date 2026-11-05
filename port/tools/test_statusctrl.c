#include "dw4/statusctrl.h"
#include "dw4/playerrecords.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
struct fixture {dw4_menu_window *root;int selected,end,finished,opening,fail,created[9],released,init,last,reply_override;};
static int leaf(dw4_menu_window *w,char *error,size_t cap)
{(void)error;(void)cap;if(dw4_menu_window_data(w)->_st0>=2)dw4_menu_window_data(w)->_isRun=0;return 0;}
static void release(void *u){((struct fixture *)u)->released++;}
static int io(void *user,int op,const char *name,const char *key,int32_t value)
{
    struct fixture *f=user;(void)name;
    if(f->fail==op+1)return -2;
    if(op==DW4_STATUS_CREATE){
        assert(value>=0 && value<9);f->created[value]++;
        dw4_menu_window *w=dw4_menu_window_open(leaf,f,release);assert(w);
        assert(!dw4_menu_window_add(f->root,w));return 0;
    }
    if(op==DW4_STATUS_MODEL)return strstr(key,"ISSEQNAME")?f->opening:0;
    if(op==DW4_STATUS_SELECT_INIT){f->init++;f->last=value;return 0;}
    if(op==DW4_STATUS_SELECT_GET)return f->selected;
    if(op==DW4_STATUS_SELECT_END){
        assert(dw4_menu_window_data(f->root)->_retCode==f->selected);
        if(f->reply_override)dw4_menu_window_data(f->root)->_retCode=f->reply_override;
        return f->end;
    }
    if(op==DW4_STATUS_FINISHED)return f->finished;
    return 0;
}
static void tick(struct fixture *f)
{char e[128]={0};assert(!dw4_menu_window_tick(f->root,e,sizeof(e)));}
static void tree(void)
{
    struct fixture f={.selected=-1,.finished=0,.opening=1};
    f.root=dw4_statusctrl_window_open(io,&f);assert(f.root);
    tick(&f);assert(dw4_menu_window_count(f.root)==1 && f.created[DW4_STATUS_TITLE00]==0); /* concrete internal Title00 */
    for(int i=0;i<10;i++)tick(&f);
    assert(dw4_menu_window_data(f.root)->_st1==1 && dw4_menu_window_count(f.root)==1); /* model query holds, ticks cannot finish it */
    f.opening=0;tick(&f);assert(dw4_menu_window_count(f.root)==4 && dw4_menu_window_data(f.root)->_st1==2);
    tick(&f);assert(dw4_menu_window_data(f.root)->_st0==1);
    tick(&f);assert(dw4_menu_window_count(f.root)==5 && f.init==1 && f.last==0 && dw4_menu_window_data(f.root)->_st2==2);
    beNDMWStatusCtrl00 *s=dw4_statusctrl_window_state(f.root);assert(s && s->_retCode==-1);
    f.selected=2;f.end=1;tick(&f);assert(s->_retCode==2 && dw4_menu_window_count(f.root)==5);
    for(int i=0;i<4;i++)tick(&f);
    assert(dw4_menu_window_count(f.root)==5); /* real close wait */
    f.finished=1;tick(&f);assert(dw4_menu_window_count(f.root)==4);
    tick(&f);assert(s->_statusMenu==2 && dw4_menu_window_data(f.root)->_st1==3);
    tick(&f);assert(f.created[DW4_STATUS_SKILL]==1 && dw4_menu_window_count(f.root)==5);
    dw4_menu_window_remove(f.root->children[4]);tick(&f);assert(dw4_menu_window_count(f.root)==4);
    tick(&f);assert(dw4_menu_window_data(f.root)->_st1==0);
    f.end=0;tick(&f);assert(f.init==2 && f.last==2);
    f.selected=-1;f.end=1;tick(&f);assert(dw4_menu_window_count(f.root)==4);
    tick(&f);assert(dw4_menu_window_data(f.root)->_st1==4 && s->_statusMenu==2);
    tick(&f);assert(dw4_menu_window_count(f.root)==1);tick(&f);assert(dw4_menu_window_data(f.root)->_st0==2);
    tick(&f);assert(dw4_menu_window_count(f.root)==0 && dw4_menu_window_data(f.root)->_isRun);
    tick(&f);assert(!dw4_menu_window_data(f.root)->_isRun && f.released==4); /* Title00 has its own concrete release */
    dw4_menu_window_close(f.root);
    f=(struct fixture){0};f.root=dw4_statustitle_window_open(io,&f);assert(f.root);
    tick(&f);assert(dw4_menu_window_data(f.root)->_st0==1);
    dw4_menu_window_remove(f.root);tick(&f);assert(dw4_menu_window_data(f.root)->_st0==3);
    for(int i=0;i<8;i++)tick(&f);
    assert(dw4_menu_window_data(f.root)->_isRun);f.finished=1;tick(&f);assert(!dw4_menu_window_data(f.root)->_isRun);
    dw4_menu_window_close(f.root);
    f=(struct fixture){.fail=DW4_STATUS_CREATE+1};f.root=dw4_statusctrl_window_open(io,&f);
    tick(&f);assert(dw4_menu_window_count(f.root)==1); /* concrete Title00 survives the next factory failure */
    char e[128];assert(dw4_menu_window_tick(f.root,e,sizeof(e))==-1 && strstr(e,"STATUS"));
    assert(dw4_menu_window_data(f.root)->_isRun && dw4_menu_window_count(f.root)==1);dw4_menu_window_close(f.root);
    f=(struct fixture){.selected=2,.finished=1,.reply_override=1};
    f.root=dw4_statusctrl_window_open(io,&f);assert(f.root);
    for(int i=0;i<4;i++)tick(&f);
    assert(dw4_menu_window_data(f.root)->_retCode==1); /* ISEND's later write must survive. */
    dw4_menu_window_close(f.root);
}
static dw4_script_value number(double v){return (dw4_script_value){DW4_SCRIPT_NUMBER,v,NULL,0};}
static void records(void)
{
    dw4_playerrecords *o=dw4_playerrecords_open();assert(o);
    char error[160];dw4_script_value a[]={number(0),number(0)},r;
    assert(dw4_playerrecords_get(o,"GETCOMMON",100));
    assert(!dw4_playerrecords_get(o,"GETPLAYER",-1) && !dw4_playerrecords_get(o,"GETPLAYER",4));
    for(int i=0;i<4;i++){
        char key[32];snprintf(key,sizeof(key),"GETPLAYER%d",i+1);
        dw4_property_folder *f=dw4_playerrecords_get(o,"GETPLAYER",i);
        assert(f==dw4_playerrecords_get(o,key,-1));a[0]=number(i);
        assert(!dw4_playerrecords_call(o,"SYSisJoinPlayer",a,1,&r,error,sizeof(error)) && r.number==0);
        assert(dw4_playerrecords_call(o,"SYSgetPlayerLevel",a,1,&r,error,sizeof(error))==-1);
        assert(!dw4_property_set_number(f,"LEVEL",i+1));
        assert(!dw4_property_set_number(f,"DIGIMONNO",i));
        assert(!dw4_property_set_number(f,"ISUSE",257));
        assert(!dw4_playerrecords_call(o,"SYSisJoinPlayer",a,1,&r,error,sizeof(error)) && r.number==1);
        assert(!dw4_playerrecords_call(o,"SYSgetPlayerLevel",a,1,&r,error,sizeof(error)) && r.number==i+1);
        assert(!dw4_playerrecords_call(o,"SYSgetPlayerDigimon",a,1,&r,error,sizeof(error)) && r.number==i);
        char name[]="m_agumon";assert(!dw4_property_set_string(f,"DIGIMONNAME",name));name[0]='x';
        assert(!dw4_playerrecords_call(o,"SYSgetPlayerName",a,1,&r,error,sizeof(error)) && !strcmp(r.string,"m_agumon"));
        assert(dw4_property_set_number(f,"DIGIMONNAME",4)==-1);
        int32_t skills[]={1,2,3};assert(!dw4_property_set_array(f,"SKILL",skills,3));skills[0]=99;
        size_t n;assert(dw4_property_array(f,"SKILL",&n)[0]==1 && n==3);
        dw4_property_folder *child=dw4_property_child(f,"nested",1);assert(child);
        for(int j=0;j<128;j++){snprintf(key,sizeof(key),"test%d",j);assert(!dw4_property_set_number(f,key,j));}
        assert(dw4_property_child(f,"nested",0)==child && !dw4_property_set_number(child,"BIT",17));
        char weapon[]="m_wp00";const char *list[]={weapon,NULL};
        assert(!dw4_property_set_strings(f,"POWERSOCKETNAME",list,2));weapon[0]='x';
        assert(!dw4_playerrecords_call(o,"SYSgetWeaponName",a,2,&r,error,sizeof(error)) && !strcmp(r.string,"m_wp00"));
        a[1]=number(1);assert(!dw4_playerrecords_call(o,"SYSgetWeaponName",a,2,&r,error,sizeof(error)) && r.type==DW4_SCRIPT_NIL);
        a[1]=number(99);assert(!dw4_playerrecords_call(o,"SYSgetWeaponName",a,2,&r,error,sizeof(error)) && r.type==DW4_SCRIPT_NIL);
        a[1]=number(.5);assert(dw4_playerrecords_call(o,"SYSgetWeaponName",a,2,&r,error,sizeof(error))==-1);a[1]=number(0);
    }
    double invalid[]={-1,4,.5,NAN,INFINITY};for(size_t i=0;i<5;i++){
        a[0]=number(invalid[i]);assert(dw4_playerrecords_call(o,"SYSisJoinPlayer",a,1,&r,error,sizeof(error))==-1);
    }
    assert(dw4_playerrecords_call(o,"SYSother",a,1,&r,error,sizeof(error))==1);
    dw4_playerrecords_close(o);
}
int main(void){records();tree();puts("player records and STATUS: ownership, selection retention, close waits and failure paths pass");return 0;}
