#include "dw4/reflected.h"

int List_Reserve();

/* Each metaobject handle is read through an array extern so the load stays absolute. */
extern int g_igAABox_metaObject[4];
extern int DAT_005610d8[4];
extern int DAT_005610c8[4];
extern int DAT_00561098[4];
extern int DAT_00561088[4];
extern int DAT_00561078[4];
extern int DAT_00561070[4];
extern int DAT_00561068[4];
extern int DAT_00561060[4];
extern int DAT_00561058[4];
extern int DAT_00561050[4];
extern int DAT_00561048[4];
extern int DAT_00561040[4];
extern int DAT_00561038[4];
extern int DAT_00561030[4];
extern int DAT_00561028[4];
extern int DAT_00561020[4];
extern int DAT_00561018[4];
extern int DAT_00560fe0[4];
extern int DAT_00560fc0[4];
extern int DAT_00560fb8[4];
extern int DAT_00560fa0[4];
extern int DAT_00560f20[4];
extern int DAT_00560f18[4];
extern int DAT_00560f10[4];
extern int DAT_00560f08[4];

int Gap__igAABox__vfunc_22(void) {
    return g_igAABox_metaObject[0];
}

int Gap__igAABoxList__vfunc_22(void) {
    return DAT_005610d8[0];
}

int Gap__igVec2fList__vfunc_22(void) {
    return DAT_005610c8[0];
}

int Gap__igVec4ucList__vfunc_22(void) {
    return DAT_00561098[0];
}

int Gap__igQuaternionfList__vfunc_22(void) {
    return DAT_00561088[0];
}

int Gap__igMatrix44fList__vfunc_22(void) {
    return DAT_00561078[0];
}

int Gap__igIntersectionFunctionList__vfunc_22(void) {
    return DAT_00561070[0];
}

int Gap__igExtendByFunctionList__vfunc_22(void) {
    return DAT_00561068[0];
}

int Gap__igContainsFunctionList__vfunc_22(void) {
    return DAT_00561060[0];
}

int Gap__igRayIntersectionFunctionList__vfunc_22(void) {
    return DAT_00561058[0];
}

int Gap__igExtendByRayFunctionList__vfunc_22(void) {
    return DAT_00561050[0];
}

int Gap__igContainsRayFunctionList__vfunc_22(void) {
    return DAT_00561048[0];
}

int Gap__igExtendByVecFunctionList__vfunc_22(void) {
    return DAT_00561040[0];
}

int Gap__igContainsVecFunctionList__vfunc_22(void) {
    return DAT_00561038[0];
}

int Gap__igTransformFunctionList__vfunc_22(void) {
    return DAT_00561030[0];
}

int Gap__igEmptyFunctionList__vfunc_22(void) {
    return DAT_00561028[0];
}

int Gap__igIsEmptyFunctionList__vfunc_22(void) {
    return DAT_00561020[0];
}

int Gap__igGetCenterFunctionList__vfunc_22(void) {
    return DAT_00561018[0];
}

int Gap__igPlane__vfunc_22(void) {
    return DAT_00560fe0[0];
}

int Gap__igRay__vfunc_22(void) {
    return DAT_00560fc0[0];
}

int Gap__igRayList__vfunc_22(void) {
    return DAT_00560fb8[0];
}

int Gap__igSphere__vfunc_22(void) {
    return DAT_00560fa0[0];
}

int Gap__igVectorBlending__vfunc_22(void) {
    return DAT_00560f20[0];
}

int Gap__igVectorMorphing__vfunc_22(void) {
    return DAT_00560f18[0];
}

int Gap__igVolumeList__vfunc_22(void) {
    return DAT_00560f10[0];
}

int Gap__igMatrix44fList__vfunc_23(void) {
    return 0x40;
}

int Gap__igQuaternionfList__vfunc_23(void) {
    return 0x10;
}

int Gap__igVec4ucList__vfunc_23(void) {
    return 4;
}

int Gap__igVec2fList__vfunc_23(void) {
    return 8;
}

int Gap__igGetCenterFunctionList__vfunc_23(void) {
    return 4;
}

int Gap__igIsEmptyFunctionList__vfunc_23(void) {
    return 4;
}

int Gap__igEmptyFunctionList__vfunc_23(void) {
    return 4;
}

int Gap__igTransformFunctionList__vfunc_23(void) {
    return 4;
}

int Gap__igContainsVecFunctionList__vfunc_23(void) {
    return 4;
}

int Gap__igExtendByVecFunctionList__vfunc_23(void) {
    return 4;
}

int Gap__igContainsRayFunctionList__vfunc_23(void) {
    return 4;
}

int Gap__igExtendByRayFunctionList__vfunc_23(void) {
    return 4;
}

int Gap__igRayIntersectionFunctionList__vfunc_23(void) {
    return 4;
}

int Gap__igContainsFunctionList__vfunc_23(void) {
    return 4;
}

int Gap__igExtendByFunctionList__vfunc_23(void) {
    return 4;
}

int Gap__igIntersectionFunctionList__vfunc_23(void) {
    return 4;
}

int Gap__igAABoxList__vfunc_24(void) {
    return g_igAABox_metaObject[0];
}

int Gap__igRayList__vfunc_24(void) {
    return DAT_00560fc0[0];
}

int Gap__igVolumeList__vfunc_24(void) {
    return DAT_00560f08[0];
}

void Gap__igIntersectionFunctionList__vfunc_18(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve(arg0, temp_a1, 4);
    }
}

void Gap__igExtendByFunctionList__vfunc_18(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve(arg0, temp_a1, 4);
    }
}

void Gap__igContainsFunctionList__vfunc_18(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve(arg0, temp_a1, 4);
    }
}

void Gap__igRayIntersectionFunctionList__vfunc_18(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve(arg0, temp_a1, 4);
    }
}

void Gap__igExtendByRayFunctionList__vfunc_18(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve(arg0, temp_a1, 4);
    }
}

void Gap__igContainsRayFunctionList__vfunc_18(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve(arg0, temp_a1, 4);
    }
}

void Gap__igExtendByVecFunctionList__vfunc_18(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve(arg0, temp_a1, 4);
    }
}

void Gap__igContainsVecFunctionList__vfunc_18(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve(arg0, temp_a1, 4);
    }
}

void Gap__igTransformFunctionList__vfunc_18(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve(arg0, temp_a1, 4);
    }
}

void Gap__igEmptyFunctionList__vfunc_18(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve(arg0, temp_a1, 4);
    }
}

void Gap__igIsEmptyFunctionList__vfunc_18(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve(arg0, temp_a1, 4);
    }
}

void Gap__igGetCenterFunctionList__vfunc_18(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve(arg0, temp_a1, 4);
    }
}

void Gap__igVec2fList__vfunc_18(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve(arg0, temp_a1, 8);
    }
}

void Gap__igVec4ucList__vfunc_18(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve(arg0, temp_a1, 4);
    }
}

void Gap__igQuaternionfList__vfunc_18(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve(arg0, temp_a1, 0x10);
    }
}

void Gap__igMatrix44fList__vfunc_18(igDataList *arg0) {
    int temp_a1;

    temp_a1 = arg0->_count;
    if (temp_a1 < arg0->_capacity) {
        List_Reserve(arg0, temp_a1, 0x40);
    }
}
