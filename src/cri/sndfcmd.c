#include "dw4/cri/sndf.h"

int sndf_SendMessage(unsigned int message)
{
    SndfContext *ctx = sndf_ctx;
    int result;

    if (ctx->sending != 0) {
        return -3;
    }
    ctx->sending = -1;
    if (!(message & 0x80)) {
        sndf_ctx->sending = 0;
        return -2;
    }
    result = sndf_PushCommand(1, 0xFFFF, 0, 0, SWAP32_A(message), 0);
    sndf_ctx->sending = 0;
    return result;
}

int SNDF_SendChMessage(unsigned int channel, unsigned int message)
{
    SndfContext *ctx = sndf_ctx;
    int result;

    if (ctx->sending != 0) {
        return -3;
    }
    if (channel >= 32) {
        return -128;
    }
    ctx->sending = -1;
    if (!(message & 0x80)) {
        sndf_ctx->sending = 0;
        return -2;
    }
    result = sndf_PushCommand(1, channel, 0, 0, SWAP32_A(message), 0);
    sndf_ctx->sending = 0;
    return result;
}

int SNDF_SendVoiceMessage(unsigned int channel, unsigned int kind, unsigned int data1, unsigned int data2)
{
    SndfContext *ctx = sndf_ctx;
    int result;

    if (ctx->sending != 0) {
        return -3;
    }
    if (channel >= 32) {
        return -128;
    }
    if (kind - 8 >= 6) {
        return -2;
    }
    if (data1 >= 128) {
        return -2;
    }
    if (data2 >= 128) {
        return -2;
    }
    ctx->sending = -1;
    result = sndf_PushCommand(1, channel, 0, 0, ((kind | 0xA0) << 24) | (data1 << 16) | (data2 << 8), 0);
    sndf_ctx->sending = 0;
    return result;
}

int SNDF_SendControl(unsigned int channel, unsigned int cmd, int value)
{
    unsigned int message = cmd;
    int mode;

    if (cmd & 0xFF0000) {
        switch (cmd) {
        case 0xA0010000:
        case 0xA0040000:
        case 0xA0090000:
        case 0xA00A0000:
        case 0xA0100000:
            message = cmd + ((value & 0x7F) << 8);
            break;
        case 0xA0050000:
        case 0xA0070000:
        case 0xA0110000:
            message = cmd + (((value + 64) & 0x7F) << 8);
            break;
        case 0xA0280000:
        case 0xA0290000:
            message = cmd + (((value - 1) & 0xF) << 8);
            break;
        case 0xA0020000:
        case 0xA0030000:
            break;
        default:
            return -2;
        }
    }
    switch (cmd) {
    case 0xA0000900:
        sndf_ctx->mode = 0;
        break;
    case 0xA0000800:
        sndf_ctx->mode = 1;
        break;
    case 0xA0002900:
        sndf_ctx->mode = 2;
        break;
    }
    return sndf_PushCommand(1, channel, 0, 0, message, 0);
}

int SNDF_SendCtrlChange(int channel, int port, unsigned int cmd, int value)
{
    unsigned int base = ((port - 1) & 0xF) << 24;
    unsigned int message = base + cmd;
    int result;

    if (cmd != 0) {
        switch (cmd) {
        case 0xB0780000:
            break;
        case 0xB0070000:
        case 0xB00D0000:
        case 0xB0270000:
        case 0xB02D0000:
            message += (value & 0x7F) << 8;
            break;
        case 0xA0110000:
        case 0xB00A0000:
        case 0xB02A0000:
            message += ((value + 64) & 0x7F) << 8;
            break;
        case 0xB0300000:
            result = sndf_PushCommand(1, channel & 0xFFFF, 0, 0,
                                      (((value / 100 + 64) & 0x7F) << 8) + base + 0xB0310000, 0);
            if (result != 0) {
                return result;
            }
            message = ((((value % 100) * 64 / 100 + 64) & 0x7F) << 8) + base + 0xB0320000;
            break;
        case 0xB0100000:
            result = sndf_PushCommand(1, channel & 0xFFFF, 0, 0,
                                      (((value / 100 + 64) & 0x7F) << 8) + base + 0xB0110000, 0);
            if (result != 0) {
                return result;
            }
            message = ((((value % 100) * 64 / 100 + 64) & 0x7F) << 8) + base + 0xB0120000;
            break;
        default:
            return -2;
        }
    }
    return sndf_PushCommand(1, channel & 0xFFFF, 0, 0, message, 0);
}

