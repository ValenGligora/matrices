#include <stdio.h>
#include <stdlib.h>

#define FILAS 4
#define COLUMNAS 4
#define ORDEN 4
//algo falla no se el que lo tengo que revisar
/*
void cargarMatriz(size_t columnas, size_t filas,int mat[][columnas]);
void mostrarMatriz(size_t columnas, size_t filas,int mat[][columnas]);
int sumaDiagonalPrincipal(size_t orden, int mat[][orden]);
int sumaDiagonalSecundaria(size_t orden, int mat[][orden]);
int sumaTriangularInferior(size_t orden, int mat[][orden]);
int sumaTriangularSuperior(size_t orden, int mat[][orden]);
*/

void** crearMatriz(size_t filas, size_t columnas, size_t tamElem);
void destruirMatriz(void** mat, size_t filas);
void cargarMatriz(int** mat, size_t filas, size_t columnas);
void mostrarMatriz(int** mat, size_t filas, size_t columnas);

int sumaDiagonalPrincipal(int** mat, size_t orden);
int sumaDiagonalSecundaria(int** mat, size_t orden);
int sumaTriangularInferior(int** mat, size_t orden);
int sumaTriangularSuperior(int** mat, size_t orden);


int main()
{
    /*
    int mat[FILAS][COLUMNAS] = {
    {1,2,3,4},
    {5,6,7,8},
    {9,10,11,12},
    {13,14,15,16}
    };
    */

    int orden = ORDEN;
    //int (*mat)[orden]; puntero a matriz para un bloque completo
    int** mat = (int**)crearMatriz(orden, orden, sizeof(int)); //esta cosa es un vector de punteros que apuntan a un vector de elementos

    //mat = malloc(orden * orden * sizeof(int));

    if (!mat)
    {
        puts("No hay memoria");
        return 1;
    }

    cargarMatriz(mat,orden, orden);
    mostrarMatriz(mat,orden, orden);

    sumaDiagonalPrincipal(mat,orden);
    sumaDiagonalSecundaria(mat,orden);
    sumaTriangularInferior(mat,orden);
    sumaTriangularSuperior(mat,orden);

    //free(mat);
    destruirMatriz((void**)mat,orden);
    return 0;
}

void** crearMatriz(size_t filas, size_t columnas, size_t tamElem){

    void** mat = malloc(filas * sizeof(void*));
    if (!mat)
    {
        puts("No se pudo reservar memoria");
        return NULL;
    }

    void** ult = mat + filas -1;

    for (void** i = mat; i <= ult; i++)
    {
        *i = malloc(columnas * tamElem);
        if (*i == NULL)
        {
            puts("No se pudo reservar memoria");
            destruirMatriz(mat, i - mat);
// i-mat resta de direcciones de memoria y el resultado es la distancia entre los punteros (en cant de elementos)
            return NULL;
        }

    }
    return mat;
}

void destruirMatriz(void**mat, size_t filas){

    void** ult = mat + filas -1;

    for (void** i = mat; i <= ult; i++)
    {
        free(*i);
    }
    free(mat);
}

void cargarMatriz(int** mat, size_t filas, size_t columnas){

    int cont=1;
        for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            mat[i][j]=cont++;
// esto es pre-incremento primero guarda el valor desp suma y sino ++cont hace un post-incremento suma y despues guarda
        }
    }
}

void mostrarMatriz(int** mat, size_t filas, size_t columnas){ //posV = i *cantCol + j;

    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            printf("%4d", mat[i][j]);
        }
        putchar('\n');
    }

}

int sumaDiagonalPrincipal(int** mat, size_t orden){

    int suma = 0;
    printf("\nElementos sumados de la diagonal principal:");
    for (int i = 0; i < ORDEN; i++)
    {
        suma += mat[i][i];
        printf("%4d",mat[i][i]);
    }
    printf("\nSuma de elementos de la diagonal principal: %d",suma);
    return suma;
}

int sumaDiagonalSecundaria(int** mat, size_t orden){

    int suma = 0;
    printf("\nElementos sumados de la diagonal secundaria:");
    for (int i = 0; i < orden; i++)// tambien se puede: for(int i = 0, j = orden -1 ; i < orden ; i++, j--)
    {
        suma += mat[i][orden-1-i];
        printf("%4d",mat[i][orden-1-i]);
    }
    printf("\nSuma de elementos de la diagonal secundaria: %d",suma);
    return suma;
}

int sumaTriangularInferior(int** mat, size_t orden){ // Lim j = i-1  j<1

    int suma = 0;
    printf("\nElementos sumados:");
    for(int i = 1; i < orden; i++)
    {
        for (int j = 0; j < i; j++)
        {
            suma+= mat[i][j];
            printf("%4d",mat[i][j]);
        }
    }
    printf("\nSuma de elementos de la triangular inferior: %d",suma);
    return suma;
}

int sumaTriangularSuperior(int** mat, size_t orden){ // Lim j = orden -2 -i  j <= orden -2 -i

    int suma = 0;
    int limI = orden -2;

    printf("\nElementos sumados:");
    for(int i = 0, limJ = limI; i <= limI ; i++, limJ--)
    {
        for (int j = 0; j <= limJ; j++)
        {
            suma+= mat[i][j];
            printf("%4d",mat[i][j]);
        }
    }
    printf("\nSuma de elementos de la triangular inferior: %d",suma);
    return suma;
}

/*TAREA
recorrer una matriz en forma de espiral
sumar los elementros de la trianguar superior y lo mismo con cada trianglar las que estan limitadas por ambas diagonales
producto de matrices*/
