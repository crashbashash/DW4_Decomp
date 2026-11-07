extern "C" int igMemoryRefMetaField_WriteRawFieldMem(void *, void *, void *, int, int);
extern "C" int igMemoryRefArrayMetaField_WriteRawFieldMem(void *, void *, void *, int, int);

int igMemoryRefArrayMetaField_WriteRawFieldMem(void *arg0, void *arg1, void *arg2, int arg3, int arg4) {
    void ** src;
    char * off;
    char * start;
    int i;
    src = (void **)arg1; off = (char *)arg2; start = off;
    for (i = 0; i < *(int *)((char *)(arg0) + 80); i++) {
        off += igMemoryRefMetaField_WriteRawFieldMem(arg0, src, off, arg3, arg4);
        src++;
    }
    return ((off - start) + 3) & ~3;
}
