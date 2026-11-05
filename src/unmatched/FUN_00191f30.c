/* 0x00191f30 - FUN_00191f30. normalise 4x4 rows by 1/len; sign bit cleared through a byte bitfield union, byte-offset loop indexing; alternate compiler -O3 */
typedef union U { float f; struct { unsigned char p0, p1, p2; unsigned char lo : 7; unsigned char sign : 1; } b; } U;
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
int FUN_00192030(int, int, float *);
float FUN_00192290(int);
void FUN_00191f30(int *arg0, float *arg1, int arg2) {
    float tmp[16];
    U u;
    float len;
    int i, j;
    FUN_00192030((int)arg1, arg2, tmp);
    len = FUN_00192290(arg2);
    u.f = len;
    u.b.sign = 0;
    if (u.f < 1.1754944e-38f) {
        *arg0 = DAT_004fb418[0];
    } else {
        float inv = 1.0f / len;
        i = 0;
        do {
            int off = i * 0x10;
            j = 0;
            do {
                int jo = j * 4;
                float *sv = (float *)((char *)tmp + off + jo);
                j++;
                *(float *)((char *)arg1 + off + jo) = inv * *sv;
            } while (j < 4);
            i++;
        } while (i < 4);
        *arg0 = DAT_004fb410[0];
    }
}
