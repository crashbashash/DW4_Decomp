/* stack-object GetVTable accessor without vtable store.py. */
int igObject_InitHeader(void *);
extern void * DAT_00586dc8[4];
int igObject_GetVTable(void) {
    int o[2];

    igObject_InitHeader(o);
    return *(int *)((char *)o + *(int *)((char *)(DAT_00586dc8[0]) + 916));
}
