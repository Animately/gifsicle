package main

/*
#cgo LDFLAGS: -L. -lgifsicle_shared
#include <stdlib.h>
#include "gifsicle_gif.h"
*/
import "C"
import (
	"fmt"
	"os"
	"strings"
	"unsafe"
)

//export gifsicle_progress_callback
func gifsicle_progress_callback(value C.int) {
	fmt.Printf("progress %d \n", value)
}

func main() {
	args := os.Args[1:]
	megred_args := strings.Join(args, " ")

	arguments := fmt.Sprintf("go %s", megred_args)
	cargs := C.CString(arguments)

	C.gifsicle_process(cargs)

	C.free(unsafe.Pointer(cargs))
}
