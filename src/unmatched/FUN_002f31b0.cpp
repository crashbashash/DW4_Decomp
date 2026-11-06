/* Fills one memory-pool handle object from the pool descriptor table: looks up descriptor `index`
 * (0x90 bytes each, from +0x14 of the table) and, when the index is in 0..45, copies it into the
 * handle object: the descriptor name via igNamedObject_SetName, the integer size/limit fields
 * (+0x1c..+0x24, +0x50), and ten interned strings (+0x18, +0x28..+0x4c, each assigned through the
 * shared StringPool with the usual retain/release of the old token). The descriptor's attached
 * object (+0 of the entry) supplies +0x1c when it reports a size; the handle name (+0x14) is built
 * from the table name 'kIGMemoryPoolHandle%s'. The status written through `result` is DAT_004fb410
 * on success and DAT_004fb418 for an out-of-range index. The string assignment macro lives in a
 * separate header because a unit cannot be split around a file-scope multi-line macro. */
extern "C" {
void igNamedObject_SetName(void *, void *);
int FUN_002eb010(int);
int StringPool_Construct(int);
void *StringPool_Intern(int, const char *);
int StringChunk_ReleaseHeader(...);
int igObject_IsKindOf(void *, int);
int sprintf(char *, const char *, ...);
}

/* Header stored in front of every interned string token. */
struct StringTokenHeader { int owner; int refCount; };
typedef void StringToken;   /* a token points at the interned text; its header precedes it */

/* The descriptor's attached object: only the four virtuals this function calls are named; the others
 * are placeholders that keep the vtable byte offsets (8 + 4 * slot) right. */
class SizedObject {
public:
    virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7();
    virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15();
    virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23();
    virtual void p24(); virtual void p25(); virtual void p26();
    virtual unsigned int hasLimitOrSize();/* byte 116 */
    virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33();
    virtual long long limit();/* byte 144 */
    virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41();
    virtual unsigned int count();/* byte 176 */
    virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual void p49(); virtual void p50();
    virtual void p51(); virtual void p52(); virtual void p53(); virtual void p54(); virtual void p55(); virtual void p56(); virtual void p57(); virtual void p58();
    virtual void p59(); virtual void p60(); virtual void p61(); virtual void p62(); virtual void p63(); virtual void p64(); virtual void p65(); virtual void p66();
    virtual void p67(); virtual void p68(); virtual void p69(); virtual void p70(); virtual void p71(); virtual void p72(); virtual void p73(); virtual void p74();
    virtual void p75(); virtual void p76(); virtual void p77(); virtual void p78(); virtual void p79(); virtual void p80(); virtual void p81(); virtual void p82();
    virtual void p83(); virtual void p84(); virtual void p85(); virtual void p86(); virtual void p87(); virtual void p88(); virtual void p89(); virtual void p90();
    virtual void p91(); virtual void p92(); virtual void p93(); virtual void p94(); virtual void p95(); virtual void p96(); virtual void p97();
    virtual unsigned long long total();/* byte 400 */
};

/* Pool descriptor defaults (entry +0x84): interned-string sources and integer limits. */
struct PoolDefaults {
    char pad0[0x18];
    const char *text0;       /* +0x18 */
    int limit;               /* +0x1c */
    int field20;
    int field24;
    const char *text1;       /* +0x28 */
    const char *text2;
    const char *text3;
    const char *text4;
    const char *text5;
    const char *text6;
    const char *text7;
    const char *text8;
    const char *text9;
    const char *text10;      /* +0x4c */
    int field50;             /* +0x50 */
};
struct PoolEntry {
    SizedObject *object;     /* +0x00 */
    char name[0x80];         /* +0x04 */
    PoolDefaults *defaults;  /* +0x84 */
    char pad88[8];
};
struct PoolTable {
    char pad0[0x14];
    PoolEntry entries[46];   /* +0x14, 0x90 bytes each */
};
/* The pool handle object being filled; string members hold interned tokens. */
struct PoolHandle {
    char pad0[0x14];
    StringToken *handleName; /* +0x14 */
    StringToken *token0;     /* +0x18 */
    int limit;               /* +0x1c */
    int field20;
    int field24;
    StringToken *token1;     /* +0x28 */
    StringToken *token2;
    StringToken *token3;
    StringToken *token4;
    StringToken *token5;
    StringToken *token6;
    StringToken *token7;
    StringToken *token8;
    StringToken *token9;
    StringToken *token10;    /* +0x4c */
    int field50;             /* +0x50 */
};

extern int DAT_00586f20[4];
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
extern int DAT_00586a88[4];
extern int DAT_004c2170[];
extern char DAT_004fa3e0[];

#include "dw4/string_token_assign.h"

extern "C" void FUN_002f31b0(int *result, PoolTable *table, int index, PoolHandle *handle)
{
    StringToken *old;
    const char *text;
    SizedObject *object;
    StringTokenHeader *header;
    PoolEntry *entry;
    char nameBuf[128];
    int poolObj;
    int count;
    StringToken *token;
    int status;

    status = DAT_004fb410[0];
    if (index >= 0 && index < 46) {
        entry = &table->entries[index];
        igNamedObject_SetName(handle, entry->name);
        if (entry->defaults != 0) {
            ASSIGN_TOKEN(handle->token0, entry->defaults->text0);
            object = table->entries[index].object;
            if (object != 0) {
                if (igObject_IsKindOf(object, DAT_00586a88[0]) != 0) {
                    if (object->count() != 0) {
                        if (object->total() > object->count()) {
                            entry->defaults->limit = (int)object->total();
                        }
                    } else if (object->hasLimitOrSize() != 0) {
                        entry->defaults->limit = (int)object->limit();
                    }
                } else if (object->limit() != 0) {
                    entry->defaults->limit = (int)object->limit();
                }
            }
            handle->limit = entry->defaults->limit;
            handle->field20 = entry->defaults->field20;
            handle->field24 = entry->defaults->field24;
            ASSIGN_TOKEN(handle->token1, entry->defaults->text1);
            ASSIGN_TOKEN(handle->token2, entry->defaults->text2);
            ASSIGN_TOKEN(handle->token3, entry->defaults->text3);
            ASSIGN_TOKEN(handle->token4, entry->defaults->text4);
            ASSIGN_TOKEN(handle->token5, entry->defaults->text5);
            ASSIGN_TOKEN(handle->token6, entry->defaults->text6);
            ASSIGN_TOKEN(handle->token7, entry->defaults->text7);
            ASSIGN_TOKEN(handle->token8, entry->defaults->text8);
            ASSIGN_TOKEN(handle->token9, entry->defaults->text9);
            ASSIGN_TOKEN(handle->token10, entry->defaults->text10);
            handle->field50 = entry->defaults->field50;
        }
        sprintf(nameBuf, DAT_004fa3e0, DAT_004c2170[index]);
        ASSIGN_TOKEN_DIRECT(handle->handleName, nameBuf);
    } else {
        status = DAT_004fb418[0];
    }
    *result = status;
}
