typedef struct sceSifRpcData {
    void *paddr;
    unsigned int pid;
    int tid;
    unsigned int mode;
} sceSifRpcData;

typedef struct sceSifClientData {
    sceSifRpcData rpcd;
    unsigned int command;
    void *buff;
    void *cbuff;
    void (*end_function)(void *);
    void *end_param;
    void *serve;
} sceSifClientData;

/* mtapman.irx's RPC servers, one per call */
#define MTAP_PORT_OPEN 0x80000901
#define MTAP_PORT_CLOSE 0x80000902
#define MTAP_GET_CONNECTION 0x80000903
#define MTAP_CHANGE_THREAD_PRIORITY 0x80000904
#define MTAP_GET_MOD_VERSION 0x80000905

#define LIBMTAP_VERSION_MAJOR 3
#define LIBMTAP_VERSION_MINOR 0

void sceSifInitRpc(unsigned int mode);
int sceSifBindRpc(sceSifClientData *client, unsigned int rpc_number, int mode);
int sceSifCallRpc(sceSifClientData *client, int rpc_number, int mode, void *send, int ssize, void *receive,
                 int rsize, void (*end_function)(void *), void *end_param);
int scePrintf(const char *format, ...);

int sceMtapGetModVersion(void);

static sceSifClientData open_client;
static sceSifClientData close_client;
static sceSifClientData connection_client;
static sceSifClientData priority_client;
static sceSifClientData version_client;
static int rpc_buffer[32] __attribute__((aligned(64)));

static void debug_printf(const char *format, ...)
{
}

int sceMtapInit(void)
{
    int i;
    int version;

    sceSifInitRpc(0);
    while (1) {
        if (sceSifBindRpc(&open_client, MTAP_PORT_OPEN, 0) < 0) {
            debug_printf("libmtap: bind failed\n");
            return 0;
        }
        if (open_client.serve != 0) break;
        i = 0x10000;
        while (i--);
    }
    while (1) {
        if (sceSifBindRpc(&close_client, MTAP_PORT_CLOSE, 0) < 0) {
            debug_printf("libmtap: bind failed\n");
            return 0;
        }
        if (close_client.serve != 0) break;
        i = 0x10000;
        while (i--);
    }
    while (1) {
        if (sceSifBindRpc(&connection_client, MTAP_GET_CONNECTION, 0) < 0) {
            debug_printf("libmtap: bind failed\n");
            return 0;
        }
        if (connection_client.serve != 0) break;
        i = 0x10000;
        while (i--);
    }
    while (1) {
        if (sceSifBindRpc(&priority_client, MTAP_CHANGE_THREAD_PRIORITY, 0) < 0) {
            debug_printf("libmtap: bind failed\n");
            return 0;
        }
        if (priority_client.serve != 0) break;
        i = 0x10000;
        while (i--);
    }
    while (1) {
        if (sceSifBindRpc(&version_client, MTAP_GET_MOD_VERSION, 0) < 0) {
            debug_printf("libmtap: bind failed\n");
            return 0;
        }
        if (version_client.serve != 0) break;
        i = 0x10000;
        while (i--);
    }
    version = sceMtapGetModVersion();
    if (version >> 8 != LIBMTAP_VERSION_MAJOR) {
        scePrintf("libmtap: Module version mismatch ");
        scePrintf("[libmtap.a = %d.%d, mtapman.irx = %d.%d]\n", LIBMTAP_VERSION_MAJOR,
                     LIBMTAP_VERSION_MINOR, version >> 8, version & 0xff);
        return 0;
    }
    return 1;
}

int sceMtapPortOpen(int port)
{
    rpc_buffer[0] = port;
    if (sceSifCallRpc(&open_client, 1, 0, rpc_buffer, sizeof(rpc_buffer), rpc_buffer, sizeof(rpc_buffer), 0, 0) < 0) {
        debug_printf("sceMtapPortOpen: rpc error\n");
        return 0;
    }
    return rpc_buffer[1];
}

int sceMtapPortClose(int port)
{
    rpc_buffer[0] = port;
    if (sceSifCallRpc(&close_client, 1, 0, rpc_buffer, sizeof(rpc_buffer), rpc_buffer, sizeof(rpc_buffer), 0, 0) < 0) {
        debug_printf("sceMtapPortClose: rpc error\n");
        return 0;
    }
    return rpc_buffer[1];
}

int sceMtapGetConnection(int port)
{
    rpc_buffer[0] = port;
    if (sceSifCallRpc(&connection_client, 1, 0, rpc_buffer, sizeof(rpc_buffer), rpc_buffer, sizeof(rpc_buffer), 0,
                     0) < 0) {
        debug_printf("sceMtapGetConnection: rpc error\n");
        return 0;
    }
    return rpc_buffer[1];
}

int sceMtapChangeThreadPriority(int high_priority, int low_priority)
{
    rpc_buffer[0] = high_priority;
    rpc_buffer[1] = low_priority;
    if (sceSifCallRpc(&priority_client, 1, 0, rpc_buffer, sizeof(rpc_buffer), rpc_buffer, sizeof(rpc_buffer), 0, 0)
        < 0) {
        debug_printf("sceMtapChangeThreadPriority: rpc error\n");
        return 0;
    }
    return rpc_buffer[2];
}

int sceMtapGetModVersion(void)
{
    if (sceSifCallRpc(&version_client, 1, 0, rpc_buffer, sizeof(rpc_buffer), rpc_buffer, sizeof(rpc_buffer), 0, 0)
        < 0) {
        debug_printf("sceMtapGetModVersion: rpc error\n");
        return 0;
    }
    return rpc_buffer[0];
}
