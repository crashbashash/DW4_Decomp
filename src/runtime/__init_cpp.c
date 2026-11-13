/* What the start-up code calls around main for C++: the static initializers before, the registered static objects'
 * destructors after. */

#include "dw4/runtime/exception.h"

void __fini_cpp(void) {
    __destroy_global_chain();
}

void __init_cpp(void) {
    __call_static_initializers(__ctors_start__, __ctors_end__, __exception_table_start__, __exception_table_end__);
}
