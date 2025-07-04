import java.io.*;
import java.nio.file.*;
import java.util.*;
import java.util.concurrent.TimeUnit;

public class BadApple {
    private static final String FRAME_DIR = "/data/data/com.termux/files/home/ascii_frames";
    private static final String AUDIO_FILE = "/data/data/com.termux/files/home/bad_apple.mp3";
    private static final int FRAME_RATE = 10; // FPS
    private static final long FRAME_DELAY_MS = 1000 / FRAME_RATE;

    public static void clearConsole() {
        // ANSI escape codes to clear terminal and move cursor to top-left
        System.out.print("\033[H\033[2J");
        System.out.flush();
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        // Launch ffplay audio asynchronously
        ProcessBuilder pb = new ProcessBuilder("ffplay", "-nodisp", "-autoexit", "-loglevel", "quiet", AUDIO_FILE);
        Process audioProcess = pb.start();

        // Read frame files and sort
        List<Path> frames = new ArrayList<>();
        try (DirectoryStream<Path> stream = Files.newDirectoryStream(Paths.get(FRAME_DIR), "*.txt")) {
            for (Path entry : stream) {
                frames.add(entry);
            }
        }
        frames.sort(Comparator.naturalOrder());

        long startTime = System.currentTimeMillis();

        for (int i = 0; i < frames.size(); i++) {
            List<String> lines = Files.readAllLines(frames.get(i));
            clearConsole();
            for (String line : lines) {
                System.out.println(line);
            }

            // Sync frame rate
            long nextFrameTime = startTime + (i + 1) * FRAME_DELAY_MS;
            long sleepTime = nextFrameTime - System.currentTimeMillis();
            if (sleepTime > 0) {
                Thread.sleep(sleepTime);
            }
        }

        // Wait for audio to finish before exit
        audioProcess.waitFor();
    }
}
