#ifndef DW4_IGWINDOW_H
#define DW4_IGWINDOW_H

#ifdef __cplusplus
#include "dw4/support/reflected.h"
/* Alchemy's window class (igPsx2Window is this build's platform window). */
struct igWindow : public igObject {};
#else
struct igWindow;
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct igWindow *igWindow_CreateInstance(int allocator);

#ifdef __cplusplus
}
#endif

#endif
