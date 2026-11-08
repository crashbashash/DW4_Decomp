void *memset(void *, int, unsigned int);

typedef struct {
    char f0;
    char f1;
    char pad2[2];
    int f4;
    int f8;
    int f12;
    int f16;
    int f20;
    int f24;
    int f28;
    int f32;
    int f36;
    char f40;
    char pad41[3];
    int f44;
    char pad48[16];
} Obj29f2b0;

void FUN_0029f2b0(Obj29f2b0 *obj) {
    memset(obj, 0, 64);
    obj->f0 = 0;
    obj->f1 = 0;
    obj->f4 = 0;
    obj->f8 = 0;
    obj->f12 = 0;
    obj->f16 = 0;
    obj->f20 = 0;
    obj->f24 = 0;
    obj->f28 = 0;
    obj->f32 = 0;
    obj->f36 = 0;
    obj->f40 = 0;
    obj->f44 = 0;
}
