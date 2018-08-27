// Improve reporting providing two macros, REPORT and INFO, that allow
// for streaming syntax like cout.
//
// Syntax:
//   REPORT(message_type, message_stream);
//   INFO(verbosity_level, message_stream);
//
//   message types are: FATAL, ERROR, WARNING, and INFO
//   verbosity levels are: ALWAYS, LOW, MEDIUM, HIGH, DEBUG
//
// Examples:
//   REPORT(ERROR,"Data " << data << " doesn't match expected " << expected);
//   INFO(DEBUG,"Packet contains " << packet);
//
// Assumes you define in every source file:
//
//   #include "report.h"
//   namespace { const char* MSGID = "/Company/Group/Project/Module"; }

#ifndef REPORT_H
#define REPORT_H
#include <systemc>
#include <sstream>
#include <iomanip>
extern std::ostringstream mout;
#define REPORT(message_type,message_stream) \
do {\
  mout.str("");\
  mout << std::dec << message_stream << std::ends;\
  SC_REPORT_##message_type(MSGID,mout.str().c_str());\
} while (0)

#define SC_ALWAYS SC_NONE
#define INFO(verbosity_level,message_stream) \
do {\
  if(sc_core::sc_report_handler::get_verbosity_level() >= sc_core::SC_##verbosity_level) {\
    mout.str("");\
    mout << std::dec << message_stream << std::ends;\
    SC_REPORT_INFO_VERB(MSGID,mout.str().c_str(),SC_##verbosity_level);\
  }\
} while (0)

#endif
