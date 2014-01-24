#ifndef __CPU_HH__
#define __CPU_HH__

#include	<list>
#include	<vector>
#include	<map>
#include	<string>
#include	"ICpu.hh"
#include	"Operand.hpp"
#include	"Io.hh"
#include	"Memory.hh"

class	Cpu : public ICpu
{
  void					(Cpu::*creation[9])();
  Io					*_io;
  Memory				*_mem;
  Init					*_bios;
  std::map<std::string, int>		_mmap;
  std::map<std::string, eOperandType>	_checkType;
  std::list<std::string>		_res;
  std::list<std::string>		&_instruction;

public:
  Cpu(std::list<std::string> &);
  virtual ~Cpu();

  /*******************/
  virtual void	add();
  virtual void	sub();
  virtual void	mul();
  virtual void	div();
  virtual void	mod();
  virtual void	pop();
  virtual void	dump();
  virtual void	print();

  /**************/

  virtual void	assert(std::vector<std::string> fields);
  virtual void	push(std::vector<std::string> fields);

  /***************/

  //  virtual void	makePtrFunc(std::string &func);
  virtual void	execInstruct();
  virtual void	pushInList(std::string &str);
  virtual std::vector<std::string> split(char delim, std::string work);
  virtual int	exec(std::string func, int *isDumpToDo);
  virtual void	initPtrFunc();
  virtual void	initMaps();
  virtual eOperandType	whatIsTheType(std::string func) const;
};

#endif
