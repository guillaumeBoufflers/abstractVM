#ifndef __GENEXCEPTION_HH__
#define __GENEXCEPTION_HH__

#include	<stdexcept>
#include	<sstream>
#include	<iostream>
#include	<list>
#include	<string>

class genException : public std::exception
{
protected:
  std::string msg;
  const char *_Msg;
  int	&_line;
  std::list<std::string> *_instr;

public:
  genException(const char *Msg, int line = 0, std::list<std::string> *instr = NULL);
  virtual ~genException() throw();
  virtual void aff()  throw();
  
  virtual const char * what() const throw();
};

#endif
