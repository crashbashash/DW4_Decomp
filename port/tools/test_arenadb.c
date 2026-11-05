/* P1 of docs/arena-object-model.md: the real DATABASE tables of the Main Lobby pack, loaded as typed instances in the game arena, must
 * answer the typed accessors (arenadb.c, clean ports of retail 0x3a9460/0x3a9540/0x3a9580 on the decomp's structs) exactly as the
 * port's retail-checked host database does, for EVERY database, table, column and row, including rows outside the table, missing
 * columns and invalid input. Needs the extracted assets (argv[1], default ../../local/extracted). */
#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dw4/arena.h"
#include "dw4/arenadb.h"
#include "dw4/arenapack.h"
#include "dw4/database.h"
#include "dw4/igb.h"
#include "dw4/mount.h"
#include "dw4/object.h"
#include "dw4/reflected.h"
#include "dw4/stageobjects.h"

/* ---- the oracle: an independent decoding of the pack records (the retail-checked host builder this replaced) ---------------- */
struct ref_numbers {char **columns;uint32_t ncolumns,count;int32_t *values;};
typedef struct {char **columns,**strings;uint32_t ncolumns,nstrings;struct ref_numbers numeric[4];} ref_db;

static char *ref_copy(const char *s)
{size_t n=strlen(s)+1;char *p=malloc(n);if(p)memcpy(p,s,n);return p;}
static uint32_t ref_raw(const dw4_igb_record *r,unsigned ordinal)
{for(uint32_t i=0;i<r->nvalues;i++)if(r->values[i].ordinal==ordinal)return r->values[i].raw;return UINT32_MAX;}
static uint32_t ref_u32(const uint8_t *p)
{return p[0]|(uint32_t)p[1]<<8|(uint32_t)p[2]<<16|(uint32_t)p[3]<<24;}
static int ref_record(const dw4_igb *g,uint32_t id,const char *kind,dw4_igb_record *r)
{
    uint32_t off;
    if(dw4_igb_ref(g,id,&off,NULL)!=2 || !dw4_igb_decode(g,off,r))return -1;
    if(strcmp(r->class_name,kind)){dw4_igb_record_free(r);memset(r,0,sizeof(*r));return -1;}
    return 0;
}
static int ref_names(const dw4_igb *g,uint32_t id,char ***out,uint32_t *count)
{
    dw4_igb_record r={0};uint32_t bytes=0;
    if(ref_record(g,id,"igNamedObjectList",&r))return -1;
    uint32_t n=ref_raw(&r,2),cap=ref_raw(&r,3),block=ref_raw(&r,4);dw4_igb_record_free(&r);
    const uint8_t *p=dw4_igb_block(g,block,&bytes);
    if(n>INT_MAX || n>cap || (n && (!p || n>bytes/4)))return -1;
    char **v=calloc(n?n:1,sizeof(*v));if(!v)return -1;
    *out=v;*count=n; /* partial allocation is released by the private owner */
    for(uint32_t i=0;i<n;i++){
        if(ref_record(g,ref_u32(p+4*i),"igNamedObject",&r))return -1;
        if(r.name)v[i]=ref_copy(r.name);
        int failed=r.name && !v[i];dw4_igb_record_free(&r);
        if(failed)return -1;
    }
    return 0;
}
static int ref_numbers(const dw4_igb *g,const dw4_object *o,unsigned type,struct ref_numbers *t)
{
    static const char *const keys[]={"_charOffsetList","_shortOffsetList","_intOffsetList","_boolOffsetList"};
    static const char *const data[]={"_charData","_shortData","_intData","_boolData"};
    static const char *const kinds[]={"igCharList","igShortList","igIntList","igBoolList"};
    unsigned width=type==3?1:1u<<type;dw4_igb_record r={0};uint32_t bytes;
    if(ref_names(g,dw4_object_get_ref(o,keys[type]),&t->columns,&t->ncolumns) ||
       ref_record(g,dw4_object_get_ref(o,data[type]),kinds[type],&r))return -1;
    uint32_t n=ref_raw(&r,2),cap=ref_raw(&r,3),block=ref_raw(&r,4);dw4_igb_record_free(&r);
    const uint8_t *p=dw4_igb_block(g,block,&bytes);
    if(n>INT_MAX || n>cap || (n && (!p || n>bytes/width)) ||
       (t->ncolumns?n%t->ncolumns:n!=0))return -1;
    t->values=calloc(n?n:1,sizeof(*t->values));if(!t->values)return -1;t->count=n;
    for(uint32_t i=0;i<n;i++){
        uint32_t v=width==1?p[i]:width==2?p[2*i]|(uint32_t)p[2*i+1]<<8:ref_u32(p+4*i);
        if(type==3)t->values[i]=(int32_t)v;
        else if(width==1)t->values[i]=(int8_t)v;
        else if(width==2)t->values[i]=(int16_t)v;
        else memcpy(t->values+i,&v,4);
    }
    return 0;
}

