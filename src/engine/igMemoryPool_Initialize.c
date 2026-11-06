int igObject_InitHeader();
extern int DAT_0052f620[4];
int **igMemoryPool_Initialize(int **arg0) {
    igObject_InitHeader();
    *arg0 = &DAT_0052f620[0];
    return arg0;
}
