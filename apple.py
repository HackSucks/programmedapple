import os
import time
import subprocess

FRAME_DIR = "/data/data/com.termux/files/home/ascii_frames"
AUDIO_FILE = "/data/data/com.termux/files/home/bad_apple.mp3"

FRAME_RATE = 10
FRAME_DELAY = 1.0 / FRAME_RATE

# Start ffplay to play audio asynchronously, no window
ffplay_process = subprocess.Popen([
    "ffplay", "-nodisp", "-autoexit", "-loglevel", "quiet", AUDIO_FILE
])

# Load and sort frame files
frames = sorted([f for f in os.listdir(FRAME_DIR) if f.endswith(".txt")])

start_time = time.time()

for i, frame in enumerate(frames):
    frame_path = os.path.join(FRAME_DIR, frame)
    with open(frame_path, "r") as f:
        # Clear screen
        os.system("clear")
        print(f.read())

    # Sync to frame rate precisely
    next_frame_time = start_time + (i + 1) * FRAME_DELAY
    sleep_time = next_frame_time - time.time()
    if sleep_time > 0:
        time.sleep(sleep_time)

# Wait for audio playback to finish before exiting
ffplay_process.wait()
