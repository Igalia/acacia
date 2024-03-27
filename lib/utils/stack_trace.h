#pragma once

#include <execinfo.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mutex>

namespace {

#define MAX_BACKTRACE 10

void SIGSEGVHandler(int sig) {
  void* array[MAX_BACKTRACE];

  size_t size = backtrace(array, MAX_BACKTRACE);

  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}

std::once_flag sigsegv_installed;

}  // namespace

namespace stack_trace {

void InstallSIGSEGVHandler() {
  std::call_once(sigsegv_installed, signal, SIGSEGV, SIGSEGVHandler);
}

}  // namespace stack_trace
