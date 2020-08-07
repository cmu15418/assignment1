#include <stdio.h>
#include <pthread.h>
#include <algorithm>
#include <math.h>

#include "CycleTimer.h"

typedef struct {
    float x0, x1;
    float y0, y1;
    unsigned int width;
    unsigned int height;
    int maxIterations;
    int* output;
    int threadId;
    int numThreads;
} WorkerArgs;


extern void mandelbrotSerial(
    float x0, float y0, float x1, float y1,
    int width, int height,
    int startRow, int numRows,
    int maxIterations,
    int output[]);


//
// workerThreadStart --
//
// Thread entrypoint.
void* workerThreadStart(void* threadArgs) {

    WorkerArgs* args = static_cast<WorkerArgs*>(threadArgs);

    // TODO: Implement worker thread here.
    // double minTime = 1e30;
    // double startTime = CycleTimer::currentSeconds();

    unsigned int threadNumRows = args->height / args->numThreads;
    if (args->height % args->numThreads != 0) {
        threadNumRows ++;
    }
    
    for (unsigned int i = 0; i < threadNumRows; i++) {
        unsigned int threadStartRow = i * args->numThreads + args->threadId;
        if (threadStartRow < args->height) {
            mandelbrotSerial(
                args->x0, args->y0, args->x1, args->y1, 
                args->width, args->height,
                threadStartRow, 1,
                args->maxIterations,
                args->output);
        }
    }

    // double endTime = CycleTimer::currentSeconds();
    // minTime = std::min(minTime, endTime - startTime);
    // printf("[mandelbrot thread %d worktime]:\t\t[%.3f] ms\n", args->threadId, minTime * 1000);

    return NULL;
}

//
// MandelbrotThread --
//
// Multi-threaded implementation of mandelbrot set image generation.
// Multi-threading performed via pthreads.
void mandelbrotThread(
    int numThreads,
    float x0, float y0, float x1, float y1,
    int width, int height,
    int maxIterations, int output[])
{
    const static int MAX_THREADS = 32;

    if (numThreads > MAX_THREADS)
    {
        fprintf(stderr, "Error: Max allowed threads is %d\n", MAX_THREADS);
        exit(1);
    }

    pthread_t workers[MAX_THREADS];
    WorkerArgs args[MAX_THREADS];

    for (int i=0; i<numThreads; i++) {
        // TODO: Set thread arguments here.
        args[i].threadId = i;
        args[i].numThreads = numThreads;
        args[i].x0 = x0;
        args[i].y0 = y0;
        args[i].x1 = x1;
        args[i].y1 = y1;
        args[i].width = width;
        args[i].height = height;
        args[i].maxIterations = maxIterations;
        args[i].output = output;
    }

    // Fire up the worker threads.  Note that numThreads-1 pthreads
    // are created and the main app thread is used as a worker as
    // well.

    for (int i=1; i<numThreads; i++)
        pthread_create(&workers[i], NULL, workerThreadStart, &args[i]);

    workerThreadStart(&args[0]);

    // wait for worker threads to complete
    for (int i=1; i<numThreads; i++)
        pthread_join(workers[i], NULL);
}
