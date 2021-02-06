#include "../Header_Files/tcp_client.h"

void post_message(const int& sock, const Message& message) {
	const Data data{
		"post",
		message
	};

	const string data_json = create_data_json(data) + '\0';

	if (send(sock, data_json.c_str(), data_json.length(), 0) != static_cast<ssize_t>(data_json.length()))
		throw runtime_error("send() failed");
}