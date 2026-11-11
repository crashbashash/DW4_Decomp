#include "dw4/reflected.h"

/* The object system: only the metadata registry (a pointer list of every registered igMetaObject,
 * +24) is used. */
typedef struct ObjectSystemRecord {
    char unknown0[24];
    int metaRegistry;
} ObjectSystemRecord;

void MetaRefList_AppendRetained(void *,void *);

/* Register a metaobject in the object system's registry, retaining it. */
void igObjectSystem_AppendMetaObject(void *system,igMetaObject *meta){
    MetaRefList_AppendRetained((void *)((ObjectSystemRecord *)system)->metaRegistry,meta);
}
