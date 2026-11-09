typedef struct PTMF {
    int this_delta;
    int vtbl_offset;
    union {
        void *func_addr;
        int ventry_offset;
    } func_data;
} PTMF;

asm void __ptmf_scall(...)
{
    lw      at, PTMF.this_delta(t9)
    lw      t8, PTMF.vtbl_offset(t9)
    lw      t9, PTMF.func_data(t9)
    bltz    t8, L1
    addu    a0, a0, at
    addu    t9, a0, t9
    lw      t9, 0(t9)
    nop
    addu    t9, t9, t8
    lw      t9, 0(t9)
    nop
L1:
    jr      t9
    nop
}
