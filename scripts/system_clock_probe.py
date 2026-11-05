#!/usr/bin/env python3
"""system_clock_probe.py -- reproduce the system-clock writer scan and the WAIT-timer
structural scan over the savestate RAM images.

Usage:
  python3 scripts/system_clock_probe.py writers [--asm asm]
  python3 scripts/system_clock_probe.py timers RAM.bin [RAM.bin ...]
  python3 scripts/system_clock_probe.py verify STATE.p2s [--min-start NS] [--quiet]

`verify` extracts the EE RAM of a savestate and checks, from memory only: the system clock
object (invariants of FUN_00237730's fields), every 30-frame WAIT timer, and the pointer chain
timer -> property array -> property list -> action -> manager -> clock object, naming the graph.
It exits 0 when at least one complete chain is found.

RAM.bin is an EE RAM image from `scripts/p2s_ram.py STATE --extract eeMemory.bin --out RAM.bin`.
Nothing here is committed evidence on its own; it is a finder for the hypotheses in
docs/engine/system-clock.md.
"""
import argparse
import re
import struct
import subprocess
import sys
import tempfile
from pathlib import Path

SYS_CLOCK = 0x006E98D8             # clock object; the +0x50 clock is read as (mgr+0xc)+0x50
DURATION_30F = 499_999_968          # EE model of 1e9f*30/60 (see docs/engine/action2-timing.md)
ONE_F32 = 0x3F800000


def writers(asm_dir):
    """Units that read-modify-write a 64-bit word at offset 80 (0x50) of one base register."""
    pat = re.compile(r"/\* ([0-9a-f]{8}): (.*?) \*/")
    for f in sorted(Path(asm_dir).glob("*.s")):
        ins = pat.findall(f.read_text(errors="ignore"))
        ops = [t for _, t in ins]
        for k, t in enumerate(ops):
            m = re.match(r"sd\s+(\w+),80\((\w+)\)", t)
            if not m:
                continue
            base = m.group(2)
            prev = ops[max(0, k - 10):k]
            if any(re.match(r"ld\s+\w+,80\(" + base + r"\)", p) for p in prev):
                print(f"{f.stem} {ins[k][0]}  {t}   (read-modify-write)")


def timers(paths):
    """Blocks with the WAIT-timer layout: scale 1.0f at +0x10, base at +0x18 equal to
    -(start>>18)<<18, start clock at +0x28, 1.0f at +0x38, duration at +0x20."""
    pat = struct.pack("<q", DURATION_30F)
    for p in paths:
        b = Path(p).read_bytes()
        found = []
        i = b.find(pat)
        while i != -1:
            t = i - 0x20
            if i % 8 == 0 and t >= 0x10 and t + 0x40 <= len(b):
                scale = struct.unpack_from("<I", b, t + 0x10)[0]
                one = struct.unpack_from("<I", b, t + 0x38)[0]
                base = struct.unpack_from("<q", b, t + 0x18)[0]
                start = struct.unpack_from("<q", b, t + 0x28)[0]
                if scale == ONE_F32 and one == ONE_F32 and base < 0 and (-base) % (1 << 18) == 0 and start > 0 and base == -((start >> 18) << 18):
                    refs = []
                    tgt = struct.pack("<I", t)
                    j = b.find(tgt)
                    while j != -1:
                        if j % 4 == 0:
                            refs.append(j)
                        j = b.find(tgt, j + 1)
                    found.append((t, start >> 18, refs))
            i = b.find(pat, i + 1)
        print(p)
        for t, tick, refs in found:
            print(f"  timer 0x{t:08x}  start_tick {tick}  incoming_ptrs {[hex(r) for r in refs]}")


def _extract(state):
    p2s = Path(__file__).with_name("p2s_ram.py")
    out = tempfile.NamedTemporaryFile(suffix=".ram", delete=False).name
    subprocess.run([sys.executable, str(p2s), state, "--extract", "eeMemory.bin", "--out", out],
                   check=True, capture_output=True)
    data = Path(out).read_bytes()
    Path(out).unlink()
    return data


def _refs(b, addr):
    tgt = struct.pack("<I", addr)
    out, j = [], b.find(tgt)
    while j != -1:
        if j % 4 == 0:
            out.append(j)
        j = b.find(tgt, j + 1)
    return out


