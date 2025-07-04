FRAME_DIR <- "/data/data/com.termux/files/home/ascii_frames"
FPS <- 10
FRAME_DELAY <- 1 / FPS

# Get frame files
frames <- list.files(FRAME_DIR, pattern = "\\.txt$", full.names = TRUE)
frames <- sort(frames)

# Play frames
for (frame_path in frames) {
  system("clear")  # Clear terminal
  frame <- readLines(frame_path, warn = FALSE)
  cat(paste(frame, collapse = "\n"), "\n")
  Sys.sleep(FRAME_DELAY)
# Start audio (non-blocking)
system("ffplay -nodisp -autoexit bad_apple.mp3 &")

# Continue playing frames (same as above)
}
