/**
 * @author      : alex (alex@mac.local)
 * @file        : log
 * @created     : Duminică Iun 09, 2024 11:14:24 EEST
 */

#include <unistd.h>

class log {
 public:
  log();
  ~log();

  size_t write_log(const char *, size_t);

 private:
  int log_level;
  int log_file;
};

log::log(){};

log::~log(){};

template <typename T>
size_t log::write_log(const T *msg, size_t size) {
  return write(log_file, msg, size);
}
