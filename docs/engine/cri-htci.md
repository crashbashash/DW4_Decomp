# CRI HTCI: the host-file device

HTCI (`HTCI/PS2EE Ver.2.69` at `0x4f0590`) is the cvFs device for files on the development host
(`host:`), read through the IOP file calls and SRD. It keeps 13 file handles of 48 bytes, opens files
(optionally through a cache of files opened in advance from a file list), queues sector reads on SRD and
tracks their completion, and loads the file list that the cache uses. The source is `src/cri/htci.c`. It
builds with Sony EE GCC 2.96 at `-O2 -G0` as one whole file (`cri_htci` in `units.tsv`, its rows in
`unit-objects.json`; [whole-file units](emitted-functions.md#whole-file-units)).

## Extent

| part | range | evidence |
| --- | --- | --- |
| code | `0x275370` up to `0x276e50` | the file opens with the function that reads the build-string pointer and returns the device's entry table; the functions before it use DVCI's data; the LSC module starts at `0x276e50` with its own data and strings |
| read-only data | `0x4f05d0` up to `0x4f0aa8` | a jump table, then the module's messages in code order; LSC's messages follow |
| data | `0x4ab5d8` up to the path buffer at `0x4abb10` | the build-string pointer, the error callback and its context, the entry table, the handles, the file-list table and the path buffers |

The source writes its messages as string literals, as the original did: GCC then lays out the object's
read-only data exactly as retail has it (one jump table, then each message once, 8-byte aligned, in the
order the code first uses it), so the whole pool links from the one object. Two functions copy short
literals (`"/"`, `"host:"`) inline, which only a literal gives.

Compiling the file whole matters: the cache lookup at `0x276220` matches only with the two helpers it calls
compiled earlier in the same file, because those calls are then known not to throw.

## Layout

A handle (`HtCiFile`, 48 bytes) holds the in-use and state bytes, the request, the 64-bit file size (read
unsigned where it is compared with the read end and signed where a read is clamped), the position and sector
count, the buffer and the SRD request. The file-list table (`HtCiTable` at `0x4ab9f0`) holds the list, its
entry count, its file count and the length of each name.

## Integer-typed list pointer

The table's pointer to its entries is declared `int` and cast to the entry type at each use, as the owner
approved on the condition already applied to cvFs ([CRI cvFs](cri-cvfs.md#integer-typed-slots)): one
declaration, used by every function that touches it, all of them matching, none needing the pointer form.
With a pointer type, GCC's alias analysis lets the first scheduling pass move the pointer's load above the
`int` stores that precede it in the cache lookup by name, and ten words differ.

## Open questions

- The functions and fields have names from the messages only (`htCiGetFileSize`, `htCiOpen`, `htCiReqRd`,
  `htCiStopTr`, `htCiLoadDirInfo`); the rest are named from use.
- The five 20-byte wrappers just before the file (`0x2752f8` up to `0x27536c`) call SRD functions and are
  called from game code; whether they end DVCI or are a file of their own is unknown.
- Four helpers that `0x276090` calls are defined old-style and called without arguments: retail never loads
  their argument register at those calls.
