#include "../Header_Files/tcp_client.h"

int main() {
	const unsigned short server_port = static_cast<unsigned short>(49152);
	const string server_ip = "127.0.0.1";

	int sock;

	try {
		sock = create_tcp_client_socket(server_port, server_ip);
	}
	catch (const exception& e) {
		die_with_error(e.what());
	}

	string user;

	do {
		cout << "ユーザー>";
		getline(cin, user);
	} while (!regex_match(user, regex(R"(.+)")));

	cout << "\x1b[32m" << "終了するには、 \"exit\" を入力してください" << "\x1b[0m" << endl;

	pthread_t thread_id1;
	pthread_t thread_id2;

	thread t1(thread_main1, sock, user, cref(thread_id2));
	thread t2(thread_main2, sock, user, cref(thread_id1));

	thread_id1 = static_cast<pthread_t>(t1.native_handle());
	thread_id2 = static_cast<pthread_t>(t2.native_handle());

	t1.join();
	t2.join();
}

void thread_main1(const int& sock, const string& user, const pthread_t& thread_id) {
	while (true) {
		try {
			const Data data = parse_data_json(receive_from(sock, '\0'));

			if (data.method == "post")
				get_message(sock, data.message);
			else if (data.method == "quit") {
				cout << "\x1b[32m" << data.message.user << "が退室しました (入力待ちを解除するには、何か文字を入力してください)" << "\x1b[0m" << endl;

				break;
			}
		} catch (const exception& e) {
			die_with_error(e.what());
		}
	}

	if (pthread_cancel(thread_id) != 0)
		die_with_error("pthread_cancel() failed");

	close(sock);
}

void thread_main2(const int& sock, const string& user, const pthread_t& thread_id) {
	while (true) {
		string command;

		do {
			getline(cin, command);
		} while (!regex_match(command, regex(R"(.+)")));

		try {
			if (command != "exit") {
				const Message message{
					user,
					command
				};

				post_message(sock, message);
			}
			else {
				quit(sock, user);

				break;
			}
		} catch (const exception& e) {
			die_with_error(e.what());
		}
	}

	if (pthread_cancel(thread_id) != 0)
		die_with_error("pthread_cancel() failed");

	close(sock);
}