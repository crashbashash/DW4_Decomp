/* 0x002d3070 — look a registered metaobject up by class name.  The object
 * system's metadata registry (the pointer list at +24) is searched on the
 * `_name` field of igMetaObject; an inactive object system (flag byte at +0
 * clear) finds nothing.  See docs/engine/allocator-builder.md, "Metadata
 * selection and backing policies". */
#include "dw4/reflected.h"

/* The object system behind g_objectSystem: only the activity flag
 * and the metadata registry are used here. */
typedef struct ObjectSystemView {
    unsigned char active;
    char unknown1[23];
    void *metaRegistry;
} ObjectSystemView;

void *ObjectPointerList_FindByStringField(void *list, igMetaField *selector, const char *name);
/* Field descriptor of igMetaObject::_name (+28): the selector for the search. */
extern igMetaField *g_igMetaObjectNameField[4];

int igObjectSystem_FindMetaByName(ObjectSystemView *objectSystem, const char *className) {
    if (objectSystem->active != 0) {
        return (int)ObjectPointerList_FindByStringField(objectSystem->metaRegistry, g_igMetaObjectNameField[0], className);
    }
    return 0;
}
