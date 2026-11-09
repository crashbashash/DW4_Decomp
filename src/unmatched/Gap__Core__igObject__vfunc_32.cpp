#include "dw4/reflected.h"
extern "C" int List_RemoveWordAt(...);
extern "C" int DAT_004fb410[4];
extern "C" int DAT_004fb418[4];
#include "dw4/igTDataList.h"
struct ObjectListOwner { char pad[16]; igTDataList<igObject *> *_list; };
extern "C" int Gap__Core__igObject__vfunc_32(ObjectListOwner *self, igObject *object) {
    if (self->_list != 0) {
        igTDataList<igObject *> *list;
        int index = (list = self->_list)->find(object);
        int result;
        if (index >= 0) {
            List_RemoveWordAt(list, index);
            result = DAT_004fb410[0];
        } else {
            result = DAT_004fb418[0];
        }
        return result == DAT_004fb410[0];
    }
    return 0;
}
