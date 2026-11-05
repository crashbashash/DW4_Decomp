extern int **DAT_00586f58[4];
extern int **DAT_00586f60[4];
int igAllocator_ResolveEncodedIndex(int arg0) {
    if (arg0 & 1) {
        return (*DAT_00586f60[0])[arg0 >> 1];
    }
    return (*DAT_00586f58[0])[arg0 >> 1];
}
