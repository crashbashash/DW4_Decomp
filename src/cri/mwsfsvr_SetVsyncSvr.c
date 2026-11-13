int SVM_SetCbSvr(int svtype, void *fn, void *arg);
extern int mwsfsvr_vsync_svr_id;

void mwsfsvr_SetVsyncSvr(void *fn, void *arg) {
    mwsfsvr_vsync_svr_id = SVM_SetCbSvr(2, fn, arg);
}
