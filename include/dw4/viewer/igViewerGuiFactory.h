#ifndef DW4_IGVIEWERGUIFACTORY_H
#define DW4_IGVIEWERGUIFACTORY_H

struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

extern struct igMetaObject *g_igViewerGuiFactory_metaObject;

#ifdef __cplusplus
}

#include "dw4/core/igSmartPointer.h"
#include "dw4/viewer/igViewerSceneInfoManager.h"

struct igViewerGuiFactory;
struct igViewerAction;

/* A new action that calls `function` on `app`. */
extern "C" igSmartPointer<igViewerAction> igViewerGuiFactory_CreateAction(struct igViewerGuiFactory *factory, struct igViewerSceneInfoManager *app, igViewerFunction function);

/* The factory has no widget of this kind: an empty reference. */
extern "C" igSmartPointer<igObject> igViewerGuiFactory_CreateEmpty(struct igViewerGuiFactory *factory, int kind);
#endif

#endif
