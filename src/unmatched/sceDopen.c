typedef struct _sceFsIob { int fd; int mode; int pad8[2]; } _sceFsIob;
extern _sceFsIob DAT_00558f80[];
extern int DAT_00481efc;
extern int DAT_00481f08;
int FUN_0010ef30(int op);
int FUN_0010f060(void);
int FUN_0010ef60(void);
_sceFsIob *new_iob(void);
int FUN_001103e8(const char *name, int op);
int WaitSema(int sema);
int SignalSema(int sema);
int sceDopen(const char *name) {
    _sceFsIob *io;
    int fd;
    FUN_0010ef30(9);
    if (DAT_00481efc == 0) {
        FUN_0010f060();
    }
    FUN_0010ef60();
    io = new_iob();
    if (io == 0) {
        return -19;
    }
    fd = FUN_001103e8(name, 9);
    if (fd < 0) {
        WaitSema(DAT_00481f08);
        io->mode = 0;
        SignalSema(DAT_00481f08);
        return fd;
    }
    WaitSema(DAT_00481f08);
    io->fd = fd;
    fd = io - DAT_00558f80;
    SignalSema(DAT_00481f08);
    return fd;
}
