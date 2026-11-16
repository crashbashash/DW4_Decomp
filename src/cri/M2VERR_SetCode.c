int m2verr_SetCodeSub();
extern int m2verrinf[4];
int M2VERR_SetCode(int arg0, int arg1) {
    if (arg0 == 0) {
        m2verr_SetCodeSub(&m2verrinf[0]);
    } else {
        m2verr_SetCodeSub(arg0 + 4);
    }
    return arg1;
}
