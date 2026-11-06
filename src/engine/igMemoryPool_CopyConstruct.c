int igObject_CopyConstructHeader();
extern int DAT_0052f620[4];
int **igMemoryPool_CopyConstruct(int **arg0) {
    igObject_CopyConstructHeader();
    *arg0 = &DAT_0052f620[0];
    return arg0;
}
