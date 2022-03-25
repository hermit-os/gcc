// Copyright 2009 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

package os

import (
	"runtime"
	//"sync/atomic"
	"syscall"
)

func (p *Process) wait() (ps *ProcessState, err error) {
	return nil, NewSyscallError("wait", err)
}

func (p *Process) release() error {
	// NOOP for unix.
	p.Pid = -1
	// no need for a finalizer anymore
        runtime.SetFinalizer(p, nil)
	return nil
}

func (p *Process) kill() error {
	return syscall.ENOSYS
}

func startProcess(name string, argv []string, attr *ProcAttr) (p *Process, err error) {
/*	sysattr := &syscall.ProcAttr{
		Dir: attr.Dir,
		Env: attr.Env,
		Sys: attr.Sys,
	}

	for _, f := range attr.Files {
		ysattr.Files = append(sysattr.Files, f.Fd())
	}

        pid, h, e := syscall.StartProcess(name, argv, sysattr)
	if e != nil {
		return nil, &PathError{"fork/exec", name, e}
	}

	return newProcess(pid, h), nil*/

	return nil, &PathError{"fork/exec", name, syscall.ENOSYS}
}

// ProcessState stores information about a process, as reported by Wait.
type ProcessState struct {
	pid    int              // The process's id.
}

// Pid returns the process id of the exited process.
func (p *ProcessState) Pid() int {
	return p.pid
}

func (p *ProcessState) success() bool {
	return false
}

func (p *ProcessState) String() string {
	if p == nil {
		return "<nil>"
	}
	return "exit status: unknown"
}
