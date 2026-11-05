#include "dw4/script.h"
#include "dw4/object.h"
#include "lua.h"
#include "lualib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

struct script_chunk { char *name; int ref; uint64_t scope; };
struct info_row { char *name; void *bytes; size_t size; };
struct script_info { struct info_row *rows; size_t count; uint64_t scope; };
struct object_value {struct object_value *next;dw4_script_object object;dw4_script *script;int valid;};
struct dw4_script {
    lua_State *L;
    int object_tag;struct object_value *objects;
    dw4_script_binding binding;
    void *user;
    struct script_chunk *chunks;
    size_t count;
    char error[512];
    unsigned depth;
    struct script_info *infos;
    size_t info_count;
    int retail;
    dw4_script_source source;
    void *source_user;
    char directory[256];
};
void dw4_script_objects_invalidate(dw4_script *s,const void *owner)
{if(s && owner)for(struct object_value *v=s->objects;v;v=v->next)if(v->object.owner==owner)v->valid=0;}
/* The original descriptor table has overloaded names; the host keeps the full
 * typed argument list instead of choosing overloads by argument count alone. */
static const char *const methods[] = {
#include "script_api_names.h"
};
static char *copy_string(const char *p) {
    size_t n = strlen(p) + 1;
    char *out = malloc(n);
    if (out) memcpy(out, p, n);
    return out;
}
static dw4_script *context(lua_State *L) {
    /* Lua 4 C closure upvalues follow the explicit arguments. */
    return lua_touserdata(L, -1);
}
static int read_value(dw4_script *s, int index, dw4_script_value *v) {
    lua_State *L=s->L;
    memset(v, 0, sizeof(*v));
    switch (lua_type(L, index)) {
    case LUA_TNIL: v->type = DW4_SCRIPT_NIL; return 0;
    case LUA_TNUMBER: v->type = DW4_SCRIPT_NUMBER; v->number = lua_tonumber(L,index); return 0;
    case LUA_TSTRING: v->type = DW4_SCRIPT_STRING; v->string = lua_tostring(L,index);
        v->length = lua_strlen(L,index); return 0;
    case LUA_TUSERDATA: {
        if(lua_tag(L,index)!=s->object_tag)return -1;
        void *userdata=lua_touserdata(L,index);struct object_value *object=s->objects;
        while(object && object!=userdata)object=object->next;
        if(!object || object->script!=s || !object->valid)return -1;
        *v=dw4_script_object_value(&object->object);return 0;
    }
    default: return -1;
    }
}
static int object_usable(const dw4_script *s,const dw4_script_value *value)
{
    if(value->type!=DW4_SCRIPT_OBJECT)return 1;
    const dw4_script_object *object=dw4_script_value_object(value);
    if(!object)return 0;
    for(struct object_value *node=s->objects;node;node=node->next)if(object==&node->object)return node->valid;
    return object->pointer && object->owner && (object->kind==DW4_SCRIPT_PROPERTY_FOLDER || object->kind==DW4_SCRIPT_DATABASE);
}
static void push_value(dw4_script *s, const dw4_script_value *v) {
    lua_State *L=s->L;
    if (v->type == DW4_SCRIPT_NUMBER) lua_pushnumber(L,v->number);
    else if (v->type == DW4_SCRIPT_STRING) lua_pushlstring(L,v->string,v->length);
    else if(v->type==DW4_SCRIPT_OBJECT){
        const dw4_script_object *object=dw4_script_value_object(v);
        if(!object_usable(s,v)){
            lua_error(L,"invalid native object descriptor");return;
        }
        struct object_value *node=s->objects;
        while(node && (!node->valid || node->object.kind!=object->kind || node->object.pointer!=object->pointer || node->object.owner!=object->owner))node=node->next;
        if(!node){node=calloc(1,sizeof *node);if(!node){lua_error(L,"native object identity allocation failed");return;}
            node->object=*object;node->script=s;node->valid=1;node->next=s->objects;s->objects=node;}
        lua_pushusertag(L,node,s->object_tag);
    }else lua_pushnil(L);
}
static int capture_error(lua_State *L) {
    dw4_script *s = context(L);
    const char *p = lua_tostring(L,1);
    snprintf(s->error,sizeof(s->error),"%s",p ? p : "Lua error");
    return 0;
}
static int dispatch(lua_State *L) {
    dw4_script *s = context(L);
    const char *method = lua_tostring(L,-2);
    dw4_script_value args[8], result = {0};
    int n = lua_gettop(L)-3; /* self + two upvalues */
    if (n < 0 || n > 8 || !lua_istable(L,1)) {
        lua_error(L,"invalid be call/self"); return 0;
    }
    for (int i=0;i<n;i++) if (read_value(s,i+2,&args[i])) {
        lua_error(L,"unsupported or expired be argument type"); return 0;
    }
    char error[384] = {0};
    static int trace=-1;if(trace<0)trace=getenv("DW4_BE_TRACE")!=NULL;
    if(trace){   /* DW4_BE_TRACE=1: every be: call from a script (bring-up aid) */
        fprintf(stderr,"BE %s",method);
        for(int i=0;i<n;i++){
            if(args[i].type==DW4_SCRIPT_STRING && args[i].string)fprintf(stderr," %.*s",(int)args[i].length,args[i].string);
            else if(args[i].type==DW4_SCRIPT_NUMBER)fprintf(stderr," %g",args[i].number);else fprintf(stderr," nil");
        }
        fputc('\n',stderr);
    }
    if (!s->binding || s->binding(s->user,method,args,(size_t)n,&result,error,sizeof(error))) {
        char full[512];
        snprintf(full,sizeof(full),"be:%s: %s",method,error[0]?error:"native binding unavailable");
        if (s->error[0]) { lua_error(L,NULL); return 0; }
        snprintf(s->error,sizeof(s->error),"%s",full);
        lua_error(L,full); return 0;
    }
    /* Native void methods return no values. A nil query result is equivalent. */
    if (result.type == DW4_SCRIPT_NIL) return 0;
    push_value(s,&result); return 1;
}
static int dofile_pack(lua_State *L) {
    dw4_script *s=context(L);
    const char *name=lua_tostring(L,1);
    if (!name || dw4_script_run(s,name)) {
        char error[512]; snprintf(error,sizeof(error),"%s",s->error);
        lua_error(L,error); return 0;
    }
    return 0;
}
static int open_state(dw4_script *s) {
    s->L=lua_open(4096);
    if (!s->L) return -1;
    s->object_tag=lua_newtag(s->L);
    lua_baselibopen(s->L); lua_strlibopen(s->L); lua_mathlibopen(s->L);
    lua_pushuserdata(s->L,s); lua_pushcclosure(s->L,capture_error,1);
    lua_setglobal(s->L,"_ERRORMESSAGE");
    lua_pushuserdata(s->L,s); lua_pushcclosure(s->L,dofile_pack,1);
    lua_setglobal(s->L,"dofile"); /* logical pack names; never host filesystem */
    lua_newtable(s->L);
    for (size_t i=0;i<sizeof(methods)/sizeof(*methods);i++) {
        lua_pushstring(s->L,methods[i]);
        lua_pushstring(s->L,methods[i]); lua_pushuserdata(s->L,s);
        lua_pushcclosure(s->L,dispatch,2); lua_settable(s->L,-3);
    }
    lua_setglobal(s->L,"be");
    return 0;
}
dw4_script *dw4_script_open(dw4_script_binding binding, void *user) {
    dw4_script *s=calloc(1,sizeof(*s));
    if (!s) return NULL;
    s->binding=binding; s->user=user;
    if(open_state(s)){free(s);return NULL;}
    return s;
}
static void close_state(dw4_script *s) {
    if(s->L){s->depth++;lua_close(s->L);s->depth--;}
    s->L=NULL;
    while(s->objects){struct object_value *v=s->objects;s->objects=v->next;free(v);}
    for(size_t i=0;i<s->count;i++)free(s->chunks[i].name);
    free(s->chunks);s->chunks=NULL;s->count=0;
}
static void free_info(struct script_info *info) {
    for(size_t i=0;i<info->count;i++) {
        free(info->rows[i].name);free(info->rows[i].bytes);
    }
    free(info->rows);
}
int dw4_script_busy(const dw4_script *s) {return s && s->depth;}
int dw4_script_remove_all(dw4_script *s) {
    if(!s || s->depth)return -1;
    for(size_t i=0;i<s->info_count;i++)free_info(s->infos+i);
    free(s->infos);s->infos=NULL;s->info_count=0;
    close_state(s);
    s->source=NULL;s->source_user=NULL;s->directory[0]=0;
    s->error[0]=0;return 0;
}
int dw4_script_recreate(dw4_script *s) {
    if(!s || s->depth)return -1;
    close_state(s);s->error[0]=0;
    if(open_state(s)) {snprintf(s->error,sizeof(s->error),"Lua state allocation failed");return -1;}
    return 0;
}
void dw4_script_close(dw4_script *s) {
    if (!s) return;
    if(!dw4_script_remove_all(s))free(s);
}
const char *dw4_script_error(const dw4_script *s) { return s?s->error:"no Lua state"; }

