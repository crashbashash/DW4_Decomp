/* Classifies an MPEG stream id: audio streams 0xC0-0xDF give 0xC0, video streams 0xE0-0xEF give
 * 0xE0, private streams 0xBD and 0xBF give 0xBD, anything else 0. */
int FUN_002b2ea0(int id) {
    if ((unsigned int)(id - 0xC0) < 32) {
        return 0xC0;
    }
    if ((unsigned int)(id - 0xE0) < 16) {
        return 0xE0;
    }
    if (id == 0xBD || id == 0xBF) {
        return 0xBD;
    }
    return 0;
}
