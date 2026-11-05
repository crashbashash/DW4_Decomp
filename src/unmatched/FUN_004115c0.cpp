/* 0x004115c0 - FUN_004115c0. Sibling of FUN_0043a950 (name table at 0x4cf6a0, vector -83/148); alternate compiler -O3,p. */
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
typedef struct Tbl { const char *s[12]; } __attribute__((aligned(16))) Tbl;
extern Tbl DAT_004cf6a0;
extern char DAT_00519a90[], DAT_00519d88[], DAT_00519b70[], DAT_00519a58[], DAT_00519c80[];
void beMessenger_SendNamed(int, char *, char *, int, char *);
int beMessenger_GetBool(int, int);
void beMessenger_SelectReceivers(int, char *, char *, int);
void beMessenger_AppendString(int, const char *);
void beMessenger_AppendVec3(int, float *);
void beMessenger_DispatchSelected(int, char *);
void FUN_004115c0(int *arg0, int arg1) {
    Tbl sp30;
    float v[3];
    if (arg1 > -1) {
        sp30 = DAT_004cf6a0;
        beMessenger_SendNamed(arg0[3], DAT_00519a90, DAT_00519d88, 0, DAT_00519b70);
        if (beMessenger_GetBool(arg0[3], 0) != 0) {
            beMessenger_SendNamed(arg0[3], DAT_00519a90, DAT_00519d88, 0, (char *)sp30.s[arg1]);
            return;
        }
        beMessenger_SelectReceivers(arg0[3], DAT_00519a90, DAT_00519d88, 0);
        beMessenger_AppendString(arg0[3], sp30.s[arg1]);
        v[2] = 0;
        v[0] = -83.0f;
        v[1] = 148.0f;
        beMessenger_AppendVec3(arg0[3], v);
        beMessenger_DispatchSelected(arg0[3], DAT_00519c80);
        return;
    }
    beMessenger_SendNamed(arg0[3], DAT_00519a90, DAT_00519d88, 0, DAT_00519b70);
    if (beMessenger_GetBool(arg0[3], 0) != 0) {
        beMessenger_SendNamed(arg0[3], DAT_00519a90, DAT_00519d88, 0, DAT_00519a58);
    }
}
} /* extern "C" */
