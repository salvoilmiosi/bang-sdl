#ifndef __WSCONNECTION_H__
#define __WSCONNECTION_H__

#include <asio.hpp>
#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>

#include <variant>
#include "utils/utils.h"

namespace net {

    template<typename Config>
    struct client_and_connection {
        using client_type = websocketpp::client<Config>;

        client_type client;
        client_type::connection_weak_ptr connection;
    };

    class wsconnection {
    public:
        using client_handle = websocketpp::connection_hdl;

    private:
        asio::io_context &m_ctx;

        std::variant<
            std::monostate,
            client_and_connection<websocketpp::config::asio_client>,
            client_and_connection<websocketpp::config::asio_tls_client>
        > m_client;
    
    protected:
        virtual void on_open() = 0;
        virtual void on_close() = 0;
        virtual void on_message(const std::string &message) = 0;

    public:
        wsconnection(asio::io_context &ctx) : m_ctx{ctx} {}

        virtual ~wsconnection() = default;
            
        void connect(const std::string &url);
        
        void disconnect();

        void push_message(const std::string &message);
    };
}

#endif