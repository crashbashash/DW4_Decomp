/* Maps a picture type: 1 -> 1, 2 -> 2, anything else -> 3. */

int FUN_00293ca0(unsigned int type) {
    int result;

    switch (type) {
    case 1:
        result = 1;
        break;
    case 2:
        result = 2;
        break;
    case 3:
        result = 3;
        break;
    default:
        result = 3;
        break;
    }
    return result;
}
