#include "Handler.hpp"

Handler::Handler(Server &server): _server(server) {
	_registration_commands();
	// std::cout << "handler constructor. server port: " << server.port << std::endl;
}

Handler::~Handler() {}

void	Handler::process_incomming_message(int fd, std::string buf) {
	size_t      pos;
	std::string msg_line;
	User		*user;

	if (_bufs.count(fd))
		_bufs[fd] += buf;
	else
		_bufs[fd] = buf;
	user = _server.map_users[fd];
	std::cout << "User <" << fd << ", " << user->getUsername()
			  << "> incoming msg(" << _bufs[fd].size() <<"): "  << _bufs[fd] << std::endl;
	while (!_bufs[fd].empty()) {
		_res_execute = 0;
		pos = _bufs[fd].find(CR_LF);
		if (pos == _bufs[fd].npos)
			break ;
		msg_line = _bufs[fd].substr(0, pos);
//		_bufs[fd] = _bufs[fd].substr(pos + 2); // раскоменить когда считывается /r
		_bufs[fd] = _bufs[fd].substr(pos + 1); // закоментить, если верхняя строка раскоменчена

		Message	msg(msg_line);
		if (msg.get_cmd().empty() or !_commands.count(msg.get_cmd())) {
			std::cout << "!Unknown command: " << msg.get_cmd() << std::endl;

			// todo send user any message?
		}

		// Самая Классная Строчка
		// Запускает нужную команду. Синтаксис пиздец...
		(this->*_commands[msg.get_cmd()])(msg, *user);
	}
}


bool	Handler::_is_valid_nick(std::string	nick) {
	// todo
	return true;
}

bool	Handler::_is_valid_groupname(std::string name) {
	// todo
	return true;
}

void	Handler::clear_buf(int fd) {
	if (_bufs.count(fd))
		_bufs.erase(fd);
}
