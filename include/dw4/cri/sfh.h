#ifndef SFH_H
#define SFH_H

#define SFH_MAX_HN 32

/* One analysed CRI header: its state, the bytes it was read from and the tool version it names. */
typedef struct SfhHn {
    int stat;
    struct SfhHdr *hdr;
    unsigned int size;
    int version;          /* major * 100 + minor */
} SfhHn;

#endif
