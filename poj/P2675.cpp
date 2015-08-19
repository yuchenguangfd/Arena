/*
 * Problem: Songs
 * http://poj.org/problem?id=2675
 */

#include <vector>
#include <functional>
#include <algorithm>
#include <cstdio>

struct Song {
	int id;
	double freq;
	double time;
};

struct SongCmp : public std::binary_function<Song, Song, bool> {
    const bool operator() (const Song& lhs, const Song& rhs) const {
        return lhs.freq * rhs.time < lhs.time * rhs.freq;
    }
};

int main() {
	while (true) {
        int n;
        if (scanf("%d", &n) == EOF) break;
		std::vector<Song> disk(n);
		for (int i = 0; i < n; ++i) {
			scanf("%d %lf %lf", &disk[i].id, &disk[i].freq, &disk[i].time);
		}
		std::sort(disk.begin(), disk.end(), SongCmp());
		int m;
		scanf("%d", &m);
		printf("%d\n", disk[m-1].id);
	}
	return 0;
}
