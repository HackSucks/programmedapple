#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <errno.h>

#define FRAME_DIR "/data/data/com.termux/files/home/ascii_frames"
#define AUDIO_FILE "/data/data/com.termux/files/home/bad_apple.mp3"
#define MAX_FRAMES 10000
#define FRAME_DELAY 100000  // microseconds (0.1 sec = 10 FPS)

// Function to compare filenames
int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

// Function to clear terminal
void clear_screen() {
    printf("\033[2J\033[H");
    fflush(stdout);
}

int main() {
    // Fork to play audio
    pid_t pid = fork();

    if (pid == 0) {
        // Child process: play audio
        execlp("ffplay", "ffplay", "-nodisp", "-autoexit", "-loglevel", "quiet", AUDIO_FILE, (char *)NULL);
        perror("execlp failed");
        exit(1);
    } else if (pid < 0) {
        perror("fork failed");
        return 1;
    }

    // Parent process: read frames
    DIR *dir = opendir(FRAME_DIR);
    if (!dir) {
        perror("opendir failed");
        return 1;
    }

    char *frames[MAX_FRAMES];
    int frame_count = 0;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, ".txt")) {
            frames[frame_count] = strdup(entry->d_name);
            frame_count++;
            if (frame_count >= MAX_FRAMES) break;
        }
    }
    closedir(dir);

    // Sort frames
    qsort(frames, frame_count, sizeof(char *), compare);

    // Display frames
    for (int i = 0; i < frame_count; i++) {
        char path[512];
        snprintf(path, sizeof(path), "%s/%s", FRAME_DIR, frames[i]);

        FILE *f = fopen(path, "r");
        if (!f) continue;

        clear_screen();
        char line[512];
        while (fgets(line, sizeof(line), f)) {
            printf("%s", line);
        }
        fclose(f);
        usleep(FRAME_DELAY);

        free(frames[i]);  // cleanup
    }

    // Wait for audio to finish
    waitpid(pid, NULL, 0);
    return 0;
}
