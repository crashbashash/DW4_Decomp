#ifndef DW4_BENDMWPANELWAZAINFOWORK_H
#define DW4_BENDMWPANELWAZAINFOWORK_H

struct beNDMWPanelWazaInfoWork;
struct igDataList;
struct igIntList;

extern "C" {
beNDMWPanelWazaInfoWork *beNDMWPanelWazaInfoWork_Create(int allocator);
int beNDMWPanelWazaInfoWork_GetTextColorList(beNDMWPanelWazaInfoWork *p);
int beNDMWPanelWazaInfoWork_GetTextSetList(beNDMWPanelWazaInfoWork *p);
void beNDMWPanelWazaInfoWork_igIntList_SetAll(igIntList *list, int *value);
void beNDMWPanelWazaInfoWork_igStringRefList_SetAll(igDataList *list, char **token);
}

#endif
