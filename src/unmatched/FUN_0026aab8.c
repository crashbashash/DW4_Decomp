/* Stores cvFsGetFileSize(object) in *out and returns 1. */
int cvFsGetFileSize(void *object);

int FUN_0026aab8(void *object, int *out) {
    *out = cvFsGetFileSize(object);
    return 1;
}
