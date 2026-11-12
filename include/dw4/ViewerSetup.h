#ifndef DW4_VIEWERSETUP_H
#define DW4_VIEWERSETUP_H
#include "dw4/igSmartPointer.h"

/* The igInsightCore that FUN_00232800 creates, with its window field (+20) as the reference holder
   it is. */
struct InsightCore : igObject {
    char pad8[12];
    igSmartPointer<igObject> window;
};

/* The viewer's setup: an Insight core, its scene-info, actor and data-pump managers, the logo
   renderer and the window, each held by reference (the same object FUN_00463bc0 reads as S). */
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
#endif
