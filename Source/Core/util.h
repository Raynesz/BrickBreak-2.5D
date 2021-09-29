#pragma once

inline double degToRad(double deg) {
	return deg * PI / 180;
}

inline int random(int from, int to) {
	srand(time(NULL));
	return  rand() % to + from;
}
