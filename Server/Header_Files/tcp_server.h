#ifndef TCPSERVER
#define TCPSERVER

#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iomanip>
#include <ios>
#include <iostream>
#include <pthread.h>
#include <regex>
#include <stdexcept>
#include <string>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>
#include "picojson.h"
using namespace std;

struct Message {
	string user;
	string body;

	Message() = default;

	Message(const string& new_user, const string& new_body) :
		user(new_user),
		body(new_body)
	{}
};

struct Data {
	string method;
	Message message;

	Data() = default;

	Data(const string& new_method, const Message& new_message) :
		method(new_method),
		message(new_message)
	{}
};

Data parse_data_json(const string& data_json);
int accept_tcp_connection(const int& server_sock);
int create_tcp_server_sock(const unsigned short& server_port);
string create_data_json(const Data& data);
string receive_from(const int& client_sock, const char& delimiter);
void die_with_error(const string& error_message);
void get_message(const int& client_sock, const Message& message);
void post_message(const int& client_sock, const Message& message);
void quit(const int& client_sock, const string& user);
void thread_main1(const int& client_sock, const string& user, const pthread_t& thread_id);
void thread_main2(const int& client_sock, const string& user, const pthread_t& thread_id);

#endif