typedef struct { int w[32]; } Info;
typedef struct { char pad[88]; Info info; } Obj;
int FUN_0028b098();
void FUN_002855d8();
void FUN_00285720(Obj *o, Info *out) {
    if (FUN_0028b098(o) != 0) {
        FUN_002855d8(0, 0xFF03020C);
        return;
    }
    *out = o->info;
}
