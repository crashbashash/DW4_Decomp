#ifndef DW4_IGRESOURCE_H
#define DW4_IGRESOURCE_H

#include "dw4/igSmartPointer.h"
struct igObject;
struct igResourceView;

extern "C" {
extern struct igResourceView *g_globalContext;
igSmartPointer<struct igObject> igResource_GetDirectory(void *directory, const char *name);
}

#endif
