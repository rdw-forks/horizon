#include "ClientSocketMgr.hpp"
#include "Server/Zone/Zone.hpp"

bool Horizon::Zone::ClientSocketMgr::start(boost::asio::io_context &io_context, std::string const &listen_ip, uint16_t port, uint32_t threads, bool minimal)
{
	if (!BaseSocketMgr::start(io_context, listen_ip, port, threads, minimal))
		return false;
	
	for (auto i : get_thread_map()) {
		sZone->register_component(Horizon::System::RUNTIME_NETWORKING, (std::dynamic_pointer_cast<ZoneNetworkThread>(i.second)));
	}

	return true;
}