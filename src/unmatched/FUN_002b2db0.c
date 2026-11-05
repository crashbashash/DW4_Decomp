/* MPEG-2 frame_rate_code -> frame rate in milli-frames per second. */
int FUN_002b2db0(int frame_rate_code)
{
    switch (frame_rate_code) {
    case 1: return 23976;
    case 2: return 24000;
    case 3: return 25000;
    case 4: return 29970;
    case 5: return 30000;
    case 6: return 50000;
    case 7: return 59940;
    case 8: return 60000;
    }
    return 0;
}
