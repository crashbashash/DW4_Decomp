/* RPC server thread body: binds the queue at 0x004aa420 to the current thread, registers handler
 * FUN_00273078 for the command id in 0x004a9b14 with receive buffer 0x004aa440, raises the ready
 * flag 0x004a9b18 and enters the serve loop. The call sequence matches sceSifSetRpcQueue,
 * sceSifRegisterRpc and sceSifRpcLoop. */
extern int GetThreadId(void);
extern void FUN_0010e4e0(void *queue, int thread_id);
extern void FUN_0010e578(void *server, int command, void *handler, void *buffer, void *cancel_handler,
                         void *cancel_buffer, void *queue);
extern void FUN_0010e990(void *queue);
extern void *FUN_00273078(int function, void *data, int size);

extern char DAT_004aa3d8[];  /* server descriptor */
extern char DAT_004aa420[];  /* queue */
extern char DAT_004aa440[];  /* receive buffer */
extern int DAT_004a9b14;     /* RPC command id */
extern volatile int DAT_004a9b18;  /* server-ready flag */

int FUN_00273128(void) {
    FUN_0010e4e0(DAT_004aa420, GetThreadId());
    FUN_0010e578(DAT_004aa3d8, DAT_004a9b14, FUN_00273078, DAT_004aa440, 0, 0, DAT_004aa420);
    DAT_004a9b18 = 1;
    FUN_0010e990(DAT_004aa420);
    return 0;
}
