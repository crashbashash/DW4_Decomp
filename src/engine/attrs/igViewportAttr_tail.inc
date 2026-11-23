namespace Gap {
namespace Attrs {

void igViewportAttr::apply(igVisualContext *vc)
{
    ((igPsx2VisualContext *)vc)->igPsx2VisualContext::setViewport(_x, _y, _w, _h, _nearZ, _farZ);
}

void igViewportAttr::synchronizeDefault(igVisualContext *vc)
{
    int x;
    int y;
    int w;
    int h;
    float nearZ;
    float farZ;

    vc->getViewport(x, y, w, h, nearZ, farZ);
    _x = x;
    _y = y;
    _w = w;
    _h = h;
    _nearZ = nearZ;
    _farZ = farZ;
}
}
}

#include "dw4/core/igMetaObject.h"

/* The object when it is an igAttr, otherwise none. */
static inline igObject *asAttr(igObject *object) {
    if (object != 0 && ((Gap::Core::igObject *)object)->isOfType((igMetaObject *)Gap::Attrs::igAttr::getClassMeta()) != 0) {
        return object;
    }
    return 0;
}

namespace Gap {
namespace Attrs {

/* createDefault: instantiate `meta`, and when it is an igAttr seed it from the managed context. */
igSmartPointer<igAttr> igVisualContextAttrDefaultManager::createDefaultAttr(igMetaObject *meta, int unitID) const
{
    if (meta == 0 || _visualContext == 0) {
        return igSmartPointer<igAttr>(0, kRetainReference);
    }
    igObjectPointer created = igMetaObject_CreateInstanceRef(meta, getMemoryPool());
    igSmartPointer<igAttr> attr((igAttr *)asAttr(created.get()), kRetainReference);
    if (attr != 0) {
        ((igAttr *)attr.get())->setUnitID(unitID);
        ((igAttr *)attr.get())->synchronizeDefault((igVisualContext *)_visualContext);
    }
    return attr;
}
}
}

