#include <dlib/logger.h>
#include <dlib/misc_api.h>

using namespace dlib;

// Create a logger object somewhere.  It is usually convenient to make it at the
// global scope which is what I am doing here.  The following statement creates
// a logger that is named example.
logger dlog("example");

int main() {
  // Every logger has a logging level (given by dlog.level()).  Each log message
  // is tagged with a level and only levels equal to or higher than dlog.level()
  // will be printed.  By default all loggers start with level() == LERROR.  In
  // this case I'm going to set the lowest level LALL which means that dlog will
  // print all logging messages it gets.
  dlog.set_level(LALL);

  // print our first message.  It will go to cout because that is the default.
  dlog << LINFO << "This is an informational message.";

  // now print a debug message.
  int variable = 8;
  dlog << LDEBUG << "The integer variable is set to " << variable;

  // the logger can be used pretty much like any ostream object.  But you have
  // to give a logging level first.  But after that you can chain << operators
  // like normal.

  if (variable > 4)
    dlog << LWARN << "The variable is bigger than 4!  Its value is "
         << variable;

  dlog << LINFO << "we are going to sleep for half a second.";
  // sleep for half a second
  dlib::sleep(500);
  dlog << LINFO << "we just woke up";

  dlog << LINFO << "program ending";
}

