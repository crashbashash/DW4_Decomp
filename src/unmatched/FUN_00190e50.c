/* 0x00190e50 — FUN_00190e50. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00190f50();
extern float DAT_004e1058[4];
extern float DAT_004e105c[4];
extern float DAT_004e1060[4];
extern float DAT_004e11c0[4];
extern float DAT_004e11c4[4];
extern float DAT_004e11c8[4];
extern float DAT_004e11cc[4];
void FUN_00190e50(void *arg0) {
    FUN_00190f50();
    *(float *)((char *)(arg0) + 48) = (float) DAT_004e11c0[0];
    *(float *)((char *)(arg0) + 52) = (float) DAT_004e11c4[0];
    *(float *)((char *)(arg0) + 56) = (float) DAT_004e11c8[0];
    *(float *)((char *)(arg0) + 60) = (float) DAT_004e11cc[0];
    *(float *)((char *)(arg0) + 12) = (float) DAT_004e1058[0];
    *(float *)((char *)(arg0) + 28) = (float) DAT_004e105c[0];
    *(float *)((char *)(arg0) + 44) = (float) DAT_004e1060[0];
}
