#include "dw4/arena.h"
#include "dw4/database.h"
#include "dw4/playerrecords.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static int object_source(void *user,const char *path,const void **bytes,size_t *size)
{(void)path;*bytes=user;*size=strlen(user);return 0;}
static void object_queries(dw4_databases *owner)
{
    dw4_scriptservices *sd=dw4_scriptservices_open();dw4_playerrecords *players=dw4_playerrecords_open();assert(sd && players);
    assert(dw4_scriptservices_register(sd,0,"GAMERAM",NULL,-1,1,dw4_playerrecords_service,players));
    assert(!dw4_databases_publish(owner,sd,3));assert(dw4_databases_publish(owner,sd,3));
    dw4_script *lua=dw4_script_open(dw4_scriptservices_call,sd);assert(lua);
    const char *names[]={"p","common","fourth","db","same"};
    const char *keys[]={"GETPLAYER1","GETCOMMON","GETPLAYER4","GETDATABASE","GETPLAYER"};
    for(unsigned i=0;i<5;i++){
        const char *category=i==3?"DATABASE":"GAMERAM";
        dw4_script_value args[]={{DW4_SCRIPT_STRING,0,category,strlen(category)},
            i==3?(dw4_script_value){DW4_SCRIPT_STRING,0,"shinka",6}:(dw4_script_value){0},
            {DW4_SCRIPT_NUMBER,-1,NULL,0},{DW4_SCRIPT_STRING,0,keys[i],strlen(keys[i])},
            {DW4_SCRIPT_STRING,0,"I<0>",4}},result={0};char error[256];
        assert(!dw4_scriptservices_call(sd,"querySD",args,i==4?5:4,&result,error,sizeof error));
        assert(!dw4_script_set(lua,names[i],result));
    }
    const char *source="assert(p==same and type(p)=='userdata' and type(db)=='userdata') missing=be:sd('DATABASE','missing',-1,'GETDATABASE') command=be:sd('DATABASE','shinka',-1,'GETDATABASE') assert(missing==nil and command==nil) [EOF]";
    dw4_script_source_set(lua,object_source,(void *)source,NULL);
    int rc=dw4_script_run_named(lua,"object-queries.lua",NULL);if(rc)fprintf(stderr,"typed receivers: %s\n",dw4_script_error(lua));assert(!rc);
    const char *methods[]={"GETPLAYER1","GETCOMMON","GETPLAYER4"};
    for(unsigned i=0;i<4;i++){
        dw4_script_value value;assert(!dw4_script_get(lua,names[i],&value));const dw4_script_object *o=dw4_script_value_object(&value);assert(o);
        if(i<3)assert(o->kind==DW4_SCRIPT_PROPERTY_FOLDER && o->owner==players && o->pointer==dw4_playerrecords_get(players,methods[i],0));
        else assert(o->kind==DW4_SCRIPT_DATABASE && o->owner==owner && o->pointer==dw4_databases_get(owner,"shinka") && !strcmp(dw4_database_string(o->pointer,0,"NAME"),"Agumon"));
    }
    dw4_script_objects_invalidate(lua,owner);dw4_databases_close(owner);
    dw4_script_value value;assert(dw4_script_get(lua,"db",&value));assert(!dw4_script_get(lua,"p",&value));
    dw4_script_objects_invalidate(lua,players);dw4_playerrecords_close(players);assert(dw4_script_get(lua,"p",&value));
    dw4_script_close(lua);dw4_scriptservices_close(sd);
    puts("typed SD receivers: actual GAMERAM folders/DATABASE tables, Lua identities, missing names and independent owner invalidation pass");
}
static uint32_t value(const dw4_igb_record *r,unsigned slot)
{for(uint32_t i=0;i<r->nvalues;i++)if(r->values[i].ordinal==slot)return r->values[i].raw;assert(0);return 0;}
static uint32_t word(const uint8_t *p){uint32_t v;memcpy(&v,p,4);return v;}
static dw4_igb_record record(const dw4_igb *g,uint32_t id)
{dw4_igb_record r={0};uint32_t off;assert(dw4_igb_ref(g,id,&off,NULL)==2 && dw4_igb_decode(g,off,&r));return r;}
static const uint8_t *list(const dw4_igb *g,uint32_t id,uint32_t *n)
{dw4_igb_record r=record(g,id);*n=value(&r,2);const uint8_t *p=dw4_igb_block(g,value(&r,4),NULL);assert(p || !*n);dw4_igb_record_free(&r);return p;}
static dw4_stageobjects *route(dw4_igb *g)
{dw4_stageobjects *s=dw4_stageobjects_open();assert(s);assert(!dw4_stageobjects_route(s,"USA-database-fixture",g,0));return s;}
static void corrupt(const dw4_igb *original,int mode)
{
    uint8_t *bytes=malloc(original->size);assert(bytes);memcpy(bytes,original->data,original->size);
    dw4_igb g={0};assert(!dw4_igb_open(&g,bytes,original->size,0) && !dw4_igb_refs_open(&g));
    dw4_stageobjects *s=route(&g);const dw4_stageobject *info=dw4_stageobjects_find(s,"beDBManagerInfo","shinka",0);assert(info);
    dw4_igb_record db=record(&g,dw4_stageobject_ref_id(info,"_dataBase"));
    dw4_igb_record offsets=record(&g,value(&db,12)),data=record(&g,value(&db,13));
    uint32_t count;const uint8_t *p=list(&g,value(&db,13),&count);assert(count);
    if(mode==0){uint32_t invalid=UINT32_MAX;memcpy(bytes+(p-g.data),&invalid,4);}
    if(mode==1){for(uint32_t i=0;i<data.nvalues;i++)if(data.values[i].ordinal==3){uint32_t zero=0;memcpy(bytes+data.values[i].voff,&zero,4);}}
    if(mode==2){for(uint32_t i=0;i<data.nvalues;i++)if(data.values[i].ordinal==2){uint32_t n=count-1;memcpy(bytes+data.values[i].voff,&n,4);}}
    if(mode==3){for(uint32_t i=0;i<db.nvalues;i++)if(db.values[i].ordinal==12)memcpy(bytes+db.values[i].voff,&info->id,4);}
    if(mode==4){ /* A null string name has the retail empty-string fallback. */
        dw4_igb_record item=record(&g,word(p));assert(item.name);memset(bytes+(item.name-(const char *)g.data),0,strlen(item.name));dw4_igb_record_free(&item);
    }
    char error[256];dw4_databases *owner=dw4_databases_open(s,error,sizeof error);
    if(mode<4){assert(!owner && strstr(error,"shinka") && strstr(error,"USA-database-fixture"));}
    else {assert(owner);const dw4_database *d=dw4_databases_get(owner,"shinka");dw4_igb_record column=record(&g,word(list(&g,value(&db,12),&count)));assert(!strcmp(dw4_database_string(d,0,column.name),""));dw4_igb_record_free(&column);}
    dw4_databases_close(owner);dw4_igb_record_free(&offsets);dw4_igb_record_free(&data);dw4_igb_record_free(&db);
    dw4_stageobjects_close(s);dw4_igb_close(&g);free(bytes);
}
int main(int argc,char **argv)
{
    dw4_mount m;assert(!dw4_mount_open(&m,argc>1?argv[1]:"../../local/extracted"));
    uint32_t size;const uint8_t *bytes=dw4_mount_data(&m,"stagML11/separate/USA_pack.igb",&size);assert(bytes);
    dw4_igb g={0};assert(!dw4_igb_open(&g,bytes,size,0) && !dw4_igb_refs_open(&g));
    for(int mode=0;mode<5;mode++)corrupt(&g,mode);
    size_t total=0,boolean_total=0;dw4_databases *kept=NULL;
    for(int cycle=0;cycle<32;cycle++){
        dw4_stageobjects *s=route(&g);char error[256];dw4_databases *owner=dw4_databases_open(s,error,sizeof error);
        if(!owner)fprintf(stderr,"%s\n",error);
        assert(owner && dw4_databases_count(owner)>0);
        if(kept){assert(dw4_databases_get(kept,"shinka")!=dw4_databases_get(owner,"shinka"));assert(!strcmp(dw4_databases_shinka_name(kept,0),"Agumon"));dw4_databases_close(kept);}
        size_t infos=0;
        for(size_t i=0;i<dw4_stageobjects_count(s);i++){
            const dw4_stageobject *info=dw4_stageobjects_at(s,i);if(strcmp(dw4_stageobject_class(info),"beDBManagerInfo"))continue;infos++;
            const dw4_database *d=dw4_databases_get(owner,dw4_stageobject_name(info));assert(d);
            dw4_igb_record db=record(&g,dw4_stageobject_ref_id(info,"_dataBase"));uint32_t columns,items;
            const uint8_t *keys=list(&g,value(&db,12),&columns),*values=list(&g,value(&db,13),&items);
            assert(dw4_database_string_rows(d)==(columns?items/columns:0));
            for(uint32_t j=0;j<items;j++){
                dw4_igb_record key=record(&g,word(keys+4*(j%columns))),v=record(&g,word(values+4*j));
                if(key.name){const char *got=dw4_database_string(d,(int32_t)(j/columns),key.name);assert(got && !strcmp(got,v.name?v.name:""));total++;}
                dw4_igb_record_free(&key);dw4_igb_record_free(&v);
            }
            assert(!dw4_database_string(d,-1,"NAME") && !dw4_database_string(d,INT32_MAX,"NAME"));
            assert(!dw4_database_string(d,(int32_t)dw4_database_string_rows(d),"NAME"));
            assert(!dw4_database_string(d,0,"missing-column") && !dw4_database_string(d,0,NULL));
            keys=list(&g,value(&db,10),&columns);values=list(&g,value(&db,11),&items);
            for(uint32_t j=0;j<items;j++){
                dw4_igb_record key=record(&g,word(keys+4*(j%columns)));int32_t v;
                if(key.name){assert(!dw4_database_bool(d,(int32_t)(j/columns),key.name,&v) && v==values[j]);boolean_total++;}
                dw4_igb_record_free(&key);
            }
            dw4_igb_record_free(&db);
        }
        assert(infos==dw4_databases_count(owner));assert(!dw4_databases_get(owner,"SHINKA") && !dw4_databases_get(owner,NULL));
        dw4_stageobjects_close(s);kept=owner;
    }
    dw4_igb_close(&g);dw4_mount_close(&m); /* copied strings survive all input owners */
    assert(!strcmp(dw4_databases_shinka_name(kept,0),"Agumon"));
    assert(!dw4_databases_shinka_name(kept,-1) && !dw4_databases_shinka_name(NULL,0));object_queries(kept);
    printf("database: %zu authored strings and %zu boolean cells across 32 independent owners; malformed references, bounds and released-input lifetimes pass\n",total,boolean_total);/* every owner has closed: the shared session arena holds nothing of theirs */
    {dw4_arena *s=dw4_session_arena();assert(s && dw4_arena_live(s,DW4_REGION_PERSISTENT)==0);}
    return 0;
}
