#include	"../headers/Init.hh"
#include	"../headers/enum.hh"
#include	"../headers/Operand.hpp"
#include	"../headers/myException.hh"

Init::Init()
{
  initTab();
}

Init::~Init()
{

}

void		Init::initTab()
{
  this->creation[0] = &Init::createInt8;
  this->creation[1] = &Init::createInt16;
  this->creation[2] = &Init::createInt32;
  this->creation[3] = &Init::createFloat;
  this->creation[4] = &Init::createDouble;
}

void		Init::checkFlowian(const std::string &svalue, long double max, long double min) const
{
  long double	value;
  std::stringstream	ss(svalue);
  
  ss >> value;
  if (value > max)
    throw myException::executionException("Error : overflow");
  else if  (value < min)
    throw myException::executionException("Error : underflow");
}

IOperand *	Init::createInt8(const std::string &value)
{
  this->checkFlowian(value, 128, -127);
  return (new Operand<char>(value, Int8));
}

IOperand *	Init::createInt16(const std::string &value)
{    
  this->checkFlowian(value, 32767, -32768);
  return (new Operand<signed short>(value, Int16));
}

IOperand *	Init::createInt32(const std::string &value)
{
  this->checkFlowian(value, 2147483647, -2147483648);
  return (new Operand<signed int>(value, Int32));
}

IOperand *	Init::createFloat(const std::string &value)
{
  this->checkFlowian(value, 3.4e+38, -3.4e-38);
  return (new Operand<float>(value, Float));
}

IOperand *	Init::createDouble(const std::string &value)
{
  this->checkFlowian(value, 1.7e308, -1.7e-308);
  return (new Operand<double>(value, Double));
}

IOperand *	Init::createOperand(eOperandType type, const std::string &value)
{
  if (type >= 0 && type <= 4)
    return ((this->*creation[type])(value));
  return NULL;
}
