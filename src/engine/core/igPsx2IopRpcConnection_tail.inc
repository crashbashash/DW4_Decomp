/* Allocate the SIF client block and create the connection's semaphore, initially free. */
void igPsx2IopRpcConnection_InitDefaults(igPsx2IopRpcConnectionView *self) {
    self->_sifData = (sceSifClientData *)((Gap::Core::igObject *)self)->malloc(sizeof(sceSifClientData));
    SemaParam param = {0, 1, 1, 0, 0, 0};
    self->_sema = CreateSema(&param);
}

void igPsx2IopRpcConnection_ReleaseDefaults(igPsx2IopRpcConnectionView *self) {
    if (self->_dataMemory != 0) {
        WaitSema(self->_sema);
        ((Gap::Core::igObject *)self)->free((void *)self->_dataMemory);
    }
    ((Gap::Core::igObject *)self)->free((void *)self->_sifData);
    DeleteSema(self->_sema);
}

/* Binds the SIF client to RPC server `serverId`, polling until the server answers. */
igResult igPsx2IopRpcConnection_Bind(igPsx2IopRpcConnectionView *self, int serverId) {
    while (1) {
        if (sceSifBindRpc(self->_sifData, serverId, 0) < 0) {
            return g_resultFailure;
        }
        if (self->_sifData->serve != 0) {
            self->_dataMemory = (char *)((Gap::Core::igObject *)self)->mallocAligned(0x20, 0x10);
            return g_resultSuccess;
        }
    }
}

/* Calls RPC function `function` with the 16-byte-aligned send and receive buffers; a call with
 * neither a receive buffer nor `wait` returns at once and its end callback releases the
 * semaphore. */
igResult igPsx2IopRpcConnection_Call(igPsx2IopRpcConnectionView *self, int function, void *send, int sendSize, void *receive, int receiveSize, int wait) {
    const igResult *result;
    int status;

    if ((int)send & 0xF) {
        return g_resultFailure;
    }
    if (sendSize & 0xF) {
        return g_resultFailure;
    }
    if ((int)receive & 0xF) {
        return g_resultFailure;
    }
    if (receiveSize & 0xF) {
        return g_resultFailure;
    }
    WaitSema(self->_sema);
    if ((receive == 0) && (wait == 0)) {
        status = sceSifCallRpc(self->_sifData, function, 1, send, sendSize, 0, 0, igPsx2IopRpcConnection_RpcEndCallback, (void *)self->_sema);
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
    char *send;
    char *receive;

    WaitSema(self->_sema);
    *(int *)self->_dataMemory = data;
    if (reply == 0) {
        send = self->_dataMemory;
        SyncDCache(send, send + 0xF);
        if (noWait != 0) {
            status = sceSifCallRpc(self->_sifData, function, 2, self->_dataMemory, 0x10, 0, 0, 0, 0);
            SignalSema(self->_sema);
        } else {
            status = sceSifCallRpc(self->_sifData, function, 3, self->_dataMemory, 0x10, 0, 0, igPsx2IopRpcConnection_RpcEndCallback, (void *)self->_sema);
        }
    } else {
        send = self->_dataMemory;
        receive = send + 0x10;
        status = sceSifCallRpc(self->_sifData, function, 0, send, 0x10, receive, 0x10, 0, 0);
        *reply = *(int *)receive;
        SignalSema(self->_sema);
    }
    if (status >= 0) {
        result = &g_resultSuccess;
    } else {
        result = &g_resultFailure;
    }
    return *result;
}

/* Calls RPC function `function` with no data; `blocking` waits for the server, otherwise the end
 * callback releases the semaphore. */
igResult igPsx2IopRpcConnection_CallNoData(igPsx2IopRpcConnectionView *self, int function, int blocking) {
    const igResult *result;
    int status;

    WaitSema(self->_sema);
    if (blocking != 0) {
        status = sceSifCallRpc(self->_sifData, function, 2, 0, 0, 0, 0, 0, 0);
        SignalSema(self->_sema);
    } else {
        status = sceSifCallRpc(self->_sifData, function, 3, 0, 0, 0, 0, igPsx2IopRpcConnection_RpcEndCallback, (void *)self->_sema);
    }
    if (status >= 0) {
        result = &g_resultSuccess;
    } else {
        result = &g_resultFailure;
    }
    return *result;
}

/* The SIF end function of a call that does not wait: its parameter is the connection's semaphore. */
void igPsx2IopRpcConnection_RpcEndCallback(void *sema) {
    iSignalSema((int)sema);
}

