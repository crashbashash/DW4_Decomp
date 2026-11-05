#!/usr/bin/env python3
"""
dw4_rng.py - Digimon World 4 RNG tools.

The game's RNG is a stock MT19937 initialised with the **1997 original
`sgenrand()` seeding** (multiplier 69069), not the later `init_genrand()`.
The seed is the hard-coded constant 5150 (0x141E) and is never changed
during play.  Everything that advances the state goes through the Lua
binding `be:SYSgetRandom(M)`, which is `genrand() % M`.

Subcommands
-----------
  check  <ram.bin> [...]   locate the live MT object in a 32 MB EE-RAM dump
                           (or a PCSX2 savestate) and report where it sits on
                           the seed-5150 sequence (twist #, draws since boot).
  sites  [NDMW.AFS]        enumerate every `be:SYSgetRandom(M)` call site in
                           the Lua bytecode corpus and print/emit a table.
  seq    [N]               print the first N genrand() outputs for seed 5150.

Live RAM addresses (stable, non-ASLR heap):
  *(0x58A1B8) + 0x30        -> igMersenneTwisterRandomNumber instance
  RNG + 0x00  vtable 0x52B8E0   +0x04 refcount/flag
  RNG + 0x08  _mti (current index, 0..624)
  RNG + 0x0C  _mt[624] (624 x u32)
"""
import argparse
import glob
import os
import struct
import sys

N = 624
M = 397
MATRIX_A = 0x9908B0DF
UPPER = 0x80000000
LOWER = 0x7FFFFFFF
SEED = 5150               # 0x141E - the game's only seed constant
VTABLE = 0x0052B8E0       # igMersenneTwisterRandomNumber vtable
MASK = 0xFFFFFFFF


def sgenrand(seed):
    """Original (1997) MT19937 seeding: 69069 LCG, high 16 bits per step."""
    mt = [0] * N
    for i in range(N):
        mt[i] = seed & 0xFFFF0000
        seed = (69069 * seed + 1) & MASK
        mt[i] |= (seed & 0xFFFF0000) >> 16
        seed = (69069 * seed + 1) & MASK
    return mt


def twist(mt):
    for k in range(N - M):
        y = (mt[k] & UPPER) | (mt[k + 1] & LOWER)
        mt[k] = (mt[k + M] ^ (y >> 1) ^ (MATRIX_A if y & 1 else 0)) & MASK
    for k in range(N - M, N - 1):
        y = (mt[k] & UPPER) | (mt[k + 1] & LOWER)
        mt[k] = (mt[k + M - N] ^ (y >> 1) ^ (MATRIX_A if y & 1 else 0)) & MASK
    y = (mt[N - 1] & UPPER) | (mt[0] & LOWER)
    mt[N - 1] = (mt[M - 1] ^ (y >> 1) ^ (MATRIX_A if y & 1 else 0)) & MASK
    return mt


def temper(y):
    y ^= y >> 11
    y = (y ^ ((y << 7) & 0x9D2C5680)) & MASK
    y = (y ^ ((y << 15) & 0xEFC60000)) & MASK
    y ^= y >> 18
    return y


def sequence(seed=SEED, twists=8000):
    """Yield successive states; state j has consumed j full twists."""
    st = sgenrand(seed)
    yield 0, st
    for j in range(1, twists + 1):
        st = twist(st)
        yield j, st


def find_rng(ram):
    """Return (addr, mti, state) for the first MT object, or None."""
    pat = struct.pack("<I", VTABLE)
    i = 0
    while True:
        a = ram.find(pat, i)
        if a < 0:
            return None
        i = a + 1
        if a + 12 + N * 4 <= len(ram):
            mti = struct.unpack_from("<I", ram, a + 8)[0]
            if 0 <= mti <= N:
                return a, mti, list(struct.unpack_from("<%dI" % N, ram, a + 12))
    return None


def check_file(path, seed=SEED):
    d = open(path, "rb").read()
    found = find_rng(d)
    if not found:
        return None
    addr, mti, state = found
    # index the seed sequence by the first 6 words
    index = {}
    for j, st in sequence(seed, 20000):
        index.setdefault(tuple(st[:6]), (j, tuple(st)))
    hit = index.get(tuple(state[:6]))
    if not hit or hit[1] != tuple(state):
        # not on the seed sequence (reseeding or a different seed)
        return dict(path=path, addr=addr, mti=mti, twist=None, draws=None,
                    state0=state[0])
    j = hit[0]
    # twist#0 is the raw sgenrand(5150) array before any draw; mti is 624 there.
    draws = 0 if j == 0 else (j - 1) * N + mti
    return dict(path=path, addr=addr, mti=mti, twist=j, draws=draws,
                state0=state[0])


