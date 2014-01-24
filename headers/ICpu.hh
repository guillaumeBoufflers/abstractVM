#ifndef __ICPU_HH__
#define __ICPU_HH__

#include	<list>
#include	<vector>
#include	<map>
#include	<string>
#include	"enum.hh"

class	ICpu
{
public:
  virtual ~ICpu(){}
  /*******************/
  virtual void	add() = 0;
  virtual void	sub() = 0;
  virtual void	mul() = 0;
  virtual void	div() = 0;
  virtual void	mod() = 0;
  virtual void	pop() = 0;
  virtual void	dump() = 0;
  virtual void	print() = 0;

  /**************/

  virtual void	assert(std::vector<std::string> fields) = 0;
  virtual void	push(std::vector<std::string> fields) = 0;

  /***************/

  virtual void	execInstruct() = 0;
  virtual void	pushInList(std::string &str) = 0;
  virtual std::vector<std::string> split(char delim, std::string work) = 0;
  virtual int	exec(std::string func, int *isDumpToDo) = 0;
  virtual void	initPtrFunc() = 0;
  virtual void	initMaps() = 0;
  virtual eOperandType	whatIsTheType(std::string func) const = 0;
};

#endif
