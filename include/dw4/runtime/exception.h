/* Metrowerks C++ exception runtime (MIPS): the throw context, the frame's exception info and the action-table records. */
#ifndef DW4_RUNTIME_EXCEPTION_H
#define DW4_RUNTIME_EXCEPTION_H

/* One function's entry in the image's exception index, sorted by address: the low bit of function_size set means
 * exception_table holds the (short) exception record itself. */
typedef struct ExceptionTableIndex {
    char *function_address;
    unsigned int function_size;
    char *exception_table;
} ExceptionTableIndex;

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
    unsigned int FPR[32];           /* 0x218: f0-f31, as their bits */
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

/* The other bits of an action's first byte: the last action of a list, and a condition or object pointer held in a
 * saved register (the record gives its number in place of a frame offset). */
enum {
    EXACTION_ENDBIT = 0x80,
    EXACTION_REGCOND = 0x40,
    EXACTION_REGPTR = 0x20,
    EXACTION_MASK = 0x1F
};

#ifdef __cplusplus
extern "C" {
#endif
/* A static initializer the start-up code runs before main (the linker's table runs __ctors_start__ to __ctors_end__). */
typedef void (*StaticInitializer)(void);
extern StaticInitializer __ctors_start__[];
extern StaticInitializer __ctors_end__[];
void __call_static_initializers(StaticInitializer *begin, StaticInitializer *end, ExceptionTableIndex *extab_begin, ExceptionTableIndex *extab_end);
void __destroy_global_chain(void);

/* The image's exception index, sorted by function address (placed by the linker). */
extern ExceptionTableIndex __exception_table_start__[];
extern ExceptionTableIndex __exception_table_end__[];

void __terminate(void);
void __call_unexpected_handler(void);
void __end__catch(CatchInfo *catchinfo);
void __unexpected(CatchInfo *catchinfo);
void __throw(char *throwtype, void *location, void *dtor);
void __ThrowHandler(ThrowContext *context);
int __GetExceptionIndexBounds(MWExceptionInfo *info, char *return_address);
unsigned char *__SkipFrameInfo(char *exception_record);
unsigned char *__DecodeUnsignedNumber(unsigned char *p, unsigned int *value);
unsigned char *__DecodeSignedNumber(unsigned char *p, int *value);
char __throw_catch_compare(const char *throwtype, const char *catchtype, long *offset_result);
void __FindExceptionTable(char *return_address, MWExceptionInfo *info);
void __SetupFrameInfo(ThrowContext *context, MWExceptionInfo *info);
char *__PopStackFrame(ThrowContext *context, MWExceptionInfo *info);
unsigned char NextAction(ActionIterator *iter);
CatchInfo *FindMostRecentException(ThrowContext *context, MWExceptionInfo *info);
unsigned char *FindExceptionHandler(ThrowContext *context, MWExceptionInfo *info, long *result_offset);
void UnwindStack(ThrowContext *context, MWExceptionInfo *info, unsigned char *catcher);
void __TransferControl(ThrowContext *context, MWExceptionInfo *info, char *address);
#ifdef __cplusplus
}
#endif

#endif