/* Preflight keeps negative/overflowing counts away from the old undumper.
 * The stock VM is for trusted game code, not an untrusted mod sandbox. */
struct cursor { const unsigned char *p; size_t n,off; };
static int take(struct cursor *c,size_t n) {
    if (n>c->n-c->off) return -1;
    c->off+=n; return 0;
}
static int word(struct cursor *c,uint32_t *v) {
    if (c->n-c->off<4) return -1;
    const unsigned char *p=c->p+c->off;
    *v=p[0]|(uint32_t)p[1]<<8|(uint32_t)p[2]<<16|(uint32_t)p[3]<<24;
    c->off+=4; return 0;
}
static int count(struct cursor *c,uint32_t *n) {
    return word(c,n) || *n>INT_MAX || *n>c->n-c->off ? -1:0;
}
static int string(struct cursor *c) {
    uint32_t n;
    if (word(c,&n) || n>c->n-c->off) return -1;
    if (n && c->p[c->off+n-1]!=0) return -1;
    return take(c,n);
}
static int proto(struct cursor *c,unsigned depth) {
    uint32_t n,params,stack,ins;
    if (depth>128 || string(c) || take(c,4) || word(c,&params) || take(c,1) ||
        word(c,&stack) || stack>4096 || params>stack || count(c,&n)) return -1;
    for (uint32_t i=0;i<n;i++) if (string(c)||take(c,8)) return -1;
    if (count(c,&n)||take(c,(size_t)n*4)||count(c,&n)) return -1;
    for (uint32_t i=0;i<n;i++) if (string(c)) return -1;
    if (count(c,&n)||take(c,(size_t)n*8)||count(c,&n)) return -1;
    for (uint32_t i=0;i<n;i++) if (proto(c,depth+1)) return -1;
    if (count(c,&n)||!n) return -1;
    for (uint32_t i=0;i<n;i++) if (word(c,&ins)||(ins&63)>48) return -1;
    return ins==0?0:-1;
}
int dw4_script_chunk_size(const void *chunk,size_t available,size_t *size) {
    static const unsigned char header[]={27,'L','u','a',0x40,1,4,4,4,32,6,9,8,
        0x12,0xe6,0x5b,0xa1,0xb0,0xb9,0xb2,0x41};
    struct cursor c={chunk,available,21};
    if (!chunk || available<21 || memcmp(chunk,header,sizeof(header)) || proto(&c,0)) return -1;
    if (size) *size=c.off;
    return 0;
}
/* Publication order determines name resolution. Keep older owners alive so
 * unloading an override exposes the previous closure without reparsing. */
