struct IniSectionText { int pad0; int _refCount; char *text; };
struct IniNamedObject { int pad0; int _refCount; };
struct IniSourceList { char pad0[20]; void *entries; };
struct IniFieldEntry { char pad0[56]; IniNamedObject *cache; };
struct IniFactoryView { char pad0[20]; int mode; char pad1[32]; IniNamedObject *cache; };
class IniFileHandle {
public:
    virtual void d0();    virtual void d1();    virtual void d2();    virtual void d3();    virtual void d4();    virtual void d5();    virtual void d6();    virtual void d7();    virtual void d8();    virtual void d9();    virtual void d10();    virtual void d11();    virtual void d12();    virtual void d13();    virtual void d14();    virtual void d15();    virtual void d16();    virtual void d17();    virtual void d18();    virtual void d19();    virtual void d20();    virtual void d21();    virtual void d22();
    virtual int open(char *, void *);
    virtual void close();
    virtual void read(char *, int, int);
    virtual void d26();    virtual void d27();    virtual void d28();    virtual void d29();    virtual void d30();    virtual void d31();    virtual void d32();    virtual void d33();    virtual void d34();    virtual void d35();
    virtual void seek(int, int);
    virtual int tell();
    int _refCount;
};
extern "C" {
void *FUN_00309a60(void *, void *, void *, int);
IniFieldEntry *FUN_003022c0(void *, void *, char *);
IniSectionText *FUN_00303d70(IniNamedObject *, char *);
void FUN_00303cd0(IniNamedObject *, char *, IniSectionText *);
void FUN_001ce400(IniSectionText **, char *);
void *igObject_GetAllocator(void *);
IniSectionText *FUN_002b9500(void *);
IniFileHandle *FUN_002c4ca0(void *);
char *FUN_00300d70(IniFactoryView *, int);
void FUN_00300f50(IniFactoryView *, char *);
void FUN_0030b3c0(IniSectionText *, char *);
int igObject_IsKindOf(void *, void *);
void igObject_Destroy(void *);
extern char *DAT_004c22f0[4];
extern void *DAT_00586dd0;
extern int DAT_004fb3a8[4];
extern int DAT_004e1b58[4];
extern void *DAT_00561500[4];
extern void *DAT_005619b0[4];
extern void *DAT_005858f0[4];
extern int DAT_004e47a8[2];
}
#define SLOT(T, x) (*(T **)&(x))
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
        { IniSectionText *a_ = *out; ADD(a_); } \
    } while (0)
extern "C" int FUN_001cdbb0(IniSectionText **out, IniFactoryView *self, char *name) {
    IniSectionText *result;
    IniNamedObject *cache;
    IniSectionText *path;
    IniFileHandle *file;
    int size;
    SLOT(IniSectionText, result) = 0;
    { IniSectionText *a_ = result; ADD(a_); }
    SLOT(IniNamedObject, cache) = 0;
    { IniNamedObject *a_ = cache; ADD(a_); }
    if (name == 0) {
        SET_OUT(0);
        DROP(IniNamedObject, cache);
        DROP(IniSectionText, result);
        return 0;
    }
    if (self->mode != 0) {
        IniNamedObject *held;
        IniSectionText *found;
        if (self->mode == 3) {
            IniSourceList *source = (IniSourceList *)FUN_00309a60(DAT_00586dd0, DAT_004fb3a8, DAT_004e1b58, 0);
            IniFieldEntry *entry;
            if (source == 0 || igObject_IsKindOf(source, DAT_00561500[0]) == 0) {
                SET_OUT(0);
                DROP(IniNamedObject, cache);
                DROP(IniSectionText, result);
                return 0;
            }
            entry = FUN_003022c0(source->entries, DAT_005619b0[0], name);
            if (entry != 0) {
                held = entry->cache;
                ADD(held);
                DROP(IniNamedObject, cache);
                SLOT(IniNamedObject, cache) = held;
            } else {
                held = self->cache;
                ADD(held);
                DROP(IniNamedObject, cache);
                SLOT(IniNamedObject, cache) = held;
            }
        } else {
            held = self->cache;
            ADD(held);
            DROP(IniNamedObject, cache);
            SLOT(IniNamedObject, cache) = held;
        }
        found = FUN_00303d70(cache, name);
        if (found != 0 && igObject_IsKindOf(found, DAT_005858f0[0]) != 0) {
            ADD(found);
            DROP(IniSectionText, result);
            SLOT(IniSectionText, result) = found;
        }
    }
    if (result == 0) {
        FUN_001ce400(&path, name);
        if (path == 0) {
            SET_OUT(0);
            DROP(IniSectionText, path);
            DROP(IniNamedObject, cache);
            DROP(IniSectionText, result);
            return 0;
        }
        {
            void *allocator = igObject_GetAllocator(self);
            char *text;
            char *buffer;
            IniFileHandle *opening;
            DROP(IniSectionText, result);
            SLOT(IniSectionText, result) = FUN_002b9500(allocator);
            SLOT(IniFileHandle, file) = FUN_002c4ca0(igObject_GetAllocator(self));
            text = path->text;
            opening = file;
            text = (text == 0) ? DAT_004c22f0[0] : text;
            if (opening->open(text, DAT_004e47a8) == 0) {
                SET_OUT(0);
                DROP(IniFileHandle, file);
                DROP(IniSectionText, path);
                DROP(IniNamedObject, cache);
                DROP(IniSectionText, result);
                return 0;
            }
            file->seek(0, 2);
            size = file->tell();
            file->seek(0, 0);
            buffer = FUN_00300d70(self, size + 1);
            file->read(buffer, size, 1);
            file->close();
            buffer[size] = 0;
            FUN_0030b3c0(result, buffer);
            FUN_00300f50(self, buffer);
            if (self->mode != 0) {
                FUN_00303cd0(cache, name, result);
            }
            DROP(IniFileHandle, file);
            DROP(IniSectionText, path);
        }
    }
    SET_OUT(result);
    DROP(IniNamedObject, cache);
    DROP(IniSectionText, result);
    return 0;
}
