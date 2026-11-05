extern "C" {
int FUN_00126308(...);
int FUN_00280a70(...);
extern int DAT_00570bd0[4];
void FUN_00280a00(void **arg0);
}
class DW4VC_12_1 { public: virtual void d0(); virtual int vX(int); };
void FUN_00280a00(void **arg0) {
    if (DAT_00570bd0[0] == 0) {
        if (arg0 == 0) {
            DAT_00570bd0[0] = FUN_00126308(4);
        } else {
            DAT_00570bd0[0] = ((DW4VC_12_1 *)(arg0))->vX((int)(4));
        }
        FUN_00280a70(DAT_00570bd0[0], arg0);
    }
}
