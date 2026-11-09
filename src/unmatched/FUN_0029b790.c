int FUN_0029c258(void *obj, int *addr, int *size);
int FUN_0029c2a0(void *obj, int arg);
int FUN_0029c2c0(void *obj);

typedef struct SfdReadHandler {
    char pad[60];
    void (*fn)(void *obj, int addr, int size, int *result);
} SfdReadHandler;

typedef struct SfdReadStream {
    char pad[8188];
    int handler;
} SfdReadStream;

/* matching construct: permuter, reduced by hand: the field read as an int and cast to the handler */
int FUN_0029b790(SfdReadStream *obj, int *out)
{
    int addr;
    int size;
    int result;
    SfdReadHandler *handler;
    int ret;

    *out = 0;
    handler = (SfdReadHandler *)obj->handler;
    if ((ret = FUN_0029c258(obj, &addr, &size)) != 0)
        return ret;
    *out = size;
    handler->fn(obj, addr, size, &result);
    if ((ret = FUN_0029c2a0(obj, result)) != 0)
        return ret;
    FUN_0029c2c0(obj);
    return 0;
}
