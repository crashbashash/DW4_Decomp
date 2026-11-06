#!/usr/bin/env python3
"""verify_object.py — the port's runtime object model agrees with the decompilation's decoder.

Constructs every record of a pack as a reflection-typed `igObject` (`dw4asset reflect --json`) and
diffs the named field values against `DW4_Decomp/scripts/igb_inst.py` decoding the same pack.  The
Python decoder is the independent one: it recovers K and the field names from the same reflection
dump, so a mismatch is a port bug, not a shared assumption.

  python3 tools/verify_object.py [--tool build/dw4asset] [--roms <dir>] [--entry 622]
                                 [--class NAME]
"""
import argparse
import json
import os
import struct
import subprocess
import sys
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
PORT = os.path.dirname(HERE)
DEFAULT_ROMS = os.path.join(PORT, "..", "..", "local/extracted")
DEFAULT_DECOMP = os.path.join(PORT, "..")


def afs_entry(path, entry):
    """The (offset, size) of an AFS entry, for igb_inst.py's --blob."""
    with open(path, "rb") as f:
        if f.read(4) != b"AFS\x00":
            raise SystemExit("%s is not an AFS archive" % path)
        n = struct.unpack("<I", f.read(4))[0]
        if entry >= n:
            raise SystemExit("entry %d out of range (%d)" % (entry, n))
        f.seek(8 + 8 * entry)
        return struct.unpack("<II", f.read(8))


def close(a, b):
    if isinstance(a, str) or isinstance(b, str):
        return str(a).rstrip("\x00") == str(b).rstrip("\x00")
    if isinstance(a, list) or isinstance(b, list):
        if not isinstance(a, list) or not isinstance(b, list) or len(a) != len(b):
            return False
        return all(close(x, y) for x, y in zip(a, b))
    if isinstance(a, float) or isinstance(b, float):
        return abs(float(a) - float(b)) <= 1e-3 * max(1.0, abs(float(a)))
    # ids and 32-bit fields are stored unsigned; the port reads them as int32, so mask
    return (int(a) & 0xFFFFFFFF) == (int(b) & 0xFFFFFFFF)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--tool", default=os.path.join(PORT, "build", "dw4asset"))
    ap.add_argument("--roms", default=DEFAULT_ROMS)
    ap.add_argument("--decomp", default=DEFAULT_DECOMP)
    ap.add_argument("--entry", type=int, default=622)
    ap.add_argument("--class", dest="cls", default=None)
    args = ap.parse_args()
    afs = os.path.join(args.roms, "NDMW.AFS")
    off, size = afs_entry(afs, args.entry)

    # the independent reference (all records; --class is applied exactly below, since igb_inst's
    # own --class is a substring match)
    with tempfile.TemporaryDirectory(prefix="dw4-verify-object-") as tmp:
        ref_json = os.path.join(tmp, "ref.json")
        ref_cmd = [sys.executable, os.path.join(args.decomp, "scripts", "igb_inst.py"), afs,
                   "--blob", hex(off), "--json", ref_json, "--quiet"]
        r = subprocess.run(ref_cmd, capture_output=True, text=True)
        if r.returncode != 0:
            print("  igb_inst.py failed: %s" % (r.stderr.strip() or r.stdout.strip()))
            return 1
        with open(ref_json) as fh:
            ref = json.load(fh)
    if args.cls:
        ref = [rec for rec in ref if rec["class"] == args.cls]

    # the port's object model
    port_cmd = [args.tool, "reflect", "--afs", afs, "--entry", str(args.entry), "--json"]
    if args.cls:
        port_cmd += ["--class", args.cls]
    r = subprocess.run(port_cmd, capture_output=True, text=True)
    if r.returncode != 0:
        print("  dw4asset reflect failed: %s" % (r.stderr.strip() or r.stdout.strip()))
        return 1
    got = {rec["off"]: rec for rec in json.loads(r.stdout)["records"]}

    bad = 0
    nrec = nfield = 0
    for rec in ref:
        o = got.get(rec["off"])
        if o is None:
            print("  record 0x%x %s: missing from the port" % (rec["off"], rec["class"]))
            bad += 1
            continue
        nrec += 1
        ref_fields = {k: (v, t) for k, v, t in rec["fields"]}
        port_tid = o.get("tid", {})
        # the port names the class's declared fields, not only the record's descriptors; compare
        # the intersection, and only where the port's declared type equals the descriptor's (the
        # ordinal map has known non-conformers, where either naming would be a guess)
        for name, (val, rtype) in ref_fields.items():
            if name == "_name":
                continue
            if name not in o["fields"]:
                # an array/struct type the schema marks 0xff is named by neither side's match
                continue
            if port_tid.get(name) != rtype:
                continue
            if not close(o["fields"][name], val):
                print("  record 0x%x %s.%s: port %r != ref %r"
                      % (rec["off"], rec["class"], name, o["fields"][name], val))
                bad += 1
            else:
                nfield += 1
        if rec["name"] is not None and o["fields"] is not None:
            pass
    print("  verify_object: %d record(s), %d field value(s) agree, %d disagreement(s)"
          % (nrec, nfield, bad))
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
