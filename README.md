Este programa calcula una aproximación del valor de π utilizando integración numérica y reparte el trabajo entre varios hilos mediante la biblioteca Pthreads. La idea general es dividir un trabajo muy grande en varias partes para que cada hilo procese un segmento distinto.

Funciones del programa

1. double GetTime()

Obtiene el tiempo actual en segundos usando gettimeofday().
Sirve para medir cuánto tarda el cálculo de π.

2. double f(double a)

Es la función que se evalúa en cada iteración del cálculo.
Representa el valor que se usa para aproximar π por integración.

3. typedef struct thread_args

Estructura que almacena la información que necesita cada hilo:
start: índice inicial que procesará el hilo
end: índice final que procesará el hilo
h: tamaño del paso entre iteraciones
Cada hilo procesa únicamente su propio segmento.

4. void *thread_function(void *arg)

Función que ejecuta cada hilo:
Recibe un rango de trabajo mediante la estructura thread_args
Recorre sus índices asignados
Calcula una suma parcial
Devuelve esa suma al hilo principal usando pthread_exit()
Cada hilo trabaja de manera independiente, por lo que no se requieren mecanismos de sincronización.

5. double CalcPi(int n, int T)

Es la función que organiza y coordina el cálculo paralelo:
Divide el total de iteraciones (n) entre los hilos (T)
Crea los hilos y les asigna sus rangos
Espera a que todos terminen usando pthread_join()
Recupera las sumas parciales
Las combina para producir el resultado final
Esta función es la encargada de repartir el trabajo y unir los resultados.

6. int main(int argc, char **argv)

Es la entrada del programa. Se encarga de:
Leer los dos argumentos:
n: cantidad de iteraciones del cálculo
T: número de hilos
Medir el tiempo antes y después del cálculo
Llamar a CalcPi(n, T)
Imprimir la aproximación obtenida, el error respecto al valor real y el tiempo total


Cómo compilar

En la terminal, ejecutar:
gcc -pthread -o pi_p pi_p.c -lm

Cómo ejecutar

Formato:
./pi_p <n> <T>


Ejemplo:

./pi_p 2000000000 4


Donde:

n = cantidad total de iteraciones
T = número de hilos que ejecutarán el cálculo en paralelo

Ejemplo de salida
pi ≈ 3.14159265358979311600
Error = 0.00000000000000000053
Tiempo = 0.803214 segundos