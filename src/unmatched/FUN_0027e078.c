/* Sends the handle's word at +16 as request 1 through DTX_CallUrpc, then clears the handle's in-
 * use byte. */
int DTX_CallUrpc();

struct Handle0027e078 {
    char used;     /* +0 */
    char pad1[15];
    int id;        /* +16: sent to the request */
};

void FUN_0027e078(struct Handle0027e078 *handle) {
    int request[1];

    request[0] = handle->id;
    DTX_CallUrpc(1, request, 1, 0, 0);
    handle->used = 0;
}
