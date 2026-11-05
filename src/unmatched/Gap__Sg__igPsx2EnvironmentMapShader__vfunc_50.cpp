struct Obj { int w0; int references; };
extern "C" {
int FUN_001c1f90(int);
int igObject_Destroy(void *);
extern Obj *DAT_00562a68[4];
extern Obj *DAT_00562a80[4];
extern Obj *DAT_00562a98[4];
extern Obj *DAT_00562ab0[4];
extern Obj *DAT_00562ac8[4];
extern Obj *DAT_00562ae0[4];
extern Obj *DAT_00562af8[4];
extern Obj *DAT_00562b10[4];
extern Obj *DAT_00562b28[4];
extern Obj *DAT_00562b40[4];
extern Obj *DAT_00562b58[4];
void Gap__Sg__igPsx2EnvironmentMapShader__vfunc_50(int arg0);
}
extern "C" void Gap__Sg__igPsx2EnvironmentMapShader__vfunc_50(int arg0) {
    Obj *o;
    o = DAT_00562a68[0];
    if (o != 0) {
        o->references = o->references - 1;
        if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
        }
    }
    DAT_00562a68[0] = 0;
    o = DAT_00562a80[0];
    if (o != 0) {
        o->references = o->references - 1;
        if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
        }
    }
    DAT_00562a80[0] = 0;
    o = DAT_00562a98[0];
    if (o != 0) {
        o->references = o->references - 1;
        if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
        }
    }
    DAT_00562a98[0] = 0;
    o = DAT_00562ab0[0];
    if (o != 0) {
        o->references = o->references - 1;
        if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
        }
    }
    DAT_00562ab0[0] = 0;
    o = DAT_00562ac8[0];
    if (o != 0) {
        o->references = o->references - 1;
        if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
        }
    }
    DAT_00562ac8[0] = 0;
    o = DAT_00562ae0[0];
    if (o != 0) {
        o->references = o->references - 1;
        if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
        }
    }
    DAT_00562ae0[0] = 0;
    o = DAT_00562af8[0];
    if (o != 0) {
        o->references = o->references - 1;
        if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
        }
    }
    DAT_00562af8[0] = 0;
    o = DAT_00562b10[0];
    if (o != 0) {
        o->references = o->references - 1;
        if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
        }
    }
    DAT_00562b10[0] = 0;
    o = DAT_00562b28[0];
    if (o != 0) {
        o->references = o->references - 1;
        if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
        }
    }
    DAT_00562b28[0] = 0;
    o = DAT_00562b40[0];
    if (o != 0) {
        o->references = o->references - 1;
        if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
        }
    }
    DAT_00562b40[0] = 0;
    o = DAT_00562b58[0];
    if (o != 0) {
        o->references = o->references - 1;
        if (((unsigned long long)((long long)o->references << 0x29) >> 0x29) == 0) {
            igObject_Destroy(o);
        }
    }
    DAT_00562b58[0] = 0;
    FUN_001c1f90(arg0);
}
