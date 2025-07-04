import sqlite3
import os

DB_PATH = "bad_apple.db"
FRAME_DIR = "/data/data/com.termux/files/home/ascii_frames"  # Change to your frame path

conn = sqlite3.connect(DB_PATH)
cur = conn.cursor()

frame_files = sorted(f for f in os.listdir(FRAME_DIR) if f.endswith(".txt"))

for idx, fname in enumerate(frame_files):
    with open(os.path.join(FRAME_DIR, fname), "r") as f:
        content = f.read()
        cur.execute("INSERT INTO frames (id, content) VALUES (?, ?)", (idx, content))

conn.commit()
conn.close()

print(f"Loaded {len(frame_files)} frames into database.")
