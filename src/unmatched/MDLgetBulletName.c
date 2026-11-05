extern int DAT_004c873c[4];
extern unsigned int DAT_0058a1fc[4];
int MDLgetBulletName(void) {
    return DAT_004c873c[(int) DAT_0058a1fc[0] / 10000];
}
