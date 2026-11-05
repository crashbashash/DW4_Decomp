/* beDataBase lookups (retail 0x3a93a0 / 0x3a9460 / 0x3a9540 / 0x3a9580) and beDBManager 0x3a9780, over the decomp's typed beDataBase
 * instances in the owner's arena (docs/arena-object-model.md, P1-P3; the accessors are src/arenadb.c). A database holds no copy of
 * its data. See docs/databases.md. Host bounds checks reject retail-unsafe indices. */
#include "dw4/database.h"
#include "dw4/arenapack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dw4_database {dw4_dbtable typed;char *name;dw4_script_object view;uint64_t token;};
/* The typed beDataBase instances live in the session arena (docs/arena-object-model.md); the owner returns every block it allocated when
 * it closes. The closure of one database is about 200 KB. */
struct dw4_databases {dw4_database *items;size_t count;dw4_scriptservices *sd;dw4_arena *arena;dw4_arena_owned owned;};
static char *copy(const char *s)
{size_t n=strlen(s)+1;char *p=malloc(n);if(p)memcpy(p,s,n);return p;}
void dw4_databases_close(dw4_databases *s)
{
    if(s && s->sd)for(size_t i=0;i<s->count;i++)dw4_scriptservices_unregister(s->sd,s->items[i].token);
    if(!s)return;
    for(size_t i=0;i<s->count;i++)free(s->items[i].name);
    free(s->items);dw4_arena_owned_release(s->arena,&s->owned);free(s);
}
dw4_databases *dw4_databases_open(const dw4_stageobjects *objects,char *e,size_t n)
{
    dw4_databases *s=objects?calloc(1,sizeof(*s)):NULL;
    if(!s){snprintf(e,n,"database owner allocation/input unavailable");return NULL;}
    const dw4_stageobject *info=NULL;
    for(size_t i=0;i<dw4_stageobjects_count(objects);i++){
        info=dw4_stageobjects_at(objects,i);
        if(strcmp(dw4_stageobject_class(info),"beDBManagerInfo"))continue;
        dw4_database *items=realloc(s->items,(s->count+1)*sizeof(*items));if(!items)goto bad;
        s->items=items;dw4_database *d=items+s->count++;memset(d,0,sizeof(*d));
        if(!dw4_stageobject_name(info) || !(d->name=copy(dw4_stageobject_name(info))))goto bad;
        {   /* the beDataBase instance and what it reaches, as typed objects in the owner's arena, then the structural checks */
            uint32_t root=dw4_stageobject_ref_id(info,"_dataBase");dw4_arena_pack pk;char why[160];dw4_handle h;
            if(!s->arena && !(s->arena=dw4_session_arena()))goto bad;
            if(dw4_arena_pack_load_from(s->arena,DW4_REGION_PERSISTENT,(info)->igb,&root,1,&pk,why,sizeof why))goto bad;
            h=dw4_arena_pack_handle(&pk,root);dw4_arena_owned_move(&s->owned,&pk.owned);dw4_arena_pack_free(&pk);
            if(!h.off || dw4_adb_validate(s->arena,h,why,sizeof why))goto bad;
            d->typed=(dw4_dbtable){s->arena,h};
        }
    }
    return s;
bad:
    snprintf(e,n,"invalid prepared database: %s/%s object %u",info?info->path:"",
        info && dw4_stageobject_name(info)?dw4_stageobject_name(info):"",info?info->id:0);
    dw4_databases_close(s);return NULL;
}
size_t dw4_databases_count(const dw4_databases *s){return s?s->count:0;}
const dw4_database *dw4_databases_get(const dw4_databases *s,const char *name)
{
    if(s && name)for(size_t i=0;i<s->count;i++)if(!strcmp(s->items[i].name,name))return s->items+i;
    return NULL;
}
dw4_dbtable dw4_database_typed(const dw4_database *d){dw4_dbtable none={0};return d?d->typed:none;}
dw4_dbtable dw4_databases_table(const dw4_databases *s,const char *name){return dw4_database_typed(dw4_databases_get(s,name));}
size_t dw4_database_string_rows(const dw4_database *d)
{return d?dw4_adb_string_rows(d->typed.arena,d->typed.db):0;}
int32_t dw4_database_string_offset(const char *const *columns,uint32_t count,int32_t row,const char *name)
{
    if(!columns || !name || !count)return -1;
    for(uint32_t i=0;i<count;i++)if(columns[i] && !strcmp(columns[i],name)){
        uint32_t bits=(uint32_t)row*count+i;int32_t v;memcpy(&v,&bits,4);return v;
    }
    return -1;
}
const char *dw4_database_string(const dw4_database *d,int32_t row,const char *column)
{return d?dw4_dbt_string(d->typed,row,column):NULL;}
const char *dw4_databases_shinka_name(void *s,int32_t row)
{return dw4_database_string(dw4_databases_get(s,"shinka"),row,"NAME");}
int dw4_database_number(const dw4_database *d,int32_t row,const char *column,int32_t *out)
{return d?dw4_dbt_number(d->typed,row,column,out):-1;}
int dw4_database_bool(const dw4_database *d,int32_t row,const char *column,int32_t *out)
{return d?dw4_dbt_bool(d->typed,row,column,out):-1;}

static int database_service(void *user,const char *method,const dw4_script_value *a,size_t n,dw4_script_value *r,char *error,size_t cap)
{
    dw4_database *d=user;
    if((strcmp(method,"sd") && strcmp(method,"querySD")) || n!=4 || a[3].type!=DW4_SCRIPT_STRING || strcmp(a[3].string,"GETDATABASE")){
        snprintf(error,cap,"DATABASE requires GETDATABASE");return -1;
    }
    *r=dw4_script_object_value(&d->view);return 0;
}
int dw4_databases_publish(dw4_databases *s,dw4_scriptservices *sd,uint64_t scope)
{
    if(!s || !sd || s->sd)return -1;
    for(size_t i=0;i<s->count;i++){
        s->items[i].view=(dw4_script_object){DW4_SCRIPT_DATABASE,s->items+i,s};
        s->items[i].token=dw4_scriptservices_register(sd,scope,"DATABASE",s->items[i].name,-1,1,database_service,s->items+i);
        if(!s->items[i].token){for(size_t j=0;j<i;j++){dw4_scriptservices_unregister(sd,s->items[j].token);s->items[j].token=0;}return -1;}
    }
    s->sd=sd;return 0;
}
void dw4_database_describe(const dw4_database *d,FILE *out)
{
    if(d)dw4_adb_describe(d->typed.arena,d->typed.db,d->name,out);
}
