int FUN_00297aa8(void);
void *FUN_00297b18(void *obj);
int FUN_00297b88(void *value);

struct Src00297a30 {
    int f0, f4, f8, f12, f16;
    void *f20, *f24;
};

struct Info00297a30 {
    int f0;
    void *f4;
    int f8, f12, f16, f20, f24;
};

void FUN_00297a30(char *obj, char *out) {
    struct Info00297a30 *dst = (struct Info00297a30 *)(out + 96);
    struct Src00297a30 *src;

    dst->f0 = FUN_00297aa8();
    src = (struct Src00297a30 *)(obj + 140);
    dst->f4 = FUN_00297b18(obj);
    dst->f8 = src->f8;
    dst->f12 = src->f12;
    dst->f16 = src->f16;
    dst->f20 = FUN_00297b88(src->f20);
    dst->f24 = FUN_00297b88(src->f24);
}
