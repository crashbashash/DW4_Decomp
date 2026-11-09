typedef struct UsrTextInfo {
    int f0;
    int f4;
    int second;
    int first;
    int f16[4];
} UsrTextInfo;

typedef struct UsrTextText {
    char buf[2][176];
    int len[2];
} UsrTextText;

typedef struct UsrTextSlot {
    int busy;
    char pad4[44];
    UsrTextText text;
} UsrTextSlot;

void FUN_0028b0c0(void *dst, void *src, int n);
void FUN_0028d5c0(int src, UsrTextInfo *info);
UsrTextSlot *FUN_002a2ed0(int obj);

void FUN_002a29d8(int obj, int src, void *data, int n)
{
    UsrTextSlot *slot;
    UsrTextText *text;
    void *dst;
    UsrTextInfo info;
    int len;

    slot = FUN_002a2ed0(obj);
    if (slot == 0 || slot->busy != 0)
        return;
    FUN_0028d5c0(src, &info);
    len = n > 176 ? 176 : n;
    text = &slot->text;
    if (info.first > 0) {
        text->len[0] = len;
        dst = text->buf[0];
    } else if (info.second > 0) {
        text->len[1] = len;
        dst = text->buf[1];
    } else
        return;
    FUN_0028b0c0(dst, data, len);
}
