#include "dw4/igSmartPointer.h"
struct RenderDestinationDesc {
    int kind;
    int width;
    int height;
    int bpp;
    int alpha;
    int bppDepth;
    float clearDepth;
    float scale;
};
struct VisualResult { int value; };
class VisualContext {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual VisualResult beginWindow();
    virtual void d31();
    virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43();
    virtual int createRenderDestination(RenderDestinationDesc *desc);
    virtual void d45(); virtual void d46(); virtual void d47();
    virtual int currentRenderDestination();
    virtual void d49(); virtual void d50();
    virtual void getRenderDestinationSize(int handle, int *width, int *height);
    unsigned int _refCount;
};
extern "C" {
void *FUN_002eb010(int size);
void *StringPool_Construct(void *pool);
const char *StringPool_Intern(void *pool, const char *text);
void StringChunk_ReleaseHeader(int chunk, int *header);
int igObject_GetAllocator(void *object);
VisualContext *FUN_0014a000(int allocator);
int printf(const char *, ...);
extern void *DAT_00586f20[4];
extern char DAT_004d7070[];
extern char DAT_004d7080[];
int Gap__igPsx2Window__vfunc_24(igPsx2Window *self, const char *name, int width, int height);
}

static inline void setWindowName(igPsx2Window *self, const char *name) {
    if (DAT_00586f20[0] == 0) {
        void *pool = FUN_002eb010(16);
        if (pool != 0) pool = StringPool_Construct(pool);
        DAT_00586f20[0] = pool;
    }
    const char *interned = StringPool_Intern(DAT_00586f20[0], name);
    int *old = (int *)self->_winName;
    if (old != 0) {
        int *header = old - 2;
        int refs = old[-1] - 1;
        old[-1] = refs;
        if (refs == 0) StringChunk_ReleaseHeader(*header, header);
    }
    self->_winName = (int)interned;
}

int Gap__igPsx2Window__vfunc_24(igPsx2Window *self, const char *name, int width, int height) {
    if (name == 0) {
        setWindowName(self, DAT_004d7070);
    } else {
        setWindowName(self, name);
    }
    self->_width = width;
    self->_height = height;
    if (self->_vc != 0) {
        self->_renderDestinationHandle = ((VisualContext *)self->_vc)->currentRenderDestination();
        if (self->_renderDestinationHandle == -1) {
            RenderDestinationDesc desc;
            desc.kind = 1;
            desc.width = width;
            desc.height = height;
            desc.bpp = self->_bpp;
            desc.alpha = self->_alpha;
            desc.bppDepth = self->_bppDepth;
            desc.clearDepth = 0.0f;
            desc.scale = 1.0f;
            self->_renderDestinationHandle = ((VisualContext *)self->_vc)->createRenderDestination(&desc);
        }
        int w;
        int h;
        ((VisualContext *)self->_vc)->getRenderDestinationSize(self->_renderDestinationHandle, &w, &h);
        self->_width = w;
        self->_height = h;
    } else {
        VisualContext *created = FUN_0014a000(igObject_GetAllocator(self));
        if (created != 0) created->_refCount = created->_refCount + 1;
        igRelease((igObject *)self->_vc);
        self->_vc = (int)created;
        VisualContext *vc = (VisualContext *)self->_vc;
        if (vc == 0) {
            printf(DAT_004d7080);
            return 0;
        }
        vc->_refCount = vc->_refCount - 1;
        if ((vc->_refCount & 0x7FFFFF) == 0) igObject_Destroy(vc);
        RenderDestinationDesc desc;
        desc.kind = 1;
        desc.width = width;
        desc.height = height;
        desc.bpp = self->_bpp;
        desc.alpha = self->_alpha;
        desc.bppDepth = self->_bppDepth;
        desc.clearDepth = 0.0f;
        desc.scale = 1.0f;
        self->_renderDestinationHandle = ((VisualContext *)self->_vc)->createRenderDestination(&desc);
    }
    ((VisualContext *)self->_vc)->beginWindow();
    self->_open = 1;
    return 1;
}
