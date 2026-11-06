/* Reads an object's status (FUN_00276b18); when its busy word (+4) is clear, prepares the request
 * block DAT_004ab8c0 (FUN_00276220), issues it (FUN_002728b0) and waits on it (FUN_00272918)
 * between FUN_002725a0 trace markers 0x4200/0x4201 and 0x4300/0x4301. Returns 1 on success or when
 * busy, 0 for a NULL object or a failed issue. */
typedef struct Status_275678 {
    int f0;
    int busy;       /* 0x04 */
    int pad8[2];
} Status_275678;

extern char DAT_004ab8c0[];
void FUN_00276b18(void *obj, Status_275678 *status);
void FUN_00276220(void *obj, char *request);
void FUN_002725a0(int marker);
int FUN_002728b0(char *request, int mode);
void FUN_00272918(int id);

int FUN_00275678(void *obj) {
    Status_275678 status;
    int id;

    if (obj == 0) {
        return 0;
    }
    FUN_00276b18(obj, &status);
    if (status.busy == 0) {
        FUN_00276220(obj, DAT_004ab8c0);
        FUN_002725a0(0x4200);
        id = FUN_002728b0(DAT_004ab8c0, 1);
        FUN_002725a0(0x4201);
        if (id < 0) {
            return 0;
        }
        FUN_002725a0(0x4300);
        FUN_00272918(id);
        FUN_002725a0(0x4301);
    }
    return 1;
}

