typedef struct O { int w0; int ref; } O;
typedef struct L { char pad0[8]; int cnt; int pad12; O **data; } L;
int igObject_Destroy();
void Gap__Sg__igCompileTraversal__vfunc_31(char *p) {
int i1,i2,i3,j1,j2,j3,n1,n2,n3,m1,m2,m3; L *l1,*l2,*l3;
    l1 = *(L**)(p+472); n1 = l1->cnt;
    for (i1 = 0; i1 < n1; i1++) { O *o = l1->data[i1]; if (o) { o->ref = o->ref - 1; if (((unsigned long long) ((long long) o->ref << 0x29) >> 0x29) == 0) igObject_Destroy(o); } }
    m1 = l1->cnt; for (j1 = 0; j1 < m1; j1++) l1->data[j1] = 0;
    l1->cnt = 0;
    l2 = *(L**)(p+476); n2 = l2->cnt;
    for (i2 = 0; i2 < n2; i2++) { O *o = l2->data[i2]; if (o) { o->ref = o->ref - 1; if (((unsigned long long) ((long long) o->ref << 0x29) >> 0x29) == 0) igObject_Destroy(o); } }
    m2 = l2->cnt; for (j2 = 0; j2 < m2; j2++) l2->data[j2] = 0;
    l2->cnt = 0;
    *(int*)(*(char**)(p+492)+8) = 0;
    l3 = *(L**)(p+504); n3 = l3->cnt;
    for (i3 = 0; i3 < n3; i3++) { O *o = l3->data[i3]; if (o) { o->ref = o->ref - 1; if (((unsigned long long) ((long long) o->ref << 0x29) >> 0x29) == 0) igObject_Destroy(o); } }
    m3 = l3->cnt; for (j3 = 0; j3 < m3; j3++) l3->data[j3] = 0;
    l3->cnt = 0;
    p[484] = 0; p[496] = 0;
}
