typedef struct { void *vt; } Obj;
typedef struct { int f0; Obj *obj; int f8; int n; } Ent;
extern int FUN_002adc40(void *h, int k);
int FUN_002ab2b8(char *h) {
    Ent *e = (Ent *)(h + *(int *)(h + 8128) * 0x74 + 0x1318);
    Obj *o = e->obj;
    int v = (*(int (**)(Obj *, int))((char *)o->vt + 36))(o, 1);
    if (v < e->n * 80 / 100 && v < FUN_002adc40(h, 70)) {
        return 0;
    }
    return 1;
}
