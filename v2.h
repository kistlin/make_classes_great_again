#ifndef V2_H
#define V2_H

#include <list>
#include <map>
#include <string>
#include <vector>

namespace v2 {

template<bool isRequest, class Body>
struct message;

template<class Body>
using request = message<true, Body>;

template<class Body>
using response = message<false, Body>;

template<bool isRequest, class Body>
struct message {
	int version;
	std::string method;
	std::string target;
	std::map<std::string, std::string> fields;
	typename Body::value_type body;
};

struct empty_body {
	struct value_type {};

	static void write(std::ostream&, value_type const&) {
		// do nothing
	}
};

struct string_body {
	using value_type = std::string;

	static void write(std::ostream& os, std::string const& body) {
		os << body;
	}
};

template<class T>
struct vector_body {
	using value_type = std::vector<T>;
};

template<class T>
struct list_body {
	using value_type = std::list<T>;

	static void write(std::ostream& os, std::list<T> const& body) {
		for (auto const& value: body) {
			os << value;
		}
	}
};

template<bool isRequest, class Body>
void write(std::ostream&, message<isRequest, Body> const& msg);

template<bool isRequest, class Body>
void write(std::ostream& os, message<isRequest, Body> const& msg) {
	// implementation
	Body::write(os, msg.body);
}

}  // namespace v2

#endif  // V2_H
