#include "Game.h"
#include "util.h"


namespace UTIL
{
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrtf(x*x + y*y);
	}

	float getDistance(float pointX, float pointY, float lineX1, float lineY1, float lineX2, float lineY2)
	{
		float a = pointX - lineX1;
		float b = pointY - lineY1;
		float c = lineX2 - lineX1;
		float d = lineY2 - lineY1;

		float dot = a * c + b * d;
		float len_sq = c * c + d * d;
		float param = -1;

		if (len_sq != 0)
			param = dot / len_sq;

		float xx, yy;	//선분중에서 점과 가장 가까운 점

		if (param < 0)
		{
			xx = lineX1;
			yy = lineY1;
		}
		else if (param > 1)
		{
			xx = lineX2;
			yy = lineY2;
		}
		else
		{
			xx = lineX1 + param * c;
			yy = lineY1 + param * d;
		}

		float dx = pointX - xx;
		float dy = pointY - yy;

		return sqrt(dx * dx + dy * dy);
	}

	float getAngle(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		float dist = sqrtf(x*x + y * y);
		float angle = acosf(x / dist);

		if (y2 > y1)
		{
			angle = PI2 - angle;

			if (angle >= PI2)
				angle -= PI2;
		}
		return angle;
	}
}