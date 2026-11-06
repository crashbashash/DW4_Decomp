/* Queries two words of the handle at +8 into the record (+172, +176), then passes it the three
 * shorts at +166..+170. */
typedef struct Rec25dbd8 {
    char pad0[8];
    void *handle;       /* +8 */
    char pad12[154];
    short arg166;       /* +166 */
    short arg168;       /* +168 */
    short arg170;       /* +170 */
    int out172;         /* +172: written by FUN_0026ef90 */
    int out176;         /* +176: written by FUN_0026ef90 */
} Rec25dbd8;

void FUN_0026ef90(void *handle, int *out_a, int *out_b);
void FUN_0026efe0(void *handle, int a, int b, int c);

void FUN_0025dbd8(Rec25dbd8 *rec) {
    FUN_0026ef90(rec->handle, &rec->out172, &rec->out176);
    FUN_0026efe0(rec->handle, rec->arg166, rec->arg168, rec->arg170);
}
