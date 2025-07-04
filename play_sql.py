import subprocess
subprocess.Popen(["ffplay", "-nodisp", "-autoexit", "bad_apple.mp3"])
import sqlite3
import time
import os

DB_PATH = "bad_apple.db"
FPS = 10
DELAY = 1 / FPS

conn = sqlite3.connect(DB_PATH)
cur = conn.cursor()

cur.execute("SELECT content FROM frames ORDER BY id")
frames = cur.fetchall()

for frame in frames:
    os.system("clear")  # or "cls" on Windows
    print(frame[0])
    time.sleep(DELAY)

conn.close()
