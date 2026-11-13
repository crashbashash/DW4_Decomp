/* Metrowerks C++ exception runtime (MIPS): the throw context, the frame's exception info and the action-table records. */
#ifndef DW4_RUNTIME_EXCEPTION_H
#define DW4_RUNTIME_EXCEPTION_H

typedef struct ExceptionTableIndex ExceptionTableIndex;

/* The exception table of the function a frame belongs to, and the current position in its action list. */
typedef struct MWExceptionInfo {
    char *current_function;
    char *exception_record;
    unsigned char *action_pointer;
    ExceptionTableIndex *exception_table_start;
    ExceptionTableIndex *exception_table_end;
    float reserved[1];
} MWExceptionInfo;

/* Lives in the catching frame at FP + cinfo_ref while its catch block runs. */
typedef struct CatchInfo {
    void *location;
    void *typeinfo;
    void *dtor;
    void *sublocation;
    int pointercopy;
    void *stacktop;
} CatchInfo;

/* The registers of the frame being unwound and that frame's layout from its exception record. */
typedef struct TargetContext {
    __int128 GPR[32];               /* 0x000 */
    unsigned int frame_size;        /* 0x200 */
    unsigned int argument_size;     /* 0x204 */
    int n_saved_GPRs;               /* 0x208 */
    int has_flushback;              /* 0x20c */
    int has_frame_ptr;              /* 0x210 */
    unsigned int n_saved_FPRs;      /* 0x214 */
    float FPR[32];                  /* 0x218 */
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
    TargetContext target;           /* 0x20 */
} ThrowContext;

typedef struct ex_catchblock {
    char *catch_type;
    unsigned int catch_pcoffset;
    int cinfo_ref;
} ex_catchblock;

typedef struct ex_specification {
    unsigned int specs;
    unsigned int pcoffset;
    int cinfo_ref;
    unsigned char *spec;
} ex_specification;

typedef struct ActionIterator {
    MWExceptionInfo info;
    ThrowContext context;
} ActionIterator;

/* exaction_type: the low five bits of an action's first byte. */
enum {
    EXACTION_ENDOFLIST,
    EXACTION_BRANCH,
    EXACTION_DESTROYLOCAL,
    EXACTION_DESTROYLOCALCOND,
    EXACTION_DESTROYLOCALPOINTER,
    EXACTION_DESTROYLOCALARRAY,
    EXACTION_DESTROYBASE,
    EXACTION_DESTROYMEMBER,
    EXACTION_DESTROYMEMBERCOND,
    EXACTION_DESTROYMEMBERARRAY,
    EXACTION_DELETEPOINTER,
    EXACTION_DELETEPOINTERCOND,
    EXACTION_CATCHBLOCK,
    EXACTION_ACTIVECATCHBLOCK,
    EXACTION_TERMINATE,
    EXACTION_SPECIFICATION
};

#ifdef __cplusplus
extern "C" {
#endif
void __terminate(void);
unsigned char *__DecodeUnsignedNumber(unsigned char *p, unsigned int *value);
unsigned char *__DecodeSignedNumber(unsigned char *p, int *value);
char __throw_catch_compare(const char *throwtype, const char *catchtype, long *offset_result);
void __FindExceptionTable(char *return_address, MWExceptionInfo *info);
void __SetupFrameInfo(ThrowContext *context, MWExceptionInfo *info);
char *__PopStackFrame(ThrowContext *context, MWExceptionInfo *info);
unsigned char NextAction(ActionIterator *iter);
CatchInfo *FindMostRecentException(ThrowContext *context, MWExceptionInfo *info);
unsigned char *FindExceptionHandler(ThrowContext *context, MWExceptionInfo *info, long *result_offset);
void UnwindStack(ThrowContext *context, MWExceptionInfo *info, unsigned char *action);
void __TransferControl(ThrowContext *context, MWExceptionInfo *info, char *address);
#ifdef __cplusplus
}
#endif

#endif
