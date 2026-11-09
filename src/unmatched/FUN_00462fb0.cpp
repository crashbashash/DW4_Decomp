#include "dw4/igSmartPointer.h"
struct Binding : igObject { char p0[68]; igObject *source; igObject *target; igObject *value; };
struct Camera : igObject { char p0[109]; char follow; char p1[18]; igObject *object; };
struct Effect : igObject { };
struct ViewSource { char p[20]; igObject *f20; char q[28]; int f52; };
struct ViewConfig { char p[16]; int *f16; };
struct ViewState : igObject { char p[204]; int f212; int f216; ViewConfig *f220; };
struct ViewSelector { char p0[12]; ViewSource *f12; int pad16; ViewState *f20; char p1[16]; int f40; igObject *f44; int f48; char p2[84]; int f136; };
struct Fetched { igObject *object; };
extern "C" {
Binding *FUN_0045c170(int);
Camera *FUN_0045c5a0(int);
Camera *FUN_0045c8e0(int);
Effect *FUN_0045cc40(int);
Fetched FUN_0045eda0(int, int);
int FUN_00463fd0(int, igObject *);
int FUN_00465260(Effect *, int);
void FUN_00462fb0(ViewSelector *self);
}

struct Tag { };
static inline Binding *create45c170() {
    Tag tag = Tag();
    return FUN_0045c170(0);
}
static inline Camera *create45c8e0() {
    Tag tag = Tag();
    return FUN_0045c8e0(0);
}
static inline Camera *create45c5a0() {
    Tag tag = Tag();
    return FUN_0045c5a0(0);
}
static inline Effect *create45cc40() {
    Tag tag = Tag();
    return FUN_0045cc40(0);
}
static inline void takeValue(const igSmartPointer<Binding> &ref, const Fetched &fetched) {
    igObject *value = fetched.object;
    Binding *owner = ref.p;
    igObject *previous;
    if (value != 0) {
        value->_refCount = value->_refCount + 1;
    }
    previous = owner->value;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    owner->value = value;
    if (fetched.object != 0) {
        fetched.object->_refCount = fetched.object->_refCount - 1;
        if ((fetched.object->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(fetched.object);
        }
    }
}
static inline void setSource(const igSmartPointer<Binding> &ref, igObject *value) {
    Binding *owner = ref.p;
    igObject *previous;
    if (value != 0) {
        value->_refCount = value->_refCount + 1;
    }
    previous = owner->source;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    owner->source = value;
}
static inline void setTarget(const igSmartPointer<Binding> &ref, igObject *value) {
    Binding *owner = ref.p;
    igObject *previous;
    if (value != 0) {
        value->_refCount = value->_refCount + 1;
    }
    previous = owner->target;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    owner->target = value;
}
static inline void setObject(const igSmartPointer<Camera> &ref, igObject *value) {
    Camera *owner = ref.p;
    igObject *previous;
    if (value != 0) {
        value->_refCount = value->_refCount + 1;
    }
    previous = owner->object;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    owner->object = value;
}
extern "C" void FUN_00462fb0(ViewSelector *self) {
    ViewState *s = self->f20;
    int mode = s->f212;
    switch (mode) {
    case 0: {
        igSmartPointer<Binding> binding(create45c170());
        takeValue(binding, FUN_0045eda0(self->f48, 1));
        setSource(binding, self->f20);
        setTarget(binding, self->f44);
        FUN_00463fd0(self->f136, binding.p);
        break;
    }
    case 2: {
        igSmartPointer<Camera> camera(create45c8e0());
        setObject(camera, self->f12->f20);
        FUN_00463fd0(self->f136, camera.p);
        break;
    }
    case 1: {
        igSmartPointer<Camera> camera(create45c5a0());
        FUN_00463fd0(self->f136, camera.p);
        break;
    }
    case 3: {
        igSmartPointer<Camera> camera(create45c5a0());
        camera.p->follow = 1;
        FUN_00463fd0(self->f136, camera.p);
        break;
    }
    default: {
        int first = s->f216;
        if (mode >= first) {
                first = mode - first;
            igSmartPointer<Effect> effect(create45cc40());
            FUN_00465260(effect.p, self->f20->f220->f16[first]);
            FUN_00463fd0(self->f136, effect.p);
            self->f40 = self->f12->f52 + 1;
        }
        break;
    }
    }
}
