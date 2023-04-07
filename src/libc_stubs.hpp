#pragma once

/* Stub implementations from https://sourceware.org/newlib/libc.html#Stubs. */
extern "C" { /* Necessary to avoid function name mangling. */
    int _close(int file) {
        return -1;
    }
    int _lseek(int file, int ptr, int dir) {
        return 0;
    }
    int _read(int file, char *ptr, int len) {
        return 0;
    }
    int _write(int file, char *ptr, int len) {
        // TODO: stdio functions (such as printf) depend on this.
        return 0;
    }
}
