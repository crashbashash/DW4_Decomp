typedef struct { int w[32]; } Info;
typedef struct { char pad[88]; Info info; } Obj;
int M2VLIB_CheckHn();
void M2VERR_SetCode();
void FUN_00285720(Obj *o, Info *out) {
    if (M2VLIB_CheckHn(o) != 0) {
        M2VERR_SetCode(0, 0xFF03020C);
        return;
    }
    *out = o->info;
}
