#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//   Estructura para pasar argumentos al hilo worker
typedef struct {
    long long *arr;   // arreglo compartido
    int N;            // número de elementos
} fib_args;

//   Función del hilo worker
void *generate_fibonacci(void *arg) {
    fib_args *args = (fib_args *)arg;
    long long *arr = args->arr;
    int N = args->N;

    if (N > 0) arr[0] = 0;
    if (N > 1) arr[1] = 1;

    for (int i = 2; i < N; i++) {
        arr[i] = arr[i - 1] + arr[i - 2];
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <N>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    if (N <= 0) {
        printf("N debe ser mayor que 0\n");
        return 1;
    }

    // Reservar memoria para el arreglo compartido
    long long *arr = malloc(sizeof(long long) * N);
    if (arr == NULL) {
        printf("Error al asignar memoria\n");
        return 1;
    }

    pthread_t worker;
    fib_args args;
    args.arr = arr;
    args.N = N;

    pthread_create(&worker, NULL, generate_fibonacci, (void *)&args);

    pthread_join(worker, NULL);

    printf("Fibonacci(%d):\n", N);
    for (int i = 0; i < N; i++) {
        printf("%lld ", arr[i]);
    }
    printf("\n");

    free(arr);

    return 0;
}
