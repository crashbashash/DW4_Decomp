struct IniSectionObject { int pad0; int _refCount; char *name; };
struct IniShaderFactoryView;
struct IniTypeTable { char pad0[60]; void *meta; };
extern "C" {
void FUN_001cdbb0(IniSectionObject **, IniShaderFactoryView *, char *);
void *igObject_GetAllocator(IniShaderFactoryView *);
IniSectionObject *FUN_002c6750(void *);
void FUN_003006a0(IniSectionObject *, void *);
int FUN_002da710(IniSectionObject *, char *, char *);
void igObject_Destroy(void *);
extern char *DAT_004c22f0[4];
extern IniTypeTable *DAT_00586dc8;
}
#define REF_ADD(x) do { IniSectionObject *a_ = (x); if (a_ != 0) { a_->_refCount = a_->_refCount + 1; } } while (0)
#define REF_DROP(x) do { IniSectionObject *o = (x); if (o != 0) { o->_refCount = o->_refCount - 1; if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(o); } } } while (0)
extern "C" int FUN_001cd9f0(IniSectionObject **out, IniShaderFactoryView *self, char *name) {
    IniSectionObject *volatile result;
    IniSectionObject *section;
    result = 0;
    REF_ADD(result);
    FUN_001cdbb0(&section, self, name);
    if (section != 0) {
        void *allocator = igObject_GetAllocator(self);
        char *text;
        REF_DROP(result);
        result = FUN_002c6750(allocator);
        FUN_003006a0(result, DAT_00586dc8->meta);
        IniSectionObject *created = result;
        text = section->name;
        text = (text == 0) ? DAT_004c22f0[0] : text;
        if (FUN_002da710(created, text, name) == 0) {
            REF_DROP(result);
            result = 0;
        }
    }
    *out = result;
    REF_ADD(*out);
    REF_DROP(section);
    REF_DROP(result);
    return 0;
}
