int RFU086_WaitEvnetFlag(int ef);

int FUN_001138c0(int ef)
{
    int result;
    if ((unsigned int)(ef - 13) >= 35) {
        result = -1;
    } else {
        result = RFU086_WaitEvnetFlag(ef);
    }
    return result;
}
