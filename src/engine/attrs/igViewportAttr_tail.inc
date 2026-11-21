namespace Gap {
namespace Attrs {

void igViewportAttr::apply(igVisualContext *vc)
{
    igPsx2VisualContext_SetViewport((igPsx2VisualContext *)vc, _x, _y, _w, _h, _nearZ, _farZ);
}

void igViewportAttr::synchronizeDefault(igVisualContext *vc)
{
    int x;
    int y;
    int w;
    int h;
    float nearZ;
    float farZ;

    ((igVisualContextDispatchView *)vc)->getViewport(x, y, w, h, nearZ, farZ);
    _x = x;
    _y = y;
    _w = w;
    _h = h;
    _nearZ = nearZ;
    _farZ = farZ;
}
}
}

/* igAttr seen through its vptr: slot 25 sets the unit (stage) the attribute applies to, slot 26
 * reads the attribute's current state back from a visual context. */
class igAttrStateView : public igVirtualObject {
public:
    virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22();
    virtual void setUnitID(short unitID);
    virtual void getFromContext(igObject *context);
};

#include "dw4/core/igMetaObject.h"

/* The object when it is an igAttr, otherwise none. */
static inline igObject *asAttr(igObject *object) {
    if (object != 0 && ((Gap::Core::igObject *)object)->isOfType((igMetaObject *)Gap::Attrs::igAttr::getClassMeta()) != 0) {
        return object;
    }
    return 0;
}

/* createDefault: instantiate `meta`, and when it is an igAttr seed it from the managed context. */
extern "C" igObjectPointer Gap__Attrs__igVisualContextAttrDefaultManager__createDefault(
    igVisualContextAttrDefaultManager *self, igMetaObject *meta, int unitID) {
    if (meta == 0 || self->_visualContext == 0) {
        return igObjectPointer(0, kRetainReference);
    }
    igObjectPointer created = igMetaObject_CreateInstanceRef(meta, ((Gap::Core::igObject *)self)->getMemoryPool());
    igObject *object = asAttr(created.get());
    igObjectPointer attr(object, kRetainReference);
    if (attr != 0) {
        ((igAttrStateView *)attr.get())->setUnitID(unitID);
        ((igAttrStateView *)attr.get())->getFromContext((igObject *)self->_visualContext);
    }
    return attr;
}

