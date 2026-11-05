/* src/game/beMessengerResults.c — accessors for the argument lists of a beMessenger
 *
 * A beMessenger carries a beMessengerArgData (self->_argData) that holds one
 * typed list per argument kind: bool, int, float, long, Vec3f, Matrix44f,
 * object and string (field names from include/dw4/reflected.h).  These are the
 * 18 count/get/clear/set helpers over those lists, in retail address order.
 * Element addresses are list->_data + index * element size (int/float/object 4,
 * long 8, Vec3f 12).  Folded from the per-function units by tools/merge_units.py;
 * the matching build splits a function back out with tools/units.py, so
 * `make check` still verifies one function at a time. */
#include "dw4/reflected.h"

/* 0x0038f0e0 */
void beMessenger_SetRunCheck(beMessenger *self, char enabled) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    args->_isRunCheck = enabled;
}

/* 0x0038f0f0 */
int beMessenger_GetBoolCount(beMessenger *self) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igBoolList *list = (igBoolList *)args->_boolList;
    return list->_count;
}

/* 0x0038f1d0 */
void beMessenger_ClearBool(beMessenger *self) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igBoolList *list = (igBoolList *)args->_boolList;
    list->_count = 0;
}

/* 0x0038f220 */
unsigned char beMessenger_GetBool(beMessenger *self, int index) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igBoolList *list = (igBoolList *)args->_boolList;
    return *(int *)(list->_data + index);
}

/* 0x0038f240 */
int beMessenger_GetIntCount(beMessenger *self) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igIntList *list = (igIntList *)args->_intList;
    return list->_count;
}

/* 0x0038f2d0 */
void beMessenger_ClearInt(beMessenger *self) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igIntList *list = (igIntList *)args->_intList;
    list->_count = 0;
}

/* 0x0038f320 */
int beMessenger_GetInt(beMessenger *self, int index) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igIntList *list = (igIntList *)args->_intList;
    return *(int *)(list->_data + (index * 4));
}

/* 0x0038f340 */
int beMessenger_GetFloatCount(beMessenger *self) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igFloatList *list = (igFloatList *)args->_floatList;
    return list->_count;
}

/* 0x0038f3d0 */
float beMessenger_GetFloat(beMessenger *self, int index) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igFloatList *list = (igFloatList *)args->_floatList;
    return *(float *)(list->_data + index * 4);
}

/* 0x0038f3f0 */
int beMessenger_GetLongCount(beMessenger *self) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igLongList *list = (igLongList *)args->_longList;
    return list->_count;
}

/* 0x0038f480 */
long long beMessenger_GetLong(beMessenger *self, int index) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igLongList *list = (igLongList *)args->_longList;
    return *(long long *)(list->_data + (index * 8));
}

/* 0x0038f4a0 */
int beMessenger_GetVec3Count(beMessenger *self) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igVec3fList *list = (igVec3fList *)args->_vec3fList;
    return list->_count;
}

/* 0x0038f550 */
void beMessenger_ClearVec3(beMessenger *self) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igVec3fList *list = (igVec3fList *)args->_vec3fList;
    list->_count = 0;
}

/* 0x0038f560 */
/* Copies element `index` of the Vec3f list (3 floats) into `out`. */
void beMessenger_GetVec3(float *out, beMessenger *self, int index) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igVec3fList *list = (igVec3fList *)args->_vec3fList;
    float *element;

    element = (float *)(list->_data + (index * 0xC));
    out[0] = element[0];
    out[1] = element[1];
    out[2] = element[2];
}

/* 0x0038f5a0 */
int beMessenger_GetMatrixCount(beMessenger *self) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igMatrix44fList *list = (igMatrix44fList *)args->_matrix44fList;
    return list->_count;
}

/* 0x0038f660 */
int beMessenger_GetObjectCount(beMessenger *self) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igObjectList *list = (igObjectList *)args->_objectList;
    return list->_count;
}

/* 0x0038f800 */
int beMessenger_GetObject(beMessenger *self, int index) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igObjectList *list = (igObjectList *)args->_objectList;
    return *(int *)(list->_data + (index * 4));
}

/* 0x0038f820 */
int beMessenger_GetStringCount(beMessenger *self) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igStringRefList *list = (igStringRefList *)args->_stringList;
    return list->_count;
}
