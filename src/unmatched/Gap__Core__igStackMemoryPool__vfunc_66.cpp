class Stack { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void d72(); virtual void d73(); virtual void d74(); virtual void d75(); virtual void d76(); virtual void d77(); virtual void d78(); virtual void d79(); virtual void d80(); virtual void d81(); virtual void d82(); virtual int Owns(); char pad[112]; unsigned base; char pad2[12]; unsigned top; unsigned *end; };
extern "C" void Gap__Core__igStackMemoryPool__vfunc_66(Stack *self, unsigned size) {
    unsigned *e;
    unsigned avail;
    unsigned top;
    unsigned v;
    if (size != 0 && self->Owns() != 0) {
        e = self->end + 1;
        top = self->top;
        v = *e;
        avail = top - v;
        if (!(avail > size)) {
            e++;
            self->top = top - (v & 0x7fffffff);
            while (self->top != self->base && (*e & 0x80000000)) {
                self->top = self->top - (*e & 0x7fffffff);
                e++;
            }
            self->end = e - 1;
            return;
        }
        e++;
        avail = avail - (*e & 0x7fffffff);
        while (avail > size) {
            e++;
            avail = avail - (*e & 0x7fffffff);
        }
        *e = *e | 0x80000000;
    }
}
