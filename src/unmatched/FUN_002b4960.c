typedef struct GammaTblObj {
    char pad[64];
    float scale;
} GammaTblObj;

int FUN_002b4b98(void);

void FUN_002b4960(GammaTblObj *obj, unsigned int *src, unsigned int *dst)
{
    float scale = obj->scale;
    int i;
    unsigned int v;

    if (FUN_002b4b98() == 1) {
        for (i = 0; i < 256; i++)
            dst[i] = (src[i] & 0x7FFFFF80) * 2;
        return;
    }
    for (i = 0; i < 256; i++) {
        if (src[i] == 0)
            src[i] = 1;
        v = src[i];
        dst[i] = 16777215.0f / (scale * v / 2147483520.0f);
    }
}
