/* When the request id at +0xA04+80 is set (not -4), fetches the current position pair through
 * FUN_002ae968 and returns 1 when FUN_00285118 rejects it against the request. */
int FUN_002ae968(int obj, int *first, int *second);
int FUN_00285118(int first, int second, int request, int value);

struct BlockA04 {
    char pad0[80];
    int request; /* +80; -4 = none */
    int value;   /* +84 */
};

int FUN_002ab460(int obj) {
    struct BlockA04 *a = (struct BlockA04 *)(obj + 0xA04);
    int first;
    int second;
    int request;
    int value;

request = a->request;
    value = a->value;
    if (request == -4) {
        return 0;
    }
    FUN_002ae968(obj, &first, &second);
    if (first < 0) {
        return 0;
    }
    return FUN_00285118(first, second, request, value) == 0;
}
