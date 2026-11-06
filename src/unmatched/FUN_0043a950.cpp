extern "C" {
typedef struct Tbl { const char *s[12]; } __attribute__((aligned(16))) Tbl;
extern Tbl DAT_004cfa70;
extern char DAT_0051b308[], DAT_0051b7c8[], DAT_0051b7d8[], DAT_0051b620[], DAT_0051b7e0[];
void beMessenger_SendNamed(int, char *, char *, int, char *);
int beMessenger_GetBool(int, int);
void beMessenger_SelectReceivers(int, char *, char *, int);
void beMessenger_AppendString(int, const char *);
void beMessenger_AppendVec3(int, float *);
void beMessenger_DispatchSelected(int, char *);
void FUN_0043a950(int *arg0, int arg1) {
    Tbl sp30;
    float v[3];
    if (arg1 > -1) {
        sp30 = DAT_004cfa70;
        beMessenger_SendNamed(arg0[3], DAT_0051b308, DAT_0051b7c8, 0, DAT_0051b7d8);
        if (beMessenger_GetBool(arg0[3], 0) != 0) {
            beMessenger_SendNamed(arg0[3], DAT_0051b308, DAT_0051b7c8, 0, (char *)sp30.s[arg1]);
            return;
        }
        beMessenger_SelectReceivers(arg0[3], DAT_0051b308, DAT_0051b7c8, 0);
        beMessenger_AppendString(arg0[3], sp30.s[arg1]);
        v[2] = 0;
        v[0] = -121.0f;
        v[1] = 128.0f;
        beMessenger_AppendVec3(arg0[3], v);
        beMessenger_DispatchSelected(arg0[3], DAT_0051b7e0);
        return;
    }
    beMessenger_SendNamed(arg0[3], DAT_0051b308, DAT_0051b7c8, 0, DAT_0051b7d8);
    if (beMessenger_GetBool(arg0[3], 0) != 0) {
        beMessenger_SendNamed(arg0[3], DAT_0051b308, DAT_0051b7c8, 0, DAT_0051b620);
    }
}
}
