extern "C" {
int FUN_00236f80(...);
int FUN_00447d00(...);
int beMessenger_AppendString(...);
int beMessenger_AppendVec3(...);
int beMessenger_DispatchSelected(...);
int beMessenger_SelectGroup(...);
int beNDMWItemBase_GetRecordString(...);
int beNDMWWindow_RunMessageScript(...);
extern char *DAT_004cf670[];
extern int DAT_00519b00[4];
extern int DAT_00519b08[4];
extern int DAT_00519b78[4];
extern int DAT_00519b90[4];
extern int DAT_00519c28[4];
extern int DAT_00519db0[4];
extern int DAT_00519f28[4];
extern int DAT_00519f30[4];
extern int DAT_00519f38[4];
extern int DAT_0058b028[4];
}
struct V3 { float x, y, z; };
struct L { char p[8]; int count; char p2[4]; int *data; };
class S { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void v22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void v26(); char p4[4]; int w8; int w12; char p16[16]; int w32; char p36[68]; L *l100; };
extern "C" void Gap__Bec__beNDMWStatusMainSlot__vfunc_24(S *arg0) {
    V3 b, a;
    beNDMWWindow_RunMessageScript(arg0, DAT_00519b90, 0x89);
    beNDMWWindow_RunMessageScript(arg0, DAT_00519b90, 0x28);
    int i = 0;
    if (0 < (*(L **)&arg0->l100)->count) {
        int item;
        int *name;
        int off;
        char **row;
        off = 0;
        row = DAT_004cf670;
        do {
            item = *(int *)((char *)arg0->l100->data + off);
            if (item == 0) {
                name = DAT_00519b00;
            } else {
                int rs;
                name = DAT_00519b78;
                rs = beNDMWItemBase_GetRecordString(item, FUN_00236f80(arg0->w8, DAT_0058b028[0]), DAT_00519f28);
                beMessenger_SelectGroup(arg0->w12, DAT_00519c28);
                beMessenger_AppendString(arg0->w12, DAT_00519db0);
                beMessenger_AppendString(arg0->w12, *row);
                beMessenger_AppendString(arg0->w12, rs);
                beMessenger_DispatchSelected(arg0->w12, DAT_00519f30);
                FUN_00447d00(&b, item);
                beMessenger_SelectGroup(arg0->w12, DAT_00519c28);
                beMessenger_AppendString(arg0->w12, DAT_00519db0);
                beMessenger_AppendString(arg0->w12, *row);
                a = b;
                beMessenger_AppendVec3(arg0->w12, &a);
                beMessenger_DispatchSelected(arg0->w12, DAT_00519f38);
            }
            beMessenger_SelectGroup(arg0->w12, DAT_00519c28);
            beMessenger_AppendString(arg0->w12, DAT_00519db0);
            beMessenger_AppendString(arg0->w12, *row);
            beMessenger_AppendString(arg0->w12, name);
            beMessenger_DispatchSelected(arg0->w12, DAT_00519b08);
            i++;
            off += 4;
            row++;
        } while (i < arg0->l100->count);
    }
    arg0->v22();
}
