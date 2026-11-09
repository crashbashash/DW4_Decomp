#include "dw4/igSmartPointer.h"
#include "dw4/reflected.h"

struct igResult { int value; };
struct ListOwner { char pad[32]; int list; };
extern "C" {
igSmartPointer<igObject> FUN_0013ba30(int, igSmartPointer<igObject>);
int FUN_0013c060();
int FUN_00460be0();
int ObjectList_AppendRetained(int, igObject *);
igResult ObjectList_RemoveFirstRetained(int, int, int);
}
static inline void removeFromList(int list, int object) {
    ObjectList_RemoveFirstRetained(list, object, 0);
}
extern "C" int FUN_00460c80(igObject *object, ListOwner *owner) {
    int found = FUN_00460be0();
    if (found != 0) {
        removeFromList(owner->list, found);
        igSmartPointer<igObject> wrapper = FUN_0013ba30(FUN_0013c060(), igSmartPointer<igObject>(object, kRetainReference));
        ObjectList_AppendRetained(owner->list, wrapper.get());
        return 1;
    }
    return 0;
}
