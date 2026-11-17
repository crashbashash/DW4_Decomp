#ifndef DW4_IGVIEWERGUIFACTORY_H
#define DW4_IGVIEWERGUIFACTORY_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igViewerGuiFactory_metaObject;

#ifdef __cplusplus
}

#include "dw4/igSmartPointer.h"

struct igViewerGuiFactory;

/* The factory has no widget of this kind: an empty reference. */
extern "C" igSmartPointer<igObject> igViewerGuiFactory_CreateEmpty(struct igViewerGuiFactory *factory, int kind);
#endif

#endif
