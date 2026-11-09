#include "dw4/reflected.h"
struct LuaFieldType {
    int type : 8;
    int indirection : 2;
    unsigned int named : 1;
    unsigned int extra : 2;
    unsigned int isTable : 1;
    unsigned int isObject : 1;
    unsigned int spare : 1;
    int accepted : 16;
    igMetaObject *metaObject;
    int tag;
};
class MetaFieldView {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual igMetaObject *getMeta();
};
extern "C" {
void FUN_0023c9a0(LuaFieldType *type, int kind, int indirection, int extra, igMetaObject *meta);
void FUN_0023cb40(LuaFieldType *type);
int FUN_002413f0(int name);
void FUN_002467a0(const char *format, int name);
char *strstr(const char *, const char *);
extern igMetaObject *g_igCharMetaField_metaObject;
extern igMetaObject *g_igUnsignedCharMetaField_metaObject;
extern igMetaObject *g_igIntMetaField_metaObject;
extern igMetaObject *g_igUnsignedIntMetaField_metaObject;
extern igMetaObject *g_igShortMetaField_metaObject;
extern igMetaObject *g_igUnsignedShortMetaField_metaObject;
extern igMetaObject *g_igLongMetaField_metaObject;
extern igMetaObject *g_igUnsignedLongMetaField_metaObject;
extern igMetaObject *g_igEnumMetaField_metaObject;
extern igMetaObject *g_igFloatMetaField_metaObject;
extern igMetaObject *g_igDoubleMetaField_metaObject;
extern igMetaObject *g_igStringMetaField_metaObject;
extern igMetaObject *g_igBoolMetaField_metaObject;
extern igMetaObject *g_igMemoryRefMetaField_metaObject;
extern igMetaObject *g_igObjectRefMetaField_metaObject;
extern char DAT_004ea258[];
extern char DAT_004ea270[];
void FUN_0023d300(LuaFieldType *out, MetaFieldView *field);
}

extern "C" void FUN_0023d300(LuaFieldType *out, MetaFieldView *field) {
    igMetaObject *meta = field->getMeta();
    LuaFieldType result;
    FUN_0023c9a0(&result, 0, 0, 0, 0);
    if (g_igCharMetaField_metaObject == meta) {
        result.type = 1;
    } else if (g_igUnsignedCharMetaField_metaObject == meta) {
        result.type = 2;
    } else if (g_igIntMetaField_metaObject == meta) {
        result.type = 5;
    } else if (g_igUnsignedIntMetaField_metaObject == meta) {
        result.type = 6;
    } else if (g_igShortMetaField_metaObject == meta) {
        result.type = 3;
    } else if (g_igUnsignedShortMetaField_metaObject == meta) {
        result.type = 4;
    } else if (g_igLongMetaField_metaObject == meta) {
        result.type = 7;
    } else if (g_igUnsignedLongMetaField_metaObject == meta) {
        result.type = 8;
    } else if (g_igEnumMetaField_metaObject == meta) {
        result.type = 10;
    } else if (g_igFloatMetaField_metaObject == meta) {
        result.type = 11;
    } else if (g_igDoubleMetaField_metaObject == meta) {
        result.type = 12;
    } else if (g_igStringMetaField_metaObject == meta) {
        result.type = 13;
    } else if (g_igBoolMetaField_metaObject == meta) {
        result.type = 9;
    } else if (g_igMemoryRefMetaField_metaObject == meta) {
        LuaFieldType element;
        FUN_0023d300(&element, (MetaFieldView *)((igMemoryRefMetaField *)field)->_memType);
        result = element;
        result.indirection = 1;
        result.named = 0;
    } else if (g_igObjectRefMetaField_metaObject == meta) {
        result.type = 14;
        result.metaObject = (igMetaObject *)((igObjectRefMetaField *)field)->_metaObject;
        result.indirection = 1;
        if (result.metaObject != 0) {
            result.tag = FUN_002413f0(result.metaObject->_name);
        }
    } else {
        char *suffix = strstr((char *)meta->_name, DAT_004ea258);
        if (suffix != 0) {
            *suffix = 0;
            result.type = 14;
            result.tag = FUN_002413f0(meta->_name);
            result.named = 1;
            *suffix = 'M';
        }
        if (result.tag == 0) {
            FUN_002467a0(DAT_004ea270, meta->_name);
        }
    }
    FUN_0023cb40(&result);
    *out = result;
}
