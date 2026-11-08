typedef struct { int w[16]; } Hdr;
typedef struct { int state; char pad[20]; Hdr hdr; char sub[1]; } Obj;
extern Hdr DAT_00573eb8;
void FUN_002859b8();
void FUN_0028ad38();
Obj *FUN_0028ae78(Obj *o) {
    o->hdr = DAT_00573eb8;
    FUN_002859b8(o);
    FUN_0028ad38(o->sub);
    o->state = 2;
    return o;
}
