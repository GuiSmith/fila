#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Shuffle function
static void shuffle(void *array, size_t n, size_t size) {
    char tmp[size]; // Temporary storage to hold an element during swapping.
    char *arr = (char *)array; // Treat the input array as a char array (byte by byte).
    size_t stride = size * sizeof(char); // Calculate the size of each element in bytes.

    if (n > 1) {
        for (size_t i = 0; i < n - 1; ++i) {
            // Generate a random index j in the range [i, n-1].
            size_t rnd = (size_t) rand();
            size_t j = i + rnd / (RAND_MAX / (n - i) + 1);

            // Swap the elements at positions i and j.
            memcpy(tmp, arr + j * stride, size); // Copy arr[j] to tmp.
            memcpy(arr + j * stride, arr + i * stride, size); // Copy arr[i] to arr[j].
            memcpy(arr + i * stride, tmp, size); // Copy tmp (old arr[j]) to arr[i].
        }
    }
}

struct Pessoa {
    char *nome;
    int idade;
};

int main() {
    srand(time(NULL)); // Seed the random number generator.

    // Array of struct Pessoa
    struct Pessoa lista[] = {
        {"Gui", 18},
        {"Jon", 19},
        {"Fer", 20}
    };

    // Print original array
    printf("Before shuffling:\n");
    for (int i = 0; i < sizeof(lista) / sizeof(lista[0]); i++) {
        printf("%s %d\n", lista[i].nome, lista[i].idade);
    }

    // Shuffle the array
    shuffle(lista, sizeof(lista) / sizeof(lista[0]), sizeof(lista[0]));

    // Print shuffled array
    printf("\nAfter shuffling:\n");
    for (int i = 0; i < sizeof(lista) / sizeof(lista[0]); i++) {
        printf("%s %d\n", lista[i].nome, lista[i].idade);
    }

    return 0;
}
