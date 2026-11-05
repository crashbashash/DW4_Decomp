/* src/game/beMessengerResults.cpp — the complete messenger result/accessor block
 *
 * One translation unit: 2 functions, in retail address order.  Folded
 * from the per-function units by tools/merge_units.py; the matching build
 * splits a function back out with tools/units.py, so `make check` still
 * verifies one function at a time. */
#include "dw4/reflected.h"
extern "C" void Matrix44_Copy(void *, void *);
extern "C" void ObjectList_AppendRetained(int, int);

/* 0x0038f630 */
extern "C" void beMessenger_GetMatrix(void *out, beMessenger *self, int index)
{
    Matrix44_Copy(out, (void *)(((igMatrix44fList *)((beMessengerArgData *)self->_argData)->_matrix44fList)->_data + index * 64));
}

/* 0x0038f670 */
extern "C" void beMessenger_AppendObject(beMessenger *self, int object)
{
    ObjectList_AppendRetained(((beMessengerArgData *)self->_argData)->_objectList, object);
}
