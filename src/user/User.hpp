#pragma once
#include "../../inc/irc.hpp"
// #include "Channel.hpp"

#define ATTEMP_TO_DISCONNECT 2

#define DISCONNECTED	0b10000000
#define ENTER_PASS		0b01000000
#define ENTER_NICK		0b00100000
#define ENTER_NAME		0b00010000
#define IRC_OPERATOR	0b00001000
#define INVISIBLE		0b00000100
#define REGISTERED		0b00000010
#define PRINT_MOTD		0b00000001

class User {
private:
	const int					_fd_sock;
	std::string					_msg_buf;
	std::string					_username;
	std::string					_hostname;
	std::string					_servername;
	std::string					_realname;
	std::string					_nick;
	std::string					_message;
	std::string					_pass;
	std::string					_rplAway;
	std::vector<std::string>	_to_send;
	size_t						_attemp;

public:
	bool isBanned() const;
	void setBanned(bool banned);

private:
	unsigned char				_flags;
	std::vector<std::string>	_chanels;
	User();
	User(const User &other);
	User& operator=(const User& other);

public:
	User(int fd_sock);
	~User();


	const std::string		&getUsername() const;
	void 					setUsername(const std::string &username);
	const 					std::string &getHostname() const;
	void					setHostname(const std::string &hostname);
	const std::string		&getServername() const;
	void					setServername(const std::string &servername);
	const std::string		&getRealname() const;
	void					setRealname(const std::string &realname);
	const std::string		&getRplAway() const;
	void					setRplAway(const std::string &rplAway);
	size_t					&getAttemp();
	void					setAttemp(size_t n);

	void					addMsgToSend(const std::string &msg);
	bool					haveMsgToSend() const;
	void					clearFirstElementToSend();
	const std::string		&getOneElementToSend() const;


	

	void					set_flag(unsigned char flag);
	void					del_flag(unsigned char flag);
	void					join_channel(std::string &channel_name);
	const unsigned char		get_flags() const;
	const int 				getFdSock() const;

	const std::vector<std::string> &getChanels() const;

	const std::string 		&getNick() const;
	void 					setNick(const std::string &nick);



	const std::string 		&getPass() const;
	void 					setPass(const std::string &pass);




};


