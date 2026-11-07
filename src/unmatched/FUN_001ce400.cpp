#include "dw4/igobject_release.h"
struct IniStringObject { int pad0; int _refCount; char *text; };
class IniStringRef {
public:
    IniStringObject *p;
    IniStringRef() {}
    IniStringRef(const IniStringRef &o);
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
extern "C" int FUN_001ce400(IniStringObject **out, char *path) {
    IniFileObject *volatile file;
    IniStringObject *volatile result;
    IniPathResolver *resolver = DAT_00562788[0];
    if (resolver == 0) {
        *out = 0;
        {
            IniStringObject *o = *out;
            if (o != 0) {
                o->_refCount = o->_refCount + 1;
            }
        }
        return;
    } else {
        void *allocator;
        int opened;
        char *text;
        allocator = GPR_00554c14 != 0 ? Memory_GetAllocatorBySelector(DAT_00587028[0]) : Memory_GetAllocatorBySelector(DAT_00587060[0]);
        {
            IniFileObject *created = FUN_002c4ca0(allocator);
            IniStringObject *o;
            result = 0;
            o = result;
            file = created;
            if (o != 0) {
                o->_refCount = o->_refCount + 1;
            }
        }
        {
            IniStringRef name = resolver->resolve(path);
            IniFileObject *f;
            text = name.p->text;
            f = file;
            text = (text == 0) ? DAT_004c22f0[0] : text;
            opened = f->open(text, DAT_004e47b0);
            IG_OBJECT_RELEASE(name.p);
        }
        if (opened != 0) {
            void *stringAllocator = Memory_GetAllocatorBySelector(DAT_00587048[0]);
            {
                IniStringObject *o = result;
                if (o != 0) {
                    o->_refCount = o->_refCount - 1;
                    if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(o);
                    }
                }
            }
            result = FUN_002b9500(stringAllocator);
            {
                int handle = file->handle;
                FUN_0030b3c0(result, handle);
            }
            file->close();
        }
        *out = result;
        {
            IniStringObject *o = *out;
            if (o != 0) {
                o->_refCount = o->_refCount + 1;
            }
        }
        {
            IniStringObject *o = result;
            if (o != 0) {
                o->_refCount = o->_refCount - 1;
                if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(o);
                }
            }
        }
        {
            IniFileObject *o = file;
            if (o != 0) {
                o->_refCount = o->_refCount - 1;
                if (((unsigned long long)((long long)(int)o->_refCount << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(o);
                }
            }
        }
        return 0;
    }
}
