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

	source := rand.NewSource(time.Now().UnixNano())
	r := rand.New(source)

	n, _ := strconv.Atoi(os.Args[1])
	m, _ := strconv.Atoi(os.Args[2])

	var text strings.Builder
	text.WriteString(fmt.Sprintf("%d %d\n", n, m))
	for i := 0; i < n; i++ {
		for j := 0; j < m; j++ {
			text.WriteString(fmt.Sprint(r.Intn(2)))
		}
		text.WriteString("\n")
	}

	file.WriteString(text.String())
}
