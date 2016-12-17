
#include "Logger.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

//---------------------------------------------------------------------------//


#include <sstream>
#include <cstdlib>

using namespace std;

static ostringstream devnull;

Logger::Severity Logger::_minSeverity = Logger::debugging;
ostream * Logger::_myOstream  = 0 ;
ostream * Logger::_myErrstream (&cerr);
ostream * Logger::_myNullstream (&devnull);
bool Logger::_doPrint = true;

Logger::Logger(){}

Logger::~Logger(){}

Logger::Logger(const Logger & other){}

ostream&  Logger::msg(Logger::Severity severity,
		       const char* facility )
{
  _doPrint = true;
  if(!_myOstream) _myOstream = new ostringstream ;
  else ((ostringstream*) _myOstream)->str("");
  
  if(severity >= _minSeverity){
    *_myOstream << toString(severity) << ":" << facility << ":";
  }else{
    _doPrint =false;
    return *_myNullstream ;
  }

  if ( severity == fatal ){
    *_myOstream << ::endlog;
    ::abort();
  }
  return *_myOstream;
}

void  Logger::endlog(ostream& os){
  if(_doPrint) {
    cout << ((ostringstream*) _myOstream)->str() << endl;
  
  }
}

const char* Logger::toString(Logger::Severity sever){
  switch (sever) {
  case -2:
    return "Debug";
  case -1:
    return "Develop";
  case 0:
    return "Trace";
  case 1:
    return "Routine";
  case 2:
    return "Warning";
  case 3:
    return "Error";
  case 4:
    return "Fatal";
  }
  return "Fatal";
}

Logger::Severity Logger::toEnum(const  std::string& level){
  if(level == "development") return development ;
  if(level == "debugging")   return debugging ;
  if(level == "trace")       return trace;
  if(level == "routine")     return routine;
  if(level == "fatal")       return fatal;
  if(level == "warning")     return warning;
  if(level == "error")       return error;
  return fatal;
}

ostream& endlog(ostream& os){
  Logger::endlog(os);
  return os;
}
