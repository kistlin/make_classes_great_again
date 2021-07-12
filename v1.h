#ifndef V1_H
#define V1_H

#include <map>
#include <string>

namespace v1 {

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
	Body body;
};

template<bool isRequest, class Body>
void write(std::ostream&, message<isRequest, Body> const& msg);

template<bool isRequest, class Body>
void write(std::ostream& os, message<isRequest, Body> const& msg) {
	// implementation
	os.write(msg.body.data(),
	         msg.body.size());  // does only work if data() and size() is available and does the right thing
}

}  // namespace v1

#endif  // V1_H
