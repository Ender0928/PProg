#!/bin/bash

# Script para compilar y ejecutar tests con o sin Valgrind

# Comprobación de argumentos
if [ $# -lt 1 ]; then
    echo "Uso: $0 <0|1> [nombre_test_sin_extension]"
    exit 1
fi

modo=$1
nombre_test=$2

# Validación del primer argumento
if [[ "$modo" != "0" && "$modo" != "1" ]]; then
    echo "Error: el primer argumento debe ser 0 (normal) o 1 (valgrind)"
    exit 1
fi

# Función para compilar y ejecutar un test
ejecutar_test() {
    testfile=$1

    echo "Compilando $testfile..."
    make "$testfile"
    if [ $? -ne 0 ]; then
        echo "Error: Fallo de compilación en $testfile"
        exit 1
    fi

    echo "Ejecutando $testfile..."
    if [ "$modo" -eq 0 ]; then
        ./"$testfile"
    else
        valgrind --leak-check=full --track-origins=yes ./"$testfile"
    fi
}

# Si no se proporciona nombre de test, compilar y ejecutar todos los _test.c
if [ -z "$nombre_test" ]; then
    echo "No se especificó un test. Buscando y ejecutando todos los *_test.c..."

    for file in *_test.c; do
        # Obtener nombre sin extensión
        base_name="${file%.c}"
        ejecutar_test "$base_name"
    done
else
    # Ejecutar el test específico
    if [ -f "$nombre_test.c" ]; then
        ejecutar_test "$nombre_test"
    else
        echo "Error: El fichero $nombre_test.c no existe."
        exit 1
    fi
fi

exit 0
