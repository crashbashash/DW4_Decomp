extern unsigned int DAT_00481d00[];
void FUN_00107f00(char *d, int *pic, void *a, void *b, void *c);
int FUN_00107ba8(char *d, int *pic);
void FUN_00107c48(char *d, int *pic);
void FUN_00107ed8(char *d);
void FUN_00108a40(char *d, int *pic);
void _outputFrame(char *d, int *pic) {
    char *o;

    o = *(char **)(d + 2160);
    FUN_00107f00(d, pic, o + 16, o + 24, o + 32);
    o = *(char **)(d + 2160);
    *(int *)(d + 152) = *(int *)(o + 16);
    *(unsigned long long *)(d + 160) = DAT_00481d00[(int)(*(long long *)(o + 32) >> 5) & 0xF];
    *(int *)(d + 228) = pic[23];
    *(int *)(d + 232) = pic[24];
    *(int *)(d + 204) = pic[17];
    *(int *)(d + 208) = pic[18];
    *(int *)(d + 212) = pic[19];
    *(int *)(d + 216) = pic[20];
    *(int *)(d + 220) = pic[21];
    *(int *)(d + 224) = pic[22];
    if (FUN_00107ba8(d, pic) && pic[10] == 1) {
        if (*(int *)(d + 200)) {
            FUN_00108a40(d, pic);
        } else {
            FUN_00107c48(d, pic);
        }
        FUN_00107ed8(d);
    }
}
