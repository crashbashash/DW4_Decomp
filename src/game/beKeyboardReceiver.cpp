#include "dw4/beKeyboardReceiver.h"
#include "dw4/igObject.h"

extern "C" void beKeyboardReceiver_userConstruct(struct beKeyboardReceiver *self);
extern "C" void beKeyboardReceiver_userDestruct(struct beKeyboardReceiver *self);
extern "C" int beKeyboardReceiver_OnKeyEvent(void);
extern "C" igMetaObject *beKeyboardReceiver_GetMeta(void);

void beKeyboardReceiver_userConstruct(struct beKeyboardReceiver *self)
{
    Gap__Core__igObject__userConstruct((igObject *)self);
}

void beKeyboardReceiver_userDestruct(struct beKeyboardReceiver *self)
{
    Gap__Core__igObject__userDestruct((igObject *)self);
}

/* Slot 21, empty override returning 0. */
int beKeyboardReceiver_OnKeyEvent(void) {
    return 0;
}

/* Slot 20, GetMetaObject. */
igMetaObject *beKeyboardReceiver_GetMeta(void)
{
    return g_beKeyboardReceiver_metaObject;
}