static size_t ref_string_rows(const ref_db *d){return d && d->ncolumns?d->nstrings/d->ncolumns:0;}
static int32_t ref_string_offset(const char *const *columns,uint32_t count,int32_t row,const char *name)
{
    if(!columns || !name || !count)return -1;
    for(uint32_t i=0;i<count;i++)if(columns[i] && !strcmp(columns[i],name)){
        uint32_t bits=(uint32_t)row*count+i;int32_t v;memcpy(&v,&bits,4);return v;
    }
    return -1;
}
static const char *ref_string(const ref_db *d,int32_t row,const char *column)
{
    if(!d || row<0 || (uint32_t)row>=ref_string_rows(d))return NULL;
    int32_t i=ref_string_offset((const char *const *)d->columns,d->ncolumns,row,column);
    if(i<0 || (uint32_t)i>=d->nstrings)return NULL;
    return d->strings[i]?d->strings[i]:""; /* 3a9580's null name fallback 4e0858 */
}

static int ref_number(const ref_db *d,int32_t row,const char *column,int32_t *out)
{
    if(!d || row<0 || !column || !out)return -1;
    *out=0;
    for(unsigned k=0;k<3;k++){
        const struct ref_numbers *t=d->numeric+k;
        int32_t i=ref_string_offset((const char *const *)t->columns,t->ncolumns,row,column);
        if(i==-1)continue;
        if(!t->ncolumns || (uint32_t)row>=t->count/t->ncolumns || i<0 || (uint32_t)i>=t->count)return -1;
        *out=t->values[i];return 0;
    }
    return 1;
}
static int ref_bool(const ref_db *d,int32_t row,const char *column,int32_t *out)
{
    if(!d || row<0 || !column || !out)return -1;
    *out=0;const struct ref_numbers *t=d->numeric+3;
    int32_t i=ref_string_offset((const char *const *)t->columns,t->ncolumns,row,column);
    if(i==-1)return 1;
    if(!t->ncolumns || (uint32_t)row>=t->count/t->ncolumns || i<0 || (uint32_t)i>=t->count)return -1;
    *out=t->values[i];return 0;
}


static int ref_build(const dw4_igb *g,const dw4_object *info,ref_db *d)
{
    dw4_igb_record r={0};dw4_object ob={0};int rc;
    memset(d,0,sizeof(*d));
    if(ref_record(g,dw4_object_get_ref(info,"_dataBase"),"beDataBase",&r))return -1;
    rc=dw4_object_from_record(&ob,g,&r);dw4_igb_record_free(&r);
    if(!rc)rc=ref_names(g,dw4_object_get_ref(&ob,"_stringOffsetList"),&d->columns,&d->ncolumns);
    if(!rc)rc=ref_names(g,dw4_object_get_ref(&ob,"_stringData"),&d->strings,&d->nstrings);
    for(unsigned k=0;!rc && k<4;k++)rc=ref_numbers(g,&ob,k,d->numeric+k);
    dw4_object_free(&ob);
    return rc;
}

