/* Error-callback adapter: reports `msg` through FUN_0029a320, ignoring the context argument. */
extern void FUN_0029a320(const char *msg);

void FUN_00294a40(void *ctx, const char *msg) {
    FUN_0029a320(msg);
}
