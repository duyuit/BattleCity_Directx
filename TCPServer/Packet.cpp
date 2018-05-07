#include "Packet.h"
#include "MemoryBitStream.h"


Packet::Packet(InputMemoryBitStream &is)
{
	is.Read(type_of_packet, Define::bitofTypePacket);
	switch (type_of_packet)
	{
	case Define::TankPacket:
		break;
	case Define::InputPacket:

		is.Read(id, Define::bitofID);
		is.Read(action, Define::bitofID);
		is.Read(time);
		break;
	}
}

Packet::~Packet()
{
}
