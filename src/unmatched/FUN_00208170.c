extern int DAT_00491478[4];
extern int DAT_00562c70[4];
extern int DAT_00569330[4];
extern long long DAT_0056b020[4];
extern int DAT_0056c020[4];
void FUN_00208170(int arg0) {
    int idx;
    long long v;
    int bits;
    long long b64;

    idx = DAT_00569330[0] * 4;
    *(int *)((char *)DAT_0056c020 + idx) = arg0;
    v = DAT_0056b020[0] & ~((long long)0xF << idx);
    DAT_0056b020[0] = v;
    bits = ((arg0 * 2) | ((*(unsigned int *)((char *)DAT_00562c70 + idx) >> 0xA) & 1)) & 0xF;
    DAT_00491478[0] |= 0x111;
    b64 = bits;
    DAT_0056b020[0] = v | (b64 << idx);
}
