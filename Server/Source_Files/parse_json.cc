#include "../Header_Files/tcp_server.h"

Data parse_data_json(const string& data_json) {
	picojson::value v;

	if (!picojson::parse(v, data_json).empty())
		throw runtime_error("picojson::parse() failed");

	const Data data{
		v.get<picojson::object>()["method"].get<string>(),
		{
			v.get<picojson::object>()["message"].get<picojson::object>()["user"].get<string>(),
			v.get<picojson::object>()["message"].get<picojson::object>()["body"].get<string>()
		}
	};

	return data;
}