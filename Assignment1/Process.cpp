// Process.cpp: 구현 파일
//

#include "pch.h"
#include "MfcCircleMove.h"
#include "Process.h"
#include "ASSERT.h"

// Process

Process::Process()
{
}

Process::~Process()
{
}

void Process::GetCircleCenter(const CImage& image, const unsigned char mapColor, const unsigned char circleColor, int* outCenterX, int* outCenterY)
{
	MY_ASSERT(outCenterX != nullptr);
	MY_ASSERT(outCenterY != nullptr);
	MY_ASSERT(mapColor != circleColor);
	const unsigned char* const fm = static_cast<const unsigned char*>(image.GetBits());
	const int nPitch = image.GetPitch();
	const int nWidth = image.GetWidth();
	const int nHeight = image.GetHeight();
	long long circlePixelCount = 0;
	long long circleXSum = 0;
	long long circleYSum = 0;
	static_assert(sizeof(circleXSum) == 8, "");
	static_assert(sizeof(circleYSum) == 8, "");
	static_assert(sizeof(circlePixelCount) == 8, "");
	bool bFoundCircle = false;
	for (int y = 0; y < nHeight; ++y) {
		bool bNowHeightFoundCircle = false;
		for (int x = 0; x < nWidth; ++x) {
			const unsigned char pixel = fm[nPitch * y + x];
			if (pixel == mapColor) {
				continue;
			}
			MY_ASSERT(pixel == circleColor);
			circleXSum += static_cast<long long>(x);
			circleYSum += static_cast<long long>(y);
			++circlePixelCount;
			bFoundCircle = true;
			bNowHeightFoundCircle = true;
		}
		if (bFoundCircle && !bNowHeightFoundCircle) {
			break;
		}
	}
	*outCenterX = static_cast<int>(static_cast<double>(circleXSum) / circlePixelCount + 0.5);
	*outCenterY = static_cast<int>(static_cast<double>(circleYSum) / circlePixelCount + 0.5);
}


// Process 멤버 함수
