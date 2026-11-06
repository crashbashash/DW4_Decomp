#!/usr/bin/env python3
"""
igb_parse.py — print an igBinary (IGB) blob's header, string table and file references.

The format is described in docs/engine/igbinary-format.md. `igb_dir.py` decodes the type
directory and `igb_inst.py` the object records.

Usage:
  igb_parse.py <file.igb>            # print header + extracted strings
  igb_parse.py <file.igb> --dump section   # hexdump a section
"""
import re
import struct
import sys


VALIDITY = 0xfada


class IGB:
    def __init__(self, data):
        self.d = data
        self.hdr = struct.unpack_from("<12I", data, 0)
        assert self.hdr[10] == VALIDITY, f"bad validity word 0x{self.hdr[10]:08x}"

    # --- header fields (reverse-engineered; see docs/engine/igbinary-format.md) ---
    @property
    def section1_records(self):
        return self.hdr[1]

    @property
    def class_count(self):
        return self.hdr[3]

    @property
    def object_stream_bytes(self):
        return self.hdr[4]

    @property
    def section2_records(self):
        return self.hdr[5]

    @property
    def content_pool_bytes(self):
        return self.hdr[6]

    @property
    def memory_blocks(self):
        return self.hdr[7]

    @property
    def ofs_interface_name(self):
        return self.hdr[8]

    @property
    def n_strings(self):
        return self.hdr[9]

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

    def report(self):
        h = self.hdr
        print(f"hdr[0]          0x{h[0]:x}")
        print(f"section 1       {self.section1_records} records")
        print(f"hdr[2]          0x{h[2]:x}")
        print(f"classes         {self.class_count}")
        print(f"object stream   0x{self.object_stream_bytes:x} bytes")
        print(f"section 2       {self.section2_records} records")
        print(f"content pool    0x{self.content_pool_bytes:x} bytes")
        print(f"memory blocks   {self.memory_blocks}")
        print(f"interface name  @0x{self.ofs_interface_name:x}")
        print(f"strings         {self.n_strings}")
        print(f"flags           0x{h[11]:08x} (version {h[11] & 0xffff})")

        start, strs = self.parse_string_table()
        print(f"\nstring table: {len(strs)} strings @ 0x{start:x}")
        for ln, f1, f2, s in strs:
            print(f"  len={ln:3d} f1={f1} f2={f2}  {s.decode('ascii','replace')}")

        print(f"\ninterface name @0x{self.ofs_interface_name:x}: "
              f"{self._cstr(self.ofs_interface_name)!r}")
        print("file references:")
        for m in re.finditer(rb"[\x20-\x7e]{1,128}\.igb(?=\x00)", self.d):
            print(f"  0x{m.start():x}: {m.group().decode('ascii')!r}")

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
