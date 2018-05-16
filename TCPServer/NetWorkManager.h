#pragma once
#include "World.h"

class NetWorkManager
{
public:
	vector<TCPSocketPtr> readBlockSockets;
	vector<TCPSocketPtr> readableSockets;

	int time_to_start = -1;

	TCPSocketPtr socket_sever;
	bool isStart = false;
	void CreatePlayerAndSend();
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

};

