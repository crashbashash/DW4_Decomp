typedef struct SofdecCallback {
    int (*fn)(void *arg);
    void *arg;
    int enabled;
} SofdecCallback;

int m2verr_SetCodeSub(SofdecCallback *cb, int enabled) {
    cb->enabled = enabled;
    if (enabled != 0) {
        enabled = (int)cb->fn;
        if (enabled != 0) {
            enabled = cb->fn(cb->arg);
        }
    }
    return enabled;
}