/* the oracle reads the pack through a transient decoded record of the stage object */
static int ref_build_info(const dw4_igb *g,const dw4_stageobject *info,ref_db *d)
{
    dw4_igb_record r={0};dw4_object o={0};uint32_t off;int rc=-1;
    if(dw4_igb_ref(g,info->id,&off,NULL)==2 && dw4_igb_decode(g,off,&r)){
        if(!dw4_object_from_record(&o,g,&r)){rc=ref_build(g,&o,d);dw4_object_free(&o);}
        dw4_igb_record_free(&r);
    }
    return rc;
}
static void ref_free(ref_db *d)
{
    for(uint32_t j=0;j<d->ncolumns;j++)free(d->columns[j]);
    for(uint32_t j=0;j<d->nstrings;j++)free(d->strings[j]);
    free(d->columns);free(d->strings);
    for(unsigned k=0;k<4;k++){struct ref_numbers *n=d->numeric+k;for(uint32_t j=0;j<n->ncolumns;j++)free(n->columns[j]);free(n->columns);free(n->values);}
}

typedef struct {
    unsigned databases, columns, cells, strings, probes;
} stats;

#define SAME(cond) do { if (!(cond)) { fprintf(stderr, "mismatch: %s (db %s, column %s, row %d)\n", #cond, dbname, col, row); exit(1); } } while (0)

static const igIntList *list_of(dw4_arena *a, int32_t handle)
{
    dw4_handle h = {(uint32_t)handle};
    return handle ? (const igIntList *)dw4_arena_at(a, h, sizeof(igIntList)) : NULL;
}

static const char *name_of(dw4_arena *a, const igIntList *cols, int32_t i)
{
    dw4_handle bh = {(uint32_t)cols->_data}, oh;
    const uint8_t *b = (const uint8_t *)dw4_arena_at(a, bh, 4u * (uint32_t)(i + 1));
    const igNamedObject *o;
    dw4_handle sh;
    if (!b) return NULL;
    oh.off = b[4 * i] | (uint32_t)b[4 * i + 1] << 8 | (uint32_t)b[4 * i + 2] << 16 | (uint32_t)b[4 * i + 3] << 24;
    o = oh.off ? DW4_ARENA_OBJ(a, igNamedObject, oh) : NULL;
    if (!o) return NULL;
    sh.off = (uint32_t)o->_name;
    return sh.off ? (const char *)dw4_arena_at(a, sh, 1) : "";
}

static void compare_numeric(dw4_arena *a, dw4_handle db, const ref_db *hd, const char *dbname, int is_bool, int32_t cols_h,
                            int32_t vals_h, stats *st)
{
    const igIntList *cols = list_of(a, cols_h), *vals = list_of(a, vals_h);
    int32_t ncols, nrows, c, row;
    if (!cols || !vals || cols->_count <= 0) return;
    ncols = cols->_count;
    nrows = vals->_count / ncols;
    for (c = 0; c < ncols; c++) {
        const char *col = name_of(a, cols, c);
        st->columns++;
        if (!col) continue;
        for (row = -1; row <= nrows + 3; row++) {
            int32_t vh = 77, va = 77;
            int rh = is_bool ? ref_bool(hd, row, col, &vh) : ref_number(hd, row, col, &vh);
            int ra = is_bool ? dw4_adb_bool(a, db, row, col, &va) : dw4_adb_number(a, db, row, col, &va);
            SAME(rh == ra);
            SAME(vh == va);
            st->cells++;
        }
        {
            int32_t vh = 77, va = 77;
            int rh = is_bool ? ref_bool(hd, INT_MAX, col, &vh) : ref_number(hd, INT_MAX, col, &vh);
            int ra = is_bool ? dw4_adb_bool(a, db, INT_MAX, col, &va) : dw4_adb_number(a, db, INT_MAX, col, &va);
            row = INT_MAX;
            SAME(rh == ra && vh == va);
            st->probes++;
        }
    }
}

