#pragma once

inline float clamp(float value, float min, float max)
{
	if (value < min) value = min;
	if (value > max) value = max;
	return  value;
}

inline float ClampAround(float value, float min, float max)
{
	if (value < min) value = max;
	if (value > max) value = min;
	return  value;
}