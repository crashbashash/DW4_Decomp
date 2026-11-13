#include "dw4/reflected.h"
extern "C" {
void igObject_Destroy(igObject *);
igObject *igStringObj_Create(int);
int FUN_00306e50(...);
int Gap__Core__igObject__vfunc_09(...);
int ObjectList_ResizeRetained(...);
int igObject_GetAllocator(...);
struct G { char p[56]; int f56; };
extern int DAT_004f9680[4];
extern G *DAT_00586dc8[4];
}
static inline void release(igObject *object) {
    if (object != 0) {
        object->_refCount = object->_refCount - 1;
        if ((object->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(object);
        }
    }
}
struct PropertyRef;
static inline void setAt(igDriverDatabase *database, int index, const PropertyRef &value);
struct PropertyRef {
    igObject *p;
    PropertyRef(igObject *object) : p(object) {}
    ~PropertyRef() { release(p); }
};
static inline void setAt(igDriverDatabase *database, int index, const PropertyRef &value) {
    igObject *retained = value.p;
    igObjectList *list = (igObjectList *)database->_currentProperties;
    if (retained != 0) {
        retained->_refCount++;
    }
    release(((igObject **)list->_data)[index]);
    if (list->_count != 0 && index >= 0 && index < list->_count) {
        ((igObject **)list->_data)[index] = retained;
    }
}
extern "C" void Gap__Core__igDriverDatabase__vfunc_11(igDriverDatabase *database) {
    unsigned char verbose;
    int i;
    Gap__Core__igObject__vfunc_09();
    FUN_00306e50(DAT_00586dc8[0]->f56, 2, DAT_004f9680, &verbose, database->_verbose, 1);
    database->_verbose = verbose;
    ObjectList_ResizeRetained(database->_currentProperties, 13);
    ObjectList_ResizeRetained(database->_subPropertyNames, 13);
    ObjectList_ResizeRetained(database->_subPropertyValues, 13);
    i = 0;
    do { {
        PropertyRef property(igStringObj_Create(igObject_GetAllocator(database)));
        setAt(database, i, property);
        } i++;
    } while (i < 13);
}
