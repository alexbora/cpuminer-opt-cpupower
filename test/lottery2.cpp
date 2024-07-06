/**
 * @author      : alex (alex@mac.local)
 * @file        : lottery2
 * @created     : Joi Apr 11, 2024 19:58:58 EEST
 */

class lottery2 {
  lottery2(int);
  ~lottery2();

 private:
  int n;
};

lottery2::lottery2(int n) : n(0) {}

lottery2::~lottery2() { delete this; }

