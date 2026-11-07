int FUN_00276ce8();
int FUN_00276d18();

void FUN_0026b188(void *arg0) {
    if (arg0 != 0) {
        FUN_00276ce8(*(int *)((char *)(arg0) + 4));
        FUN_00276d18(*(int *)((char *)(arg0) + 0));
        return;
    }
    FUN_00276ce8();
    FUN_00276d18(0);
}
