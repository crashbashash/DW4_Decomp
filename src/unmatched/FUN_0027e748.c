/* SVM_SetCbSvrId by its message strings: registers a server callback and its object in the
 * [svtype][6] table at 0x005709e0 inside the FUN_0027e1c0 / FUN_0027e1d8 critical section,
 * reporting an illegal id, an illegal svtype and an overwritten callback through FUN_0027e398. */
struct ServerCallback27e {
    void *function;
    void *object;
};

extern void FUN_0027e398(const char *message);
extern void FUN_0027e1c0(void);
extern void FUN_0027e1d8(void);
extern struct ServerCallback27e DAT_005709e0[][6];
extern const char text_1071201_SVM_SetCbSvrId_illegal_id[];
extern const char text_1071202_SVM_SetCbSvrId_illegal_svtype[];
extern const char text_2100801_SVM_SetCbSvrId_over_write_callback_function[];

void FUN_0027e748(int svtype, unsigned int id, void *function, void *object) {
    struct ServerCallback27e *entry;

    if (id >= 6) {
        FUN_0027e398(text_1071201_SVM_SetCbSvrId_illegal_id);
    }
    if (svtype < 0 || (int)id >= 8) {   /* the retail bytes test id here, not svtype */
        FUN_0027e398(text_1071202_SVM_SetCbSvrId_illegal_svtype);
    }
    FUN_0027e1c0();
    entry = &DAT_005709e0[svtype][id];
    if (entry->function != 0) {
        FUN_0027e398(text_2100801_SVM_SetCbSvrId_over_write_callback_function);
    }
    entry->function = function;
    entry->object = object;
    FUN_0027e1d8();
}
