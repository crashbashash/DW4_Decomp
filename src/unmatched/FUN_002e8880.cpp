struct L;
class O {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void v30(L *);
    virtual void v31(L *);
    virtual void v32(L *);
};
struct L { int p0, p4; int n; int p12; void **arr; char pad[80]; int f100; };
extern "C" {
O *FUN_002d7e90(L *, int);
int igObject_IsKindOf(void *, int);
extern int DAT_004fb410[4];
extern int DAT_00585b70[4];
void FUN_002e8880(int *arg0, L *arg1) {
    int i;
    for (i = 0; i < arg1->n; i++) {
        if (((igObject_IsKindOf(arg1->arr[i], DAT_00585b70[0]) != 0) ^ 1) != 0) {
            FUN_002d7e90(arg1, i)->v30(arg1);
        }
    }
    if (arg1->f100 < 4) {
        for (i = 0; i < arg1->n; i++) {
            if (((igObject_IsKindOf(arg1->arr[i], DAT_00585b70[0]) != 0) ^ 1) != 0) {
                FUN_002d7e90(arg1, i)->v31(arg1);
            }
        }
    } else {
        for (i = 0; i < arg1->n; i++) {
            if (((igObject_IsKindOf(arg1->arr[i], DAT_00585b70[0]) != 0) ^ 1) != 0) {
                FUN_002d7e90(arg1, i)->v32(arg1);
            }
        }
    }
    *arg0 = DAT_004fb410[0];
}
}
