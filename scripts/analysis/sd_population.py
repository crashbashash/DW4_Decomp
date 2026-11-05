#!/usr/bin/env python3
"""Classify every asm/*.s function as MWCC-style or GCC-style from its words.

GCC evidence: callee-saved register stored with `sd` (opcode 0x3f) off sp, or a
branch-likely (beql/bnel/blezl/bgtzl).  MWCC evidence: callee-saved register
stored with `sq`, or `slt/sltu` into `at`.  Prints contiguous GCC runs.
Usage: python3 scripts/analysis/sd_population.py
"""
import glob
import re

PAT = re.compile(r'\.word\s+(0x[0-9a-f]+)\s+/\* ([0-9a-f]+):')
SAVED = set(range(16, 24)) | {30}


def classify(ws):
    gcc = mwcc = False
    sd_saved = False
    for w in ws:
        op, base, rt = w >> 26, (w >> 21) & 31, (w >> 16) & 31
        if op == 0x3f and base == 29 and rt in SAVED:
            gcc = sd_saved = True
        if op in (0x14, 0x15, 0x16, 0x17):
            gcc = True
        if op == 0x1f and base == 29 and rt in SAVED:
            mwcc = True
        if op == 0 and (w & 63) in (0x2a, 0x2b) and (w >> 11) & 31 == 1:
            mwcc = True
    return ('G' if gcc else 'M' if mwcc else '.'), sd_saved


def main():
    rows = []
    for f in glob.glob('asm/*.s'):
        ws, addr = [], None
        for line in open(f):
            m = PAT.search(line)
            if m:
                addr = addr or int(m.group(2), 16)
                ws.append(int(m.group(1), 16))
        if ws:
            c, sd = classify(ws)
            rows.append((addr, len(ws) * 4, c, sd))
    rows.sort()
    cur = None
    for a, sz, c, sd in rows:
        if c == '.':
            continue
        if cur is None or cur[0] != c:
            if cur:
                print(*cur[:1], hex(cur[1]), hex(cur[2]), cur[3], 'sd-saved', cur[4])
            cur = [c, a, a, 0, 0]
        cur[2] = a
        cur[3] += 1
        cur[4] += sd
    print(*cur[:1], hex(cur[1]), hex(cur[2]), cur[3], 'sd-saved', cur[4])


if __name__ == '__main__':
    main()
