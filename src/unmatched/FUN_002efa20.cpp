extern "C" {
int FUN_002c0890(...);
void *FUN_002c0b60(...);
int ObjectList_AppendRetained(...);
int igNamedObject_SetName(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
extern int DAT_00586f48[4];
void FUN_002efa20(int arg0, int arg1, int arg2);
}
struct Rc { int vt; int rc; int p8; int f12; int f16; };
struct Ref {
    Rc *p;
    ~Ref() {
        Rc *object = p;
        if (object) {
            --object->rc;
            if (((unsigned long long)(long long)object->rc & 0x7fffffULL) == 0)
                igObject_Destroy(object);
        }
    }
};
void FUN_002efa20(int arg0, int arg1, int arg2) {
    FUN_002c0890();
    if (arg1 != 0) {
        Ref sp4C;
        sp4C.p = (Rc *)FUN_002c0b60(igObject_GetAllocator(DAT_00586f48[0]));
        igNamedObject_SetName(sp4C.p, arg0);
        sp4C.p->f16 = arg2;
        sp4C.p->f12 = arg1;
        ObjectList_AppendRetained(DAT_00586f48[0], sp4C.p);
    }
}
