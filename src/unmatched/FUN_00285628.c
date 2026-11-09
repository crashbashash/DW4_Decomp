typedef struct SofdecCallback {
    int (*fn)(void *arg);
    void *arg;
    int enabled;
} SofdecCallback;

int FUN_00285628(SofdecCallback *cb, int enabled) {
    cb->enabled = enabled;
    if (enabled != 0) {
        enabled = (int)cb->fn;
        if (enabled != 0) {
            enabled = cb->fn(cb->arg);
        }
    }
    return enabled;
}