def _cstr(b, p):
    if not 0x100000 <= p < len(b) - 64:
        return None
    s = b[p:p + 48].split(b"\0")[0]
    return s.decode() if len(s) >= 3 and all(32 <= c < 127 for c in s) else None


def verify(state, min_start=0, quiet=False):
    b = _extract(state)
    w = lambda a: struct.unpack_from("<I", b, a)[0]
    q = lambda a: struct.unpack_from("<q", b, a)[0]
    log = (lambda *a: None) if quiet else print
    S = SYS_CLOCK
    clock, sample, delta, scale = q(S + 0x50), q(S + 0x38), q(S + 0x40), w(S + 0x48)
    ok_clock = clock > 0 and clock == sample and 0 < delta < 2_000_000_000 and scale == 0x40000
    log(f"clock object {S:#x}: clock {clock} ns  sample {sample}  delta {delta}  scale {scale:#x}  "
        f"{'OK' if ok_clock else 'INVARIANTS FAIL'}")
    found = 0
    for t, start in _timers_in(b):
        if start < min_start:
            continue
        name = _cstr(b, w(t + 8))
        if name != "WAIT":
            continue
        dur, base = q(t + 0x20), q(t + 0x18)
        chain = None
        for slot in _refs(b, t):                      # array element holding the timer
            for k in range(0, 9):
                arr = slot - 4 * k
                for x in _refs(b, arr):               # list header's data pointer (+8)
                    hdr = x - 8
                    if hdr < 8 or not (k < w(hdr) <= w(hdr + 4) <= 4096):
                        continue
                    for y in _refs(b, hdr - 8):       # property list wrapper referenced by act+0x28
                        act = y - 0x28
                        if not 0x100000 <= act < len(b) - 0x40 or w(act) != 0x00534350:
                            continue
                        mgr = w(act + 0x10)
                        if 0x100000 <= mgr < len(b) - 0x20 and w(mgr + 0xC) == S:
                            data = w(act + 0xC)
                            wk = w(act + 0x38)
                            if not (0x100000 <= data < len(b) - 12 and 0x100000 <= wk < len(b) - 0x45):
                                continue
                            chain = (act, mgr, _cstr(b, w(data + 8)), b[wk + 0x44])
        log(f"WAIT timer {t:#010x} name={name!r} duration={dur} base={base} start={start} "
            f"(start>>18 = {start >> 18}, elapsed so far {(clock >> 18) - (start >> 18)} ticks)")
        if chain:
            act, mgr, graph, wstate = chain
            log(f"  chain: act {act:#x} -> mgr {mgr:#x} -> mgr+0xc == clock object; graph {graph!r}; "
                f"work+0x44 wait state {wstate}")
            found += 1
        else:
            log("  chain: NOT FOUND")
    return 0 if (ok_clock and found) else 1


def _timers_in(b):
    pat = struct.pack("<q", DURATION_30F)
    i = b.find(pat)
    while i != -1:
        t = i - 0x20
        if i % 8 == 0 and t >= 0x10 and t + 0x40 <= len(b):
            sc, one = struct.unpack_from("<II", b, t + 0x10)[0], struct.unpack_from("<I", b, t + 0x38)[0]
            base, start = struct.unpack_from("<qq", b, t + 0x18)[0], struct.unpack_from("<q", b, t + 0x28)[0]
            if sc == ONE_F32 and one == ONE_F32 and base < 0 and start > 0 and base == -((start >> 18) << 18) and struct.unpack_from("<I", b, t)[0] == 0x00534830:
                yield t, start
        i = b.find(pat, i + 1)


def main():
    ap = argparse.ArgumentParser()
    sub = ap.add_subparsers(dest="cmd", required=True)
    w = sub.add_parser("writers")
    w.add_argument("--asm", default="asm")
    t = sub.add_parser("timers")
    t.add_argument("ram", nargs="+")
    v = sub.add_parser("verify")
    v.add_argument("state")
    v.add_argument("--min-start", type=int, default=0)
    v.add_argument("--quiet", action="store_true")
    a = ap.parse_args()
    if a.cmd == "writers":
        writers(a.asm)
    elif a.cmd == "verify":
        return verify(a.state, a.min_start, a.quiet)
    else:
        timers(a.ram)


if __name__ == "__main__":
    sys.exit(main())
