#include <stdio.h>
#include <immintrin.h>

// Definir o tamanho do array como uma macro
#define SIZE 16

// Função para somar dois vetores usando AVX
void vector_add_avx(int* a, int* b, int* result, int size) {
  int i;
  __m256i va, vb, vsum;

  for (i = 0; i < size; i += 8) {
    // Carregar 8 elementos inteiros de 'a' e 'b' em registradores AVX
    va = _mm256_loadu_si256((__m256i*)&a[i]);
    vb = _mm256_loadu_si256((__m256i*)&b[i]);

    // Realizar a operação de soma em paralelo usando AVX
    vsum = _mm256_add_epi16(va, vb);

    // Armazenar o resultado de volta no vetor de destino
    _mm256_storeu_si256((__m256i*)&result[i], vsum);
  }
}

int main() {
  int a[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
  int b[SIZE] = {16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  int result[SIZE];

  vector_add_avx(a, b, result, SIZE);

  printf("Resultado:\n");
  for (int i = 0; i < SIZE; i++) {
      printf("%d ", result[i]);
  }
  printf("\n");

  return 0;
}