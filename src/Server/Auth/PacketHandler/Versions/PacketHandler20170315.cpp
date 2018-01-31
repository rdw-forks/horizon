//
// Created by SagunKho on 27/01/2018.
//

#include "PacketHandler20170315.hpp"
#include "Core/Logging/Logger.hpp"
#include <boost/bind.hpp>

Horizon::Auth::PacketHandler20170315::PacketHandler20170315(std::shared_ptr<AuthSession> &session)
: PacketHandler(session)
{
	InitializeHandlers();
}

Horizon::Auth::PacketHandler20170315::~PacketHandler20170315()
{
}

void Horizon::Auth::PacketHandler20170315::Respond_AC_ACCEPT_LOGIN()
{
	// Override common handler.
	AuthLog->info("Overloaded!");
	Respond_AC_REFUSE_LOGIN(login_error_codes::ERR_UNREGISTERED_ID);
}

void Horizon::Auth::PacketHandler20170315::Handle_TEST_POLY(PacketBuffer &buf)
{
	PACKET_CA_LOGIN pkt;
	buf >> pkt;

	AuthLog->info("poly working {}", pkt.version);
	Respond_AC_ACCEPT_LOGIN();
}

void Horizon::Auth::PacketHandler20170315::InitializeHandlers()
{
	Horizon::Auth::PacketHandler::InitializeHandlers();
	_handlers.erase(CA_LOGIN);
	_handlers.insert(std::make_pair(CA_LOGIN, boost::bind(&PacketHandler20170315::Handle_TEST_POLY, this, boost::placeholders::_1)));
}