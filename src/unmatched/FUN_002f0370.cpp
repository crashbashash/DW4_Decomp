extern "C" {
struct PL { void **d; int n; };
int igMemoryPoolInfoList_Append(...);
int igMemoryPoolInfoList_IndexOf(...);
extern PL *DAT_00586f58[4];
extern PL *DAT_00586f60[4];
void FUN_002f0370(void **arg0);
}
class DW4VC_116_0 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual int vX(); };
class DW4VC_368_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual void d83(); virtual void d84(); virtual void d85(); virtual void d86(); virtual void d87(); virtual void d88(); virtual void d89(); virtual int vX(int); };
void FUN_002f0370(void **arg0) {
    PL *list;
    int idx;
    int flag;

    if (((DW4VC_116_0 *)(arg0))->vX() == 0) {
        list = DAT_00586f58[0];
        idx = list->n;
        flag = 0;
    } else {
        flag = 1;
        list = DAT_00586f60[0];
        idx = list->n;
    }
    if (idx < 0x1F) {
        igMemoryPoolInfoList_Append(list, arg0);
    } else {
        idx = igMemoryPoolInfoList_IndexOf(list, 0);
        if (idx == -1) {
            idx = list->n;
            igMemoryPoolInfoList_Append(list, arg0);
        } else {
            list->d[idx] = arg0;
        }
    }
    flag = flag + (idx * 2);
    ((DW4VC_368_1 *)(arg0))->vX((int)flag);
}
