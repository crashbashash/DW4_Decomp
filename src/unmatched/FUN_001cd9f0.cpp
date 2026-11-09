struct IniSectionObject { int pad0; int _refCount; char *name; };
struct IniShaderFactoryView;
struct IniTypeTable { char pad0[60]; void *meta; };
struct SectionRef;
extern "C" {
void *igObject_GetAllocator(IniShaderFactoryView *);
IniSectionObject *FUN_002c6750(void *);
void FUN_003006a0(IniSectionObject *, void *);
int FUN_002da710(IniSectionObject *, char *, char *);
void igObject_Destroy(IniSectionObject *);
extern char *DAT_004c22f0[4];
extern IniTypeTable *DAT_00586dc8;
}
struct SectionRef {
    IniSectionObject *p;
    SectionRef(IniSectionObject *object) : p(object) {
        if (p != 0) {
            p->_refCount = p->_refCount + 1;
        }
    }
    SectionRef(const SectionRef &other) : p(other.p) {
        if (p != 0) {
            p->_refCount = p->_refCount + 1;
        }
    }
    ~SectionRef() {
        release();
    }
    void release() {
        IniSectionObject *object = p;
        if (object != 0) {
            object->_refCount = object->_refCount - 1;
            if ((object->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(object);
            }
        }
    }
    IniSectionObject *get() const { return p; }
};
extern "C" SectionRef FUN_001cdbb0(IniShaderFactoryView *, char *);
extern "C" SectionRef FUN_001cd9f0(IniShaderFactoryView *self, char *name) {
    SectionRef result(0);
    SectionRef section = FUN_001cdbb0(self, name);
    if (section.get() != 0) {
        void *allocator = igObject_GetAllocator(self);
        char *text;
        result.release();
        result.p = FUN_002c6750(allocator);
        FUN_003006a0(result.get(), DAT_00586dc8->meta);
        IniSectionObject *created = result.get();
        text = section.get()->name;
        text = (text == 0) ? DAT_004c22f0[0] : text;
        if (FUN_002da710(created, text, name) == 0) {
            result.release();
            result.p = 0;
        }
    }
    return result;
}
