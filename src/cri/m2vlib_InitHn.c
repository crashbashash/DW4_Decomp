typedef struct { int w[16]; } Hdr;
typedef struct { int state; char pad[20]; Hdr hdr; char sub[1]; } Obj;
extern Hdr m2vlib_libwork;
void FUN_002859b8();
void FUN_0028ad38();
Obj *m2vlib_InitHn(Obj *o) {
    o->hdr = m2vlib_libwork;
    FUN_002859b8(o);
    FUN_0028ad38(o->sub);
    o->state = 2;
    return o;
}
