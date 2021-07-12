#ifndef V3_H
#define V3_H

#include <list>
#include <map>
#include <string>
#include <vector>

namespace v3 {

template<bool isRequest, class Body>
struct message;

template<class Body>
using request = message<true, Body>;

template<class Body>
using response = message<false, Body>;

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

struct file_body {
	using value_type = std::string;

	static void write(std::ostream& os, std::string const& path) {
		size_t n;
		char buf[4096];
		FILE* f = fopen(path.c_str(), "rb");
		if (f) {
			while (n = fread(buf, 1, sizeof(buf), f)) {
				os.write(buf, n);
			}
			fclose(f);
		}
	}
};

template<bool isRequest, class Body>
struct message : private Body::value_type {  // empty base optimization
	int version;
	std::string method;
	std::string target;
	std::map<std::string, std::string> fields;

	typename Body::value_type& body() {
		return *this;
	}

	typename Body::value_type const& body() const {
		return *this;
	}
};

template<bool isRequest, class Body>
void write(std::ostream&, message<isRequest, Body> const& msg);

template<bool isRequest, class Body>
void write(std::ostream& os, message<isRequest, Body> const& msg) {
	// implementation
	Body::write(os, msg.body());
}

}  // namespace v3

#endif  // V3_H
