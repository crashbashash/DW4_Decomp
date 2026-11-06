#!/usr/bin/env python3
"""verify_present.py -- the SDL and Vulkan backends must put the same pixels on the screen.

The frame is CPU-rasterised, so the Vulkan swapchain must change nothing about the picture. A B,G,R,A
swapchain would show red as blue, and an sRGB one would gamma-shift every tone. This shows a built-in
test frame through each backend on a private Xvfb display and compares the screen with the expected
pixels. It needs no game data or GPU and opens nothing on the desktop. What is missing is skipped,
or fails under --require.
"""
import argparse
import os
import select
import shutil
import subprocess
import sys
import tempfile
import time

W, H = 256, 224
START_TIMEOUT = 20.0
SETTLE = 0.5


def expected_frame():
    out = bytearray()
    for y in range(H):
        for x in range(W):
            out += bytes(((x * 7 + y) & 255, (x + y * 5) & 255, (x * 3 + y * 11) & 255))
    return bytes(out)


def start_display():
    """Returns the Xvfb process and its display name, or (None, None)."""
    read_end, write_end = os.pipe()
    server = subprocess.Popen(
        ["Xvfb", "-displayfd", str(write_end), "-screen", "0", "%dx%dx24" % (W, H), "-nolisten", "tcp"],
        pass_fds=(write_end,), stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    os.close(write_end)
    ready, _, _ = select.select([read_end], [], [], START_TIMEOUT)
    number = os.read(read_end, 32).decode().strip() if ready else ""
    os.close(read_end)
    if not number:
        server.terminate()
        server.wait()
        return None, None
    return server, ":" + number


def wait_presenting(proc, log):
    """True once the tool has shown its first frame."""
    deadline = time.monotonic() + START_TIMEOUT
    while time.monotonic() < deadline and proc.poll() is None:
        with open(log) as text:
            if "presenting\n" in text.read():
                return True
        time.sleep(0.05)
    return False


def show_and_capture(tool, backend, env, path):
    """Returns the screen's RGB bytes, or an exit code: 2 for an unavailable backend, 1 for a failure."""
    log = path + ".log"
    with open(log, "w") as out:
        proc = subprocess.Popen([tool, "hold-" + backend], env=env, stdout=out,
                                stderr=subprocess.STDOUT)
    try:
        if not wait_presenting(proc, log):
            return 2 if proc.poll() == 2 else 1
        time.sleep(SETTLE)
        if subprocess.run(["import", "-window", "root", path], env=env,
                          capture_output=True).returncode != 0:
            return 1
    finally:
        proc.terminate()
        try:
            proc.wait(timeout=5)
        except subprocess.TimeoutExpired:
            proc.kill()
            proc.wait()
    from PIL import Image
    image = Image.open(path).convert("RGB")
    return image.tobytes() if image.size == (W, H) else 1


def compare(name, got, want):
    pixels = W * H
    exact = sum(got[i:i + 3] == want[i:i + 3] for i in range(0, 3 * pixels, 3))
    mean = sum(abs(a - b) for a, b in zip(got, want)) / (3.0 * pixels)
    ok = exact == pixels
    print("  present: %s %.3f%% as expected, mean |delta| %.3f  %s"
          % (name, 100.0 * exact / pixels, mean, "ok" if ok else "BAD"))
    return ok


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--tool", default="build/test_gpu_present")
    ap.add_argument("--require", action="store_true", help="fail instead of skipping")
    args = ap.parse_args()

    def skipped(reason):
        print("  present: %s, %s" % (reason, "REQUIRED" if args.require else "skipped"))
        return 1 if args.require else 0

    try:
        import PIL  # noqa: F401
    except ImportError:
        return skipped("no Pillow")
    missing = [name for name in ("Xvfb", "import") if not shutil.which(name)]
    if missing:
        return skipped("%s not installed" % " and ".join(missing))
    if not os.path.exists(args.tool):
        return skipped("no %s" % args.tool)

    server, display = start_display()
    if not server:
        return skipped("Xvfb did not start")
    env = {k: v for k, v in os.environ.items() if k not in ("WAYLAND_DISPLAY", "XAUTHORITY")}
    env.update(DISPLAY=display, SDL_VIDEODRIVER="x11", SDL_AUDIODRIVER="dummy")
    want = expected_frame()
    status = 0
    try:
        with tempfile.TemporaryDirectory(prefix="dw4present-") as tmp:
            for name, backend in (("SDL", "sdl"), ("Vulkan", "vk")):
                got = show_and_capture(args.tool, backend, env, os.path.join(tmp, backend + ".png"))
                if got == 2:
                    status |= skipped("%s unavailable on the virtual display" % name)
                elif got == 1 or isinstance(got, int):
                    print("  present: BAD (%s run gave no capture)" % name)
                    status = 1
                elif not compare(name, got, want):
                    status = 1
    finally:
        server.terminate()
        server.wait()
    return status


if __name__ == "__main__":
    sys.exit(main())
