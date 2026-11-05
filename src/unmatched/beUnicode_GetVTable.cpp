/* 0x00340f80 - beUnicode_GetVTable. temporary stack object as a union (byte index folds into the load), alternate compiler -O3 Verified byte-identical by tools/verify.py.
 * C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
union U { int vt; int w[2]; void *p[2]; char b[8]; };
extern "C" {
int igObject_InitHeader(char *);
extern int DAT_00539870[4];
extern void * DAT_00586dc8[4];
int beUnicode_GetVTable(void);
}
int beUnicode_GetVTable(void) {
    union U u;

    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_00539870[0]);
    return *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
}
