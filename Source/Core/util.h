#pragma once

inline double degToRad(double deg) {
	return deg * PI / 180;
}

inline int random(int from, int to) {
	return  from + rand() / (RAND_MAX / (to + 1 - from));
}

inline float random(float from, float to) {
	return  from + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (to - from)));
}
