// Copyright 2012 The Go Authors. All rights reserved.
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file.

//go:build hermit

package signal

import (
	"context"
	"os"
)

// Stop causes package signal to stop relaying incoming signals to c.
// It undoes the effect of all prior calls to Notify using c.
// When Stop returns, it is guaranteed that c will receive no more signals.
func Stop(c chan<- os.Signal) {
	panic("os/signal: Stop not supported on hermit")
}

func Notify(c chan<- os.Signal, sig ...os.Signal) {
	panic("os/signal: Notify not supported on hermit")
}

func NotifyContext(parent context.Context, signals ...os.Signal) (ctx context.Context, stop context.CancelFunc) {
	panic("os/signal: NotifyContext not supported on hermit")
}