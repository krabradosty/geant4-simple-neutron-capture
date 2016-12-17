
#ifndef LOGGER_HH
#define LOGGER_HH

#include <iostream>
#include <string>

#define ERRLINE_HACK_1(line)   #line
#define ERRLINE_HACK_2(line)   ERRLINE_HACK_1(line)

#ifdef Log
#undef Log
#endif
#define Log(sev) Logger::msg( Logger::sev, __FILE__ "(" ERRLINE_HACK_2(__LINE__) ")" )


//---------------------------------------------------------------------------//

class Logger
{
public:

  // a severity enum is defined; use only these values
  enum Severity {debugging=-2, development=-1, trace=0, routine, warning, error, fatal};
   //	fatal:		The message is related to a condition preventing
  //			further execution of the program.  ErrLogger will
  //			terminate the program.  Programmers should not call
  //			abort or exit themselves.

  //	error:		A condition exists such that requested result
  //			or action can not be produced.  This is a serious

  //	warning:	The result is produced, but may not be
  //			what's desired due to an unexpected condition

  //	routine:	Nothing known to be wrong with the result;
  //			messages that are always produced in normal
  //			operation

  //	trace:		Messages about the flow of program control
  //			and which optional operations took place.
  //			(This is the default if nothing is defined)
  
  //	debugging:	Information in addition to the above

 // members
  static Severity GetSeverity() { return _minSeverity; }
  static std::ostream& msg( Logger::Severity severity,
		       const char* facility);

  static void SetSeverity(Severity sever){ _minSeverity = sever;}
  static void endlog(std::ostream& s);
  static Severity toEnum(const std::string& );

protected:
 //default constructor
  Logger();

  //copy constructor
  Logger(const Logger &);

  //destructor
  ~Logger();

  //public interface

  //protected members
protected:


  //private  members
private:
  
  static const char* toString(Severity);

  static std::ostream* _myOstream;
  static std::ostream* _myErrstream;
  static std::ostream* _myNullstream;

  static Severity _minSeverity;

  static bool _doPrint;
};
std::ostream& endlog(std::ostream& s);

#endif
