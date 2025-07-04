const fs = require('fs');
const path = require('path');
const { spawn } = require('child_process');

const FRAME_DIR = "/data/data/com.termux/files/home/ascii_frames";
const AUDIO_FILE = "/data/data/com.termux/files/home/bad_apple.mp3";
const FPS = 10;
const FRAME_DELAY = 1000 / FPS;

function clearScreen() {
  process.stdout.write('\x1Bc'); // Clear screen and move cursor home
}

async function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}

async function playFrames() {
  const files = await fs.promises.readdir(FRAME_DIR);
  const frames = files.filter(f => f.endsWith('.txt')).sort();

  // Spawn ffplay to play audio
  const ffplay = spawn('ffplay', ['-nodisp', '-autoexit', '-loglevel', 'quiet', AUDIO_FILE], {
    stdio: 'ignore'
  });

  const startTime = Date.now();

  for (let i = 0; i < frames.length; i++) {
    const content = await fs.promises.readFile(path.join(FRAME_DIR, frames[i]), 'utf8');
    clearScreen();
    process.stdout.write(content);

    // Sync frame timing
    const nextFrameTime = startTime + (i + 1) * FRAME_DELAY;
    const delay = nextFrameTime - Date.now();
    if (delay > 0) {
      await sleep(delay);
    }
  }

  // Wait for ffplay audio to finish
  await new Promise(resolve => ffplay.on('exit', resolve));
}

playFrames().catch(console.error);
