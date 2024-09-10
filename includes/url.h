#ifndef URL_H
#define URL_H

#include <map>
#include <string>
#include <vector>

struct url {
public:
  url(const std::string& url_str) { Parse(url_str); }

  std::string proto, host, path;
  std::map<std::string, std::vector<std::string>> query;

private:
  const std::string protocol_end_seq_ = "://";

  void Parse(const std::string& url_str);
  void ParseProtocol(std::string::const_iterator& begin,
                     std::string::const_iterator& end);
  void ParseHost(std::string::const_iterator& begin,
                 std::string::const_iterator& end);
  void ParsePath(std::string::const_iterator& begin,
                 std::string::const_iterator& end);
  void ParseQuery(std::string::const_iterator& begin,
                  std::string::const_iterator& end);
};

std::ostream& operator<<(std::ostream& out, const url& u);

std::vector<std::string> Split(const std::string& source, char sep);

#endif
