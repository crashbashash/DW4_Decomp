int FUN_002eb010();
int StringChunk_ReleaseHeader();
int StringPool_Construct();
char *StringPool_Intern();
int igStringMetaField_AssignRetainedToken();
extern int DAT_00586f20[4];
void igStringMetaField_ResetValue(int *arg0, int arg1) {
    char *tok;
    char *t;
    int *h;
    int v;
    int s0 = *(int *)arg0[8];
    int p;
    if (s0 == 0) {
        t = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            p = FUN_002eb010(16);
            if (p != 0) {
                p = StringPool_Construct(p);
            }
            DAT_00586f20[0] = p;
        }
        t = StringPool_Intern(DAT_00586f20[0], s0);
    }
    tok = t;
    igStringMetaField_AssignRetainedToken(arg0, arg1, &tok);
    if (tok != 0) {
        h = (int *)(tok - 8);
        v = h[1] - 1;
        h[1] = v;
        if (v == 0) {
            StringChunk_ReleaseHeader(*h, h);
        }
    }
}
