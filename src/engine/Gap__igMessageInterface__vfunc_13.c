/* IgMessageInterface slot 13: run the base-class hook (Gap::Core::igObject::vfunc_11, a bare
 * return), then point _messageInterface at the object itself: the message interface is its own
 * message-interface member. */
#include "dw4/reflected.h"
int Gap__Core__igObject__vfunc_11();

void Gap__igMessageInterface__vfunc_13(igMessageInterface *self) {
    Gap__Core__igObject__vfunc_11();
    self->_messageInterface = (int)(self);
}
