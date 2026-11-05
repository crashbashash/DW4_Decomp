int igObject_Destroy();
int igObject_InitHeader();
union U { int vt; int w[12]; void *p[12]; char b[48]; };
struct Rc { int vt; int rc; };
extern int DAT_0052a5a0[4];
extern void * DAT_00586dc8[4];
int igCompiledTransform_GetVTable(void) {
    union U u;
    int temp_s1;
    void **q1;
    void **q2;
    struct Rc *temp_a0;
    struct Rc *temp_a0_2;

    igObject_InitHeader(u.b);
    q1 = &u.p[3];
    q2 = &u.p[6];
    u.w[0] = (int)(&DAT_0052a5a0[0]);
    *q1 = 0;
    *q2 = 0;
    temp_s1 = *(int *)&u.b[*(int *)((char *)(DAT_00586dc8[0]) + 916)];
    u.w[0] = (int)(&DAT_0052a5a0[0]);
    if (q2 != 0) {
        temp_a0 = (struct Rc *)*q2;
        if (temp_a0 != 0) {
            temp_a0->rc = temp_a0->rc - 1;
            if ((temp_a0->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0);
            }
        }
    }
    if (q1 != 0) {
        temp_a0_2 = (struct Rc *)*q1;
        if (temp_a0_2 != 0) {
            temp_a0_2->rc = temp_a0_2->rc - 1;
            if ((temp_a0_2->rc & 0x7FFFFF) == 0) {
                igObject_Destroy(temp_a0_2);
            }
        }
    }
    return temp_s1;
}
