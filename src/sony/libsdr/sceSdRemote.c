typedef char *ArgList;
#define ARGS_START(args, last) ((args) = (ArgList)__builtin_next_arg(last) - (8 - __builtin_args_info(0)) * 8)
#define ARGS_NEXT(args, type) ((args) += 8, *(type *)((args) - 8))
typedef void (*RpcEnd)(void *);
typedef struct {
    unsigned short func;
    unsigned short entry;
    unsigned int value;
} SdBatch;
typedef struct {
    int words[10];
} RpcClient;
int sceSifCallRpc(RpcClient *client, unsigned int command, unsigned int mode, void *send, int sendSize, void *recv,
                 int recvSize, RpcEnd end, void *endArg);
extern unsigned int DAT_0055d540[];
extern RpcClient DAT_0055d580;
extern RpcEnd DAT_00485140;
extern void *DAT_00485144;
extern void *DAT_00485158, *DAT_0048515c, *DAT_00485160;
extern void *DAT_00485164, *DAT_00485168, *DAT_0048516c;
extern void *DAT_00485170, *DAT_00485174, *DAT_00485178;
static inline void *currentGp(void) {
    void *gp;
    __asm__ volatile("move %0,$28" : "=r"(gp));
    return gp;
}
static inline void *swapGp(void *gp) {
    void *old;
    __asm__ volatile("move %0,$28; move $28,%1" : "=&r"(old) : "r"(gp));
    return old;
}
int sceSdRemote(int block, ...) {
    int ret, i;
    unsigned int mode, command;
    ArgList args;
    RpcEnd end = 0;
    int previous;
    void *gp = 0;

    ARGS_START(args, block);
    mode = block;
    command = ARGS_NEXT(args, int);
    DAT_0055d540[0] = (int)DAT_0055d540;
    for (i = 1; i < 7; i++) {
        DAT_0055d540[i] = ARGS_NEXT(args, int);
    }
    if (mode == 0) {
        mode = 1;
        end = DAT_00485140;
    } else {
        mode = 0;
    }
    previous = 0;
    if (command == 0x8160) {
        if (DAT_0055d540[1] == 0) {
            previous = (int)DAT_00485158;
            DAT_00485158 = (void *)DAT_0055d540[2];
            DAT_00485164 = (void *)DAT_0055d540[3];
            DAT_00485170 = currentGp();
        } else {
            previous = (int)DAT_0048515c;
            DAT_0048515c = (void *)DAT_0055d540[2];
            DAT_00485168 = (void *)DAT_0055d540[3];
            DAT_00485174 = currentGp();
        }
    } else if (command == 0x8170) {
        previous = (int)DAT_00485160;
        DAT_00485160 = (void *)DAT_0055d540[1];
        DAT_0048516c = (void *)DAT_0055d540[2];
        DAT_00485178 = currentGp();
    }
    ret = 0;
    if (command == 0x8130 || command == 0x81a0 || command == 0x81b0) {
        if (end != 0) gp = swapGp(DAT_00485144);
        sceSifCallRpc(&DAT_0055d580, command | DAT_0055d540[1], mode, (void *)DAT_0055d540[2], 64, DAT_0055d540, 64,
                     end, (void *)DAT_0055d540[0]);
        if (end != 0) (void)swapGp(gp);
        ret = DAT_0055d540[0];
    } else if (command == 0x8140) {
        if (end != 0) gp = swapGp(DAT_00485144);
        sceSifCallRpc(&DAT_0055d580, command | DAT_0055d540[1], mode, &DAT_0055d540[0], 64, (void *)DAT_0055d540[2],
                     64, end, (void *)DAT_0055d540[2]);
        if (end != 0) (void)swapGp(gp);
    } else if (command == 0x81c0 || command == 0x81d0) {
        SdBatch *batch;
        unsigned int results;
        int resultsSize;

        batch = (SdBatch *)DAT_0055d540[1];
        batch[0].entry = DAT_0055d540[2];
        if (command == 0x81d0) {
            batch[0].value = DAT_0055d540[5];
        }
        results = DAT_0055d540[3];
        resultsSize = DAT_0055d540[4];
        if (DAT_0055d540[3] == 0) {
            results = (unsigned int)&ret;
            resultsSize = 4;
        }
        if (end != 0) gp = swapGp(DAT_00485144);
        sceSifCallRpc(&DAT_0055d580, command, mode, (void *)DAT_0055d540[1],
                     (int)(sizeof(SdBatch) * (DAT_0055d540[2] + 1)), (void *)results, resultsSize, end,
                     (void *)DAT_0055d540);
        if (end != 0) (void)swapGp(gp);
        if (DAT_0055d540[3] != 0) {
            ret = (int)*(unsigned int *)DAT_0055d540[3];
        }
    } else if (command >= 0x9000 && command <= 0x90f0) {
        if (end != 0) gp = swapGp(DAT_00485144);
        sceSifCallRpc(&DAT_0055d580, command, mode, (void *)DAT_0055d540[1], (int)DAT_0055d540[2], &DAT_0055d540[0], 16,
                     end, &DAT_0055d540[0]);
        if (end != 0) (void)swapGp(gp);
        ret = DAT_0055d540[0];
    } else {
        if (end != 0) gp = swapGp(DAT_00485144);
        sceSifCallRpc(&DAT_0055d580, command, mode, &DAT_0055d540[0], 64, &DAT_0055d540[0], 16, end, &DAT_0055d540[0]);
        if (end != 0) (void)swapGp(gp);
        ret = DAT_0055d540[0];
    }
    switch (command) {
    case 0x8160:
    case 0x8170:
        ret = previous;
        break;
    }
    return ret;
}
