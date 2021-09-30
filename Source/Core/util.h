#pragma once

inline double degToRad(double deg) {
	return deg * PI / 180;
}

inline int random(int from, int to) {
	return  rand() % (to+1) + from;
}

inline double random(double from, double to) {
	return  from + static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (to - from)));
}
