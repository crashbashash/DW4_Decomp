int memset();

typedef struct {
    char pad0[8];
    unsigned long long f8;
    char pad16[28 - 16];
    int f28;
    char *f32;
    int f36;
} Buffer;

void FUN_002754c0(Buffer *b)
{
    unsigned long long end;
    int n;

    end = ((unsigned long long)b->f28 + b->f36) << 11;
    if (b->f8 < end) {
        n = end - b->f8;
        memset(b->f32 + (b->f36 << 11) - n, 0, n);
    }
}
