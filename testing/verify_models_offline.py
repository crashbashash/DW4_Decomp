#!/usr/bin/env python3
"""verify_models_offline.py — the offline model extractor against the live game's models.

`scripts/igb_models.py` reads geometry straight out of a stage's model pack: a
pack states its own addressing, a stream block's `_memSize` is its
content size exactly and every block is laid out 4-byte aligned, so no replay
and no running game are involved.  This is the rule test for that claim, and it is the
reason the extractor is trusted: it compares the offline result against the ground truth a
*paused game's* RAM holds.

Ground truth is a saved EE RAM dump read with the live extractor
(`scripts/extract_live_models.py --from <dump>`), which walks the objects where the game
actually put them; the offline side walks the pack.  Both write OBJ, and a model counts as
verified only when an offline model's vertex list is byte-identical to a live one.  The live namer
(`scripts/name_live_models.py --from <dump>`, keyed by the heap address in the OBJ filename) then
checks the *names*: the offline shape -> attribute link against the live `M_*Shape` walk.

    python3 testing/verify_models_offline.py
    python3 testing/verify_models_offline.py --dump <ee-dump>.bin --pack ../local/extracted/NDMW.AFS:621

The two sides legitimately differ in coverage: the dump holds only the models the session
had loaded (669 of them, for one stage), while the pack holds the stage's whole set (549
attributes), so models the live session never loaded cannot match and are reported as such
rather than as failures.
"""
import argparse
import os
import subprocess
import sys
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)
DEFAULT_DUMP = os.path.join(os.path.dirname(ROOT), "local", "evidence", "models", "ee-pre-leomon.bin")
DEFAULT_PACK = os.path.join(os.path.dirname(ROOT), "local", "extracted", "NDMW.AFS") + ":621"
REPO = os.path.join(ROOT)
LIVE = os.path.join(ROOT, "scripts", "extract_live_models.py")
LIVE_NAMES = os.path.join(ROOT, "scripts", "name_live_models.py")
FLOOR = 400          # measured 450 of 549; below this something in the chain has broken
NAME_FLOOR = 350     # measured 383 of the 386 live-named models agree


def verts(path):
    return [l.strip() for l in open(path) if l.startswith("v ")]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--dump", default=DEFAULT_DUMP)
    ap.add_argument("--pack", default=DEFAULT_PACK, help="NDMW.AFS:<entry>")
    args = ap.parse_args()
    afs, entry = args.pack.rsplit(":", 1)
    entry = int(entry, 0)
    for path in (args.dump, afs, LIVE, os.path.join(REPO, "scripts", "igb_models.py")):
        if not os.path.exists(path):
            print("missing %s" % path)
            return 2

    sys.path.insert(0, os.path.join(REPO, "scripts"))
    import igb_ids
    import igb_models
    import igb_pool

    refl = igb_ids.igb_inst.load_reflection(os.path.join(REPO, "data", "reflection.json"))
    data = open(afs, "rb").read()
    off = int.from_bytes(data[8 + 8 * entry:12 + 8 * entry], "little")
    P = igb_pool.load(afs, hex(off), refl)

    offline = []
    for g in igb_models.read_geometry(P, refl):
        got, why = igb_models.extract(P, g)
        if got is None:
            offline.append((g["vertex_array"], None, why, g.get("name")))
        else:
            # the same text the OBJ writer emits, so the live lines can be compared directly
            offline.append((g["vertex_array"],
                            ["v %.6f %.6f %.6f" % v for v in got[0]], None, g.get("name")))

    with tempfile.TemporaryDirectory() as tmp:
        live_dir = os.path.join(tmp, "live")
        os.mkdir(live_dir)
        r = subprocess.run([sys.executable, LIVE, "--from", args.dump, "--pack",
                            "%s:%d" % (afs, entry), "--out-dir", live_dir],
                           capture_output=True, text=True)
        if r.returncode != 0:
            print(r.stdout + r.stderr)
            return 1
        summary = (r.stdout + r.stderr).strip().splitlines()[-1]
        live = {}
        for n in os.listdir(live_dir):
            v = verts(os.path.join(live_dir, n))
            if v:
                # keyed by content: a pack may hold several attributes with identical vertices
                # (a reused primitive), and the live attrs that share them are all valid names
                live.setdefault(tuple(v), []).append(n[6:-4])
        live_counts = {len(k) for k in live}
        # the live namer keys names by heap address and the live OBJ files are
        # `model_<address>.obj`, so the two line up with no further mapping
        names_path = os.path.join(tmp, "names.tsv")
        r = subprocess.run([sys.executable, LIVE_NAMES, "--from", args.dump, "--tsv",
                            names_path], capture_output=True, text=True)
        live_names = {}
        if r.returncode == 0 and os.path.exists(names_path):
            for line in open(names_path):
                if line.startswith("#"):
                    continue
                a, _, nm = line.rstrip("\n").partition("\t")
                live_names[a.lower().removeprefix("0x")] = nm

    matched = absent = differing = failed = named = agreed = 0
    for _id, v, why, name in offline:
        if v is None:
            failed += 1
            continue
        hits = live.get(tuple(v))
        if not hits:
            if len(v) not in live_counts:
                absent += 1     # the live session never had a model this size
            else:
                differing += 1
            continue
        matched += 1
        want = {live_names[a] for a in hits if a in live_names}
        if want:
            named += 1
            if name and name in want:
                agreed += 1

    total = len(offline)
    print("live: %s" % summary)
    print("offline: %d geometry attributes from %s entry %d" % (total, os.path.basename(afs),
                                                                entry))
    print("  byte-identical to a live model: %d" % matched)
    print("  a vertex count the live session never had: %d" % absent)
    print("  same vertex count, different geometry (another prop): %d" % differing)
    print("  the extractor could not resolve: %d" % failed)
    if named:
        print("  names: %d of the %d matched models are named live, %d identical offline"
              % (named, matched, agreed))
    if failed:
        print("FAIL: an unresolvable attribute means the chain or the alignment rule broke")
        return 1
    if matched < FLOOR:
        print("FAIL: only %d models verified (floor %d)" % (matched, FLOOR))
        return 1
    if named and agreed < NAME_FLOOR:
        print("FAIL: only %d of %d names agree (floor %d)" % (agreed, named, NAME_FLOOR))
        return 1
    print("OK: %d of %d models byte-identical to the live game's%s"
          % (matched, total, (", and %d of %d names identical" % (agreed, named)) if named else ""))
    return 0


if __name__ == "__main__":
    sys.exit(main())
