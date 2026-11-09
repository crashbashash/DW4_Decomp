#include "dw4/reflected.h"
#include "dw4/igTDataList.h"
typedef igTDataList<igObject *> FieldList;
extern "C" {
igObject *igProperty_FindByName(FieldList *, int, int);
extern int DAT_00585be0[4];
}
struct FieldTable { char pad[8]; FieldList *fields; };
extern "C" int FUN_00303dc0(FieldTable *table, int name) {
    igObject *field = igProperty_FindByName(table->fields, DAT_00585be0[0], name);
    if (field == 0) {
        return -1;
    }
    FieldList *fields = table->fields;
    return fields->find(field);
}
