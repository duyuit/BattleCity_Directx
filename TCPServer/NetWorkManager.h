#pragma once
#include "World.h"

class NetWorkManager
{
public:
	vector<TCPSocketPtr> readBlockSockets;
	vector<TCPSocketPtr> readableSockets;
	TCPSocketPtr socket_sever;


	vector<Packet> queue_packet;
	void Handle_Packet();
	int ID = 1;
	World* mWorld;
	NetWorkManager();
	~NetWorkManager();
	void Update(float dt);
	void ProcessNewClient();
	void UpdatePlayerCount();
	void ReceivePacket();
	int RandomNumber(int x, int y);
};

