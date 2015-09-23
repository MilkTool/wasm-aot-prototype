;; RUN: waot %s | FileCheck %s
(module
;; CHECK: return.wast

(func (return))
;; CHECK: define internal void @0
;; CHECK: ret void
(func (result i32)
;; CHECK: define internal i32 @1
  (return (i32.const 42)))
;; CHECK: ret i32 42
(func (result f64)
;; CHECK: define internal double @2
  (return (f64.const 0.1)))
;; CHECK: ret double 1.000000e-01
)