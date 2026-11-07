struct Result { int v; };
class Stream { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual int Seek(int pos, int n); virtual Result Move(int pos, int n); virtual int Tell(); };
extern "C" void FUN_003291a0(Stream *self, int n) {
    if (n > 0) {
        if (self->Seek(self->Tell(), n) == -1) {
            self->Seek(0, n);
        }
    } else if (n < 0) {
        int pos = self->Tell();
        self->Move(pos + n, -n);
        self->Tell();
    } else {
        self->Tell();
    }
}
