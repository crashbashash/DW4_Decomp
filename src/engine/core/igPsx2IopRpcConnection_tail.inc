/* Allocate the SIF client block and create the connection's semaphore, initially free. */
void igPsx2IopRpcConnection_InitDefaults(igPsx2IopRpcConnectionView *self) {
    self->_sifData = (SifClientData *)igObject_AllocateStorage((int)self, sizeof(SifClientData));
    SemaParam param = {0, 1, 1, 0, 0, 0};
    self->_sema = CreateSema(&param);
}

void igPsx2IopRpcConnection_ReleaseDefaults(igPsx2IopRpcConnectionView *arg0) {
    if (arg0->_dataMemory != 0) {
        WaitSema(arg0->_sema);
        igObject_FreeMemory((int)arg0, (int)arg0->_dataMemory);
    }
    igObject_FreeMemory((int)arg0, (int)arg0->_sifData);
    DeleteSema(arg0->_sema);
}

/* Binds the SIF client to RPC server `serverId`, polling until the server answers. */
igResult igPsx2IopRpcConnection_Bind(igPsx2IopRpcConnectionView *self, int serverId) {
    while (1) {
        if (sceSifBindRpc(self->_sifData, serverId, 0) < 0) {
            return g_resultFailure;
        }
        if (self->_sifData->serve != 0) {
            self->_dataMemory = (char *)igObject_MallocAligned((int)self, 0x20, 0x10);
            return g_resultSuccess;
        }
    }
}

/* Calls RPC function `function` with the 16-byte-aligned send and receive buffers; a call with
 * neither a receive buffer nor `wait` returns at once and its end callback releases the
 * semaphore. */
igResult igPsx2IopRpcConnection_Call(igPsx2IopRpcConnectionView *self, int function, int send, int sendSize, int receive, int receiveSize, int wait) {
    const igResult *result;
    int status;

    if (send & 0xF) {
        return g_resultFailure;
    }
    if (sendSize & 0xF) {
        return g_resultFailure;
    }
    if (receive & 0xF) {
        return g_resultFailure;
    }
    if (receiveSize & 0xF) {
        return g_resultFailure;
    }
    WaitSema(self->_sema);
    if ((receive == 0) && (wait == 0)) {
        status = sceSifCallRpc(self->_sifData, function, 1, send, sendSize, 0, 0, igPsx2IopRpcConnection_RpcEndCallback, self->_sema);
    } else {
        status = sceSifCallRpc(self->_sifData, function, 0, send, sendSize, receive, receiveSize, 0, 0);
        SignalSema(self->_sema);
    }
    if (status >= 0) {
        result = &g_resultSuccess;
    } else {
        result = &g_resultFailure;
    }
    return *result;
}

/* Sends the one-word `data` to RPC function `function`; with `reply` the call waits and stores the
 * server's first word there, otherwise `noWait` chooses between a fire-and-forget call and one
 * whose end callback signals the semaphore. */
igResult igPsx2IopRpcConnection_CallWithData(igPsx2IopRpcConnectionView *self, int function, int data, int *reply, int noWait) {
    const igResult *result;
    int status;
    char *p;
    char *q;

    WaitSema(self->_sema);
    *(int *)self->_dataMemory = data;
    if (reply == 0) {
        p = self->_dataMemory;
        SyncDCache(p, p + 0xF);
        if (noWait != 0) {
            status = sceSifCallRpc(self->_sifData, function, 2, self->_dataMemory, 0x10, 0, 0, 0, 0);
            SignalSema(self->_sema);
        } else {
            status = sceSifCallRpc(self->_sifData, function, 3, self->_dataMemory, 0x10, 0, 0, igPsx2IopRpcConnection_RpcEndCallback, self->_sema);
        }
    } else {
        p = self->_dataMemory;
        q = p + 0x10;
        status = sceSifCallRpc(self->_sifData, function, 0, p, 0x10, q, 0x10, 0, 0);
        *reply = *(int *)q;
        SignalSema(self->_sema);
    }
    if (status >= 0) {
        result = &g_resultSuccess;
    } else {
        result = &g_resultFailure;
    }
    return *result;
}

void igPsx2IopRpcConnection_CallNoData(int *arg0, igPsx2IopRpcConnectionView *arg1, int arg2, int arg3) {
    const int *var_v1;
    int var_s1;

    WaitSema(arg1->_sema);
    if (arg3 != 0) {
        var_s1 = sceSifCallRpc(arg1->_sifData, arg2, 2, 0, 0, 0, 0, 0, 0);
        SignalSema(arg1->_sema);
    } else {
        var_s1 = sceSifCallRpc(arg1->_sifData, arg2, 3, 0, 0, 0, 0, igPsx2IopRpcConnection_RpcEndCallback, arg1->_sema);
    }
    if (var_s1 >= 0) {
        var_v1 = &g_resultSuccess.v;
    } else {
        var_v1 = &g_resultFailure.v;
    }
    *arg0 = *var_v1;
}

void igPsx2IopRpcConnection_RpcEndCallback(int sema) {
    iSignalSema(sema);
}

