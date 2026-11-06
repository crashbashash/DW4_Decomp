/* A beMessenger carries a beMessengerArgData (self->_argData) that holds one typed list per
 * argument kind: bool, int, float, long, Vec3f, Matrix44f, object and string. These are the 18
 * count/get/clear/set helpers over those lists. Element addresses are list->_data + index *
 * element size (int/float/object 4, long 8, Vec3f 12). */
#include "dw4/reflected.h"

void beMessenger_SetRunCheck(beMessenger *self, char enabled) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    args->_isRunCheck = enabled;
}

int beMessenger_GetBoolCount(beMessenger *self) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igBoolList *list = (igBoolList *)args->_boolList;
    return list->_count;
}

void beMessenger_ClearBool(beMessenger *self) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igBoolList *list = (igBoolList *)args->_boolList;
    list->_count = 0;
}

unsigned char beMessenger_GetBool(beMessenger *self, int index) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igBoolList *list = (igBoolList *)args->_boolList;
    return *(int *)(list->_data + index);
}

int beMessenger_GetIntCount(beMessenger *self) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igIntList *list = (igIntList *)args->_intList;
    return list->_count;
}

void beMessenger_ClearInt(beMessenger *self) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igIntList *list = (igIntList *)args->_intList;
    list->_count = 0;
}

int beMessenger_GetInt(beMessenger *self, int index) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igIntList *list = (igIntList *)args->_intList;
    return *(int *)(list->_data + (index * 4));
}

int beMessenger_GetFloatCount(beMessenger *self) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igFloatList *list = (igFloatList *)args->_floatList;
    return list->_count;
}

float beMessenger_GetFloat(beMessenger *self, int index) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igFloatList *list = (igFloatList *)args->_floatList;
    return *(float *)(list->_data + index * 4);
}

int beMessenger_GetLongCount(beMessenger *self) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igLongList *list = (igLongList *)args->_longList;
    return list->_count;
}

long long beMessenger_GetLong(beMessenger *self, int index) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igLongList *list = (igLongList *)args->_longList;
    return *(long long *)(list->_data + (index * 8));
}

int beMessenger_GetVec3Count(beMessenger *self) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igVec3fList *list = (igVec3fList *)args->_vec3fList;
    return list->_count;
}

void beMessenger_ClearVec3(beMessenger *self) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igVec3fList *list = (igVec3fList *)args->_vec3fList;
    list->_count = 0;
}

void beMessenger_GetVec3(float *out, beMessenger *self, int index) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igVec3fList *list = (igVec3fList *)args->_vec3fList;
    float *element;

    element = (float *)(list->_data + (index * 0xC));
    out[0] = element[0];
    out[1] = element[1];
    out[2] = element[2];
}

int beMessenger_GetMatrixCount(beMessenger *self) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igMatrix44fList *list = (igMatrix44fList *)args->_matrix44fList;
    return list->_count;
}

int beMessenger_GetObjectCount(beMessenger *self) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igObjectList *list = (igObjectList *)args->_objectList;
    return list->_count;
}

int beMessenger_GetObject(beMessenger *self, int index) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igObjectList *list = (igObjectList *)args->_objectList;
    return *(int *)(list->_data + (index * 4));
}

int beMessenger_GetStringCount(beMessenger *self) {
    beMessengerArgData *args = (beMessengerArgData *)self->_argData;
    igStringRefList *list = (igStringRefList *)args->_stringList;
    return list->_count;
}
