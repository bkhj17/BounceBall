#pragma once

#define PI		3.141592654f
#define PI2		PI * 2

namespace UTIL
{
	//���� ���� �Ÿ��� ���ϴ� �Լ�
	float getDistance(float startX, float startY, float endX, float endY);

	//���а� ���� �Ÿ��� ���ϴ� �Լ�
	float getDistance(float pointX, float pointY, float lineX1, float lintY1, float lineX2, float lineY2);

	//���� ���� ������ ���ϴ� �Լ�
	float getAngle(float x1, float y1, float x2, float y2);
}