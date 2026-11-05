/* C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
struct F { int *vt; char pad[4]; int *str; char pad2[68]; };
extern "C" {
void StringChunk_ReleaseHeader(int, int *);
int igObject_InitHeader(struct F *);
extern int DAT_00524950[4];
extern int DAT_0053d120[4];
extern char *DAT_00586dc8[4];
int beNDMWLoadIntf2Diffselect_GetVTable(void);
}
int beNDMWLoadIntf2Diffselect_GetVTable(void) {
    struct F o;
    int r;
    int *s;
    int *h;
    int c;

    igObject_InitHeader(&o);
    o.vt = DAT_00524950;
    o.str = 0;
    o.vt = DAT_0053d120;
    r = *(int *)((char *)&o + *(int *)(DAT_00586dc8[0] + 916));
    o.vt = DAT_00524950;
    if (&o.str != 0) {
        s = o.str;
        if (s != 0) {
            h = s - 2;
            c = s[-1] - 1;
            s[-1] = c;
            if (c == 0) StringChunk_ReleaseHeader(*h, h);
        }
    }
    return r;
}
