#include "dw4/igobject_release.h"
extern "C" void igObject_Destroy(void *);
struct IniStringObject { int pad0; int _refCount; char *text; };
static inline void drop(IniStringObject *object) {
    if (object != 0) {
        object->_refCount = object->_refCount - 1;
        if ((object->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(object);
        }
    }
}
class IniStringRef {
public:
    IniStringObject *p;
    IniStringRef() {}
    IniStringRef(const IniStringRef &o);
    ~IniStringRef() { drop(p); }
};
class IniPathResolver {
public:
    virtual void d0();    virtual void d1();    virtual void d2();    virtual void d3();    virtual void d4();    virtual void d5();    virtual void d6();    virtual void d7();    virtual void d8();    virtual void d9();    virtual void d10();    virtual void d11();    virtual void d12();    virtual void d13();    virtual void d14();    virtual void d15();    virtual void d16();    virtual void d17();    virtual void d18();    virtual void d19();    virtual void d20();
    virtual IniStringRef resolve(char *);
};
class IniFileObject {
public:
    virtual void d0();    virtual void d1();    virtual void d2();    virtual void d3();    virtual void d4();    virtual void d5();    virtual void d6();    virtual void d7();    virtual void d8();    virtual void d9();    virtual void d10();    virtual void d11();    virtual void d12();    virtual void d13();    virtual void d14();    virtual void d15();    virtual void d16();    virtual void d17();    virtual void d18();    virtual void d19();    virtual void d20();    virtual void d21();    virtual void d22();
    virtual int open(char *, void *);
    virtual void close();
    int _refCount;
    char pad0[4];
    int handle;
};
extern "C" {
IniFileObject *FUN_002c4ca0(void *);
IniStringObject *FUN_002b9500(void *);
void FUN_0030b3c0(IniStringObject *, int);
void *Memory_GetAllocatorBySelector(int);
void igObject_Destroy(void *);
extern char *DAT_004c22f0[4];
extern int DAT_004e47b0[4];
extern IniPathResolver *DAT_00562788[4];
extern int DAT_00587028[4];
extern int DAT_00587048[4];
extern int DAT_00587060[4];
extern unsigned char GPR_00554c14;
}
struct FileRef {
    IniFileObject *p;
    FileRef(IniFileObject *object) : p(object) {}
    ~FileRef() {
        IniFileObject *object = p;
        if (object != 0) {
            object->_refCount = object->_refCount - 1;
            if ((object->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(object);
            }
        }
    }
    IniFileObject *operator->() const { return p; }
};
static inline void retain(IniStringObject *object) {
    if (object != 0) {
        object->_refCount = object->_refCount + 1;
    }
}
static inline void release(IniStringObject *object) {
    if (object != 0) {
        object->_refCount = object->_refCount - 1;
        if ((object->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(object);
        }
    }
}
struct StringObjectRef {
    IniStringObject *p;
    StringObjectRef(IniStringObject *object) : p(object) { retain(p); }
    ~StringObjectRef() { release(p); }
};
extern "C" int FUN_001ce400(IniStringObject **out, char *path) {
    IniPathResolver *resolver = DAT_00562788[0];
    if (resolver == 0) {
        *out = 0;
        retain(*out);
        return;
    }
    void *allocator = GPR_00554c14 != 0 ? Memory_GetAllocatorBySelector(DAT_00587028[0]) : Memory_GetAllocatorBySelector(DAT_00587060[0]);
    FileRef file(FUN_002c4ca0(allocator));
    StringObjectRef result(0);
    int opened;
    {
        IniStringRef name = resolver->resolve(path);
        char *text = name.p->text;
        IniFileObject *opener = file.p;
        text = (text == 0) ? DAT_004c22f0[0] : text;
        opened = opener->open(text, DAT_004e47b0);
    }
    if (opened != 0) {
        void *stringAllocator = Memory_GetAllocatorBySelector(DAT_00587048[0]);
        release(result.p);
        result.p = FUN_002b9500(stringAllocator);
        FUN_0030b3c0(result.p, file->handle);
        file->close();
    }
    *out = result.p;
    retain(*out);
    return 0;
}
