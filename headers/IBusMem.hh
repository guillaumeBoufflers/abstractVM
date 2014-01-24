#ifndef __IBUSMEM_HH__
#define __IBUSMEM_HH__

#include	<list>
#include	<string>

class	IBusMem
{
private:

public:
  virtual std::list<std::string> &getMemory() const = 0;
  virtual void setMemory(std::list<std::string> &) = 0;
  virtual ~IBusMem(){};
};

#endif
