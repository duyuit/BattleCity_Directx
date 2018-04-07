#pragma once
#include <cstdint>
#include <cstdlib>

class InputMemoryStream
{
public:
	InputMemoryStream(char* inBuffer, uint32_t inByteCount) :
		mCapacity(inByteCount), mHead(0), mBuffer(inBuffer)
	{}
	~InputMemoryStream() { free(mBuffer); }
	uint32_t GetRemainingDataSize() const { return mCapacity - mHead; }
	void Read(void* outData, uint32_t inByteCount);
	void Read(uint32_t& outData) { Read(&outData, sizeof(outData)); }
	void Read(int32_t& outData) { Read(&outData, sizeof(outData)); }
private:
	char* mBuffer;
	uint32_t mHead;
	uint32_t mCapacity;
};
inline void InputMemoryStream::Read(void* outData, uint32_t inByteCount)
{
	memcpy(outData, mBuffer+mHead , inByteCount);

	mHead += inByteCount;
}

