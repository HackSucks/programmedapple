package main

import (
	"fmt"
	"io/ioutil"
	"os"
	"os/exec"
	"sort"
	"strings"
	"time"
)

const (
	frameDir  = "/data/data/com.termux/files/home/ascii_frames"
	frameRate = 10
	delay     = time.Second / frameRate
	audioFile = "/data/data/com.termux/files/home/bad_apple.mp3"
)

func main() {
	// Optional: Play audio
	exec.Command("ffplay", "-nodisp", "-autoexit", "-loglevel", "quiet", audioFile).Start()

	// Read frame filenames
	files, err := ioutil.ReadDir(frameDir)
	if err != nil {
		fmt.Println("Failed to read frame directory:", err)
		return
	}

	var frameFiles []string
	for _, file := range files {
		if strings.HasSuffix(file.Name(), ".txt") {
			frameFiles = append(frameFiles, file.Name())
		}
	}

	sort.Strings(frameFiles)

	// Play frames
	for _, name := range frameFiles {
		content, err := os.ReadFile(frameDir + "/" + name)
		if err != nil {
			fmt.Println("Error reading frame:", name)
			continue
		}
		fmt.Print("\033[H\033[2J") // Clear screen
		fmt.Print(string(content))
		time.Sleep(delay)
	}
}