static void remove_chunk(dw4_script *s,size_t i) {
    lua_unref(s->L,s->chunks[i].ref); free(s->chunks[i].name);
    memmove(s->chunks+i,s->chunks+i+1,(s->count-i-1)*sizeof(*s->chunks));
    s->count--;
}
void dw4_script_remove_scope(dw4_script *s,uint64_t scope) {
    if(s)for(size_t i=s->count;i>0;i--)
        if(s->chunks[i-1].scope==scope)remove_chunk(s,i-1);
    if(s)for(size_t i=s->info_count;i>0;i--)if(s->infos[i-1].scope==scope) {
        free_info(s->infos+i-1);
        memmove(s->infos+i-1,s->infos+i,(s->info_count-i)*sizeof(*s->infos));
        s->info_count--;
    }
}
static void publish_chunk(dw4_script *s,char *name,int ref,uint64_t scope) {
    for(size_t i=s->count;i>0;i--)
        if(s->chunks[i-1].scope==scope && !strcmp(s->chunks[i-1].name,name))
            remove_chunk(s,i-1);
    s->chunks[s->count++]=(struct script_chunk){name,ref,scope};
}
int dw4_script_load_scoped(dw4_script *s,uint64_t scope,const char *name,
    const void *chunk,size_t size) {
    size_t used;
    if (!s || !s->L || !name || !*name) return -1;
    s->error[0]=0;
    if (dw4_script_chunk_size(chunk,size,&used) || used!=size) {
        snprintf(s->error,sizeof(s->error),"%s: invalid/truncated Lua 4.0.1 chunk",name); return -1;
    }
    int top=lua_gettop(s->L);
    if (lua_loadbuffer(s->L,chunk,size,name)) { lua_settop(s->L,top); return -1; }
    int ref=lua_ref(s->L,1);
    char *copy=copy_string(name);
    struct script_chunk *list=realloc(s->chunks,(s->count+1)*sizeof(*list));
    if (!copy || !list) {
        free(copy); if (list) s->chunks=list;
        lua_unref(s->L,ref); snprintf(s->error,sizeof(s->error),"Lua chunk allocation failed"); return -1;
    }
    s->chunks=list; publish_chunk(s,copy,ref,scope); return 0;
}
int dw4_script_load(dw4_script *s,const char *name,const void *chunk,size_t size) {
    return dw4_script_load_scoped(s,0,name,chunk,size);
}
int dw4_script_run(dw4_script *s,const char *name) {
    if (!s || !s->L || !name) return -1;
    if(s->retail)return dw4_script_run_named(s,name,NULL)?-1:0;
    if (s->depth>=64) { snprintf(s->error,sizeof(s->error),"recursive script call limit"); return -1; }
    for (size_t n=s->count;n>0;n--) {
        size_t i=n-1;
        if (strcmp(s->chunks[i].name,name)) continue;
        int top=lua_gettop(s->L);
        if (!s->depth) s->error[0]=0;
        lua_getref(s->L,s->chunks[i].ref); s->depth++;
        int rc=lua_call(s->L,0,0); s->depth--; lua_settop(s->L,top);
        if (rc && !s->error[0]) snprintf(s->error,sizeof(s->error),"%s: Lua error %d",name,rc);
        return rc?-1:0;
    }
    snprintf(s->error,sizeof(s->error),"script not loaded: %s",name); return -1;
}
int dw4_script_call(dw4_script *s,const char *name,const dw4_script_value *args,size_t n) {
    if (!s || !s->L || !name || n>8 || s->depth>=64) return -1;
    int top=lua_gettop(s->L);
    if (!s->depth) s->error[0]=0;
    lua_getglobal(s->L,name);
    if (!lua_isfunction(s->L,-1)) {
        lua_settop(s->L,top); snprintf(s->error,sizeof(s->error),"Lua function missing: %s",name); return -1;
    }
    for (size_t i=0;i<n;i++){
        if(!object_usable(s,&args[i])){lua_settop(s->L,top);snprintf(s->error,sizeof s->error,"invalid or expired native object argument");return -1;}
        push_value(s,&args[i]);
    }
    s->depth++; int rc=lua_call(s->L,(int)n,0); s->depth--; lua_settop(s->L,top);
    if (rc && !s->error[0]) snprintf(s->error,sizeof(s->error),"%s: Lua error %d",name,rc);
    return rc?-1:0;
}
int dw4_script_set(dw4_script *s,const char *name,dw4_script_value v) {
    if (!s || !s->L || !name) return -1;
    if(!object_usable(s,&v)){snprintf(s->error,sizeof s->error,"invalid or expired native object value");return -1;}
    push_value(s,&v); lua_setglobal(s->L,name); return 0;
}
int dw4_script_get(dw4_script *s,const char *name,dw4_script_value *v) {
    if (!s || !s->L || !name || !v) return -1;
    lua_getglobal(s->L,name); int rc=read_value(s,-1,v); lua_pop(s->L,1); return rc;
}

