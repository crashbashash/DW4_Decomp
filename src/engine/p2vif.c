/* What the VIF1 row and mask registers hold, so a draw writes STROW or STMASK only when its values
 * differ. p2InitVifRegisters loads both at start-up. */

extern float p2VifRowScale;
extern int p2VifMask;

void p2SetVifRowScale(float scale) {
    p2VifRowScale = scale;
}

float p2GetVifRowScale(void) {
    return p2VifRowScale;
}

void p2SetVifMask(int mask) {
    p2VifMask = mask;
}

int p2GetVifMask(void) {
    return p2VifMask;
}
