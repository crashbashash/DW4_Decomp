struct T { unsigned char lo:7; unsigned char flag:1; };
struct B { char pad[3]; unsigned char sz:5; unsigned char mid:2; unsigned char big:1; char pad2[4]; unsigned int u0:12; unsigned int ext:12; unsigned int u1:8; };
int Gap__Core__igArenaMemoryPool__vfunc_95(int arg0, unsigned char *p) {
    struct B *a0; unsigned int off, v;
    if (p == 0) return -1;
    if (*(unsigned int *)(p - 4) == 0xAAAAAAAF) {
        off = *(unsigned int *)(p - 8);
        if (off < 0x100011) { p = p - off; } else { return -1; }
    }
    a0 = (struct B *)(p - 4);
    if (((struct T *)(p - 1))->flag == 1) { a0 = (struct B *)(p - 12); }
    if (a0 == 0) return -1;
    if (a0->big == 0) { v = a0->sz; } else { v = a0->sz + (a0->ext << 5); }
    return v * 2;
}
