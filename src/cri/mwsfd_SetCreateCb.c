/* Called with each new player handle and the scratchpad-save flag. */
typedef void (*MwsfdCreateCb)(void *ply, int sprSave);

extern MwsfdCreateCb mwsfd_create_cb;

void mwsfd_SetCreateCb(MwsfdCreateCb fn) {
    mwsfd_create_cb = fn;
}
