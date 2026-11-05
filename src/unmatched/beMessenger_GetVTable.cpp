/* C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
union U { int vt; char b[64]; };
extern "C" {
int FUN_00231030(char *, int);
int FUN_00357a90(char *, int);
int FUN_00357b10(char *, int);
int FUN_00357b90(char *, int);
int FUN_00357c10(char *, int);
int FUN_00357c90(char *, int);
int igObject_InitHeader(char *);
extern int DAT_0053ab70[4];
extern void * DAT_00586dc8[4];
int beMessenger_GetVTable(void);
}
int beMessenger_GetVTable(void) {
    union U u;
    int r;
    int *v1;
    int *a1;
    int v0;

    igObject_InitHeader(u.b);
    *(int *)&u.b[8] = 0;
    u.vt = (int)&DAT_0053ab70[0];
    *(int *)&u.b[16] = 0;
    *(int *)&u.b[20] = 0;
    *(int *)&u.b[24] = 0;
    *(int *)&u.b[28] = 0;
    *(int *)&u.b[32] = 0;
    r = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.vt = (int)&DAT_0053ab70[0];
    FUN_00357c90(&u.b[32], -1);
    FUN_00357c10(&u.b[28], -1);
    FUN_00357b90(&u.b[24], -1);
    FUN_00357b10(&u.b[20], -1);
    FUN_00357a90(&u.b[16], -1);
    FUN_00231030(u.b, 0);
    return r;
}
