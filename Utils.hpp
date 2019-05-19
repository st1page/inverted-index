#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include<string>
#include<functional>

size_t stl_hash(const std::string &s){
    std::hash<std::string> h;
	return h(s);
}
#endif