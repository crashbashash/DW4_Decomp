struct IniDocument { int pad0; int _refCount; char *text; };
struct IniCacheTable { int pad0; int _refCount; };
struct IniSourceList { char pad0[20]; void *entries; };
struct IniFieldEntry { char pad0[56]; IniCacheTable *cache; };
struct IniFactoryState { char pad0[20]; int mode; char pad1[32]; IniCacheTable *cache; };
extern "C" {
void *FUN_00309a60(void *, void *, void *, int);
IniFieldEntry *FUN_003022c0(void *, void *, char *);
IniDocument *FUN_00303d70(IniCacheTable *, char *);
void FUN_00303cd0(IniCacheTable *, char *, IniDocument *);
void FUN_001ce400(IniDocument **, char *);
void *igObject_GetAllocator(void *);
IniDocument *FUN_002baff0(void *);
int FUN_00305d30(IniDocument *, char *, void *);
void FUN_003061c0(IniDocument *, IniDocument *, int);
int igObject_IsKindOf(void *, void *);
void igObject_Destroy(void *);
extern char *DAT_004c22f0[4];
extern void *DAT_00586dd0;
extern int DAT_004fb3a8[4];
extern int DAT_004e1b58[4];
extern int DAT_004e4660[4];
extern void *DAT_00561500[4];
extern void *DAT_005619b0[4];
extern void *DAT_00585a08[4];
}
#define SLOT(T, x) (*(T *volatile *)&(x))
#define ADD(o) do { if (o != 0) { o->_refCount = o->_refCount + 1; } } while (0)
#define DROP(T, x) \
    do { \
        T *o_ = (x); \
        if (o_ != 0) { \
            o_->_refCount = o_->_refCount - 1; \
            if (((unsigned long long)((long long)(int)o_->_refCount << 0x29) >> 0x29) == 0) { \
                igObject_Destroy(o_); \
            } \
        } \
    } while (0)
#define SET_OUT(v) \
    do { \
        *out = (v); \
        { IniDocument *a_ = *out; ADD(a_); } \
    } while (0)
#define FINISH() \
    do { \
        DROP(IniCacheTable, cache); \
        DROP(IniDocument, parsed); \
        DROP(IniDocument, result); \
        return 0; \
    } while (0)
#define USE_CACHE(source) \
    do { \
        held = (source); \
        ADD(held); \
        DROP(IniCacheTable, cache); \
        SLOT(IniCacheTable, cache) = held; \
    } while (0)
extern "C" int FUN_001cd150(IniDocument **out, IniFactoryState *self, char *name) {
    IniDocument *result;
    IniDocument *parsed;
    IniCacheTable *cache;
    IniDocument *found;
    IniDocument *path;
    IniCacheTable *held;
    SLOT(IniDocument, result) = 0;
    { IniDocument *a_ = result; ADD(a_); }
    SLOT(IniDocument, parsed) = 0;
    { IniDocument *a_ = parsed; ADD(a_); }
    SLOT(IniCacheTable, cache) = 0;
    { IniCacheTable *a_ = cache; ADD(a_); }
    if (name == 0) {
        SET_OUT(0);
        FINISH();
    }
    if (self->mode != 0) {
        if (self->mode == 3) {
            IniSourceList *source = (IniSourceList *)FUN_00309a60(DAT_00586dd0, DAT_004fb3a8, DAT_004e1b58, 0);
            IniFieldEntry *entry;
            if (source == 0 || igObject_IsKindOf(source, DAT_00561500[0]) == 0) {
                SET_OUT(result);
                FINISH();
            }
            entry = FUN_003022c0(source->entries, DAT_005619b0[0], name);
            if (entry != 0) {
                USE_CACHE(entry->cache);
            } else {
                USE_CACHE(self->cache);
            }
        } else {
            USE_CACHE(self->cache);
        }
        SLOT(IniDocument, found) = FUN_00303d70(cache, name);
        { IniDocument *a_ = found; ADD(a_); }
        if (found != 0 && igObject_IsKindOf(found, DAT_00585a08[0]) != 0) {
            IniDocument *keep = found;
            ADD(keep);
            DROP(IniDocument, parsed);
            SLOT(IniDocument, parsed) = keep;
        }
        DROP(IniDocument, found);
    }
    if (parsed == 0) {
        FUN_001ce400(&path, name);
        if (path == 0) {
            SET_OUT(0);
            DROP(IniDocument, path);
            FINISH();
        }
        {
            void *allocator = igObject_GetAllocator(self);
            char *text;
            IniDocument *loading;
            DROP(IniDocument, parsed);
            SLOT(IniDocument, parsed) = FUN_002baff0(allocator);
            loading = parsed;
            text = path->text;
            text = (text == 0) ? DAT_004c22f0[0] : text;
            if (FUN_00305d30(loading, text, DAT_004e4660) == 0) {
                SET_OUT(0);
                DROP(IniDocument, path);
                FINISH();
            }
            if (self->mode != 0) {
                FUN_00303cd0(cache, name, parsed);
            }
            DROP(IniDocument, path);
        }
    }
    if (self->mode == 0) {
        IniDocument *keep = parsed;
        ADD(keep);
        DROP(IniDocument, result);
        SLOT(IniDocument, result) = keep;
    } else {
        void *allocator = igObject_GetAllocator(self);
        DROP(IniDocument, result);
        SLOT(IniDocument, result) = FUN_002baff0(allocator);
        FUN_003061c0(result, parsed, 1);
    }
    SET_OUT(result);
    FINISH();
}
