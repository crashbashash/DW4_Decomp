#include "dw4/reflected.h"
extern "C" {
void igObject_Destroy(igObject *);
igObject *FUN_002b9500(int);
int FUN_00306e50(...);
int Gap__Core__igObject__vfunc_09(...);
int ObjectList_ResizeRetained(...);
int igObject_GetAllocator(...);
/* the object-system global (0x586dc8) has no reflected class; +56 stays a local layout */
struct G { char p[56]; int f56; };
extern int DAT_004f9680[4];
extern G *DAT_00586dc8[4];
}
struct Rel { static inline void go(igObject *object) {
    if (object) {
        --object->_refCount;
        if (((unsigned long long)(long long)object->_refCount & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
extern "C" void Gap__Core__igDriverDatabase__vfunc_11(igDriverDatabase *arg0);
void Gap__Core__igDriverDatabase__vfunc_11(igDriverDatabase *arg0) {
    unsigned char sp6F;
    igObject * volatile sp68;
    int i;
    igObject *s2;
    igObjectList *s1;
    Gap__Core__igObject__vfunc_09();
    FUN_00306e50(DAT_00586dc8[0]->f56, 2, DAT_004f9680, &sp6F, arg0->_verbose, 1);
    arg0->_verbose = sp6F;
    ObjectList_ResizeRetained(arg0->_currentProperties, 13);
    ObjectList_ResizeRetained(arg0->_subPropertyNames, 13);
    ObjectList_ResizeRetained(arg0->_subPropertyValues, 13);
    i = 0;
    do {
        sp68 = FUN_002b9500(igObject_GetAllocator(arg0));
        s2 = sp68;
        s1 = (igObjectList *)arg0->_currentProperties;
        if (s2 != 0) {
            s2->_refCount++;
        }
        Rel::go(((igObject **)s1->_data)[i]);
        if (s1->_count != 0 && i >= 0 && i < s1->_count) {
            ((igObject **)s1->_data)[i] = s2;
        }
        { igObject *t = sp68; Rel::go(t); }
        i++;
    } while (i < 13);
}
