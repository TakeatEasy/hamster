#include "StringUtil.h"


namespace hamster {
namespace utils {

std::string stripBasename(const std::string& full_path) {
    const char kSeparator = '/';
    size_t pos = full_path.rfind(kSeparator);
    if (pos != std::string::npos) { 
        return full_path.substr(pos + 1, std::string::npos);
    } else {
        return full_path;
    }
}

std::ostream& operator<<(std::ostream& out, const SourceLocation& loc) {
  out << loc.function << " at " << loc.file << ":" << loc.line;
  return out;
}

size_t ReplaceAll(std::string& s, const char* from, const char* to) {
    size_t numReplaced = 0;
    std::string::size_type lenFrom = std::strlen(from);
    std::string::size_type lenTo = std::strlen(to);
    for (auto pos = s.find(from); pos != std::string::npos;
        pos = s.find(from, pos + lenTo)) {
        s.replace(pos, lenFrom, to);
        numReplaced++;
    }
    return numReplaced;
}

} // namespace utils
} // namespace hamster