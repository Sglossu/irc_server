#pragma once
#include "../../inc/irc.hpp"

#define CR_LF	"\r\n"
#define REGISTERED		0b00000001
#define ADMIN			0b00000010
#define DISCONNECTED	0b10000000


class User {
private:
	const int		_fd_sock;
	std::string		_msg_buf;
	std::string		_username;
	std::string		_realname;
	std::string		_nick;
	std::string		_message;
	unsigned char	_flags;
//	std::vector<>	_chanels; // придумать какой тип данных. массив для каналов юзера
	User();
	User(const User &other);
	User& operator=(const User& other);

public:
	User(int fd_sock);
	~User();

	void	processIncommingMessage(std::string buf);
	void	parceComand(std::string cmnd);
	void	set_flag(unsigned char flag);

	const unsigned char	get_flags() const;
	const std::string	&get_name() const;

};