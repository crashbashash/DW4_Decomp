int FUN_002823f0(unsigned int message);

#define SWAP32(x) ((((x) & 0xFF) << 24) | (((x) & 0xFF00) << 8) | (((x) & 0xFF0000) >> 8) | (((x) & 0xFF000000) >> 24))

int FUN_00282ab8(unsigned int channel, unsigned int base, unsigned int value) {
    unsigned int chan = (channel & 0xF) << 16;
    unsigned int message;
    int result;

    message = chan + base;
    switch (base) {
    case 0xA5000000:
        message = chan + (value & 0x7F00) + 0xA5700000;
        result = FUN_002823f0(SWAP32(message));
        if (result != 0) {
            return result;
        }
        message = chan + ((value & 0x7F) << 8) + base;
        break;
    case 0xA5100000:
        message += (value & 0x7F) << 8;
        break;
    case 0xA5200000:
    case 0xA7000000:
    case 0xA7100000:
        message += ((value + 64) & 0x7F) << 8;
        break;
    case 0xA6000000:
        message += ((value & 0x7F) << 8) + ((value & 0x80) << 13);
        break;
    default:
        return -2;
    }
    return FUN_002823f0(SWAP32(message));
}
