import os

FRAME_DIR = "/data/data/com.termux/files/home/ascii_frames"
OUTPUT_DIR = "/data/data/com.termux/files/home/bf_frames"

os.makedirs(OUTPUT_DIR, exist_ok=True)

def char_to_bf(char, prev=0):
    code = ""
    diff = ord(char) - prev
    if diff > 0:
        code += "+" * diff
    elif diff < 0:
        code += "-" * abs(diff)
    code += "."
    return code, ord(char)

for frame in sorted(os.listdir(FRAME_DIR)):
    if not frame.endswith(".txt"):
        continue

    with open(os.path.join(FRAME_DIR, frame)) as f:
        content = f.read()

    bf_code = ""
    prev = 0
    for c in content:
        code, prev = char_to_bf(c, prev)
        bf_code += code

    output_name = frame.replace(".txt", ".bf")
    with open(os.path.join(OUTPUT_DIR, output_name), "w") as f:
        f.write(bf_code)
