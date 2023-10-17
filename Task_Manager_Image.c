#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <windows.h>

int shouldRunList[] = {
        255, 255, 255, 255, 255, 255, 255, 255,
        255, 0, 0, 0, 255, 0, 0, 255,
        255, 0, 255, 255, 255, 0, 255, 0,
        255, 0, 0, 0, 255, 0, 0, 255,
        255, 255, 255, 0, 255, 0, 255, 0,
        255, 0, 0, 0, 255, 0, 0, 255,
        255, 255, 255, 255, 255, 255, 255, 255,
};


void* threadFunction(void* arg) {
    int threadId = *((int*)arg);

    if (shouldRunList[threadId] == 255) {
        // This thread should remain idle.
        while (1) {
            Sleep(1000);  // Sleep for a second to avoid unnecessary CPU usage.
        }
    } else {
        // Set thread affinity using Windows API for non-idle threads.
        DWORD_PTR affinityMask = 1ULL << threadId;
        SetThreadAffinityMask(GetCurrentThread(), affinityMask);

        while (1) {
            // Perform busy loop or calculations for threads other than the idle ones.
            int result = 0;
            for (int i = 0; i < 1000000; i++) {
                result += i;
            }
        }
    }

    return NULL;
}

int main() {
    int numThreads = 56;
    pthread_t threads[numThreads];
    int threadIds[numThreads];

    for (int i = 0; i < numThreads; i++) {
        threadIds[i] = i;
        pthread_create(&threads[i], NULL, threadFunction, &threadIds[i]);
    }

    for (int i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
