void Gap__Core__igPsx2IopRpcConnection__vfunc_12(igPsx2IopRpcConnectionView *arg0) {
    if (arg0->_dataMemory != 0) {
        WaitSema(arg0->_sema);
        FUN_00300f50((int)arg0, (int)arg0->_dataMemory);
    }
    FUN_00300f50((int)arg0, (int)arg0->_sifData);
    DeleteSema(arg0->_sema);
}

void FUN_0032d640(int *arg0, igPsx2IopRpcConnectionView *arg1, int arg2) {
    while (1) {
        if (sceSifBindRpc(arg1->_sifData, arg2, 0) < 0) {
            *arg0 = g_resultFailure.v;
            return;
        }
        if (arg1->_sifData->serve != 0) {
            arg1->_dataMemory = (char *)FUN_00300db0((int)arg1, 0x20, 0x10);
            *arg0 = g_resultSuccess.v;
            return;
        }
    }
}

int FUN_0032d6d0(int *arg0, igPsx2IopRpcConnectionView *arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7) {
    const int *var_v1_2;
    int var_s0;

    if (arg3 & 0xF) {
        *arg0 = g_resultFailure.v;
        return;
    }
    if (arg4 & 0xF) {
        *arg0 = g_resultFailure.v;
        return;
    }
    if (arg5 & 0xF) {
        *arg0 = g_resultFailure.v;
        return;
    }
    if (arg6 & 0xF) {
        *arg0 = g_resultFailure.v;
        return;
    }
    WaitSema(arg1->_sema);
    if ((arg5 == 0) && (arg7 == 0)) {
        var_s0 = sceSifCallRpc(arg1->_sifData, arg2, 1, arg3, arg4, 0, 0, thunk_iSignalSema, arg1->_sema);
    } else {
        var_s0 = sceSifCallRpc(arg1->_sifData, arg2, 0, arg3, arg4, arg5, arg6, 0, 0);
        SignalSema(arg1->_sema);
    }
    if (var_s0 >= 0) {
        var_v1_2 = &g_resultSuccess.v;
    } else {
        var_v1_2 = &g_resultFailure.v;
    }
    *arg0 = *var_v1_2;
}

int FUN_0032d850(int *arg0, igPsx2IopRpcConnectionView *arg1, int arg2, int arg3, int *arg4, int arg5) {
    const int *var_v1;
    int var_s0;
    char *p;
    char *q;

    WaitSema(arg1->_sema);
    *(int *)arg1->_dataMemory = arg3;
    if (arg4 == 0) {
        p = arg1->_dataMemory;
        SyncDCache(p, p + 0xF);
        if (arg5 != 0) {
            var_s0 = sceSifCallRpc(arg1->_sifData, arg2, 2, arg1->_dataMemory, 0x10, 0, 0, 0, 0);
            SignalSema(arg1->_sema);
        } else {
            var_s0 = sceSifCallRpc(arg1->_sifData, arg2, 3, arg1->_dataMemory, 0x10, 0, 0, thunk_iSignalSema, arg1->_sema);
        }
    } else {
        p = arg1->_dataMemory;
        q = p + 0x10;
        var_s0 = sceSifCallRpc(arg1->_sifData, arg2, 0, p, 0x10, q, 0x10, 0, 0);
        *arg4 = *(int *)q;
        SignalSema(arg1->_sema);
    }
    if (var_s0 >= 0) {
        var_v1 = &g_resultSuccess.v;
    } else {
        var_v1 = &g_resultFailure.v;
    }
    *arg0 = *var_v1;
}

void FUN_0032d9b0(int *arg0, igPsx2IopRpcConnectionView *arg1, int arg2, int arg3) {
    const int *var_v1;
    int var_s1;

    WaitSema(arg1->_sema);
    if (arg3 != 0) {
        var_s1 = sceSifCallRpc(arg1->_sifData, arg2, 2, 0, 0, 0, 0, 0, 0);
        SignalSema(arg1->_sema);
    } else {
        var_s1 = sceSifCallRpc(arg1->_sifData, arg2, 3, 0, 0, 0, 0, thunk_iSignalSema, arg1->_sema);
    }
    if (var_s1 >= 0) {
        var_v1 = &g_resultSuccess.v;
    } else {
        var_v1 = &g_resultFailure.v;
    }
    *arg0 = *var_v1;
}

void thunk_iSignalSema(int sema) {
    iSignalSema(sema);
}

