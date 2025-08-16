// Copyright 2009 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

//go:build hermit
// +build hermit

package os

import (
	"errors"
	"sync"
	"syscall"
	"time"
)

// The only signal values guaranteed to be present in the os package on all
// systems are os.Interrupt (send the process an interrupt) and os.Kill (force
// the process to exit). On Windows, sending os.Interrupt to a process with
// os.Process.Signal is not implemented; it will return an error instead of
// sending a signal.
var (
	Interrupt Signal = syscall.SIGINT
	Kill      Signal = syscall.SIGKILL
)

// ErrProcessDone indicates a Process has finished.
var ErrProcessDone = errors.New("os: process already finished")

// Process stores the information about a process created by StartProcess.
type Process struct {
	Pid    int
	handle uintptr      // handle is accessed atomically on Windows
	isdone uint32       // process has been successfully waited on, non zero if true
	sigMu  sync.RWMutex // avoid race between wait and signal
}

// A Signal represents an operating system signal.
// The usual underlying implementation is operating system-dependent:
// on Unix it is syscall.Signal.
type Signal interface {
	String() string
	Signal() // to distinguish from other Stringers
}

// Getpid returns the process id of the caller.
func Getpid() int { return syscall.Getpid() }

// Getppid returns the process id of the caller's parent.
func Getppid() int { return syscall.Getppid() }

// Signal sends a signal to the Process.
// Sending Interrupt on Windows is not implemented.
func (p *Process) Signal(sig Signal) error {
	return syscall.ENOSYS
}

// ProcessState stores information about a process, as reported by Wait.
type ProcessState struct {
	pid    int                // The process's id.
	rusage *syscall.Rusage
}

// Exited reports whether the program has exited.
// On Unix systems this reports true if the program exited due to calling exit,
// but false if the program terminated due to a signal.
func (p *ProcessState) Exited() bool {
	return true
}

// Kill causes the Process to exit immediately. Kill does not wait until
// the Process has actually exited. This only kills the Process itself,
// not any other processes it may have started.
func (p *Process) Kill() error {
	return syscall.ENOSYS
}

func (p *ProcessState) userTime() time.Duration {
	return time.Duration(p.rusage.Utime.Nano()) * time.Nanosecond
}

func (p *ProcessState) systemTime() time.Duration {
	return time.Duration(p.rusage.Stime.Nano()) * time.Nanosecond
}

// UserTime returns the user CPU time of the exited process and its children.
func (p *ProcessState) UserTime() time.Duration {
	return p.userTime()
}

// SystemTime returns the system CPU time of the exited process and its children.
func (p *ProcessState) SystemTime() time.Duration {
	return p.systemTime()
}

// ExitCode returns the exit code of the exited process, or -1
// if the process hasn't exited or was terminated by a signal.
func (p *ProcessState) ExitCode() int {
	return -1
}