#include	"genException.hh"

#ifndef	        __MYEXCEPTION_HH__
#define		__MYEXCEPTION_HH__

class myException
{
public:
  class lexicalException : public genException
  {
  public:
    lexicalException(const char *msg, int line = 0) : genException(msg, line, NULL)
    {
      
    }
    
    virtual ~lexicalException() throw()
    {
      
    }
  };
  
  class executionException : public genException
  {
  public:
    executionException( const char *msg, std::list<std::string> *list = NULL) : genException(msg, 0, list)
    {
      
    }
    
    virtual ~executionException() throw()
    {
      
    }
  };
  
};

#endif
