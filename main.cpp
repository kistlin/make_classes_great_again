//#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "v1.h"
#include "v2.h"
#include "v3.h"

int main() {
	// Source: CppCon 2017: Vinnie Falco “Make Classes Great Again! (Using Concepts for Customization Points)”
	//         https://www.youtube.com/watch?v=WsUnnYEKPnI

	// v1
	v1::request<std::string> req_v1_1;
	req_v1_1.body = "Hello, world!\n";
	v1::write(std::cout, req_v1_1);
	v1::response<std::vector<char>> res_v1_1;
	res_v1_1.body = {'a', 'b', 'c', '\n'};
	v1::write(std::cout, res_v1_1);

	// v2
	v2::response<v2::string_body> res_v2_1;
	res_v2_1.body = "Hello, world!\n";
	v2::write(std::cout, res_v2_1);
	v2::response<v2::list_body<std::string>> res_v2_2;
	res_v2_2.body = {"Hello ", "world!\n"};
	v2::write(std::cout, res_v2_2);
	v2::request<v2::empty_body> req_v2_1;
	v2::write(std::cout, res_v2_2);
	// assert(sizeof(req_v2_1.body) == 0);  // fails with v2 implementation

	// v3
	v3::response<v3::file_body> res;
	res.body() = "test.txt";
	v3::write(std::cout, res);
	return 0;
}