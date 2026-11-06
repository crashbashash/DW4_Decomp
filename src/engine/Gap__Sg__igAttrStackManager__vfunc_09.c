struct L { char pad8[8]; volatile int n; int cap; int *data; };
struct Z { char pad56[56]; int f56; };
int Gap__Core__igObject__vfunc_07(void *);
int igObject_GetAllocator(void *);
int Memory_GetAllocatorBySelector(int);
struct L *FUN_001a51d0(int);
int FUN_00306e50(int, int, void *, void *, int, int);
int List_Resize(struct L *, int, int);
extern int DAT_004e4520[4];
extern struct L *DAT_00562580[4];
extern struct Z *DAT_00586dc8[4];
extern int DAT_005870f8[4];
extern unsigned char GPR_00554c14;
void Gap__Sg__igAttrStackManager__vfunc_09(unsigned char *arg0, int arg1) {
    unsigned char sp4F;
    int al; int idx; int z; struct L *l;
    Gap__Core__igObject__vfunc_07(arg0);
    if (arg1 == 0) {
        if (DAT_00562580[0] == 0) {
            al = igObject_GetAllocator(arg0);
            al = GPR_00554c14 != 0 ? al : Memory_GetAllocatorBySelector(DAT_005870f8[0]);
            DAT_00562580[0] = FUN_001a51d0(al);
        }
        l = DAT_00562580[0];
        idx = l->n;
        if (idx < l->cap) { l->n = l->n + 1; } else { List_Resize(l, idx + 1, 4); }
        l->data[idx] = (int)arg0;
        z = DAT_00586dc8[0]->f56;
        sp4F = arg0[60];
        FUN_00306e50(z, 7, &DAT_004e4520[0], &sp4F, 0, 0);
        arg0[60] = sp4F;
    }
}
