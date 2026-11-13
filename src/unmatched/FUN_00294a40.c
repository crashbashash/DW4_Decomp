/* Error-callback adapter: reports `msg` through mwsfd_Error, ignoring the context argument. */
extern void mwsfd_Error(const char *msg);

void FUN_00294a40(void *ctx, const char *msg) {
    mwsfd_Error(msg);
}
