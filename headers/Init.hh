#ifndef __INIT_HH__
#define __INIT_HH__

#include	<string>
#include	<list>
#include	"IInit.hh"
#include	"enum.hh"

class		Init : public IInit
{
  IOperand *createInt32(const std::string & value);
  IOperand *createInt16(const std::string & value);
  IOperand *createInt8(const std::string & value);
  IOperand *createFloat(const std::string & value);
  IOperand *createDouble(const std::string & value);
  IOperand *(Init::*creation[5])(const std::string &);
public:
  Init();
  virtual ~Init();

  IOperand *createOperand(eOperandType type, const std::string & value);
  void	   checkFlowian(const std::string &svalue, long double max, long double min) const;
  virtual void	initTab();
};

#endif
