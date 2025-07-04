#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <chrono>
#include <thread>
#include <algorithm>
#include <unistd.h>     // fork, execlp
#include <sys/types.h>  // pid_t
#include <sys/wait.h>   // waitpid
#include <cstdlib>      // exit

namespace fs = std::filesystem;

int main() {
    const std::string frame_dir = "/data/data/com.termux/files/home/ascii_frames";
    const std::string audio_file = "/data/data/com.termux/files/home/bad_apple.mp3";
    const double frame_delay = 0.1; // 10 FPS

    // Fork to play audio asynchronously
    pid_t pid = fork();

    if (pid == 0) {
        // Child process: run ffplay to play audio, no video display
        execlp("ffplay", "ffplay", "-nodisp", "-autoexit", "-loglevel", "quiet", audio_file.c_str(), nullptr);
        // If exec fails
        std::cerr << "Failed to exec ffplay\n";
        exit(1);
    } else if (pid < 0) {
        std::cerr << "Fork failed\n";
        return 1;
    }

    // Parent process: display frames
    std::vector<std::string> frames;

    // Read and sort frame filenames
    for (const auto& entry : fs::directory_iterator(frame_dir)) {
        if (entry.path().extension() == ".txt") {
            frames.push_back(entry.path().string());
        }
    }
    std::sort(frames.begin(), frames.end());

    auto start_time = std::chrono::steady_clock::now();

    for (size_t i = 0; i < frames.size(); ++i) {
        std::ifstream file(frames[i]);
        if (!file) continue;

        // Clear terminal screen (ANSI escape codes)
        std::cout << "\033[2J\033[H";

        // Print frame content
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << "\n";
        }
        file.close();

        // Calculate next frame time and sleep
        auto next_frame_time = start_time + std::chrono::duration<double>(frame_delay * (i + 1));
        std::this_thread::sleep_until(next_frame_time);
    }

    // Wait for ffplay (audio) to finish before exiting
    waitpid(pid, nullptr, 0);

    return 0;
}
