#include "dw4/igobject_release.h"
struct ShaderObject { int pad0; int _refCount; };
struct ShaderNameList { int pad0; int _refCount; int count; };
struct ShaderMetaView;
struct ShaderProcessorView { char pad0[24]; int kind; int ini; char pad1[12]; int allocatorKey; };
struct ShaderCacheView;
extern "C" {
int FUN_00306360(int, char *, int);
unsigned char FUN_00306910(int, int, void *, char **, void *, int);
ShaderMetaView *FUN_002fe460(char *);
void FUN_002fd6e0(ShaderObject **, ShaderMetaView *, int);
void *igObject_GetAllocator(void *);
ShaderNameList *FUN_002b90e0(void *);
void FUN_00306aa0(int, int, void *, ShaderNameList *, int);
void StringList_CopyRetained(char **, ShaderNameList *, int);
void *FUN_002fdf20(ShaderMetaView *, char *);
int FUN_001c7680(ShaderProcessorView *, int, char *, ShaderObject *, void *, unsigned char *);
void FUN_00306e50(int, int, void *, unsigned char *, int, int);
ShaderCacheView *FUN_001ca6b0(ShaderProcessorView *, int);
ShaderObject *FUN_00303d70(ShaderCacheView *, char *);
int FUN_00300920(ShaderObject *, ShaderObject *);
void FUN_00303cd0(ShaderCacheView *, char *, ShaderObject *);
void StringChunk_ReleaseHeader(int, int *);
void igObject_Destroy(void *);
extern int DAT_004e4660[4];
extern int DAT_004e46f8[2];
extern int DAT_004e4700[2];
extern int DAT_004e4708[2];
}
static inline void releaseString(char *s) {
    if (s != 0) {
        int *h = (int *)s - 2;
        int c = ((int *)s)[-1] - 1;
        ((int *)s)[-1] = c;
        if (c == 0) {
            StringChunk_ReleaseHeader(*h, h);
        }
    }
}
#define SET_OUT(v) \
    do { \
        *out = (v); \
        { \
            ShaderObject *a_ = *out; \
            if (a_ != 0) { \
                a_->_refCount = a_->_refCount + 1; \
            } \
        } \
    } while (0)
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
extern "C" int FUN_001ca6c0(ShaderObject **out, ShaderProcessorView *self, char *name, unsigned char flag) {
    unsigned char cached;
    char *text;
    ShaderObject *object;
    ShaderNameList *names;
    char *key;
    int section;
    ShaderMetaView *meta;
    int count;
    int i;
    char *field;
    void *info;
    ShaderCacheView *cache;
    ShaderObject *existing;
    section = FUN_00306360(self->ini, name, 0);
    if (section == -1) {
        SET_OUT(0);
        return;
    }
    text = 0;
    if (FUN_00306910(self->ini, section, DAT_004e46f8, &text, DAT_004e4660, 0) == 0) {
        SET_OUT(0);
        releaseString(text);
        return 0;
    }
    meta = FUN_002fe460(text);
    if (meta == 0) {
        SET_OUT(0);
        releaseString(text);
        return 0;
    }
    FUN_002fd6e0((ShaderObject **)&object, meta, self->allocatorKey);
    if (object == 0) {
        SET_OUT(0);
        DROP(ShaderObject, object);
        releaseString(text);
        return 0;
    }
    *(ShaderNameList **)&names = FUN_002b90e0(igObject_GetAllocator(self));
    FUN_00306aa0(self->ini, section, DAT_004e4700, names, 0);
    count = names->count;
    for (i = 0; i < count; i++) {
        StringList_CopyRetained(&key, names, i);
        field = key;
        releaseString(field);
        info = FUN_002fdf20(meta, field);
        if (info == 0) {
            SET_OUT(0);
            DROP(ShaderNameList, names);
            DROP(ShaderObject, object);
            releaseString(text);
            return 0;
        }
        if (FUN_001c7680(self, section, field, object, info, &flag) == 0) {
            SET_OUT(0);
            DROP(ShaderNameList, names);
            DROP(ShaderObject, object);
            releaseString(text);
            return 0;
        }
    }
    {
        bool initial = !(bool)flag;
        cached = initial;
        FUN_00306e50(self->ini, section, DAT_004e4708, &cached, initial, 0);
    }
    if (cached != 0) {
        cache = FUN_001ca6b0(self, self->kind);
        existing = FUN_00303d70(cache, name);
        if (existing != 0) {
            if (FUN_00300920(existing, object) != 0) {
                SET_OUT(existing);
                DROP(ShaderNameList, names);
                DROP(ShaderObject, object);
                releaseString(text);
                return 0;
            }
            SET_OUT(object);
            DROP(ShaderNameList, names);
            DROP(ShaderObject, object);
            releaseString(text);
            return 0;
        }
        FUN_00303cd0(cache, name, object);
    }
    SET_OUT(object);
    DROP(ShaderNameList, names);
    DROP(ShaderObject, object);
    releaseString(text);
    return 0;
}
