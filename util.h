#pragma once

#define PI		3.141592654f
#define PI2		PI * 2

namespace UTIL
{
	//점과 점의 거리를 구하는 함수
	float getDistance(float startX, float startY, float endX, float endY);

	//선분과 점의 거리를 구하는 함수
	float getDistance(float pointX, float pointY, float lineX1, float lintY1, float lineX2, float lineY2);

	//점과 점의 각도를 구하는 함수
	float getAngle(float x1, float y1, float x2, float y2);
}