int SNDF_SetMasterParam(unsigned int base, unsigned int value)
{
    unsigned int message;
    int result;

    if (base != 0xA4000000) {
        return -2;
    }
    message = (value & 0x7F00) + 0xA4700000;
    result = sndf_SendMessage(SWAP32_C(message));
    if (result != 0) {
        return result;
    }
    message = ((value & 0x7F) << 8) + base;
    return sndf_SendMessage(SWAP32_C(message));
}

int SNDF_SetChannelParam(unsigned int channel, unsigned int base, unsigned int value)
{
    unsigned int chan = (channel & 0xF) << 16;
    unsigned int message;
    int result;

    message = chan + base;
    switch (base) {
    case 0xA5000000:
        message = chan + (value & 0x7F00) + 0xA5700000;
        result = sndf_SendMessage(SWAP32_C(message));
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
    return sndf_SendMessage(SWAP32_C(message));
}

int SNDF_StartSound(unsigned int message, int arg)
{
    SndfContext *ctx = sndf_ctx;
    int id = -1;
    int result;
    int i;

    if (ctx->sending != 0) {
        return -30;
    }
    ctx->sending = -1;
    if ((message & 0xFF) >= 0xAE) {
        for (i = 0; i < 24; i++) {
            if (sndf_ctx->slots[i].used == 0) {
                id = i + 1;
                sndf_ctx->slots[i].used = 1;
                break;
            }
        }
    } else {
        id = 0;
    }
    if (id >= 0) {
        result = sndf_PushCommand(3, 0xFFFF, 0xF00, id, message, arg);
    } else {
        result = -2;
    }
    if (result == 0) {
        result = id;
    }
    sndf_ctx->sending = 0;
    return result;
}

int SNDF_StopSound(int id)
{
    SndfContext *ctx = sndf_ctx;
    int result;

    if (ctx->sending != 0) {
        return -30;
    }
    ctx->sending = -1;
    if ((unsigned int)(id - 1) < 24) {
        result = sndf_PushCommand(3, 0xFFFF, 0x1000, id, 0, 0);
    } else {
        result = -2;
    }
    sndf_ctx->sending = 0;
    return result;
}

int SNDF_ReleaseSound(int id)
{
    SndfContext *ctx = sndf_ctx;
    int result;

    if (ctx->sending != 0) {
        return -30;
    }
    ctx->sending = -1;
    if ((unsigned int)(id - 1) < 24) {
        result = sndf_PushCommand(3, 0xFFFF, 0x1100, id, 0, 0);
    } else {
        result = -2;
    }
    sndf_ctx->sending = 0;
    return result;
}

int SNDF_SetSoundPanVol(int id, unsigned short angle, unsigned short vol)
{
    SndfContext *ctx = sndf_ctx;
    int result;
    int pan;
    int p;
    int v;

    if (ctx->sending != 0) {
        return -30;
    }
    ctx->sending = -1;
    pan = (angle % 360) >> 1;
    p = pan + 45;
    if (p >= 180) {
        p = pan - 135;
    }
    if (sndf_ctx->mode == 2) {
        p = sndf_pan_remap[p];
    }
    v = vol < 256 ? vol : 255;
    if ((unsigned int)(id - 1) < 24) {
        result = sndf_PushCommand(3, 0xFFFF, 0x1200, id, p, v);
    } else {
        result = -1;
    }
    sndf_ctx->sending = 0;
    return result;
}

int SNDF_StartChannelSound(unsigned int channel, unsigned int kind, unsigned int value)
{
    unsigned int message = (channel & 0x3F) + kind;

    switch (kind) {
    case 0xA0000500:
    case 0xA0001500:
        break;
    case 0xA0120000:
        message += (value & 0x7F) << 8;
        break;
    default:
        return -1;
    }
    return SNDF_StartSound(SWAP32_A(message), 0);
}

int SNDF_SetSoundPitch(int id, int value)
{
    SndfContext *ctx = sndf_ctx;
    int result;

    if (ctx->sending != 0) {
        return -30;
    }
    ctx->sending = -1;
    if ((unsigned int)(id - 1) < 24) {
        result = sndf_PushCommand(3, 0xFFFF, 0x1800, id, value / 100 + 64, ((value % 100) << 6) / 100 + 64);
    } else {
        result = -2;
    }
    sndf_ctx->sending = 0;
    return result;
}