static void compare_database(dw4_arena *a, dw4_handle db, const ref_db *hd, const char *dbname, stats *st)
{
    const beDataBase *d = DW4_ARENA_OBJ(a, beDataBase, db);
    const igIntList *scols, *svals;
    int32_t c, row = 0, vh = 5, va = 5;
    const char *col = "";
    assert(d);
    compare_numeric(a, db, hd, dbname, 0, d->_charOffsetList, d->_charData, st);
    compare_numeric(a, db, hd, dbname, 0, d->_shortOffsetList, d->_shortData, st);
    compare_numeric(a, db, hd, dbname, 0, d->_intOffsetList, d->_intData, st);
    compare_numeric(a, db, hd, dbname, 1, d->_boolOffsetList, d->_boolData, st);

    scols = list_of(a, d->_stringOffsetList);
    svals = list_of(a, d->_stringData);
    SAME(dw4_adb_string_rows(a, db) == ref_string_rows(hd));
    if (scols && svals && scols->_count > 0) {
        int32_t nrows = svals->_count / scols->_count;
        for (c = 0; c < scols->_count; c++) {
            col = name_of(a, scols, c);
            st->columns++;
            if (!col) continue;
            for (row = -1; row <= nrows + 2; row++) {
                const char *sh = ref_string(hd, row, col), *sa = dw4_adb_string(a, db, row, col);
                SAME((sh == NULL) == (sa == NULL));
                SAME(!sh || !strcmp(sh, sa));
                st->strings++;
            }
        }
    }
    /* missing columns and invalid input behave alike */
    col = "NO_SUCH_COLUMN_XYZ";
    row = 0;
    SAME(ref_number(hd, 0, col, &vh) == dw4_adb_number(a, db, 0, col, &va) && vh == va);
    SAME(ref_bool(hd, 0, col, &vh) == dw4_adb_bool(a, db, 0, col, &va) && vh == va);
    SAME(ref_string(hd, 0, col) == NULL && dw4_adb_string(a, db, 0, col) == NULL);
    row = -5;
    SAME(ref_number(hd, -5, "NAME", &vh) == dw4_adb_number(a, db, -5, "NAME", &va));
    SAME(ref_string(hd, -5, "NAME") == NULL && dw4_adb_string(a, db, -5, "NAME") == NULL);
    SAME(dw4_adb_number(a, db, 0, NULL, &va) == -1 && dw4_adb_number(a, db, 0, "NAME", NULL) == -1);
    st->databases++;
}

