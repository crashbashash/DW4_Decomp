/* The start-up code's C++ entry and exit: the static initializers before main, the registered static objects'
 * destructors after. */
#ifndef DW4_RUNTIME_INIT_CPP_H
#define DW4_RUNTIME_INIT_CPP_H

#ifdef __cplusplus
extern "C" {
#endif

void __init_cpp(void);
void __fini_cpp(void);

#ifdef __cplusplus
}
#endif

#endif
