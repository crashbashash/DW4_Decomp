typedef struct {
    char pad[44];
    void (*callback)(void *ctx, int arg);
    void *ctx;
} Handler;
extern Handler *mwsfd_GetWork(void);

void FUN_00293670(int arg) {
    Handler *h = mwsfd_GetWork();
    h->callback(h->ctx, arg);
}
