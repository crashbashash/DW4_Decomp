/* Looks a field descriptor up by name. The metadata object's _metaFields list is searched by
 * igMetaField::_fieldName (+12). */
#include "dw4/reflected.h"
void *ObjectPointerList_FindByStringField(void *list, igMetaField *stringMember, const char *name);
/* The reflected handle of igMetaField::_fieldName (the string-member selector). */
extern igMetaField *g_fieldNameMember[4];
void *igMetaObject_FindFieldByName(igMetaObject *meta, const char *name) {
    return ObjectPointerList_FindByStringField((void *)meta->_metaFields, g_fieldNameMember[0], name);
}
