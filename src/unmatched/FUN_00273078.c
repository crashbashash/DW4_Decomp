/* Command dispatcher over a word buffer: command 2 replaces data[0] with FUN_00273338(data[0..3]),
 * command 3 shuts down the object data[0] (FUN_002734d0), commands 0x400-0x43f go to the
 * registered handler DAT_004aa540[n] with its object DAT_004aa640[n] and the size in words;
 * returns the buffer. */
extern void (*DAT_004aa540[64])(int object, int *data, unsigned int words);
extern int DAT_004aa640[64];
int FUN_00273338(int a, int b, int c, int d);
void FUN_002734d0(int object);

int *FUN_00273078(unsigned int command, int *data, unsigned int size) {
    switch (command) {
    case 0:
    case 1:
        break;
    case 2:
        data[0] = FUN_00273338(data[0], data[1], data[2], data[3]);
        break;
    case 3:
        FUN_002734d0(data[0]);
        break;
    default:
        if (command - 0x400 < 64 && DAT_004aa540[command - 0x400] != 0) {
            DAT_004aa540[command - 0x400](DAT_004aa640[command - 0x400], data, size / 4);
        }
        break;
    }
    return data;
}

