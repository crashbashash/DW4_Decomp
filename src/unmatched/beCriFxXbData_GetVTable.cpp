/* 0x00367040 - beCriFxXbData_GetVTable. temporary stack object as a union (byte index folds into the load), alternate compiler -O3 Verified byte-identical by tools/verify.py.
 * C++ translation unit (tools/initfields_gen.py): the unit compiled with exceptions on and retail keeps this function's exception index record, which only the C++ front end emits. */
union U { int vt; int w[16]; void *p[16]; char b[64]; };
extern "C" {
int igObject_InitHeader(char *);
extern int DAT_00534e90[4];
extern void * DAT_00586dc8[4];
int beCriFxXbData_GetVTable(void);
}
int beCriFxXbData_GetVTable(void) {
    union U u;

    igObject_InitHeader(u.b);
    u.w[0] = (int)(&DAT_00534e90[0]);
    return *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
}
