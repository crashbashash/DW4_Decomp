struct Status { int value; bool operator!=(const Status &o) const { return value != o.value; } };
struct Obj { int p0; int rc; };
struct L { char p[8]; int count; int cap; int data; };
struct A { char p[12]; struct Obj *conn; char q[8]; int f24; char r[4]; int f32; int f36; int f40; };
extern int DAT_004d5f80[4];
extern int DAT_004d5f98[4];
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
extern struct L *DAT_0055f5d0[4];
extern "C" void FUN_00143800(void);
extern "C" int FUN_00112ca0(int *);
extern "C" struct Status FUN_0032cf50(int *, int, int, int);
extern "C" int FUN_00300db0(struct A *, int, int);
extern "C" int FUN_00301000(struct A *);
extern "C" void igObject_Destroy(struct Obj *);
extern "C" int FUN_002cfe10(int);
extern "C" struct Status FUN_0032d640(struct Obj *, int);
extern "C" void List_Reserve(struct L *, int, int);
extern "C" void List_Resize(struct L *, int, int);
extern "C" void *memset(void *, int, unsigned int);
extern "C" struct Status FUN_0032d6d0(struct Obj *, int, int, int, int, int, int);
extern "C" int FUN_00300f50(struct A *, int);
extern "C" struct Status FUN_0032d850(struct Obj *, int, unsigned int, int, int);
extern "C" int FUN_00113f20(void);
extern "C" int FUN_0010d4c8(int, void (*)(void), int);
extern "C" int FUN_00113f78(void);
extern "C" void Gap__igPsx2AudioContext__vfunc_24(int *arg0, struct A *arg1) {
    struct Obj *o;
    int s0; int *buf; int n; struct L *l;
    if (FUN_00112ca0(DAT_004d5f80) < 0) {
        if (FUN_0032cf50(DAT_004d5f98, 2, 0, 0) != *(Status *)DAT_004fb410) {
            *arg0 = DAT_004fb418[0];
            return;
        }
    }
    s0 = FUN_00301000(arg1);
    o = arg1->conn;
    if (o != 0) {
        o->rc = o->rc - 1;
        if (((unsigned long long)((long long)o->rc << 41) >> 41) == 0)
            igObject_Destroy(o);
    }
    arg1->conn = (struct Obj *)FUN_002cfe10(s0);
    FUN_0032d640(arg1->conn, 0x12111);
    s0 = FUN_00300db0(arg1, 0x10, 0x10);
    buf = (int *)s0;
    buf[0] = arg1->f24;
    buf[1] = arg1->f32;
    buf[2] = arg1->f36;
    n = arg1->f32 + arg1->f36;
    if (n >= DAT_0055f5d0[0]->count) List_Reserve(DAT_0055f5d0[0], n, 0x24);
    n = arg1->f32 + arg1->f36;
    l = DAT_0055f5d0[0];
    if (n >= 0) {
        if (n <= l->cap) l->count = n;
        else List_Resize(l, n, 0x24);
    }
    n = DAT_0055f5d0[0]->count;
    if (n != 0) memset((void *)DAT_0055f5d0[0]->data, 0, n * 0x24);
    FUN_0032d6d0(arg1->conn, 0x20000, s0, 0x10, 0, 0, 0);
    FUN_00300f50(arg1, s0);
    FUN_0032d850(arg1->conn, 0x40000, 0x3FFF3FFFu, 0, 0);
    FUN_0032d850(arg1->conn, 0x40001, 0x3FFF3FFF, 0, 0);
    arg1->f40 = FUN_00300db0(arg1, 0x2000, 0x10);
    FUN_00113f20();
    FUN_0010d4c8(3, FUN_00143800, 0);
    FUN_00113f78();
    *arg0 = DAT_004fb410[0];
}
