typedef struct GsPacketBuffer { char pad0[40]; unsigned int *end; unsigned int pad44; unsigned int *cursor; } GsPacketBuffer;

extern GsPacketBuffer *DAT_00568f04;
extern unsigned int DAT_00490f50, DAT_00490f54, DAT_00490f58, DAT_00490f5c, DAT_00490f60, DAT_00490f68, DAT_00490f70;
extern unsigned int DAT_00569328;
extern int DAT_00568e50;
void FUN_001ee600(void);
void FUN_001eef70(int arg);

void FUN_001f7370(float value) {
    unsigned int *p = DAT_00568f04->cursor;
    p[0] = DAT_00490f50;
    p[1] = DAT_00490f54;
    p[2] = DAT_00490f58;
    p[3] = DAT_00490f5c;
    p[4] = DAT_00490f60;
    p[5] = DAT_00490f70;
    p[6] = 0xFCFCFCFC;
    p[7] = DAT_00569328;
    p[8] = DAT_00490f68;
    ((float *)p)[9] = value;
    p[10] = DAT_00569328;
    p[11] = DAT_00569328;
    DAT_00568f04->cursor = p + 12;
    if (DAT_00568f04->cursor >= DAT_00568f04->end) {
        if (DAT_00568e50 != 0) {
            FUN_001ee600();
        } else {
            FUN_001eef70(1);
        }
    }
}
