#include "../Header_Files/tcp_server.h"

void quit(const int& client_sock, const string& user) {
	const Data data{
		"quit",
		{
			user,
			""
		}
	};

	const string data_json = create_data_json(data) + '\0';

	if (send(client_sock, data_json.c_str(), data_json.length(), 0) != static_cast<ssize_t>(data_json.length()))
		throw runtime_error("send() failed");
}