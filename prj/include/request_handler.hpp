#ifndef PRJ_INCLUDE_REQUEST_HANDLER_HPP
#define PRJ_INCLUDE_REQUEST_HANDLER_HPP

#include <string>
#include "database_manager.hpp"

namespace http {
    namespace server {

        struct reply;
        struct request;

/// The common handler for all incoming requests.
        class request_handler
        {
        public:
            request_handler(const request_handler&) = delete;
            request_handler& operator=(const request_handler&) = delete;

            /// Construct with a directory containing files to be served.
            explicit request_handler(const std::string& doc_root);

            /// Handle a request and produce a reply.
            void handle_request(const request& req, reply& rep);

            void handle_request(const request& req, reply& rep, database_manager& db_manager);

        private:
            /// The directory containing the files to be served.
            std::string doc_root_;

            /// Perform URL-decoding on a string. Returns false if the encoding was
            /// invalid.
            static bool url_decode(const std::string& in, std::string& out);
        };

    } // namespace server
} // namespace http

#endif // PRJ_INCLUDE_REQUEST_HANDLER_HPP