clang -O3 -c -emit-llvm -D_CRT_SECURE_NO_WARNINGS -DPERFTOOLS_DLL_DECL= -I../../src -I../../src/windows ../main.cpp ../../src/base/dynamic_annotations.c ../../src/base/logging.cc ../../src/base/spinlock.cc ../../src/base/spinlock_internal.cc ../../src/base/sysinfo.cc ../../src/central_freelist.cc ../../src/common.cc ../../src/fake_stacktrace_scope.cc ../../src/internal_logging.cc ../../src/malloc_extension.cc ../../src/page_heap.cc ../../src/sampler.cc ../../src/span.cc ../../src/stacktrace.cc ../../src/stack_trace_table.cc ../../src/static_vars.cc ../../src/tcmalloc.cc ../../src/thread_cache.cc ../../src/windows/port.cc ../../src/windows/system-alloc.cc
llvm-link -o link.bc central_freelist.bc common.bc dynamic_annotations.bc fake_stacktrace_scope.bc internal_logging.bc logging.bc main.bc malloc_extension.bc page_heap.bc port.bc sampler.bc span.bc spinlock.bc spinlock_internal.bc stacktrace.bc stack_trace_table.bc static_vars.bc sysinfo.bc system-alloc.bc tcmalloc.bc thread_cache.bc
opt -O3 -o opt1.bc link.bc
opt -O3 -o opt2.bc opt1.bc
opt -O3 -o opt3.bc opt2.bc
clang -O3 -o final.exe -lOLDNAMES opt3.bc
pause