#include	"../headers/genException.hh"

genException::genException(const char *Msg, int line , std::list<std::string> *instr) : _Msg(Msg), _line(line), _instr(instr)
{
  this->aff();
}

genException::~genException() throw()
{

}

void genException::aff()  throw()
  {
    if (_instr)
      {
	for (std::list<std::string>::const_iterator it = _instr->begin(); it != _instr->end(); ++it)
	  std::cout << *it << std::endl;
      }
    std::ostringstream oss;
    if (_line != 0)
      oss <<  _Msg << " à la ligne " << _line << std::endl;
    else
      oss << _Msg << std::endl;
    this->msg = oss.str();
  }

const char * genException::what() const throw()
{
  return this->msg.c_str();
}
