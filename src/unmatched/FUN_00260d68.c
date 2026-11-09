int FUN_00260de8(void *handle);
int FUN_002612c0(void *handle);
void FUN_002651e8(void);
void FUN_00260cd0(void);

int FUN_00260d68(void *handle) {
    int result = FUN_00260de8(handle);
    int status;
    if (result < 0) {
        return result;
    }
    for (;;) {
        status = FUN_002612c0(handle);
        if (status == 3) {
            result = 0;
            break;
        }
        if (status == 4) {
            result = -1;
            break;
        }
        FUN_002651e8();
        FUN_00260cd0();
    }
    return result;
}
