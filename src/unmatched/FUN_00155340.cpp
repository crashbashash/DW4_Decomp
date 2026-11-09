#include "dw4/igSmartPointer.h"

class FieldTypeSource {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int getMetaObject();
};

struct FieldTypeEntry : igObject {
    char pad8[8];
    FieldTypeSource *source;
};

struct FieldTypeList {
    int _pad0[2];
    int _count;
    int _capacity;
    FieldTypeEntry **_data;
};

struct FieldTypeTable {
    char pad0[308];
    FieldTypeList *extraTypes;
};

extern "C" {
extern int g_igVec4fMetaField_metaObject;
extern int g_igMatrix44fMetaField_metaObject;
int FUN_00155340(FieldTypeTable *table, unsigned int type);
}

int FUN_00155340(FieldTypeTable *table, unsigned int type) {
    FieldTypeList *list;

    if (type < 47) {
        switch (type) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
        case 30:
        case 31:
        case 32:
        case 33:
        case 34:
        case 35:
        case 36:
        case 37:
        case 38:
        case 39:
            return g_igVec4fMetaField_metaObject;
        case 40:
        case 41:
        case 42:
        case 43:
        case 44:
        case 45:
        case 46:
            return g_igMatrix44fMetaField_metaObject;
        default:
            return 0;
        }
    }
    list = table->extraTypes;
    if ((int)type < list->_count + 47) {
        int index = type - 47;
        igSmartPointer<FieldTypeEntry> entry(list->_data[index], kRetainReference);
        if (entry == 0) {
            return 0;
        }
        return entry->source->getMetaObject();
    }
    return 0;
}
