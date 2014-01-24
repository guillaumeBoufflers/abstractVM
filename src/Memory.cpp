#include	<string>
#include	"../headers/genException.hh"
#include	"../headers/myException.hh"
#include	"../headers/Memory.hh"
#include	"../headers/IOperand.hh"

Memory::Memory()
{

}

Memory::~Memory()
{

}

std::list<IOperand *>	Memory::getPile() const
{
  return(this->mem);
}

void			Memory::setPile(std::list<IOperand *> & mem)
{
  this->mem = mem;
}

bool			Memory::myStackEmpty() const
{
  return (this->mem.empty());
}

int			Memory::myStackSize() const
{
  return (this->mem.size());
}

IOperand		*Memory::mFrontGet() const
{
  if (this->myStackEmpty())
    {
      throw myException::executionException("emtpy stack !");
    }
  else
    return(this->mem.front());
}

void			Memory::mFrontPop()
{
  if (this->myStackEmpty())
    throw myException::executionException("emtpy stack !");
  else
    this->mem.pop_front();
}

void			Memory::mFrontPush(IOperand *n)
{
  this->mem.push_front(n);
}
