/* ViewerInlineCopies.h - the Viewer library's out-of-line copies of shared inlines
 * (src/engine/ViewerInlineCopies.cpp). */
#ifndef DW4_VIEWERINLINECOPIES_H
#define DW4_VIEWERINLINECOPIES_H

#include "dw4/core/igSmartPointer.h"

struct igInfoManager;

extern "C" {
igSmartPointer<igObject> *igSmartPointer_igViewerGuiFactory_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igRadioGroup_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igViewerSceneInfoManager_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
igSmartPointer<igObject> *igSmartPointer_igStatisticsItem_Destruct(igSmartPointer<igObject> *self, short deleteFlag);
int *igSmartPointer_igStatisticsItem_Construct(int *p);
int *igSmartPointer_igGuiComponent_Construct(int *p);
int *igSmartPointer_igBoxComponent_Construct(int *p);
int *igSmartPointer_igViewerGuiFactory_Construct(int *p);
struct igInfoManager *igInfoManager_Construct(struct igInfoManager *self);
}

#endif
