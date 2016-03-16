package main

import (
	"os"
)

func main() {
	f, _ := os.Open(os.Args[1])
	buf := make([]byte, 4+2400*2*12/8)

	totalcoarse := uint(0)
	totalfine := uint(0)
	for {
		r, err := f.Read(buf)
		if err != nil {
			break
		}
		for i := 4; i < r-3; {
			combined := uint(buf[i])
			i++
			combined |= uint(buf[i]) << 8
			i++
			combined |= uint(buf[i]) << 16
			i++
			coarse := combined & 0xfff
			fine := combined >> 12

			totalcoarse += coarse
			totalfine += fine
		}
	}
}
