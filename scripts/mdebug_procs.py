#!/usr/bin/env python3
"""mdebug_procs.py OBJECT.o...: the procedure records of an SDK object's `.mdebug` section.

Sony's EE objects carry ECOFF symbolic debug data in `.mdebug`. Each function has a procedure record giving its
address, frame size, frame register and return-address register, and its source lines. The compiler writes frame
register 29 and return register 31 for every function it emits, leaves included (`.frame $sp,N,$31`); a routine
assembled from a `.S` file without `.frame`/`.ent` directives has 0 and 0. So the records say, member by member,
which functions were compiled C and which were hand-written assembly. Extract members with `ar x LIB.a`.

    python3 scripts/mdebug_procs.py alarm.o klib.o

Prints one line per procedure: object, address, name, frame size, frame register, return register, source file.
"""
import struct
import sys


def section(data, wanted):
    shoff, = struct.unpack_from("<I", data, 0x20)
    shnum, shstrndx = struct.unpack_from("<HH", data, 0x30)
    headers = [struct.unpack_from("<10I", data, shoff + 40 * i) for i in range(shnum)]
    names = headers[shstrndx][4]
    for h in headers:
        end = data.index(b"\0", names + h[0])
        if data[names + h[0]:end] == wanted:
            return h[4], h[5]
    return None


def cstr(data, offset):
    return data[offset:data.index(b"\0", offset)].decode(errors="replace")


def procedures(data):
    """[(address, name, frame size, frame register, return register, file)]."""
    found = section(data, b".mdebug")
    if found is None:
        return []
    base = found[0]
    h = struct.unpack_from("<hh23i", data, base)
    ipd_max, cb_pd = h[7], h[8]
    cb_sym, cb_ss, ifd_max, cb_fd = h[10], h[16], h[19], h[20]
    out = []
    for f in range(ifd_max):
        fd = struct.unpack_from("<6I4i2h7I", data, cb_fd + 72 * f)
        rss, iss_base, isym_base, ipd_first, cpd = fd[1], fd[2], fd[4], fd[10], fd[11]
        source = cstr(data, cb_ss + iss_base + rss)
        for p in range(ipd_first, ipd_first + cpd):
            if p >= ipd_max:
                break
            adr, isym, _iline, _regmask, _regoffset, _iopt, _fregmask, _fregoffset, frame, framereg, pcreg = \
                struct.unpack_from("<I8i2h", data, cb_pd + 52 * p)[:11]
            iss, = struct.unpack_from("<i", data, cb_sym + 12 * (isym_base + isym))
            out.append((adr, cstr(data, cb_ss + iss_base + iss), frame, framereg, pcreg, source))
    return out


def main(paths):
    if not paths:
        print(__doc__.strip())
        return 2
    for path in paths:
        data = open(path, "rb").read()
        for adr, name, frame, framereg, pcreg, source in procedures(data):
            print("%s\t%#06x\t%s\tframe %d\t$%d\t$%d\t%s" % (path, adr, name, frame, framereg, pcreg, source))
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
