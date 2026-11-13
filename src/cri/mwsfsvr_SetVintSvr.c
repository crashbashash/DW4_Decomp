int SVM_SetCbSvr(int svtype, void *fn, void *arg);
extern int mwsfsvr_vint_svr_id;

void mwsfsvr_SetVintSvr(void *fn, void *arg) {
    mwsfsvr_vint_svr_id = SVM_SetCbSvr(0, fn, arg);
}
