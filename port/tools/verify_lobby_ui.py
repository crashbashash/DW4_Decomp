#!/usr/bin/env python3
"""Check greeting fonts, portrait and window against a private retail GS dump.

The animated bottom decoration is reported separately: this held screenshot does
not establish its phase. Clipped GS boundary vertices have no original counterpart.
"""
import argparse
from collections import defaultdict
import csv
import json
from pathlib import Path
import subprocess
import sys
import tempfile

import numpy as np
from PIL import Image

PORT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PORT.parent / "scripts"))
import gsdump  # noqa: E402


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--roms", default=str(PORT.parent.parent / "local/extracted"))
    ap.add_argument("--dump", required=True)
    ap.add_argument("--page", type=int, choices=range(39, 54), default=39,
                    help="retail greeting page in the capture (default: 39)")
    ap.add_argument("--json")
    args = ap.parse_args()
    dump = gsdump.read_dump(args.dump)
    state = gsdump.read_state(dump)
    offset = state["CTXT0.XYOFFSET"]
    ox, oy = (offset & 0xffff)/16, ((offset >> 32) & 0xffff)/16
    retail = defaultdict(list)
    textures = {}
    for draw in gsdump.draws(dump):
        if not draw["state"]["PRIM_EFF"] & 64:
            continue
        tex0 = draw["state"].get(6, state["CTXT0.TEX0"])
        tex = gsdump.tex0_fields(tex0)
        if (tex["TW"], tex["TH"]) not in ((128, 32), (64, 64), (512, 512)):
            continue
        for vertex in draw["verts"]:
            if "ST" not in vertex:
                continue
            x, y = vertex["XYZ"][0]/16-ox, vertex["XYZ"][1]/16-oy
            if y < 275:
                continue
            s, t, q = vertex["ST"]
            key = (tex["TW"], tex["TH"], *vertex["RGBA"])
            retail[key].append((x, y, s/q, t/q))
            textures[tex["TW"], tex["TH"]] = tex0
    report = {}
    with tempfile.TemporaryDirectory() as tmp:
        out = Path(tmp)
        subprocess.run([str(PORT / "build/lobby_ui_frame"), args.roms, str(args.page),
                        str(out/"ui.png"), str(out/"ui.tsv"), tmp], check=True)
        native = defaultdict(set)
        with (out/"ui.tsv").open() as f:
            for row in csv.DictReader(f, delimiter="\t"):
                x, y, u, v = (float(row[c]) for c in ("x", "y", "u", "v"))
                if not (0 <= x <= 640 and 275 <= y <= 448):
                    continue
                key = tuple(int(row[c]) for c in ("w", "h", "r", "g", "b", "a"))
                native[key].add((x, y, u, v))
        for key, vertices in native.items():
            candidates = np.array(retail[key]).reshape(-1, 4)
            errors, decoration = [], []
            for vertex in vertices:
                delta = abs(candidates-np.array(vertex))
                same_uv = delta[(delta[:, 2:] < .002).all(axis=1)]
                error = float(same_uv[:, :2].max(axis=1).min()) if len(same_uv) else 999.
                # Define this exclusion before reading retail positions: only the
                # window atlas's bottom decoration moves during its LOOPL clock.
                (decoration if key[:2] == (128, 32) and vertex[1] >= 430 else errors).append(error)
            label = "window" if key[0] == 128 else "portrait" if key[0] == 64 else "speaker" if key[4] == 60 else "body"
            if not errors:
                assert decoration, (label, key)
                report["bottom_decoration"] = {"vertices": len(decoration),
                                               "max_position_error_px": max(decoration)}
                continue
            report[label] = {"vertices": len(errors), "max_position_error_px": max(errors),
                             "matched_within_0.126_px": sum(e <= .126 for e in errors)}
            assert errors and max(errors) <= .126, (label, report[label])
            if decoration:
                report["bottom_decoration"] = {"vertices": len(decoration),
                                               "max_position_error_px": max(decoration)}
        # Announcement-window boundary vertices lie outside the viewport;
        # GS clipping creates new UVs there. Only its decoration survives this
        # unclipped-vertex comparison, and is phase-dependent as above.
        required = {"bottom_decoration", "body"} if args.page in (49, 50) else {"window", "portrait", "speaker", "body"}
        assert required <= report.keys(), (args.page, report)
        for wh, tex0 in textures.items():
            rgba, w, h, _fields = gsdump.texture_rgba(dump, tex0)
            actual = np.array(Image.open(out/f"{w}x{h}.png"))
            expected = np.frombuffer(rgba, dtype=np.uint8).reshape(h, w, 4)
            assert np.array_equal(actual, expected), f"texture {wh} differs from retail VRAM"
        report["textures_rgba_byte_exact"] = len(textures)
    if args.json:
        Path(args.json).write_text(json.dumps(report, indent=2)+"\n")
    print(json.dumps(report, indent=2))


if __name__ == "__main__":
    main()
