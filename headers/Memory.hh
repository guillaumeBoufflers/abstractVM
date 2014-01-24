#ifndef __MEMORY_HH__
#define __MEMORY_HH__

#include	"IMemory.hh"

class	Memory : public IMemory
{
private:
  std::list<IOperand *>	mem;
public:
  Memory();
  virtual ~Memory();

  /****************/
  virtual std::list<IOperand *> getPile() const;
  virtual void			setPile(std::list<IOperand *> &);

  virtual bool			myStackEmpty() const;
  virtual int			myStackSize() const;
  virtual IOperand		*mFrontGet() const;
  virtual void			mFrontPop();
  virtual void			mFrontPush(IOperand *n);
};

#endif
