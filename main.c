#include <Python.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char* CAPSULE_NAME = "_curses._C_API";

#define N_THREADS 2
#define bool int

typedef struct {
    bool import;
    int id;
} arg_t;

void *acquire_gil(void *arg) {
    bool import = ((arg_t *)arg)->import;
    int n = ((arg_t *)arg)->id;

    printf("Waiting for GIL (%d)\n", n);
    int gstate = PyGILState_Ensure();
    printf("Gil acquired! (%d)\n", n);
    usleep(125000);
    if (import) {
        PyCapsule_Import(CAPSULE_NAME, 0);
    }
    usleep(125000);
    PyGILState_Release(gstate);
    printf("Gil released! (%d)\n", n);
    return NULL;
}

void init_threads() {
#ifndef PY_VERSION3_7
    assert(PyEval_ThreadsInitialized() == 0);
#endif
    Py_InitializeEx(0);
    PyEval_InitThreads();
    PyEval_SaveThread();
}


int main(int argc, char **argv) {
    bool import = 0;
    if (argc == 2) {
        if (strcmp(argv[1], "import") == 0) {
            import = 1;
        }
    }

    pthread_t *tid = malloc(N_THREADS * sizeof(pthread_t));
    arg_t threads[3];

    init_threads();

    for (int i = 0; i < N_THREADS; i++) {
        threads[i] = (arg_t) { import, i };
        pthread_create(&tid[i], NULL, acquire_gil, &threads[i]);
    }

    for (int i = 0; i < N_THREADS; i++) {
        pthread_join(tid[i], NULL);
    }

    free(tid);
}
