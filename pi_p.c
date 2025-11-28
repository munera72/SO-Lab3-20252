/*
 *  OpenMP lecture exercises
 *  Copyright (C) 2011 by Christian Terboven <terboven@rz.rwth-aachen.de>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>


double GetTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + tv.tv_usec * 1e-6;
}


double f(double a) {
    return 4.0 / (1.0 + a * a);
}


typedef struct {
    int start;
    int end;
    double h;
} thread_args;


void *thread_function(void *arg) {
    thread_args *args = (thread_args *)arg;

    double local_sum = 0.0;
    double x;

    for (int i = args->start; i < args->end; i++) {
        x = args->h * ((double)i + 0.5);
        local_sum += f(x);
    }


    double *ret = malloc(sizeof(double));
    *ret = local_sum;
    pthread_exit(ret);
}


double CalcPi(int n, int T) {
    pthread_t threads[T];
    thread_args args[T];

    double h = 1.0 / (double)n;

    int chunk = n / T;
    int remainder = n % T;

    int start = 0;

    for (int t = 0; t < T; t++) {
        int end = start + chunk;
        if (t == T - 1) end += remainder;

        args[t].start = start;
        args[t].end = end;
        args[t].h = h;

        pthread_create(&threads[t], NULL, thread_function, (void*)&args[t]);

        start = end;
    }

    double global_sum = 0.0;
    for (int t = 0; t < T; t++) {
        double *partial_sum;
        pthread_join(threads[t], (void**)&partial_sum);
        global_sum += *partial_sum;
        free(partial_sum);
    }

    return h * global_sum;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Uso: %s <n> <num_hilos>\n", argv[0]);
        return 1;
    }

    long n = atol(argv[1]);
    int T = atoi(argv[2]);

    if (n <= 0 || T <= 0) {
        printf("Valores inválidos.\n");
        return 1;
    }

    const double PI_REAL = 3.141592653589793238462643;

    double t_start = GetTime();
    double pi = CalcPi(n, T);
    double t_end = GetTime();

    printf("\npi ≈ %.20f \nError = %.20f\n", pi, fabs(pi - PI_REAL));
    printf("Tiempo = %f segundos\n", t_end - t_start);

    return 0;
}
