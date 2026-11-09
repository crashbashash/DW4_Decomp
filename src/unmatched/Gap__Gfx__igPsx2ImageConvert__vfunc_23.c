typedef void (*ConvertFunc)(void);

void FUN_0015aaf0(void);
void FUN_0015ab90(void);
void FUN_0016f700(void);
void FUN_0016f780(void);
void FUN_0016f7f0(void);
void FUN_0016f9b0(void);
void DAT_0016fa60(void);
void FUN_0016fae0(void);
void FUN_0016fb60(void);
void DAT_0016fbd0(void);

ConvertFunc Gap__Gfx__igPsx2ImageConvert__vfunc_23(void *self, int srcFormat, int dstFormat, int flag)
{
    switch (dstFormat) {
    case 0x2:
        return flag ? FUN_0016fb60 : DAT_0016fbd0;
    case 0x8:
        return flag ? FUN_0016f700 : DAT_0016fa60;
    case 0xA:
        return flag ? FUN_0016f780 : FUN_0016f9b0;
    case 0x9:
        return flag ? FUN_0016f7f0 : FUN_0016fae0;
    case 0x10001:
        return flag ? FUN_0015ab90 : FUN_0015aaf0;
    default:
        return 0;
    }
}
