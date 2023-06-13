package main

import (
	"bufio"
	"fmt"
	"os"
)

type Object struct {
}

func main() {
	fmt.Printf("pid = %d; press a key to start\n", os.Getpid())
	r := bufio.NewReader(os.Stdin)
	r.ReadString('\n')
	
	n := 1024 * 1024 * 10
	a := []Object{}
	for i:= 0; i < n; i++ {
		o := Object{}
		a = append(a, o)
	}

	fmt.Println("allocation is done. I will enter spinning. Find me with top")
	for {}
}
