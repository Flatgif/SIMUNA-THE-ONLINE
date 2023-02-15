#include "Math.h"

float Math::EaseIn(float* speed, float acceleration, float max)
{
	float result;
	if (*speed <= max)
	{
		result = *speed * *speed;
		*speed += acceleration;
		return result;
	}

}

float Math::EaseOut(float* speed, float acceleration, float min)
{
	float result;
	if (*speed >= min)
	{
		result = *speed * *speed;
		*speed -= acceleration;
		return result;
	}

}

XMVECTOR Math::Normal(XMVECTOR dir)
{
	return (dir - (2 * dir));
}