#include "pixmap.h"
#include <stack>
#include <utility>
bool fill(PixMap& image, Pixel fillColour, int x, int y){
	if (x < 0 || y < 0 || x > image.width() - 1 || y > image.height() - 1) {
		return false;
	}
	auto srcColor = image.getPixel(x, y);
	std::stack<std::pair<int, int>> s;
	s.push(std::pair<int, int>(x, y));
	while (!s.empty()) {
		int x = s.top().first;
		int y = s.top().second;
		s.pop();
		if (x < 0 || y < 0 || x > image.width() - 1 || y > image.height() - 1) {
			continue;
		}

		if (image.getPixel(x, y) == srcColor) {
			image.setPixel(fillColour, x, y);
			s.push(std::pair<int, int>(x + 1, y));
			s.push(std::pair<int, int>(x - 1, y));
			s.push(std::pair<int, int>(x, y + 1));
			s.push(std::pair<int, int>(x, y - 1));
		}
	}
	return true;
}










