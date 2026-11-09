#include "dw4/igSmartPointer.h"

extern "C" {
struct Image : public igObject { char p[80]; int name; };
struct TextureAttr { char p[16]; int bColor; int magFilter; int minFilter; int wrapS; int wrapT; char p2[4]; int mipmapMode; int source; char p3[4]; unsigned char paging; };
int sprintf(...);
int strcpy(int a, char *b);
int strlen(char *s);
int *FUN_001405a0(int a);
Image *FUN_00140c00(TextureAttr *a, int b);
extern int DAT_004d5df8[4];
extern int DAT_004d5e10[4];
extern int DAT_00587020[4];
}
class Allocator { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual int allocate(int n); };
extern "C" Allocator *Memory_GetAllocatorBySelector(int s);
static inline void retain(Image *o) { if (o != 0) { o->_refCount = o->_refCount + 1; } }

static inline unsigned magFilter(const TextureAttr *a) { return a->magFilter; }
static inline unsigned minFilter(const TextureAttr *a) { return a->minFilter; }
static inline unsigned wrapS(const TextureAttr *a) { return a->wrapS; }
static inline unsigned wrapT(const TextureAttr *a) { return a->wrapT; }
extern "C" int Gap__Attrs__igTextureAttr__vfunc_37(TextureAttr *attr, int unused, Allocator *allocator) {
    char text[8204];
    if (allocator == 0) {
        allocator = Memory_GetAllocatorBySelector(DAT_00587020[0]);
    }
    igSmartPointer<Image> image(FUN_00140c00(attr, 0), kRetainReference);
    int *name = &DAT_004d5df8[0];
    if (image.p != 0) {
        if (image.p->name != 0) {
            name = FUN_001405a0(image.p->name);
        }
    }
    sprintf(text, &DAT_004d5e10[0], name, attr->bColor, magFilter(attr), minFilter(attr), wrapS(attr), wrapT(attr), (long long)attr->mipmapMode, (long long)attr->source, (long long)attr->paging);
    int copy = allocator->allocate(strlen(text) + 1);
    strcpy(copy, text);
    return copy;
}
