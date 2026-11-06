struct Node { int f0; struct Node *next; };
int memset();
int FUN_002468a0();
int Memory_AllocateDefaultBuffer();
int Memory_FreeBufferAliasA();
extern unsigned int DAT_00498718[4];
extern unsigned int DAT_00498720[4];
extern unsigned int DAT_0056df60[4];
extern struct Node **DAT_0056df68[4];
extern int DAT_0056df70[4];
void FUN_002468e0(void) {
    unsigned int s0;
    unsigned int s3;
    unsigned int s2;
    unsigned int a0;
    struct Node *n;
    struct Node *s4;
    struct Node **s1;
    if (DAT_0056df68[0] == 0) {
        DAT_0056df68[0] = (struct Node **)Memory_AllocateDefaultBuffer(DAT_00498720[0] * 4);
        memset(DAT_0056df68[0], 0, DAT_00498720[0] * 4);
        return;
    }
    if (DAT_0056df70[0] == 0) {
        if (DAT_0056df60[0] == 0) {
            Memory_FreeBufferAliasA(DAT_0056df68[0], DAT_0056df60[0]);
            DAT_0056df68[0] = 0;
            DAT_00498720[0] = 0x10;
            return;
        }
        a0 = DAT_00498718[0];
        s3 = a0;
        if (DAT_00498720[0] < DAT_0056df60[0]) {
            s3 = a0 + 1;
        } else if (DAT_0056df60[0] < (DAT_00498720[0] >> 1) && a0 > 4) {
            s3 = a0 - 1;
        }
        if (s3 != a0) {
            s2 = 1 << s3;
            s0 = s2 * 4;
            s1 = (struct Node **)Memory_AllocateDefaultBuffer(s0);
            memset(s1, 0, s0);
            for (s0 = 0; s0 < DAT_00498720[0]; s0++) {
                for (n = DAT_0056df68[0][s0]; n != 0; n = s4) {
                    s4 = n->next;
                    FUN_002468a0(n, s1, s2, s3);
                }
            }
            DAT_00498720[0] = s2;
            DAT_00498718[0] = s3;
            Memory_FreeBufferAliasA(DAT_0056df68[0]);
            DAT_0056df68[0] = s1;
        }
    }
}
