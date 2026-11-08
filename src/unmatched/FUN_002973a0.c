void FUN_0029b1e8(int stream, int *out);

int FUN_002973a0(char *ply) {
    int value[4];
    int stream;

    stream = *(int *)(ply + 68);
    if (stream == 0) {
        return 0;
    }
    FUN_0029b1e8(stream, value);
    return value[0];
}
