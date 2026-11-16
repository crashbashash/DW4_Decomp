#ifndef DW4_VIEWERSETUP_H
#define DW4_VIEWERSETUP_H
#include "dw4/igSmartPointer.h"
#include "dw4/igWindow.h"

/* The igInsightCore that igInsightCore_CreateInstance creates, with its window field (+20) as the reference holder
   it is. */
struct InsightCore : igObject {
    char pad8[12];
    igSmartPointer<igObject> window;
};

/* The viewer's setup: an Insight core, its scene-info, actor and data-pump managers, the logo
   renderer and the window, each held by reference. */
struct ViewerSetup {
    igSmartPointer<InsightCore> core;
    igSmartPointer<igObject> sceneInfo;
    igSmartPointer<igObject> actors;
    igSmartPointer<igObject> dataPump;
    unsigned char showLogo;
    igSmartPointer<igObject> logo;
    igSmartPointer<igObject> window;
    ViewerSetup(igObject *window);
    ~ViewerSetup();
};

extern "C" {
void ViewerSetup_Open(ViewerSetup *setup);
void ViewerSetup_Close(ViewerSetup *setup);
int ViewerSetup_RunFrame(ViewerSetup *setup);
/* Nonzero while the viewer keeps running. */
int ViewerSetup_Update(ViewerSetup *setup);
void ViewerSetup_ResetView(ViewerSetup *setup);
int ViewerSetup_ClearInfos(ViewerSetup *setup);
/* Creates the display: the window, its visual context and frame buffer, from the shared viewer options. */
igSmartPointer<igWindow> Viewer_CreateDisplay(int allocator);
}
#endif
