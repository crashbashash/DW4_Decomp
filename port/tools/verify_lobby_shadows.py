#!/usr/bin/env python3
"""Optional retail GS receiver-projection oracle; private captures are inputs.

This compares authored receiver vertices, without fitting a projection or using
retail colours to select candidates. It does not assert synchronized caster pose.
"""
import argparse
import csv
import json
from pathlib import Path
import subprocess
import sys
import tempfile

import numpy as np
from scipy.spatial import cKDTree

PORT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(PORT.parent / "scripts"))
import gsdump  # noqa: E402


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--dump", required=True)
    ap.add_argument("--roms", default=str(PORT.parent.parent / "local/extracted"))
    ap.add_argument("--frame", type=int, default=339)
    ap.add_argument("--light", choices=("hard", "soft"), default="hard")
    ap.add_argument("--tool", default=str(PORT / "build/lobby_frame"))
    ap.add_argument("--json")
    args = ap.parse_args()
    with tempfile.TemporaryDirectory() as tmp:
        png, tsv = Path(tmp)/"frame.png", Path(tmp)/"vertices.tsv"
        subprocess.run([args.tool, args.roms, str(args.frame), str(png), str(tsv), "--"+args.light],
                       check=True, stdout=subprocess.DEVNULL)
        with tsv.open() as stream:
            rows = [r for r in csv.DictReader(stream, delimiter="\t") if int(r["shadow"])]
        assert rows, "native shadow receivers absent"
        xy = np.array([[float(r[k]) for k in ("x", "y")] for r in rows])
        uv = np.array([[float(r[k]) for k in ("u", "v")] for r in rows])
        tree = cKDTree(xy)
        dump = gsdump.read_dump(args.dump)
        state = gsdump.read_state(dump)
        offset = state["CTXT0.XYOFFSET"]
        ox, oy = (offset & 0xffff)/16, ((offset >> 32) & 0xffff)/16
        errors, positions = [], []
        for draw in gsdump.draws(dump):
            # Retail receiver pass: strip, texture, blend, no fog; ALPHA
            # (ZERO-DST)*SRC_ALPHA+DST, never an opaque body/portal draw.
            if draw["state"].get("PRIM_EFF") != 93:
                continue
            assert draw["state"].get(0x42) == 0x46, "receiver blend changed"
            for vertex in draw["verts"]:
                x, y = vertex["XYZ"][0]/16-ox, vertex["XYZ"][1]/16-oy
                if not (0 <= x < 640 and 0 <= y < 448):
                    continue
                candidates = tree.query_ball_point((x, y), .125)
                if not candidates:
                    continue
                # Exclude ambiguous geometry before consulting retail UV.
                values = uv[candidates]
                if np.ptp(values, axis=0).max() > .00001:
                    continue
                s, t, q = vertex["ST"]
                if not q:
                    continue
                errors.append(abs(values[0]-np.array((s, t))/q))
                positions.append(min(np.linalg.norm(xy[i]-(x, y)) for i in candidates))
        assert len(errors) > 500, "too few matched retail receiver instances"
        error = np.array(errors)
        report = {"frame": args.frame, "light": args.light, "matched_receiver_instances": len(errors),
                  "uv_mae": float(error.mean()), "uv_max": float(error.max()),
                  "screen_median_px": float(np.median(positions)),
                  "screen_max_px": float(max(positions))}
        assert report["uv_max"] < .0001, report
        if args.json:
            Path(args.json).write_text(json.dumps(report, indent=2)+"\n")
        print(json.dumps(report, indent=2))


if __name__ == "__main__":
    main()
