#include "../Header_Files/tcp_client.h"

void get_message(const int& client_sock, const Message& message) {
	winsize w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	cout << right << setw(static_cast<int>(w.ws_col) + static_cast<int>(strlen("\x1b[35m"))) << message.body + '<' + "\x1b[35m" + message.user << "\x1b[0m" << endl;
}