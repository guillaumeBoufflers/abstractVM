#ifndef __IMEMORY_HH__
#define __IMEMORY_HH__

#include	<list>
#include	<string>
#include	"IOperand.hh"

class	IMemory
{
public:
  virtual			~IMemory() {};
  virtual std::list<IOperand *> getPile() const = 0;
  virtual void			setPile(std::list<IOperand *> &)  = 0;

  virtual bool			myStackEmpty() const = 0;
  virtual int				myStackSize() const = 0;
  virtual void			mFrontPop() = 0;
  virtual void			mFrontPush(IOperand *) = 0;
};

#endif
