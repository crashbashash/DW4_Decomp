typedef struct Vec3fList { int _vtable; unsigned int _refCount; int _count; int _capacity; float (*_data)[3]; } Vec3fList;

/* matching construct: declaration-order sweep — v, scale, count, i order */
void FUN_001e5de0(Vec3fList *list, unsigned short *out, float base, float range) {
    float *v;
    float scale;
    int count;
    int i;
    float x;
    float y;
    float z;

    count = list->_count;
    scale = 65535 / range;
    for (i = 0; i < count; i++) {
        v = list->_data[i];
        x = v[0];
        y = v[1];
        z = v[2];
        *out++ = (unsigned int)(scale * (x - base));
        *out++ = (unsigned int)(scale * (y - base));
        *out++ = (unsigned int)(scale * (z - base));
    }
}
