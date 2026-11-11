/* Interned strings are reference counted in place: the count sits at (string - 4) and the owning
 * StringChunk header at (string - 8); dropping the last reference hands the header back with
 * StringChunk_ReleaseHeader. */
#include "dw4/reflected.h"
void MetaRefList_AppendRetained(void *, void *);
int StringPool_Construct();
void *StringPool_Intern();
int FUN_002eb010();
void igMetaField_EnsureDefaultStorage(igMetaField *);
int StringChunk_ReleaseHeader();
void igMetaField_SetFieldName(igMetaField *, void **);
extern int g_stringPool[4];
int memcpy(int, int, unsigned short);
void igMetaObject_AppendField(igMetaObject *meta, igMetaField *field)
{
    MetaRefList_AppendRetained((void *)meta->_metaFields, field);
}
