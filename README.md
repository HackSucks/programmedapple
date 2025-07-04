# programmedapple
Bad Apple in almost every programming language

This is Bad Apple in many programming languages.

# How? 

Download app called Termux on your phone
 copy your files from /sdcard/Download or whatever doenload folder to ~ like cp /sdcard/Download/badapplefiles ~
Go inside
Copy ascii_frames to ~ like cp -r ascii_frames ~
Copy bad_apple.mp3 to ~ in same fashion
copy bf_frames to ~
Run one of the scripts.


# Currently:
Python (python3 -m apple)
C (./bad_apple_c)
C++ (./bad_apple_cpp)
Java (java BadApple)
JS (node bad_apple.js)
HTML (cd bad_apple_html python -m http.server 8080 and then go to URL localhost:8080)
BrainFuck (
ffplay /storage/emulated/0/bad_apple.mp3 &

for f in /data/data/com.termux/files/home/bf_frames/frame_*.bf; do
  clear
  brainfuck "$f"
  sleep 0.1
done)
Go (./badapple)
Rust (./badapplerust)
Lua (lua apple.lua)
SQL (python -m play_sql)
R (Rscript bad_apple.R)
