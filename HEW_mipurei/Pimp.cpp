#include "Pimp.h"

Vector2 Tension(Vector2 _pos1, Vector2 _pos2, float _coefficient , float _defoult_length)
{
	Vector2 tension;
	Vector2 vec;
	float length;
	float now_tension;

	vec = _pos1 - _pos2;
	length = F_SQRT(vec);
	if (length == 0) {
		tension = Vector2(0, 0);
	}
	else {
		now_tension = _coefficient * (length - _defoult_length);

		if (_coefficient == 0.0f) {
			now_tension = (length - _defoult_length);
		}	
		tension.x = vec.x * (now_tension / length);
		tension.y = vec.y * (now_tension / length);
	}

	return tension;
}
