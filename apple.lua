local lfs = require("lfs")
local FRAME_DIR = "/data/data/com.termux/files/home/ascii_frames"
local FPS = 10
local DELAY = 1.0 / FPS

-- Get sorted list of frame files
local frames = {}
for file in lfs.dir(FRAME_DIR) do
    if file:match("%.txt$") then
        table.insert(frames, file)
    end
end

-- Sort by frame number
table.sort(frames)

-- Optional: Play audio (non-blocking)
os.execute("ffplay -nodisp -autoexit -loglevel quiet bad_apple.mp3 &")

-- Play frames
for i, frame in ipairs(frames) do
    local path = FRAME_DIR .. "/" .. frame
    local f = io.open(path, "r")
    local content = f:read("*a")
    f:close()

    os.execute("clear")  -- or "cls" on Windows
    print(content)
    os.execute("sleep " .. DELAY)
end
