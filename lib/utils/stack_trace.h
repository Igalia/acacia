#pragma once

#ifndef NDEBUG

#include <execinfo.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

namespace {

#define MAX_BACKTRACE 10

void SIGSEGVHandler(int sig) {
  void* array[MAX_BACKTRACE];

  size_t size = backtrace(array, MAX_BACKTRACE);

  fprintf(stderr, "Error: signal %d:\n", sig);
  backtrace_symbols_fd(array, size, STDERR_FILENO);
  exit(1);
}

}  // namespace

namespace acacia {

static bool sigsegv_handler_installed = [] {
  signal(SIGSEGV, SIGSEGVHandler);
  return true;
}();

}  // namespace acacia

#endif  // NDEBUG
