#ifndef _CLIENT_H
#define _CLIENT_H
#include <Pch/Pch.h>
#include "NetworkPlayer.h"

class Client
{
public:
	Client();
	~Client();

	static Client* getInstance();

	void startup();
	void destroy();
	void connectToAnotherServer(const ServerInfo& server);
	void connectToMyServer();
	void threadedProcess();
	const std::vector<std::pair<unsigned int, ServerInfo>>& getServerList() const;
	const std::vector<NetworkPlayer>& getConnectedPlayers() const;
	void refreshServerList();
	bool doneRefreshingServerList();
	const bool& isInitialized() const;

	const ServerInfo& getServerByID(const unsigned int& ID) const;
	const bool doesServerExist(const unsigned int& ID) const;

	const bool& isConnectedToSever() const;
	const bool& connectionFailed() const;


private:
	void findAllServerAddresses();
	unsigned char getPacketID(RakNet::Packet* p);

	void printAllConnectedPlayers();

private:
	RakNet::RakPeerInterface* m_clientPeer;
	RakNet::SystemAddress m_serverAddress;
	std::vector<std::pair<unsigned int, ServerInfo>> m_serverList;
	bool m_isRefreshingServerList;
	bool m_isConnectedToAnServer;
	bool m_failedToConnect;

	std::thread m_processThread;
	bool m_shutdownThread;
	bool m_initialized = false;
	std::vector<NetworkPlayer> m_connectedPlayers;

};

#endif