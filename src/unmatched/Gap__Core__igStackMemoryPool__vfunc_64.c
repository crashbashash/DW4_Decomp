typedef struct Stack { char pad[116]; unsigned base; char pad2[12]; unsigned top; unsigned *end; } Stack;
void Gap__Core__igStackMemoryPool__vfunc_64(Stack *self, unsigned count, unsigned *ptrs) {
    unsigned last;
    unsigned *end;
    unsigned top;
    unsigned avail;
    unsigned *e;
    unsigned i;
    end = self->end;
    last = ptrs[count - 1];
    top = self->top;
    avail = top - end[1];
    e = end + 1;
    if (!(avail > last)) {
        self->top = avail;
        for (i = 0; i < count - 1; i++) {
            e++;
            self->top = self->top - (*e & 0x7fffffff);
        }
        while (self->top != self->base && (*e & 0x80000000)) {
            self->top = self->top - (*e & 0x7fffffff);
            e++;
        }
        self->end = e - 1;
        return;
    }
    e++;
    avail = avail - (*e & 0x7fffffff);
    while (avail > last) {
        e++;
        avail = avail - (*e & 0x7fffffff);
    }
    for (i = 0; i < count; i++) {
        *e = *e | 0x80000000;
        e++;
    }
}
