# CRI MPEG start-code scanner

A small Sofdec file between the CRI MPS core (`CRI MPS/PS2EE Ver.1.924`) and the next module. It classifies an
MPEG video start code read from four bytes (picture, slice, user data, sequence header, extension, sequence end,
group of pictures) and scans a buffer for a start code whose class is in a mask (one scanner works back from the end of the buffer).
The MPS and MPV code call it. The source is `src/cri/startcode.c`. It builds with Sony EE GCC 2.96 at `-O2 -G0`
as one whole file (`cri_startcode` in `units.tsv`, its rows in `unit-objects.json`;
[whole-file units](emitted-functions.md#whole-file-units)).

## Extent

| part | range | evidence |
| --- | --- | --- |
| code | `0x28dc78` up to `0x28ea10` | the functions before it use the MPS object and its words and call the MPS internals; the function at `0x28ea10` uses the next file's data |
| data | `0x4bcc70` up to `0x4bccb8` | a 72-byte table read by the two slice checks; the MPS object ends at `0x4bcc70` |

Compiling the file whole matters: the other two scanners match only with the classifier compiled before them
in the same file, because the call is then known not to throw, which decides how their delay slots are filled.

## Open questions

- The file's CRI name and its functions' names.
- The two slice checks at `0x28e028` and `0x28e4d0` have no source: they read the bitstream a byte at a time
  through an expanded bit-reader and look codes up in the table, and link from the retail image after the
  file's other members.
