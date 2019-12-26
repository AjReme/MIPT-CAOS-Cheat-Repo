#include <stdio.h>
#include <stdlib.h>
#include <x86intrin.h>

int main()
{
    int n, m, lim;
    scanf("%d%d", &n, &m);
    lim = m / 4 * 4;
    float* mtx1[n];
    float* mtx2[n];
    for (int i = 0; i < n; ++i) {
        mtx1[i] = aligned_alloc(16, m * sizeof(float));
        mtx2[i] = aligned_alloc(16, m * sizeof(float));
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%f", &mtx1[i][j]);
        }
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%f", &mtx2[j][i]);
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            float tmp = 0;
            int k = 0;
            for (; k < lim; k += 4) {
                __m128 v4 = _mm_mul_ps(
                    _mm_load_ps(&mtx1[i][k]), _mm_load_ps(&mtx2[j][k]));
                v4 = _mm_hadd_ps(v4, v4);
                tmp += _mm_cvtss_f32(_mm_hadd_ps(v4, v4));
            }
            for (; k < m; ++k) {
                tmp += mtx1[i][k] * mtx2[j][k];
            }
            printf("%0.4f ", tmp);
        }
        puts("");
    }
    for (int i = 0; i < n; ++i) {
        free(mtx1[i]);
        free(mtx2[i]);
    }
}
