# CRI ADXSJD: the ADX stream-joint decoder

ADXSJD sits between ADXT and ADXB. Each of its 16 objects (168 bytes) owns an ADXB decoder handle, reads ADX
data from an input SJ, decodes the header and then the stream, and writes the samples into one output SJ per
channel; a fill count and a skip count let the caller pad or drop output samples. Most of the file is
one-line wrappers that read an ADXB value through the object's handle. The source is `src/cri/adxsjd.c`. It
builds with Sony EE GCC 2.96 at `-O2 -G0` as one whole file (`cri_adxsjd` in `units.tsv`, its rows in
`unit-objects.json`; [whole-file units](emitted-functions.md#whole-file-units)).

## Extent

| part | range | evidence |
| --- | --- | --- |
| code | `0x265f28` up to `0x2674e8` | ADXRNA ends before it; the encoder (`0x2674e8`) starts a new file; every function in the range reads the object table or forwards through an object's ADXB handle |
| strings | `0x4ee3a0` up to `0x4ee3e8` | the header-decode failure message (`E03010901 ADXB_DecodeHeader:`), right after ADXRNA's |
| data | `0x4a52c8` up to `0x4a5d58` | a use count the Sofdec ADX glue raises and lowers, a word the header step reads, then the object table |

## Layout

An object (`AdxSjdObj`) holds the in-use byte, the state (`AdxSjdStat`: stop, decoding the header,
decoding, done), the channel count, the ADXB handle, the input SJ, the two output SJs, the two output chunks
the decode callback fills, counters of decoded samples and bytes, the loop and trap words the reset sets, two
caller-set pairs at +72 and +80, a 64-byte block whose address one wrapper returns, and the fill and skip
counts. The server step pads each output SJ with silence for the fill count and moves samples back for the
skip count, each under the ADX critical section.

## Open questions

- No string names the functions; they keep their address names until callers outside the file can be
  renamed with them (the Sofdec glue and ADXT call most of them).
- Five ADXB getters are declared returning `int` here: their wrappers tail-call them, which a `short` or
  `char` return would not allow; `src/cri/adxb.c` defines them with the narrower types.
- Four functions have no source and link from the retail image: the header step at `0x2662f8`, the decode
  callback at `0x266590`, and the two decode steps at `0x2666b0` and `0x266a18`.
- The reset (`0x265fb0`) and the counter update (`0x266be0`) keep the permuter-found constructs their drafts
  matched with.
