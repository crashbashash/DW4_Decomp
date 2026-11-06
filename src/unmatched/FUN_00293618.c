/* Releases a handle: through FUN_00293668 when the owner's +512 mode word is set, otherwise
 * through FUN_00293670; then calls FUN_00293718 on the owner. */
extern void FUN_00293668(void *owner, int handle);
extern void FUN_00293670(int handle);
extern void FUN_00293718(void *owner);

typedef struct {
    char pad0[512];
    int f512;
} Owner293618;

void FUN_00293618(Owner293618 *owner, int handle) {
    if (owner->f512 != 0) {
        FUN_00293668(owner, handle);
    } else {
        FUN_00293670(handle);
    }
    FUN_00293718(owner);
}
