/*
 * Problem: Color Me Less
 * http://poj.org/problem?id=1046
 */

#include <vector>
#include <cstdio>

class ColorRGB {
public:
	ColorRGB() : mRGB(0) { }
	ColorRGB(int r, int g, int b) {
	    mRGB = (r & 0xFF) + ((g & 0xFF) << 8) + ((b & 0xFF) << 16);
	}
	int Red() const { return mRGB & 0xFF; }
	int Green() const { return (mRGB >> 8) & 0xFF; }
	int Blue() const { return (mRGB >> 16) & 0xFF; }
private:
	int mRGB;
};

int main() {
    const int NUM_COLOR = 16;
    std::vector<ColorRGB> colorTable;
    for (int i = 0; i < NUM_COLOR; ++i) {
        int r, g, b;
        scanf("%d %d %d", &r, &g, &b);
        colorTable.push_back(ColorRGB(r, g, b));
    }
    while(true) {
    	int r, g, b;
    	scanf("%d %d %d", &r, &g, &b);
    	if(r == -1 && g == -1 && b == -1) break;
    	ColorRGB realColor(r, g, b);
        int min = 0x7FFFFFFF;
        int minIdx = -1;
        for(int i = 0; i < colorTable.size(); ++i) {
            int dr = realColor.Red() - colorTable[i].Red();
            int dg = realColor.Green() - colorTable[i].Green();
            int db = realColor.Blue() - colorTable[i].Blue();
            int dist = dr*dr+dg*dg+db*db;
            if(dist < min) {
                min = dist;
                minIdx = i;
            }
        }
    	ColorRGB mappedColor = colorTable[minIdx];
    	printf("(%d,%d,%d) maps to (%d,%d,%d)\n",
    			realColor.Red(), realColor.Green(), realColor.Blue(),
    			mappedColor.Red(), mappedColor.Green(), mappedColor.Blue());
     }
     return 0;
}
