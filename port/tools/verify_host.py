#!/usr/bin/env python3
"""verify_host.py — the native host boots, loads a stage, and runs its frame loop.

The `dw4` executable is the engine host (P6.1/P2.6): it must print the platform seam, the object
graph census, the ported `igObject_InitHeader` result and the merged geometry, then write one PNG
per frame with the frames differing (so the loop is really stepping, not writing one image twice).

  tools/verify_host.py [--tool build/dw4] [--roms <dir>] [--stage stag0102.igb] [--ref 1]
"""
import argparse
import os
import re
import struct
import subprocess
import sys
import tempfile
import zlib

HERE = os.path.dirname(os.path.abspath(__file__))
PORT = os.path.dirname(HERE)
DEFAULT_ROMS = os.path.join(PORT, "..", "..", "local/extracted")
BG = (18, 22, 30)


def coverage(path):
    d = open(path, "rb").read()
    w, h = struct.unpack(">II", d[16:24])
    idat = b""
    i = 8
    while i + 8 <= len(d):
        ln, typ = struct.unpack(">I", d[i:i + 4])[0], d[i + 4:i + 8]
        if typ == b"IDAT":
            idat += d[i + 8:i + 8 + ln]
        i += 12 + ln
    raw = zlib.decompress(idat)
    if len(raw) != (w * 4 + 1) * h:
        return None
    n = 0
    for y in range(h):
        row = raw[y * (w * 4 + 1) + 1:][:w * 4]
        for x in range(0, len(row), 4):
            if (row[x], row[x + 1], row[x + 2]) != BG:
                n += 1
    return n / float(w * h)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--tool", default=os.path.join(PORT, "build", "dw4"))
    ap.add_argument("--roms", default=DEFAULT_ROMS)
    ap.add_argument("--stage", default="stag0102.igb")
    ap.add_argument("--ref", type=int, default=1)
    a = ap.parse_args()
    if not os.path.exists(a.tool):
        print("  host: %s not built" % a.tool)
        return 1
    with tempfile.TemporaryDirectory() as tmp:
        r = subprocess.run([a.tool, "--roms", a.roms, "--stage", a.stage, "--ref", str(a.ref),
                            "--frames", "2", "--spin", "40", "--w", "320", "--h", "240",
                            "--out-dir", tmp], capture_output=True, text=True)
        if r.returncode != 0:
            print("  host failed: %s" % (r.stderr.strip() or r.stdout.strip()))
            return 1
        out = r.stdout
        need = ["platform seam:", "boot: FUN_002595e0", "object graph:", "scene:",
                "igObject_InitHeader:", "merged geometry:", "update: FUN_0025a580"]
        missing = [n for n in need if n not in out]
        f0 = os.path.join(tmp, "frame_0000.png")
        f1 = os.path.join(tmp, "frame_0001.png")
        if missing or not os.path.exists(f0) or not os.path.exists(f1):
            print("  host output missing %s / frames: %s" % (missing, out))
            return 1
        c0, c1 = coverage(f0), coverage(f1)
        same = open(f0, "rb").read() == open(f1, "rb").read()
        # a boot line and a live loop: the header is the ported engine function's output
        hdr = [l for l in out.splitlines() if "igObject_InitHeader" in l]
        obj = [l for l in out.splitlines() if "object graph:" in l]

        # the engine's boot: the three Insight managers from `FUN_002595e0`, each constructed the
        # way its matched `_Create` does (reflected size 0x20, its class's recovered vtable, flags
        # 0x1).  The vtables are the classes' own, from the `<Class>_GetVTable` map;
        # before the fix the schema knew only the 478 RTTI vtables, so these three fell
        # back to the base igObject vtable 0x52f0f0.
        mlines = [l.strip() for l in out.splitlines() if l.strip().startswith("manager ")]
        seen_mgr = {}
        for l in mlines:
            m = re.match(r"manager\s+(\S+)\s+.*\+0 = (0x[0-9a-f]+)", l)
            if m:
                seen_mgr[m.group(1)] = m.group(2)
        managers_ok = (len(mlines) == 3 and seen_mgr == {
            "igEnbayaContextPool": "0x529110",
            "igAnimationCombinerBoneInfoPool": "0x529e70",
            "igAnimationStatePool": "0x52a020",
        } and all("created" in l and "flags = 0x1" in l for l in mlines))
        # the frame tick is FUN_0025a580's per-frame setup: the `+0x94`/`+0x9c` fields 0.1,
        # `+0xa0` 1.0, `+0x5e`/`+0xa8` 1, and `+0xe8` peaks at 1 because the context is one-shot
        # (acquire -> run -> release every tick).
        ulines = [l for l in out.splitlines() if "frame context acquire/release" in l]
        tick_ok = bool(ulines) and all(s in ulines[0] for s in (
            "+0xe8 peak = 1", "+0x94 = 0.10", "+0xa0 = 1.00", "+0x5e = 1", "+0xa8 = 1"))
        gate_ok = any("app object: constructed" in l and "+0x18 = set" in l
                      for l in out.splitlines())
        tick_ok = tick_ok and gate_ok

        # the window/present backend (SDL2): it must open the headless driver and present the
        # frame; if the build has no SDL2 the test reports the skip rather than failing.
        window_ok = True
        rw = subprocess.run([a.tool, "--roms", a.roms, "--stage", a.stage, "--ref", str(a.ref),
                             "--frames", "1", "--w", "160", "--h", "120", "--window",
                             "--headless", "--out-dir", tmp], capture_output=True, text=True)
        wl = [l.strip() for l in rw.stdout.splitlines() if l.strip().startswith("window:")]
        if "not compiled in" in rw.stdout:
            print("  host window: SDL2 not compiled in, skipped")
        elif rw.returncode == 0 and wl and "compiled in" in wl[0] and "headless" in wl[0]:
            # the present path reorders channels silently if the SDL pixel format is wrong: the
            # window shows red as blue while the PNG from the same buffer is right, so the tool
            # presents a test colour and reads it back -- require that line, not just "presented".
            order = [l for l in wl if "pixel order" in l]
            if order and "pixel order ok" in order[0]:
                print("  host window: SDL2 headless present ok, pixel order ok")
            else:
                print("  host window: BAD (%s)" % (order[0] if order else "no pixel-order line"))
                window_ok = False
        else:
            print("  host window: BAD (%s)" % (wl[0] if wl else (rw.stdout or rw.stderr).strip()))
            window_ok = False

        # the Vulkan present backend (src/vk_present.c): with no window it initialises the loader and
        # a real device, which is checkable anywhere (SDL's dummy driver has no Vulkan window).  The
        # loaded device name and the format/byte-order choice are the two things worth asserting: an
        # sRGB swapchain would gamma-shift the frame and a B,G,R,A one would swap red and blue, and
        # both are decided at device/format selection time.
        vk_ok = True
        rv = subprocess.run([a.tool, "--roms", a.roms, "--stage", a.stage, "--ref", str(a.ref),
                             "--frames", "1", "--w", "160", "--h", "120", "--vulkan", "--headless",
                             "--out-dir", tmp], capture_output=True, text=True,
                            env=dict(os.environ, SDL_VIDEODRIVER="dummy"))
        vl = [l.strip() for l in rv.stdout.splitlines() if l.strip().startswith("vulkan:")]
        if not vl:
            print("  host vulkan: not compiled in, skipped")
        elif rv.returncode == 0 and any("device only" in l for l in vl) and \
                any("device \"" in l for l in vl):
            dev = [l for l in vl if 'device "' in l][0]
            print("  host vulkan: loader + device ok (%s)" % dev.split("device ")[1].split(" (queue")[0])
        else:
            print("  host vulkan: BAD (%s)" % (vl[0] if vl else (rv.stderr or rv.stdout).strip()))
            vk_ok = False

        # the GPU backend (EGL/GLES offscreen FBO): same camera, a non-degenerate and
        # deterministic frame.  It runs on llvmpipe here; without GL the test reports the skip.
        gl_ok = True
        gl_dirs = []
        for run in (0, 1):
            d = os.path.join(tmp, "gl%d" % run)
            os.makedirs(d, exist_ok=True)
            gl_dirs.append(os.path.join(d, "frame_0000.png"))
            rg = subprocess.run([a.tool, "--roms", a.roms, "--stage", a.stage,
                                 "--ref", str(a.ref), "--frames", "1", "--w", "160", "--h", "120",
                                 "--camera", "--gl", "--out-dir", d], capture_output=True, text=True)
            if run == 0 and "not compiled in" in rg.stdout:
                print("  host gl: EGL/GLES not compiled in, skipped")
                gl_ok = True
                break
            if rg.returncode != 0:
                print("  host gl: BAD (%s)" % (rg.stdout or rg.stderr).strip())
                gl_ok = False
                break
        if gl_ok and len(gl_dirs) == 2 and os.path.exists(gl_dirs[0]) and os.path.exists(gl_dirs[1]):
            cov = coverage(gl_dirs[0])
            same_gl = open(gl_dirs[0], "rb").read() == open(gl_dirs[1], "rb").read()
            gl_ok = cov is not None and cov >= 0.05 and same_gl
            print("  host gl: coverage %.1f%%, two runs identical: %s  %s"
                  % (100.0 * (cov or 0.0), "yes" if same_gl else "NO", "ok" if gl_ok else "BAD"))

        ok = (c0 is not None and 0.02 <= c0 <= 0.98 and not same
              and "0x52f0f0" in hdr[0] and managers_ok and tick_ok and window_ok and gl_ok and vk_ok)
        print("  host boot: %s" % (obj[0].strip() if obj else "?"))
        print("  host managers: %d constructed, %s"
              % (len(mlines), "ok" if managers_ok else "BAD"))
        print("  host frames: coverage %.1f%%, frames differ: %s, tick %s  %s"
              % (100.0 * (c0 or 0), "yes" if not same else "NO",
                 "ok" if tick_ok else "BAD", "ok" if ok else "BAD"))
        return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
