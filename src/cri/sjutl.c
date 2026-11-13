/* CRI SJ utilities: chunk splitting and the tags that frame data inside a chunk. A tag is a 16-byte
 * header: a 7-character id at 0, its content length as seven hex digits at 8, the content from 16. */
#include "dw4/cri/sfdsj.h"

#define SJ_TAG_ID_LEN 7
#define SJ_TAG_LEN_OFS 8
#define SJ_TAG_HDR_LEN 16

void *memset(void *dst, int value, unsigned int size);
char *strncpy(char *dst, const char *src, unsigned int size);
int strncmp(const char *a, const char *b, unsigned int size);

extern unsigned char sj_hex_digit[];   /* "0123456789abcdef" */
extern int sj_hex_value[];    /* indexed by character */

/* head gets the first nbyte of a chunk (all of it if shorter), rest the remainder, with no data pointer
 * when nothing is left. */
void SJ_SplitChunk(SfdSjChunk *ck, int nbyte, SfdSjChunk *head, SfdSjChunk *rest)
{
    *head = *ck;
    rest->len = head->len;
    if (nbyte < head->len) {
        head->len = nbyte;
    }
    rest->len -= head->len;
    if (rest->len == 0) {
        rest->data = 0;
    } else {
        rest->data = head->data + head->len;
    }
}

/* Writes the low 28 bits of value as seven lower-case hex digits, most significant first, unterminated. */
void sj_PutHex7(int value, char *text)
{
    text[6] = sj_hex_digit[value & 15];
    value >>= 4;
    text[5] = sj_hex_digit[value & 15];
    value >>= 4;
    text[4] = sj_hex_digit[value & 15];
    value >>= 4;
    text[3] = sj_hex_digit[value & 15];
    value >>= 4;
    text[2] = sj_hex_digit[value & 15];
    value >>= 4;
    text[1] = sj_hex_digit[value & 15];
    value >>= 4;
    text[0] = sj_hex_digit[value & 15];
}

int sj_GetHex7(signed char *text)
{
    int value;

    value = sj_hex_value[text[0]];
    value = value * 16 + sj_hex_value[text[1]];
    value = value * 16 + sj_hex_value[text[2]];
    value = value * 16 + sj_hex_value[text[3]];
    value = value * 16 + sj_hex_value[text[4]];
    value = value * 16 + sj_hex_value[text[5]];
    value = value * 16 + sj_hex_value[text[6]];
    return value;
}

/* Clears a chunk and makes it a tag with the given id whose content is the rest of the chunk. */
void SJ_MakeTag(SfdSjChunk *tag, const char *id)
{
    memset(tag->data, 0, tag->len);
    strncpy(tag->data, id, SJ_TAG_ID_LEN);
    sj_PutHex7(tag->len - SJ_TAG_HDR_LEN, tag->data + SJ_TAG_LEN_OFS);
}

void SJ_GetTagContent(char *tag, SfdSjChunk *content)
{
    content->data = tag + SJ_TAG_HDR_LEN;
    content->len = sj_GetHex7((signed char *)tag + SJ_TAG_LEN_OFS);
}

/* Walks the tags of a chunk for id, giving up at the end tag endid; returns the tag found and its
 * content, or 0. */
char *SJ_SearchTag(SfdSjChunk *ck, const char *id, const char *endid, SfdSjChunk *content)
{
    char *tag;
    char *end;

    content->data = 0;
    content->len = 0;
    end = ck->data + ck->len;
    for (tag = ck->data; tag < end; tag += sj_GetHex7((signed char *)tag + SJ_TAG_LEN_OFS) + SJ_TAG_HDR_LEN) {
        if (strncmp(tag, id, SJ_TAG_ID_LEN) == 0) {
            SJ_GetTagContent(tag, content);
            break;
        }
        if (endid != 0 && strncmp(tag, endid, SJ_TAG_ID_LEN) == 0) {
            return 0;
        }
    }
    if (tag < end) {
        return tag;
    }
    return 0;
}
