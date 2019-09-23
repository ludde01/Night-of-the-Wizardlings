#ifndef _LOCAL_SERVER_H
#define _LOCAL_SERVER_H
#include <Pch/Pch.h>
#include "NetworkPlayer.h"
class LocalServer
{
public:

	LocalServer();
	~LocalServer();

	static LocalServer* getInstance();

	void startup(const std::string& serverName);
	void destroy();
	void threadedProcess();
	const bool& isInitialized() const;

private:
	unsigned char getPacketID(RakNet::Packet* p);
	void handleLostPlayer(const RakNet::Packet& packet, const RakNet::BitStream& bsIn);
private:
	RakNet::RakPeerInterface* m_serverPeer = nullptr;
	std::thread m_processThread;
	bool m_shutdownServer;

	std::vector<NetworkPlayer> m_connectedPlayers;
	ServerInfo m_serverInfo;
	bool m_initialized = false;

};

#endif