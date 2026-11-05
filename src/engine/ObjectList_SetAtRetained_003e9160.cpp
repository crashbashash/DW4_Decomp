/* Retain replacement and release the unchecked old slot before the store guard. */
#include "dw4/reflected.h"
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
typedef struct ObjectRefTarget { int word0; int references; } ObjectRefTarget;
void igObject_Destroy(ObjectRefTarget *);
void ObjectList_SetAtRetained_003e9160(igDataList *list, int index, ObjectRefTarget *replacement) {
    ObjectRefTarget *previous;
    if(replacement) ++replacement->references;
    previous=((ObjectRefTarget **)list->_data)[index];
    if(previous) {
        --previous->references;
        if(((unsigned long long)(long long)previous->references & 0x7fffffULL)==0)
            igObject_Destroy(previous);
    }
    if(list->_count && index>=0 && index<list->_count)
        ((ObjectRefTarget **)list->_data)[index]=replacement;
}
} /* extern "C" */
