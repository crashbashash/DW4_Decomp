struct R { int v; R() {} R(const R &o) : v(o.v) {}
  bool operator==(const R &o) const { return v == o.v; }
  bool operator!=(const R &o) const { return v != o.v; }
};
class Sub { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual R v92(); };
struct Media { void *vt; int f4; int f8; int f12; Sub *f16; char p20[16]; char f36; };
extern "C" {
void Gap__Core__igObject__resetFields(Media *);
R igPsx2_LoadIopModule(void *, int, int, int);
R igPsx2IopRpcConnection_Bind(int, int);
R igPsx2IopRpcConnection_CallWithData(int, int, int, int, int);
void DIntr(void);
void EIntr(void);
void sceSifAddCmdHandler(int, void *, int);
void igPsx2Media_RpcCompletionHandler(void);
extern R DAT_004fb410;
extern int DAT_004f9498[4];
extern int DAT_004ffd30[4];
extern int DAT_004ffbd8[2];
extern int DAT_004ffbe0[2];
extern int DAT_00587338;
extern Media *DAT_00587360;
extern int *DAT_00587368;
extern char GPR_00554de0;
}
extern "C" void Gap__Core__igPsx2Media__resetFields(Media *self) {
    Gap__Core__igObject__resetFields(self);
    if (igPsx2_LoadIopModule(DAT_004f9498, 1, 0, 0) != DAT_004fb410) {
        return;
    }
    if (igPsx2_LoadIopModule(DAT_004ffd30, 2, 0, 0) != DAT_004fb410) {
        return;
    }
    self->f36 = 1;
    igPsx2IopRpcConnection_Bind(self->f12, 0x12114);
    igPsx2IopRpcConnection_CallWithData(self->f12, 19, (int)(unsigned)self->f8, (char)0, (char)0);
    DIntr();
    sceSifAddCmdHandler(4, (void *)igPsx2Media_RpcCompletionHandler, 0);
    EIntr();
    DAT_00587360 = self;
    self->f16->v92();
    if (DAT_00587338 == 0) {
        GPR_00554de0 = 0;
        if (DAT_00587368 == 0) {
            DAT_00587368 = DAT_004ffbd8;
        }
    } else {
        GPR_00554de0 = 1;
        DAT_00587368 = DAT_004ffbe0;
    }
}
