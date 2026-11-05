typedef struct {
    char pad[44];
    void (*callback)(void *ctx, int arg);
    void *ctx;
} Handler;
extern Handler *FUN_00294a30(void);

void FUN_00293670(int arg) {
    Handler *h = FUN_00294a30();
    h->callback(h->ctx, arg);
}
