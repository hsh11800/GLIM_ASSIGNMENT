#pragma once

// Process 명령 대상

class Process : public CObject
{
public:
	Process();
	virtual ~Process();
	static void GetCircleCenter(const CImage& image, const unsigned char mapColor, const unsigned char circleColor, int* outCenterX, int* outCenterY);
};


