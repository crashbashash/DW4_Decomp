typedef struct { int w[0x600]; } Blk;
extern Blk DAT_004bb3f8;
void FUN_00284dc8(Blk *dst) {
    *dst = DAT_004bb3f8;
}