def cmd_check(args):
    ok = True
    for path in args.files:
        r = check_file(path)
        name = os.path.basename(path)
        if not r:
            print("%-24s no RNG object found" % name)
            ok = False
            continue
        if r["twist"] is None:
            print("%-24s RNG @ %#x mti=%d state0=%08x  NOT on seed-%d sequence"
                  % (name, r["addr"], r["mti"], r["state0"], SEED))
            ok = False
        else:
            print("%-24s RNG @ %#x mti=%4d state0=%08x  twist#%-3d draws_since_boot=%d"
                  % (name, r["addr"], r["mti"], r["state0"], r["twist"], r["draws"]))
    return 0 if ok else 1


def cmd_seq(args):
    st = sgenrand(SEED)
    st = twist(st)
    idx = 0
    for _ in range(args.count):
        if idx >= N:
            st = twist(st)
            idx = 0
        print("%6d  %08x  -> %%2=%d %%6=%d %%19=%d %%99=%d %%121=%d %%299=%d"
              % (_, temper(st[idx]), temper(st[idx]) % 2, temper(st[idx]) % 6,
                 temper(st[idx]) % 19, temper(st[idx]) % 99,
                 temper(st[idx]) % 121, temper(st[idx]) % 299))
        idx += 1
    return 0


def cmd_sites(args):
    sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
    from lua_dump import parse_chunk
    data = open(args.afs, "rb").read()
    count = struct.unpack("<I", data[4:8])[0]
    entries = [struct.unpack("<II", data[8 + i * 8:16 + i * 8])
               for i in range(count)]

    def walk(fn, path, out):
        code = fn["code"]
        for pc, ins in enumerate(code):
            if (ins & 0x3F) == 16:  # OP_PUSHSELF
                u = ins >> 6
                if 0 <= u < len(fn["kstr"]) and fn["kstr"][u] == "SYSgetRandom":
                    mod = None
                    for q in range(pc + 1, min(pc + 6, len(code))):
                        o2 = code[q] & 0x3F
                        if o2 == 6:
                            mod = (code[q] >> 6) - (1 << 25)
                            break
                        if o2 in (8, 9):
                            k = code[q] >> 6
                            mod = fn["knum"][k] if 0 <= k < len(fn["knum"]) else "?"
                            break
                        if o2 == 2:
                            break
                    out.append((path, pc, mod))
        for i, p in enumerate(fn["kproto"]):
            walk(p, path + ".%d" % i, out)

    total = 0
    rows = []
    for e, (off, size) in enumerate(entries):
        seg = data[off:off + size]
        i = ci = 0
        while True:
            j = seg.find(b"\x1bLua", i)
            if j < 0:
                break
            i = j + 1
            try:
                _, main, _ = parse_chunk(seg, j)
            except Exception:
                continue
            out = []
            walk(main, "e%04d/c%04d" % (e, ci), out)
            rows.extend(out)
            ci += 1
    if args.tsv:
        with open(args.tsv, "w") as f:
            f.write("entry\tchunk\tpc\tmodulus\n")
            for path, pc, mod in rows:
                f.write("%s\t%d\t%s\n" % (path, pc, mod))
        print("wrote %s" % args.tsv)
    from collections import Counter
    print("SYSgetRandom sites: %d" % len(rows))
    print("moduli: %s" % dict(Counter(str(r[2]) for r in rows)))
    return 0


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    c = sub.add_parser("check", help="locate + classify the RNG in RAM dumps")
    c.add_argument("files", nargs="+")
    c.set_defaults(func=cmd_check)
    s = sub.add_parser("seq", help="print genrand() outputs for seed 5150")
    s.add_argument("count", nargs="?", type=int, default=16)
    s.set_defaults(func=cmd_seq)
    t = sub.add_parser("sites", help="enumerate Lua SYSgetRandom call sites")
    t.add_argument("afs", nargs="?",
                   default="local/extracted/NDMW.AFS")
    t.add_argument("--tsv", default=None)
    t.set_defaults(func=cmd_sites)
    args = ap.parse_args()
    sys.exit(args.func(args))


if __name__ == "__main__":
    main()
