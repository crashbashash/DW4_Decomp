#!/usr/bin/env python3
"""
igb_parse.py — partial parser for the Insomniac-style igBinary (IGB) format
used by Digimon World 4 (Gap::Core engine, derived from the Insomniac `ig`
object model).

Reverse-engineered from NDMW.IGB (see docs/engine/igbinary-format.md).  This parses the
header, the string table, and extracts the type-name / file-reference strings.
The full object graph is not yet decoded (see docs).

Usage:
  igb_parse.py <file.igb>            # print header + extracted strings
  igb_parse.py <file.igb> --dump section   # hexdump a section
"""
import struct
import sys


class IGB:
    def __init__(self, data):
        self.d = data
        self.hdr = struct.unpack_from("<12I", data, 0)
        self.magic = self.hdr[0]
        assert self.magic == 0x00000100, f"bad magic 0x{self.magic:08x}"

    # --- header fields (reverse-engineered; see docs/engine/igbinary-format.md) ---
    @property
    def version(self):
        return self.hdr[1]

    @property
    def n_strings(self):
        return self.hdr[9]

    @property
    def ofs_interface_name(self):
        return self.hdr[8]

    @property
    def ofs_type_dir(self):
        return self.hdr[5]

    @property
    def ofs_int_array(self):
        return self.hdr[6]

    @property
    def ofs_file_refs(self):
        return self.hdr[10]

    def parse_string_table(self):
        """String table: descriptors {u32 len, u32=1, u32=0} then concatenated
        null-terminated strings. Located at 0x30 (right after the 0x2c header)."""
        n = self.n_strings
        pos = 0x30
        descs = [struct.unpack_from("<III", self.d, pos + 12 * k) for k in range(n)]
        strings_start = pos + 12 * n
        i = strings_start
        out = []
        for ln, f1, f2 in descs:
            s = self.d[i : i + ln - 1]
            out.append((ln, f1, f2, s))
            i += ln
        return strings_start, out

    def strings_near(self, offset, limit=256):
        """Extract null-terminated ASCII strings starting at offset (best effort)."""
        out = []
        i = offset
        end = min(len(self.d), offset + limit)
        while i < end:
            if 32 <= self.d[i] < 127:
                j = self.d.find(b"\x00", i, end)
                if j < 0:
                    break
                s = self.d[i:j]
                if 3 <= len(s) <= 64:
                    out.append((i, s))
                i = j + 1
            else:
                i += 1
        return out

    def report(self):
        h = self.hdr
        print(f"magic  0x{h[0]:08x}  version {h[1]}")
        print(f"hdr[2]={h[2]} (0x{h[2]:x})  hdr[3]={h[3]} (0x{h[3]:x})")
        print(f"ofs_file_refsA  0x{h[4]:x}  ({h[4]})")
        print(f"ofs_type_dir    0x{h[5]:x}  ({h[5]})")
        print(f"ofs_int_array   0x{h[6]:x}  ({h[6]})")
        print(f"hdr[7]          0x{h[7]:x}  ({h[7]})")
        print(f"ofs_iface_name  0x{h[8]:x}  ({h[8]})")
        print(f"n_strings       {h[9]}  (0x{h[9]:x})")
        print(f"ofs_file_refsB  0x{h[10]:x}  ({h[10]})")
        print(f"flags           0x{h[11]:08x}")

        start, strs = self.parse_string_table()
        print(f"\nstring table: {len(strs)} strings @ 0x{start:x}")
        for ln, f1, f2, s in strs:
            print(f"  len={ln:3d} f1={f1} f2={f2}  {s.decode('ascii','replace')}")

        print(f"\ninterface name @0x{self.ofs_interface_name:x}: "
              f"{self._cstr(self.ofs_interface_name)!r}")
        print(f"type dir strings near 0x{self.ofs_type_dir:x}:")
        for off, s in self.strings_near(self.ofs_type_dir, 512):
            print(f"  0x{off:x}: {s.decode('ascii','replace')!r}")
        print(f"file-ref strings near 0x{self.ofs_file_refs:x} & 0x{h[4]:x}:")
        seen = set()
        for base in (self.ofs_file_refs, h[4]):
            for off, s in self.strings_near(base, 512):
                if s.endswith(b".igb") and off not in seen:
                    seen.add(off)
                    print(f"  0x{off:x}: {s.decode('ascii','replace')!r}")

    def _cstr(self, off):
        j = self.d.find(b"\x00", off)
        return self.d[off:j]


def main():
    path = sys.argv[1]
    data = open(path, "rb").read()
    igb = IGB(data)
    if "--dump" in sys.argv:
        off = int(sys.argv[sys.argv.index("--dump") + 1], 0)
        n = 64
        if len(sys.argv) > sys.argv.index("--dump") + 2:
            n = int(sys.argv[sys.argv.index("--dump") + 2], 0)
        print(igb.d[off : off + n].hex())
        print("".join(chr(c) if 32 <= c < 127 else "." for c in igb.d[off : off + n]))
    else:
        igb.report()


if __name__ == "__main__":
    main()
