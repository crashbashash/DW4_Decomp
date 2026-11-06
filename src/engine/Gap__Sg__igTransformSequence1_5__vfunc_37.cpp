#include "dw4/reflected.h"
struct V3 { float x, y, z; };
struct V4 { float x, y, z, w; };
extern "C" int List_InsertBytes(...);
/* matching construct: the list/arena-reference fields are 4-byte handles; the casts give the typed list views (no layout effect).
 * The three interpolation-data lists (+60/+64/+68) are hypothesised to be Vec3f lists (12-byte elements, two per key); kept as igDataList. */
extern "C" void Gap__Sg__igTransformSequence1_5__vfunc_37(igTransformSequence1_5 *t, int idx) {
    long long sp216;
    V3 sp200;
    V3 sp184;
    V3 sp168;
    V3 sp152;
    V3 sp136;
    V3 sp120;
    V3 sp104;
    V3 sp88;
    V4 sp64;
    int s0;
    sp216 = ((long long *)((igLongList *)t->_timeListLong)->_data)[idx];
    List_InsertBytes((igLongList *)t->_timeListLong, idx, 1, &sp216, 8);
    if (t->_drivenChannels & 1) {
        sp200 = ((V3 *)((igVec3fList *)t->_xlateList)->_data)[idx];
        List_InsertBytes((igVec3fList *)t->_xlateList, idx, 1, &sp200, 12);
        if (t->_interpolationDataTranslation != 0) {
            s0 = idx * 2;
            sp184 = ((V3 *)((igDataList *)t->_interpolationDataTranslation)->_data)[idx * 2];
            sp168 = ((V3 *)((igDataList *)t->_interpolationDataTranslation)->_data)[s0 + 1];
            List_InsertBytes((igDataList *)t->_interpolationDataTranslation, s0, 1, &sp168, 12);
            List_InsertBytes((igDataList *)t->_interpolationDataTranslation, s0, 1, &sp184, 12);
        }
    }
    if (t->_drivenChannels & 8) {
        sp152 = ((V3 *)((igVec3fList *)t->_scaleList)->_data)[idx];
        List_InsertBytes((igVec3fList *)t->_scaleList, idx, 1, &sp152, 12);
        if (t->_interpolationDataScale != 0) {
            s0 = idx * 2;
            sp136 = ((V3 *)((igDataList *)t->_interpolationDataScale)->_data)[idx * 2];
            sp120 = ((V3 *)((igDataList *)t->_interpolationDataScale)->_data)[s0 + 1];
            List_InsertBytes((igDataList *)t->_interpolationDataScale, s0, 1, &sp120, 12);
            List_InsertBytes((igDataList *)t->_interpolationDataScale, s0, 1, &sp136, 12);
        }
    }
    if ((t->_drivenChannels & 2) || (t->_drivenChannels & 4)) {
        sp64 = ((V4 *)((igQuaternionfList *)t->_quatList)->_data)[idx];
        List_InsertBytes((igQuaternionfList *)t->_quatList, idx, 1, &sp64, 16);
        if (t->_interpolationDataRotation != 0) {
            s0 = idx * 2;
            sp104 = ((V3 *)((igDataList *)t->_interpolationDataRotation)->_data)[idx * 2];
            sp88 = ((V3 *)((igDataList *)t->_interpolationDataRotation)->_data)[s0 + 1];
            List_InsertBytes((igDataList *)t->_interpolationDataRotation, s0, 1, &sp88, 12);
            List_InsertBytes((igDataList *)t->_interpolationDataRotation, s0, 1, &sp104, 12);
        }
    }
}