static int load_pack(dw4_script *s,uint64_t scope,dw4_igb *g,const char *selected) {
    if(!s || !s->L || !g)return -1;
    struct pending { char *name; const uint8_t *bytes; size_t size; int ref; };
    struct pending *pending=NULL;
    size_t n=0;
    int rc=-1, top=lua_gettop(s->L);
    s->error[0]=0;
    if (dw4_igb_refs_open(g)) goto failed;
    for (uint32_t id=0;id<g->table_n;id++) {
        dw4_igb_record r={0}; dw4_object o={0};
        if (g->id_kind[id]!=2 || !dw4_igb_decode(g,g->id_off[id],&r)) continue;
        if (strcmp(r.class_name,"beLuaData")) { dw4_igb_record_free(&r); continue; }
        if(selected && (!r.name || strcmp(selected,r.name))){dw4_igb_record_free(&r);continue;}
        if (dw4_object_from_record(&o,g,&r)) { dw4_igb_record_free(&r); goto failed; }
        uint32_t data_id=dw4_object_get_ref(&o,"_dataObject"),off,len;
        char *name=r.name?copy_string(r.name):NULL;
        dw4_object_free(&o); dw4_igb_record_free(&r);
        if (!name || !*name || dw4_igb_ref(g,data_id,&off,&len)!=2 ||
            !dw4_igb_decode(g,off,&r)) { free(name); goto failed; }
        if (strcmp(r.class_name,"beLuaDataObject") || dw4_object_from_record(&o,g,&r)) {
            dw4_igb_record_free(&r); free(name); goto failed;
        }
        int32_t size=dw4_object_get_i32(&o,"_dataSize");
        const uint8_t *bytes=dw4_igb_block(g,dw4_object_get_ref(&o,"_data"),&len);
        dw4_object_free(&o); dw4_igb_record_free(&r);
        size_t used;
        if (size<=0 || !bytes || (uint32_t)size>len ||
            dw4_script_chunk_size(bytes,(size_t)size,&used) || used!=(size_t)size) {
            snprintf(s->error,sizeof(s->error),"%s: bad beLuaDataObject chunk",name);
            free(name); goto failed;
        }
        for (size_t i=0;i<n;i++) if (!strcmp(name,pending[i].name)) {
            snprintf(s->error,sizeof(s->error),"duplicate script in pack: %s",name);
            free(name); goto failed;
        }
        struct pending *list=realloc(pending,(n+1)*sizeof(*list));
        if (!list) { free(name); goto failed; }
        pending=list; pending[n++]=(struct pending){name,bytes,(size_t)size,LUA_NOREF};
    }
    if (!n) { snprintf(s->error,sizeof(s->error),"pack contains no beLuaData"); goto failed; }
    for (size_t i=0;i<n;i++) {
        if (lua_loadbuffer(s->L,(const char *)pending[i].bytes,pending[i].size,pending[i].name)) goto failed;
        pending[i].ref=lua_ref(s->L,1);
    }
    /* Allocate before publication. Replacement refs stay live until all load. */
    struct script_chunk *list=realloc(s->chunks,(s->count+n)*sizeof(*list));
    if (!list) goto failed;
    s->chunks=list;
    for (size_t i=0;i<n;i++) {
        publish_chunk(s,pending[i].name,pending[i].ref,scope);
        pending[i].name=NULL; pending[i].ref=LUA_NOREF;
    }
    rc=(int)n;
failed:
    for (size_t i=0;i<n;i++) {
        free(pending[i].name);
        if (pending[i].ref!=LUA_NOREF) lua_unref(s->L,pending[i].ref);
    }
    free(pending); lua_settop(s->L,top);
    if (rc<0 && !s->error[0]) snprintf(s->error,sizeof(s->error),"Lua pack load failed");
    return rc;
}
int dw4_script_load_pack(dw4_script *s,dw4_igb *g) {return load_pack(s,0,g,NULL);}
int dw4_script_load_pack_named(dw4_script *s,dw4_igb *g,const char *name) {
    return name?load_pack(s,0,g,name):-1;
}
int dw4_script_load_pack_scoped(dw4_script *s,uint64_t scope,dw4_igb *g) {
    return load_pack(s,scope,g,NULL);
}
int dw4_script_load_pack_named_scoped(dw4_script *s,uint64_t scope,dw4_igb *g,const char *name) {
    return name?load_pack(s,scope,g,name):-1;
}

