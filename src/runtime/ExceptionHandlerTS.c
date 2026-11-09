typedef struct CatchInfo CatchInfo;
typedef struct ExceptionInfo ExceptionInfo;

typedef struct TargetContext {
    __int128 GPR[32];
    unsigned int frame_size;
    unsigned int argument_size;
    int n_saved_GPRs;
    int has_flushback;
    int has_frame_ptr;
    unsigned int n_saved_FPRs;
    float FPR[32];
} TargetContext;

typedef struct ThrowContext {
    char *throwtype;
    void *location;
    void *dtor;
    CatchInfo *catchinfo;
    char *returnaddr;
    char *SP;
    char *FP;
    char *throwSP;
    TargetContext target;
} ThrowContext;

asm void __TransferControl(register ThrowContext *context, register ExceptionInfo *info, register char *address)
{
    .set    reorder
    lq      s0, ThrowContext.target.GPR[16](a0)
    lq      s1, ThrowContext.target.GPR[17](a0)
    lq      s2, ThrowContext.target.GPR[18](a0)
    lq      s3, ThrowContext.target.GPR[19](a0)
    lq      s4, ThrowContext.target.GPR[20](a0)
    lq      s5, ThrowContext.target.GPR[21](a0)
    lq      s6, ThrowContext.target.GPR[22](a0)
    lq      s7, ThrowContext.target.GPR[23](a0)
    lq      fp, ThrowContext.target.GPR[30](a0)
    lwc1    f20, ThrowContext.target.FPR[20](a0)
    lwc1    f21, ThrowContext.target.FPR[21](a0)
    lwc1    f22, ThrowContext.target.FPR[22](a0)
    lwc1    f23, ThrowContext.target.FPR[23](a0)
    lwc1    f24, ThrowContext.target.FPR[24](a0)
    lwc1    f25, ThrowContext.target.FPR[25](a0)
    lwc1    f26, ThrowContext.target.FPR[26](a0)
    lwc1    f27, ThrowContext.target.FPR[27](a0)
    lwc1    f28, ThrowContext.target.FPR[28](a0)
    lwc1    f29, ThrowContext.target.FPR[29](a0)
    lwc1    f30, ThrowContext.target.FPR[30](a0)
    lwc1    f31, ThrowContext.target.FPR[31](a0)
    lw      sp, ThrowContext.throwSP(a0)
    lw      v0, ThrowContext.target.argument_size(a0)
    sub     sp, sp, v0
    jr      a2
}
