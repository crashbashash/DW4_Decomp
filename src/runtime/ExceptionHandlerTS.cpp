/* The target-specific half of the C++ exception handler: the R5900 frame a function's exception record describes,
 * popping such a frame, the image's exception index, the throw entry and the jump into a catch block. */
#include "dw4/runtime/exception.h"

/* An exception record starts with the frame: a flag byte (EXFRAME_*, low four bits the count of saved s registers)
 * and the frame size and argument size, then the count of saved float registers when EXFRAME_SAVED_FPRS is set. */
enum {
    EXFRAME_SAVED_GPRS = 0x0F,
    EXFRAME_FLUSHBACK = 0x10,
    EXFRAME_FRAME_POINTER = 0x20,
    EXFRAME_SAVED_FPRS = 0x40
};

/* Restores the catching frame's saved registers, drops the stack to its arguments and jumps to `address`. */
extern "C" asm void __TransferControl(register ThrowContext *context, register MWExceptionInfo *info, register char *address)
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

/* Saves the thrower's stack pointer, callee-saved registers and return address with the thrown type, object and
 * destructor in a ThrowContext on the stack and hands it to __ThrowHandler, which does not return. */
extern "C" asm void __throw(register char *throwtype, register void *location, register void *dtor)
{
    .set    reorder
    qmove   v0, sp
    addiu   sp, -sizeof(ThrowContext)
    sq      s0, ThrowContext.target.GPR[16](sp)
    sq      s1, ThrowContext.target.GPR[17](sp)
    sq      s2, ThrowContext.target.GPR[18](sp)
    sq      s3, ThrowContext.target.GPR[19](sp)
    sq      s4, ThrowContext.target.GPR[20](sp)
    sq      s5, ThrowContext.target.GPR[21](sp)
    sq      s6, ThrowContext.target.GPR[22](sp)
    sq      s7, ThrowContext.target.GPR[23](sp)
    sq      fp, ThrowContext.target.GPR[30](sp)
    swc1    f20, ThrowContext.target.FPR[20](sp)
    swc1    f21, ThrowContext.target.FPR[21](sp)
    swc1    f22, ThrowContext.target.FPR[22](sp)
    swc1    f23, ThrowContext.target.FPR[23](sp)
    swc1    f24, ThrowContext.target.FPR[24](sp)
    swc1    f25, ThrowContext.target.FPR[25](sp)
    swc1    f26, ThrowContext.target.FPR[26](sp)
    swc1    f27, ThrowContext.target.FPR[27](sp)
    swc1    f28, ThrowContext.target.FPR[28](sp)
    swc1    f29, ThrowContext.target.FPR[29](sp)
    swc1    f30, ThrowContext.target.FPR[30](sp)
    swc1    f31, ThrowContext.target.FPR[31](sp)
    sw      v0, ThrowContext.SP(sp)
    sw      v0, ThrowContext.throwSP(sp)
    sw      ra, ThrowContext.returnaddr(sp)
    sw      a0, ThrowContext.throwtype(sp)
    sw      a1, ThrowContext.location(sp)
    sw      a2, ThrowContext.dtor(sp)
    qmove   a0, sp
    jal     __ThrowHandler
}

/* The exception record past its frame description: the code ranges and their action lists. */
extern "C" unsigned char *__SkipFrameInfo(char *exception_record) {
    unsigned int value;
    int has_fprs = *exception_record & EXFRAME_SAVED_FPRS;
    unsigned char *p = (unsigned char *)exception_record;

    p = __DecodeUnsignedNumber(p + 1, &value); /* past the flag byte: the frame size */
    p = __DecodeUnsignedNumber(p, &value);     /* the argument size */

    if (has_fprs) {
        p = __DecodeUnsignedNumber(p, &value);
    }
    return p;
}

/* The exception index this image searches: its one table. */
extern "C" int __GetExceptionIndexBounds(MWExceptionInfo *info, char *return_address) {
    info->exception_table_start = __exception_table_start__;
    info->exception_table_end = __exception_table_end__;
    return 1;
}

/* Reads the frame description of the function `info` found into the context's target. */
extern "C" void __SetupFrameInfo(ThrowContext *context, MWExceptionInfo *info) {
    char *record = info->exception_record;
    unsigned char *p;
    int has_fprs = *record & EXFRAME_SAVED_FPRS;

    context->target.has_frame_ptr = *record & EXFRAME_FRAME_POINTER;
    context->target.has_flushback = *record & EXFRAME_FLUSHBACK;
    context->target.n_saved_GPRs = *record & EXFRAME_SAVED_GPRS;
    p = (unsigned char *)record;
    p = __DecodeUnsignedNumber(p + 1, &context->target.frame_size); /* past the flag byte */
    p = __DecodeUnsignedNumber(p, &context->target.argument_size);
    if (context->target.has_frame_ptr) {
        context->FP = (char *)(int)context->target.GPR[30];
    } else {
        context->FP = context->SP;
    }
    if (has_fprs) {
        __DecodeUnsignedNumber(p, &context->target.n_saved_FPRs);
    } else {
        context->target.n_saved_FPRs = 0;
    }
}

/* Restores the registers the frame saved (the s registers above the arguments, then fp, the return address, and
 * the float registers below them) and steps to the caller's frame; returns the return address. */
extern "C" char *__PopStackFrame(ThrowContext *context, MWExceptionInfo *info) {
    unsigned long long argument_size;
    int has_fprs;
    unsigned long long frame_size;
    unsigned long long n_gprs;
    char *return_address;
    __int128 *gpr_save;
    int i;
    unsigned long long n_fprs;
    unsigned int *fpr_save;

    frame_size = context->target.frame_size;
    argument_size = context->target.argument_size;
    has_fprs = *info->exception_record & EXFRAME_SAVED_FPRS;
    n_gprs = context->target.n_saved_GPRs;
    if (has_fprs) {
        n_fprs = context->target.n_saved_FPRs;
        fpr_save = (unsigned int *)(context->FP + (int)argument_size + (int)((n_fprs * 4 + 15) & ~15ULL));
        gpr_save = (__int128 *)((unsigned long long)(unsigned int)fpr_save + (n_gprs << 4));
    } else {
        gpr_save = (__int128 *)(context->FP + (int)argument_size + (int)(n_gprs << 4));
    }
    if (context->target.has_frame_ptr) {
        gpr_save++;
    }
    return_address = *(char **)gpr_save;
    if (context->target.has_frame_ptr) {
        gpr_save--;
        context->target.GPR[30] = *gpr_save;
    } else if (n_gprs == 9) {
        /* s0-s7 and fp */
        gpr_save--;
        n_gprs--;
        context->target.GPR[30] = *gpr_save;
    }
    gpr_save -= (int)n_gprs;
    for (i = 0; (unsigned long long)i < n_gprs; i++) {
        context->target.GPR[16 + i] = *gpr_save++;
    }
    context->SP = context->FP + (int)frame_size;
    if (has_fprs) {
        fpr_save -= (int)n_fprs;
        for (i = 0; (unsigned long long)i < n_fprs; i++) {
            context->target.FPR[20 + i] = *fpr_save++;
        }
    }
    return return_address;
}
