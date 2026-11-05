#!/usr/bin/env python3
"""verify_present.py -- the two present backends must put the same pixels on the screen.

The strongest claim to make about the Vulkan path (src/vk_present.c) is that it changes *nothing*
about the picture: the frame is CPU-rasterised, so the swapchain is a transport.  This renders the
same static frame through `--window` (SDL's renderer) and `--vulkan` (the swapchain) at the display's
own size and compares what the screen actually shows.  Both known failure modes are loud in that
comparison -- a B,G,R,A swapchain presents the red logo blue, an sRGB one gamma-shifts every tone --
which is why this is a measurement rather than an assertion about the code.

Uses native X11/XWayland window capture with xdotool and ImageMagick import.
The measured processes use SDL's X11 driver so Wayland sessions expose capturable
XWayland windows; selection is scoped to the launched process. Prints a skip
without the display/tools, so `make check` can always run it.
"""
import argparse
import atexit
import os
import shutil
import shlex
import subprocess
import sys
import tempfile
import time
_PATH_HERE = os.path.dirname(os.path.abspath(__file__))
_PATH_REPO = os.path.dirname(os.path.dirname(_PATH_HERE))
_PATH_WS = os.path.dirname(_PATH_REPO)

HERE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.dirname(HERE)

_TMP = tempfile.mkdtemp(prefix="dw4present-")     # one scratch dir, removed on the way out
_N = iter(range(1000))
atexit.register(lambda: shutil.rmtree(_TMP, ignore_errors=True))


def capture(cmd, env):
    out = os.path.join(_TMP, "shot-%d.png" % next(_N))
    if cmd:
        command = [*shlex.split(cmd), "--out", out]
    else:
        wid = env.get("DW4_WINDOW_ID")
        if not wid:
            search = ["xdotool", "search", "--all", "--onlyvisible"]
            if env.get("DW4_CAPTURE_PID"):
                search += ["--pid", env["DW4_CAPTURE_PID"]]
            search += ["--name", env.get("DW4_WINDOW_PATTERN", "^dw4$")]
            windows = subprocess.run(search, capture_output=True, text=True, env=env)
            ids = windows.stdout.splitlines()
            if windows.returncode != 0 or len(ids) != 1:
                print("  present: expected one game window; set DW4_WINDOW_ID")
                return None
            wid = ids[0]
        command = ["import", "-window", wid, out]
    result = subprocess.run(command, capture_output=True, text=True, env=env)
    if result.returncode != 0:
        return None
    return out if os.path.exists(out) else None


def run_and_grab(tool, run, out, flags, env, grab):
    """Start one windowed run, let it map and settle, grab the screen, tear it down."""
    os.makedirs(out, exist_ok=True)
    logpath = os.path.join(out, "log.txt")
    with open(logpath, "w") as log:
        proc = subprocess.Popen([tool] + run + flags, cwd=ROOT, env=env,
                                stdout=log, stderr=subprocess.STDOUT)
        try:
            time.sleep(8.0)                  # mapping + a few frames before the grab
            shot = grab(cmd=env["DW4_CAPTURE"], env=dict(env, DW4_CAPTURE_PID=str(proc.pid)))
        finally:
            proc.terminate()
            try:
                proc.wait(timeout=5)
            except subprocess.TimeoutExpired:
                proc.kill()
    return shot, open(logpath).read()


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--tool", default=os.path.join(ROOT, "build", "dw4"))
    ap.add_argument("--roms", default=os.environ.get("DW4_ROMS", os.path.join(_PATH_WS, "local/extracted")))
    ap.add_argument("--stage", default="stagml11.igb")
    ap.add_argument("--ref", default="0")
    a = ap.parse_args()

    env = dict(os.environ)
    env["DW4_CAPTURE"] = env.get("DW4_CAPTURE", "")
    env.setdefault("DW4_WINDOW_PATTERN", "^dw4$")
    if not env["DW4_CAPTURE"]:
        env["SDL_VIDEODRIVER"] = "x11"
    missing = [n for n in ("DISPLAY",) if not env.get(n)]
    if missing or not os.path.exists(a.tool) or not os.path.isdir(a.roms):
        print("  present: no X11/XWayland session or missing tool/roms (%s), skipped"
              % (",".join(missing) or "paths"))
        return 0
    try:
        from PIL import Image
    except ImportError:
        print("  present: skipped (no Pillow)")
        return 0
    required = ("xdotool", shlex.split(env["DW4_CAPTURE"])[0]) if env["DW4_CAPTURE"] else ("xdotool", "import")
    if any(not shutil.which(name) for name in required):
        print("  present: X11 capture utilities unavailable, skipped")
        return 0
    # Query the desktop before starting the game; no game window exists yet.
    dimensions = subprocess.run(["xdotool", "getdisplaygeometry"], capture_output=True,
                                text=True, env=env)
    try:
        dw, dh = map(int, dimensions.stdout.split())
    except ValueError:
        print("  present: display geometry unavailable, skipped")
        return 0
    run = ["--roms", a.roms, "--stage", a.stage, "--ref", a.ref, "--camera",
           "--w", str(dw), "--h", str(dh), "--frames", "100000"]

    shots = {}
    for name, flags in (("sdl", ["--window"]), ("vulkan", ["--vulkan"])):
        shot, log = run_and_grab(a.tool, run, os.path.join(_TMP, name),
                                 flags, env, capture)
        if "vulkan: presenting" in log and name == "sdl":
            print("  present: BAD (the SDL run presented through Vulkan)")
            return 1
        if "vulkan: unavailable" in log:
            print("  present: skipped (no Vulkan backend in this build)")
            return 0
        if not shot:
            print("  present: BAD (%s run gave no capture; see log)" % name)
            return 1
        shots[name] = Image.open(shot).convert("RGB")

    a_img, b_img = shots["sdl"], shots["vulkan"]
    if a_img.size != b_img.size:
        print("  present: BAD (capture sizes differ, %s vs %s)" % (a_img.size, b_img.size))
        return 1
    d = [(abs(p[0] - q[0]), abs(p[1] - q[1]), abs(p[2] - q[2]))
         for p, q in zip(a_img.getdata(), b_img.getdata())]
    n = len(d)
    exact = sum(1 for t in d if t == (0, 0, 0))
    mean = sum(sum(t) for t in d) / (3.0 * n)
    # the compositor owns a few pixels (cursor, indicators), and both runs are timing-independent
    ok = exact >= 0.99 * n and mean <= 1.0
    print("  present: SDL vs Vulkan %.3f%% identical, mean |delta| %.3f  %s"
          % (100.0 * exact / n, mean, "ok" if ok else "BAD"))
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
