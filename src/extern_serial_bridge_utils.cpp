// Includes & namespaces from test/test_all.cpp
#include <iostream>
#include <iterator>
#include <sstream>
#include <boost/thread.hpp>

#include "cryptonote_format_utils.h"
#include "monero_fork_rules.hpp"
#include "serial_bridge_utils.hpp"
#include "string_tools.h"

using namespace boost;
using namespace epee;
using namespace serial_bridge_utils;
using namespace std;

//
// Serialization bridge
//
#include "../src/serial_bridge_index.hpp"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
using namespace serial_bridge;

//
// External serialization bridge functions
// All functions must use char* arrays instead of strings to be exported and used in rust.
//
extern "C" {
    const char* extern_decode_address(const char* args_arr) {
    	string s = args_arr;

        auto ret_string = serial_bridge::decode_address(s);

    	char *c = new char[ret_string.length() + 1];
        strcpy(c, ret_string.c_str());

        return c;
    }

    const char* extern_send_step1(const char* args_arr) {
        string s = args_arr;

        auto ret_string = serial_bridge::send_step1__prepare_params_for_get_decoys(s);

        char *c = new char[ret_string.length() + 1];
        strcpy(c, ret_string.c_str());

        return c;
    }

    const char* extern_send_step2(const char* args_arr) {
        string s = args_arr;

        auto ret_string = serial_bridge::send_step2__try_create_transaction(s);

        char *c = new char[ret_string.length() + 1];
        strcpy(c, ret_string.c_str());

        return c;
    }
}