int main(int argc, char **argv)
{
    dw4_mount m;
    uint32_t size;
    const uint8_t *bytes;
    dw4_igb g = {0};
    dw4_stageobjects *s;
    dw4_databases *owner;
    dw4_arena *a;
    dw4_arena_pack pk;
    char error[256];
    stats st = {0};
    const char *seen[64];
    size_t nseen = 0, i, j;
    dw4_handle first_db = {0};
    char first_name[128] = "";

    assert(!dw4_mount_open(&m, argc > 1 ? argv[1] : "../../local/extracted"));
    bytes = dw4_mount_data(&m, "stagML11/separate/USA_pack.igb", &size);
    assert(bytes);
    assert(!dw4_igb_open(&g, bytes, size, 0) && !dw4_igb_refs_open(&g));

    s = dw4_stageobjects_open();
    assert(s && !dw4_stageobjects_route(s, "USA-arena-database", &g, 0));
    owner = dw4_databases_open(s, error, sizeof error);
    if (!owner) fprintf(stderr, "%s\n", error);
    assert(owner && dw4_databases_count(owner) > 0);

    a = dw4_arena_open(0, error, sizeof error);
    assert(a && dw4_class_register_schema(a) > 100);
    if (dw4_arena_pack_load(a, DW4_REGION_STAGE, &g, &pk, error, sizeof error)) {
        fprintf(stderr, "%s\n", error);
        return 1;
    }
    assert(pk.objects > 100 && pk.blocks > 10);

    for (i = 0; i < dw4_stageobjects_count(s); i++) {
        const dw4_stageobject *info = dw4_stageobjects_at(s, i);
        ref_db rd;
        const ref_db *hd = &rd;
        dw4_handle db;
        dw4_dbtable twin;
        int dup = 0;
        if (strcmp(dw4_stageobject_class(info), "beDBManagerInfo")) continue;
        for (j = 0; j < nseen; j++) if (!strcmp(seen[j], dw4_stageobject_name(info))) dup = 1;
        if (dup || nseen == 64) continue;                      /* the owner answers the first database of a name */
        seen[nseen++] = dw4_stageobject_name(info);
        assert(!ref_build_info(&g, info, &rd));
        db = dw4_arena_pack_handle(&pk, dw4_stageobject_ref_id(info, "_dataBase"));
        assert(db.off);
        assert(dw4_arena_object_is(a, db, dw4_arena_object_vtable(a, db)));
        assert(!dw4_adb_validate(a, db, error, sizeof error));
        compare_database(a, db, hd, dw4_stageobject_name(info), &st);
        {   /* the production path: the owner's own typed table answers the same */
            stats sx = {0};
            twin = dw4_databases_table(owner, dw4_stageobject_name(info));
            assert(dw4_dbtable_valid(twin));
            compare_database(twin.arena, twin.db, hd, dw4_stageobject_name(info), &sx);
            assert(sx.cells == 0 || sx.databases == 1);
        }
        if (!first_db.off && ref_string(hd, 0, "NAME")) {
            first_db = db;
            snprintf(first_name, sizeof first_name, "%s", ref_string(hd, 0, "NAME"));
        }
        ref_free(&rd);
    }
    assert(st.databases > 0 && st.cells > 100 && st.strings > 10);

    /* the closure loader: only what the database roots reach, and every answer is the same */
    {
        uint32_t roots[64], nroots = 0;
        dw4_arena *b = dw4_arena_open(0, error, sizeof error);
        dw4_arena_pack pk2;
        stats st2 = {0};
        size_t n2 = 0;
        assert(b && dw4_class_register_schema(b) > 100);
        nseen = 0;
        for (i = 0; i < dw4_stageobjects_count(s); i++) {
            const dw4_stageobject *info = dw4_stageobjects_at(s, i);
            if (strcmp(dw4_stageobject_class(info), "beDBManagerInfo") || nroots == 64) continue;
            roots[nroots++] = dw4_stageobject_ref_id(info, "_dataBase");
        }
        assert(!dw4_arena_pack_load_from(b, DW4_REGION_PERSISTENT, &g, roots, nroots, &pk2, error, sizeof error));
        assert(pk2.objects > 0 && pk2.objects < pk.objects);
        for (i = 0; i < dw4_stageobjects_count(s); i++) {
            const dw4_stageobject *info = dw4_stageobjects_at(s, i);
            ref_db rd2;
            int dup = 0;
            if (strcmp(dw4_stageobject_class(info), "beDBManagerInfo")) continue;
            for (j = 0; j < n2; j++) if (!strcmp(seen[j], dw4_stageobject_name(info))) dup = 1;
            if (dup || n2 == 64) continue;
            seen[n2++] = dw4_stageobject_name(info);
            assert(!ref_build_info(&g, info, &rd2));
            compare_database(b, dw4_arena_pack_handle(&pk2, dw4_stageobject_ref_id(info, "_dataBase")), &rd2,
                             dw4_stageobject_name(info), &st2);
            ref_free(&rd2);
        }
        assert(st2.databases == st.databases && st2.cells == st.cells && st2.strings == st.strings);
        printf("arena database closure: %u of %u objects and %u of %u blocks reach the databases (%u of %u arena bytes), answers identical\n",
               pk2.objects, pk.objects, pk2.blocks, pk.blocks, dw4_arena_used(b, DW4_REGION_PERSISTENT),
               dw4_arena_used(a, DW4_REGION_STAGE));
        dw4_arena_pack_free(&pk2);
        dw4_arena_close(b);
    }

    /* the arena owns everything: the pack, the host owner and the mount can go, and the answers are unchanged */
    dw4_igb_close(&g);
    dw4_stageobjects_close(s);
    dw4_databases_close(owner);
    dw4_mount_close(&m);
    {
        const char *after = dw4_adb_string(a, first_db, 0, "NAME");
        assert(first_name[0] ? (after && !strcmp(after, first_name)) : 1);
    }
    printf("arena database: %u databases, %u columns, %u numeric/bool cells, %u string cells and %u edge probes match the host database "
           "(independent decoding of the pack records, retail-checked); pack of %u objects, %u blocks and %u strings loaded as typed instances\n",
           st.databases, st.columns, st.cells, st.strings, st.probes, pk.objects, pk.blocks, pk.strings);
    dw4_arena_pack_free(&pk);
    dw4_arena_close(a);
    assert(dw4_arena_live(dw4_session_arena(), DW4_REGION_PERSISTENT) == 0);   /* the owner released everything it allocated */
    return 0;
}
