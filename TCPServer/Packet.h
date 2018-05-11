#pragma once
class InputMemoryBitStream;
class Packet
{
public:
	Packet(InputMemoryBitStream &is);
	int type_of_packet = 0;
	int id = 0;
	int action = 0;
	int time = 0;

	~Packet();
};

