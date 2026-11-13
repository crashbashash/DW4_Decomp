/* Attaches an object to stream id 188..255 (0xBC..0xFF, the MPEG stream ids; callers pass 0xC0 + n)
 * in the stream table of the handle's second transfer module, and sets the callback (with its
 * argument) run on that object's data; error 0xFF000171 on a bad handle. */
typedef struct {
    char pad0[64];
    void *object[68];           /* +64, indexed by stream id - 188 */
    int (*stmCb)(void *obj, int arg); /* +336 */
    void *stmCbObj;             /* +340 */
} SfdStmTbl;

typedef struct {
    char pad0[8052];
    SfdStmTbl *stm;     /* +8052 */
} SfdHn;

int sfd_CheckHn(SfdHn *hn);
int sfd_ReportError(SfdHn *hn, int code);

int SFD_SetStmObject(SfdHn *hn, int id, void *object, int (*cb)(void *obj, int arg), void *cbObj) {
    SfdStmTbl *stm;

    if (sfd_CheckHn(hn) != 0) {
        return sfd_ReportError(0, 0xFF000171);
    }
    if ((unsigned int)(id - 188) < 68) {
        stm = hn->stm;
        stm->object[id - 188] = object;
        stm->stmCbObj = cbObj;
        stm->stmCb = cb;
    }
    return 0;
}
