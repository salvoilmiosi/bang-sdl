#ifndef __SERVER_H__
#define __SERVER_H__

#include <filesystem>
#include <functional>
#include <thread>
#include <map>

#include "utils/sdlnet.h"

using message_callback_t = std::function<void(const std::string &)>;

class bang_server {
public:
    bang_server(const std::filesystem::path &base_path);
    bang_server(const bang_server &) = delete;

    void set_message_callback(message_callback_t &&fun) {
        m_message_callback = std::move(fun);
    }

    void set_error_callback(message_callback_t &&fun) {
        m_error_callback = std::move(fun);
    }

    bool start();

    void join() {
        m_thread.join();
    }
    
    void stop() {
        m_thread.request_stop();
    }

private:
    sdlnet::socket_set m_sockset;
    sdlnet::tcp_server_socket m_socket;
    std::map<sdlnet::ip_address, sdlnet::tcp_peer_socket> m_clients;

    std::jthread m_thread;

    message_callback_t m_message_callback;
    message_callback_t m_error_callback;

    std::filesystem::path m_base_path;

    void print_message(const std::string &msg) {
        if (m_message_callback) m_message_callback(msg);
    }

    void print_error(const std::string &msg) {
        if (m_error_callback) m_error_callback(msg);
    }
};

#endif