#ifndef PRJ_INCLUDE_HEADER_HPP
#define PRJ_INCLUDE_HEADER_HPP

#include <string>

namespace http {
namespace server {

struct header
{
  std::string name;
  std::string value;
};

} // namespace server
} // namespace http

#endif // PRJ_INCLUDE_HEADER_HPP