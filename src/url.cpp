#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "print.h"
#include "url.h"

std::ostream& operator<<(std::ostream& out, const url& u) {
  if (!u.proto.empty())
    out << u.proto << std::string("://");

  if (!u.host.empty())
    out << u.host;

  if (!u.path.empty())
    out << u.path;

  if (!u.query.empty()) {
    out << std::string("?");

    bool first = true;

    for (auto& [key, values] : u.query) {
      for (const std::string& value : values) {
        if (!first) {
          out << std::string("&");
        }
        first = false;
        out << key << "=" << value;
      }
    }
  }

  return out;
}

std::vector<std::string> Split(const std::string& source, char sep) {
  std::vector<std::string> result;

  auto start = source.begin();
  const auto& end = source.end();

  while (start < end) {
    auto sep_it = find(start, end, sep);
    std::string param(start, sep_it);
    result.push_back(param);
    start = sep_it + 1;
  }

  return result;
}

void url::ParseProtocol(std::string::const_iterator& begin,
                        std::string::const_iterator& end) {
  auto protocol_it = std::search(
      begin, end, protocol_end_seq_.begin(), protocol_end_seq_.end());

  if (protocol_it != end) {
    proto = {begin, protocol_it};

    int proto_offset =
        std::distance(begin, protocol_it + protocol_end_seq_.length());
    std::advance(begin, proto_offset);
  }
}

void url::ParseHost(std::string::const_iterator& begin,
                    std::string::const_iterator& end) {
  auto path_it = std::find(begin, end, '/');

  int host_offset;

  if (path_it != end) {
    host = {begin, path_it};
    host_offset = std::distance(begin, path_it);
  } else {
    host = {begin, end};
    host_offset = std::distance(begin, end);
  }
  std::advance(begin, host_offset);
}

void url::ParsePath(std::string::const_iterator& begin,
                    std::string::const_iterator& end) {
  auto query_it = std::find(begin, end, '?');

  int path_offset;

  if (query_it != end) {
    path = {begin, query_it};
    path_offset = std::distance(begin, query_it);
  } else {
    path = {begin, end};
    path_offset = std::distance(begin, end);
  }
  std::advance(begin, path_offset);
}

void url::ParseQuery(std::string::const_iterator& begin,
                     std::string::const_iterator& end) {
  std::string query_string = {next(begin), end}; // skip `?`

  std::vector<std::string> query_vec = Split(query_string, '&');

  for (auto param : query_vec) {
    std::vector<std::string> key_value_vec = Split(param, '=');

    if (key_value_vec.size() == 2) {
      std::string key = key_value_vec[0];
      std::string value = key_value_vec[1];

      query[key].push_back(value);
    }
  }
}

void url::Parse(const std::string& url_str) {
  std::string::const_iterator url_begin = url_str.begin();
  std::string::const_iterator url_end = url_str.end();

  ParseProtocol(url_begin, url_end);

  ParseHost(url_begin, url_end);

  if (url_begin == url_end)
    return;

  ParsePath(url_begin, url_end);

  if (url_begin == url_end)
    return;

  auto fragment_it = find(url_begin, url_end, '#');

  if (fragment_it != url_end)
    url_end = fragment_it;

  ParseQuery(url_begin, url_end);
}
