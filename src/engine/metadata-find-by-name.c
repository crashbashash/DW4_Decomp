/* 0x002fdf20 - igMetaObject_FindFieldByName: look a field descriptor up by name.
 * The metadata object's _metaFields list is searched by the string member that
 * global descriptor 0x585cd8 names, igMetaField::_fieldName (+12); see
 * docs/engine/metadata-callback-services.md (finding #885). */
#include "dw4/reflected.h"
void *ObjectPointerList_FindByStringField(void *list, igMetaField *stringMember, const char *name);
/* The reflected handle of igMetaField::_fieldName (the string-member selector). */
extern igMetaField *g_fieldNameMember_00585cd8[4];
void *igMetaObject_FindFieldByName(igMetaObject *meta, const char *name) {
    return ObjectPointerList_FindByStringField((void *)meta->_metaFields, g_fieldNameMember_00585cd8[0], name);
}
