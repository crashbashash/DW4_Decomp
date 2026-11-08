void FUN_002979d8(void *plane, int addr, int width, int height);
void FUN_00293f60(int addr, int width, int height, int *out);

void FUN_00297910(int *src, char *dst) {
    int out[6];
    int width = src[2];
    int height = src[3];
    int mode = src[1];

    *(int *)(dst + 68) = width;
    *(int *)(dst + 72) = height;
    if (mode != 3) {
        FUN_002979d8(dst + 4, src[0], width, height);
        return;
    }
    FUN_00293f60(src[0], width, height, out);
    FUN_002979d8(dst + 4, out[0], out[3], height);
    FUN_002979d8(dst + 20, out[1], out[4], height);
    FUN_002979d8(dst + 36, out[2], out[5], height);
}