int dw4_script_collect_info(dw4_script *s,const dw4_script_buffer *rows,size_t n) {
    if(!s || (n && !rows) || n>INT_MAX)return -1;
    struct script_info info={0};
    info.rows=calloc(n?n:1,sizeof(*info.rows));
    if(!info.rows)goto fail;
    info.count=n;
    for(size_t i=0;i<n;i++) {
        size_t used;
        if(!rows[i].name || !*rows[i].name ||
           dw4_script_chunk_size(rows[i].bytes,rows[i].size,&used) || used!=rows[i].size)goto fail;
        info.rows[i].name=copy_string(rows[i].name);
        info.rows[i].bytes=malloc(rows[i].size);
        if(!info.rows[i].name || !info.rows[i].bytes)goto fail;
        memcpy(info.rows[i].bytes,rows[i].bytes,rows[i].size);
        info.rows[i].size=rows[i].size;
    }
    struct script_info *list=realloc(s->infos,(s->info_count+1)*sizeof(*list));
    if(!list)goto fail;
    s->infos=list;list[s->info_count++]=info;s->retail=1;s->error[0]=0;
    return (int)n;
fail:
    free_info(&info);snprintf(s->error,sizeof(s->error),"Lua info collection failed");return -1;
}
static uint32_t little32(const uint8_t *p) {
    return p[0]|(uint32_t)p[1]<<8|(uint32_t)p[2]<<16|(uint32_t)p[3]<<24;
}
static int object_record(dw4_igb *g,uint32_t id,const char *kind,dw4_igb_record *r,dw4_object *o) {
    uint32_t off;
    if(dw4_igb_ref(g,id,&off,NULL)!=2 || !dw4_igb_decode(g,off,r))return -1;
    if(strcmp(r->class_name,kind) || dw4_object_from_record(o,g,r)) {
        dw4_igb_record_free(r);return -1;
    }
    return 0;
}
/* Unlike the legacy cache loader, only referenced rows are collected. */
static int collect_pack_info(dw4_script *s,dw4_igb *g,uint32_t id) {
    dw4_igb_record r={0};dw4_object o={0};
    if(object_record(g,id,"beLuaInfo",&r,&o))return -1;
    uint32_t list=dw4_object_get_ref(&o,"_dataList"),off,len;
    dw4_object_free(&o);dw4_igb_record_free(&r);
    if(dw4_igb_ref(g,list,&off,NULL)!=2 || !dw4_igb_decode(g,off,&r))return -1;
    if(strcmp(r.class_name,"beLuaDataList")){dw4_igb_record_free(&r);return -1;}
    uint32_t count=UINT32_MAX,capacity=0,array=UINT32_MAX;
    for(uint32_t i=0;i<r.nvalues;i++) {
        if(r.values[i].ordinal==2)count=r.values[i].raw;
        if(r.values[i].ordinal==3)capacity=r.values[i].raw;
        if(r.values[i].ordinal==4 && r.values[i].type==DW4_IGB_TY_MEMREF)array=r.values[i].raw;
    }
    dw4_igb_record_free(&r);
    const uint8_t *ids=dw4_igb_block(g,array,&len);
    if(count>INT_MAX || count>capacity || (count && (!ids || count>len/4)))return -1;
    dw4_script_buffer *rows=calloc(count?count:1,sizeof(*rows));
    if(!rows)return -1;
    int rc=-1;
    for(uint32_t i=0;i<count;i++) {
        if(object_record(g,little32(ids+4*i),"beLuaData",&r,&o))goto done;
        uint32_t data=dw4_object_get_ref(&o,"_dataObject");
        rows[i].name=r.name?copy_string(r.name):NULL;
        dw4_object_free(&o);dw4_igb_record_free(&r);
        if(!rows[i].name || object_record(g,data,"beLuaDataObject",&r,&o))goto done;
        int32_t size=dw4_object_get_i32(&o,"_dataSize");
        rows[i].bytes=dw4_igb_block(g,dw4_object_get_ref(&o,"_data"),&len);
        dw4_object_free(&o);dw4_igb_record_free(&r);
        if(size<=0 || !rows[i].bytes || (uint32_t)size>len)goto done;
        rows[i].size=(size_t)size;
    }
    rc=dw4_script_collect_info(s,rows,count);
done:
    for(uint32_t i=0;i<count;i++)free((void *)rows[i].name);
    free(rows);return rc;
}
int dw4_script_collect_pack_scoped(dw4_script *s,uint64_t scope,dw4_igb *g) {
    if(!s || !g)return -1;
    dw4_script pending={0};int chunks=0;
    if(dw4_igb_refs_open(g))goto failed;
    for(uint32_t id=0;id<g->table_n;id++) {
        dw4_igb_record r={0};
        if(g->id_kind[id]!=2 || !dw4_igb_decode(g,g->id_off[id],&r))continue;
        int match=!strcmp(r.class_name,"beLuaInfo");dw4_igb_record_free(&r);
        if(!match)continue;
        int n=collect_pack_info(&pending,g,id);
        if(n<0 || chunks>INT_MAX-n)goto failed;
        chunks+=n;pending.infos[pending.info_count-1].scope=scope;
    }
    if(!pending.info_count)goto failed;
    struct script_info *list=realloc(s->infos,(s->info_count+pending.info_count)*sizeof(*list));
    if(!list)goto failed;
    s->infos=list;memcpy(list+s->info_count,pending.infos,pending.info_count*sizeof(*list));
    s->info_count+=pending.info_count;free(pending.infos);s->retail=1;s->error[0]=0;
    return chunks;
failed:
    dw4_script_remove_all(&pending);
    snprintf(s->error,sizeof(s->error),"Lua pack info collection failed");return -1;
}
int dw4_script_collect_pack(dw4_script *s,dw4_igb *g) {
    return dw4_script_collect_pack_scoped(s,0,g);
}
void dw4_script_source_set(dw4_script *s,dw4_script_source source,void *user,const char *directory) {
    if(!s)return;
    s->source=source;s->source_user=user;s->retail=1;
    snprintf(s->directory,sizeof(s->directory),"%s",directory?directory:"");
}
static int run_buffer(dw4_script *s,const void *bytes,size_t size,const char *name) {
    int top=lua_gettop(s->L);
    s->error[0]=0;s->depth++;
    int rc=lua_dobuffer(s->L,bytes,size,name);
    s->depth--;lua_settop(s->L,top);
    if(rc && !s->error[0])snprintf(s->error,sizeof(s->error),"%s: Lua error %d",name,rc);
    return rc;
}
int dw4_script_has_info(const dw4_script *s,const char *name) {
    if(!s || !name)return 0;
    if(!s->info_count)return 1;   /* no info registry (a host-supplied source): every name may resolve */
    for(size_t i=0;i<s->info_count;i++)for(size_t j=0;j<s->infos[i].count;j++)if(!strcmp(s->infos[i].rows[j].name,name))return 1;
    return 0;
}
int dw4_script_run_named(dw4_script *s,const char *name,const char *directory) {
    if(!s || !s->L || !name)return -1;
    if(s->depth>=64){snprintf(s->error,sizeof(s->error),"recursive script call limit");return LUA_ERRRUN;}
    int status=-1;
    /* Snapshot the selected bytes before invoking native code: scope removal
     * from a callback must not invalidate this call's later info matches. */
    struct script_info selected={0};
    selected.rows=calloc(s->info_count?s->info_count:1,sizeof(*selected.rows));
    if(!selected.rows)return LUA_ERRMEM;
    for(size_t i=0;i<s->info_count;i++)for(size_t j=0;j<s->infos[i].count;j++) {
        struct info_row *row=s->infos[i].rows+j;
        if(strcmp(row->name,name))continue;
        struct info_row *out=selected.rows+selected.count++;
        out->name=copy_string(row->name);out->bytes=malloc(row->size);out->size=row->size;
        if(!out->name || !out->bytes){free_info(&selected);return LUA_ERRMEM;}
        memcpy(out->bytes,row->bytes,row->size);break;
    }
    for(size_t i=0;i<selected.count;i++) {
        struct info_row *row=selected.rows+i;
        status=run_buffer(s,row->bytes,row->size,row->name);
    }
    free_info(&selected);
    if(status!=-1)return status;
    char path[512];const void *bytes=NULL;size_t size=0;
    const char *dir=directory?directory:s->directory;
    int length=snprintf(path,sizeof(path),"%s%s%s",dir,*dir?"/":"",name);
    if(length<0 || (size_t)length>=sizeof(path))return -1;
    s->depth++;
    status=s->source?s->source(s->source_user,path,&bytes,&size):LUA_ERRFILE;
    s->depth--;
    if(status) {
        snprintf(s->error,sizeof(s->error),"script not loaded: %.450s (fallback %d)",path,status);return status;
    }
    if(bytes)for(size_t i=0;i+5<=size;i++)if(!memcmp((const char *)bytes+i,"[EOF]",5))
        return run_buffer(s,bytes,i,path);
    snprintf(s->error,sizeof(s->error),"%.480s: missing [EOF] marker",path);return -1;
}
