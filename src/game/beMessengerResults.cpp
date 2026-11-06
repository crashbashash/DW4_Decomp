#include "dw4/reflected.h"
extern "C" void Matrix44_Copy(void *, void *);
extern "C" void ObjectList_AppendRetained(int, int);

extern "C" void beMessenger_GetMatrix(void *out, beMessenger *self, int index)
{
    Matrix44_Copy(out, (void *)(((igMatrix44fList *)((beMessengerArgData *)self->_argData)->_matrix44fList)->_data + index * 64));
}

extern "C" void beMessenger_AppendObject(beMessenger *self, int object)
{
    ObjectList_AppendRetained(((beMessengerArgData *)self->_argData)->_objectList, object);
}
