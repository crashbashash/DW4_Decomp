#include "dw4/reflected.h"
extern "C" {
void *igProperty_FindByName(...);
int igStrCmp(...);
int FUN_00394400(...);
int FUN_003a8580(...);
extern int DAT_004e0858[4];
extern int DAT_0050ef68[4];
extern int DAT_0050ef78[4];
extern int DAT_0050efd8[4];
extern int DAT_0050f128[4];
extern int DAT_0050f130[4];
extern int DAT_00585be0[4];
}
struct V3 { float x, y, z; };
extern "C" V3 *DAT_0058a218[4];
extern "C" int FUN_00394920(beModelCtrl *arg0, beModelCtrlInfo *arg1, beBaseInfoRam *arg2, beModelCtrlInfoWork *arg3, beModelCtrlMSGBOX *arg4) {
    V3 vec;
    int i;
    int cnt;
    int idx;
    beModelCtrlAIMapList *lst;
    int *name;
    int *name2;
    beModelCtrlInfoAI *o;
    beModelCtrlAIMap *prop;
    lst = (beModelCtrlAIMapList *)((beModelCtrlInfoDataAIM *)igProperty_FindByName(arg1->_dataList, DAT_00585be0[0], &DAT_0050efd8[0]))->_aIMapList;
    name = (int *)arg4->_name;
    name = name != 0 ? name : &DAT_004e0858[0];
    prop = (beModelCtrlAIMap *)igProperty_FindByName(lst, DAT_00585be0[0], name);
    beModelCtrlAIMap *volatile key = prop;
    cnt = lst->_count;
    for (i = 0; i < cnt; i++) { if (*(beModelCtrlAIMap **)&key == ((beModelCtrlAIMap **)lst->_data)[i]) { idx = i; goto found; } }
    idx = -1;
found:
    o = (beModelCtrlInfoAI *)arg3->_aI;
    if (o != 0) {
        o->_mapNo = idx;
        if (prop->_targetType != 0 && igStrCmp(prop->_targetType, &DAT_0050ef78[0]) == 0) {
            DAT_0058a218[0] = &vec;
            name2 = (int *)arg1->_name;
            name2 = name2 != 0 ? name2 : &DAT_004e0858[0];
            FUN_00394400(arg0, arg2, &DAT_0050f128[0], &DAT_0050f130[0], name2, 0, 0, 0, 0, 0);
            { beModelCtrlInfoAI *oo = (beModelCtrlInfoAI *)arg3->_aI; ((float *)oo->_worldPos)[0] = vec.x; ((float *)oo->_worldPos)[1] = vec.y; ((float *)oo->_worldPos)[2] = vec.z; }
            DAT_0058a218[0] = 0;
        }
    }
    FUN_003a8580(arg2, &DAT_0050ef68[0]);
    return 1;
}
