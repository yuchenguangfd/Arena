/*
 * Problem: Flip Game
 * http://poj.org/problem?id=1753
 */

#include <cstdio>

bool NextCombination(int *array, int n, int r) {
    int i = r - 1;
    while (i >= 0 && array[i] == n-r+i) {
        --i;
    }
    if (i < 0) return false;
    ++array[i];
    for (int j = i + 1; j < r; ++j) {
        array[j] = array[j-1]+1;
    }
    return true;
}

int main() {
    const int N = 4;
    char board[N][N+1];
    for (int i = 0; i < N; ++i) {
        scanf("%s", board[i]);
    }

    int state = 0;
    for (int x = 0; x < N; ++x) {
      for (int y = 0; y < N; ++y) {
          if (board[x][y] == 'w') {
              int p = x * N + y;
              state |= (1 << p);
          }
      }
    }
    for (int rounds = 0; rounds <= N*N; ++rounds) {
        int array[N*N];
        for (int i = 0; i < rounds; ++i) {
            array[i] = i;
        }
        do {
            int currState = state;
            for (int r = 0; r < rounds; ++r) {
                int p = array[r];
                currState ^= (1 << p);
                int x = p / N, y = p % N;
                int dx[] = {0, 0, 1, -1};
                int dy[] = {1, -1, 0, 0};
                for (int k = 0; k < 4; ++k) {
                    int xx = x + dx[k];
                    int yy = y + dy[k];
                    if (xx >= 0 && xx < N && yy >= 0 && yy < N) {
                        int q = xx * N + yy;
                        currState ^= (1 << q);
                    }
                }
            }
            if (currState == 0 || ((~currState) & 0xffff) == 0) {
                printf("%d\n", rounds);
                return 0;
            }
        } while (NextCombination(array, N*N, rounds));
    }
    printf("Impossible\n");
    return 0;
}
