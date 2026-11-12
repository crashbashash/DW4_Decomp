void Gap__Core__igPsx2IopRpcConnection__vfunc_12(S0_32d5f0 *arg0) {
    if (arg0->fC != 0) {
        WaitSema(arg0->f10);
        FUN_00300f50((int)arg0, arg0->fC);
    }
    FUN_00300f50((int)arg0, arg0->f8);
    DeleteSema(arg0->f10);
}

void FUN_0032d640(int *arg0, struct A_32d640 *arg1, int arg2) {
    while (1) {
        if (FUN_0010e0d8(arg1->f8, arg2, 0) < 0) {
            *arg0 = g_allocatorFailureStatus.v;
            return;
        }
        if (arg1->f8->f36 != 0) {
            arg1->f12 = FUN_00300db0((int)arg1, 0x20, 0x10);
            *arg0 = g_statusSucceeded.v;
            return;
        }
    }
}

int FUN_0032d6d0(int *arg0, Ob_32d6d0 *arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7) {
    int *var_v1_2;
    int var_s0;

    if (arg3 & 0xF) {
        *arg0 = g_allocatorFailureStatus.v;
        return;
    }
    if (arg4 & 0xF) {
        *arg0 = g_allocatorFailureStatus.v;
        return;
    }
    if (arg5 & 0xF) {
        *arg0 = g_allocatorFailureStatus.v;
        return;
    }
    if (arg6 & 0xF) {
        *arg0 = g_allocatorFailureStatus.v;
        return;
    }
    WaitSema(arg1->f16);
    if ((arg5 == 0) && (arg7 == 0)) {
        var_s0 = FUN_0010e2a8(arg1->f8, arg2, 1, arg3, arg4, 0, 0, thunk_iSignalSema, arg1->f16);
    } else {
        var_s0 = FUN_0010e2a8(arg1->f8, arg2, 0, arg3, arg4, arg5, arg6, 0, 0);
        SignalSema(arg1->f16);
    }
    if (var_s0 >= 0) {
        var_v1_2 = (int *)(&g_statusSucceeded.v);
    } else {
        var_v1_2 = (int *)(&g_allocatorFailureStatus.v);
    }
    *arg0 = *var_v1_2;
}

int FUN_0032d850(int *arg0, Ob_32d850 *arg1, int arg2, int arg3, int *arg4, int arg5) {
    int *var_v1;
    int var_s0;
    char *p;
    char *q;

    WaitSema(arg1->f16);
    *(int *)arg1->f12 = arg3;
    if (arg4 == 0) {
        p = arg1->f12;
        FUN_0010b7d8(p, p + 0xF);
        if (arg5 != 0) {
            var_s0 = FUN_0010e2a8(arg1->f8, arg2, 2, arg1->f12, 0x10, 0, 0, 0, 0);
            SignalSema(arg1->f16);
        } else {
            var_s0 = FUN_0010e2a8(arg1->f8, arg2, 3, arg1->f12, 0x10, 0, 0, thunk_iSignalSema, arg1->f16);
        }
    } else {
        p = arg1->f12;
        q = p + 0x10;
        var_s0 = FUN_0010e2a8(arg1->f8, arg2, 0, p, 0x10, q, 0x10, 0, 0);
        *arg4 = *(int *)q;
        SignalSema(arg1->f16);
    }
    if (var_s0 >= 0) {
        var_v1 = (int *)(&g_statusSucceeded.v);
    } else {
        var_v1 = (int *)(&g_allocatorFailureStatus.v);
    }
    *arg0 = *var_v1;
}

void FUN_0032d9b0(int *arg0, Ob_32d9b0 *arg1, int arg2, int arg3) {
    int *var_v1;
    int var_s1;

    WaitSema(arg1->f16);
    if (arg3 != 0) {
        var_s1 = FUN_0010e2a8(arg1->f8, arg2, 2, 0, 0, 0, 0, 0, 0);
        SignalSema(arg1->f16);
    } else {
        var_s1 = FUN_0010e2a8(arg1->f8, arg2, 3, 0, 0, 0, 0, thunk_iSignalSema, arg1->f16);
    }
    if (var_s1 >= 0) {
        var_v1 = (int *)(&g_statusSucceeded.v);
    } else {
        var_v1 = (int *)((char *)&g_allocatorFailureStatus);
    }
    *arg0 = *var_v1;
}

void thunk_iSignalSema(void) {
    iSignalSema();
}

