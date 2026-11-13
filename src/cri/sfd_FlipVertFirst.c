/* Turns a line walk upside down: start at the last line and step backwards. */
typedef struct SfdLineWalk {
    int addr;
    int pad4;
    int lines;
    int pitch;
} SfdLineWalk;

void sfd_FlipVertFirst(SfdLineWalk *walk) {
    int pitch = walk->pitch;

    walk->pitch = -pitch;
    walk->addr += pitch * (walk->lines - 1);
}
