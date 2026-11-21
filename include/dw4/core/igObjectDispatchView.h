/* reflected.h first, outside the guard: its converted classes can include this header back (through
 * igSmartPointer.h) and must then find the view declared. */
#include "dw4/support/reflected.h"
#ifndef DW4_IGOBJECTDISPATCHVIEW_H
#define DW4_IGOBJECTDISPATCHVIEW_H
#include "dw4/core/igObject.h"

/* igObject's virtual functions: slot n sits at vtable byte offset 8 + 4 * n (the first two words
 * are the class header). The reflected igObject is the same object seen as data. The slots carry
 * the igObject symbol names (Gap::Core::igObject::<name>, igObject_<Name>). Slot 17 takes the
 * value the meta-object's write proxy returns.
 * A class whose virtual functions are called is seen through `<Class>DispatchView`, derived from
 * its base class's view: `dN` holds slot N's place, and a called slot carries the method name of
 * its implementation's symbol, or where that symbol has none a name for what its body does, spelled
 * as the engine's own views spell it; `vfunc_N` (the symbol's number) while neither is known.
 * ABI view only: never instantiated. */
class igObjectDispatchView {
public:
    virtual void Destruct();
    virtual void constructFields(int flag);
    virtual void destructFields();
    virtual void userDeepCopy(igObjectDispatchView *source); virtual void userShallowCopy(int source);
    virtual int userIsAlikeDeep(igObjectDispatchView *other);
    virtual int userIsAlikeShallow(igObjectDispatchView *other);
    virtual void userConstruct(int flag);
    virtual void userDestruct();
    virtual void InitDefaults(); virtual void ReleaseDefaults();
    virtual void resetFields(int flag);
    virtual void userPreWrite(); virtual void userWriteFilePreProcess(); virtual void userPostRead();
    virtual void userPostLoad(); virtual void TrimCapacity(); virtual void userApplyWriteProxy(int value); virtual void userMakeConcrete(igMetaObject *meta);
    virtual igObject *CloneViaMetadata(int copyMode);
    virtual igMetaObject *GetMeta();
    unsigned int _refCount;
    /* the kit's static ref/release, forwarding to Gap::Core::igObject's members as the flat igObject's do */
    static inline void release(igObjectDispatchView *obj) { if (obj != 0) ((const Gap::Core::igObject *)obj)->release(); }
    static inline void ref(igObjectDispatchView *obj) { if (obj != 0) ((const Gap::Core::igObject *)obj)->ref(); }
};

static inline void igObject_Destroy(igObjectDispatchView *object) { igObject_Destroy((igObject *)object); }
#endif
