package main

import (
	"fmt"
	"math/rand"
	"os"
	"strconv"
	"strings"
	"time"
)

func main() {
	file, err := os.OpenFile("gen.txt", os.O_WRONLY|os.O_TRUNC|os.O_CREATE, 0644)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	defer file.Close()

	letters := []string{
		"a", "b", "c", "d", "e", "f", "g", "h", "i",
		"j", "k", "l", "m", "o", "p", "q", "r", "s",
		"t", "q", "v", "w", "q", "x", "y", "z",
	}
	
	source := rand.NewSource(time.Now().UnixNano())
	r := rand.New(source)

	textSize, _ := strconv.Atoi(os.Args[1])
	patternCount, _ := strconv.Atoi(os.Args[2])

	var text strings.Builder
	for i := 0; i < textSize; i++ {
		text.WriteString(letters[r.Intn(4)])
	}
	text.WriteString("\n")

	for i := 0; i < patternCount; i++ {
		for j := 0; j < 1+r.Intn(textSize); j++ {
			text.WriteString(letters[r.Intn(4)])
		}
		text.WriteString("\n")
	}

	file.Write([]byte(text.String()))
}
