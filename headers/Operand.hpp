#ifndef			__OPERAND_HPP__
#define			__OPERAND_HPP__

#include		<cmath>
#include		<iostream>
#include		<iomanip>
#include		<sstream>
#include		<string>
#include		"enum.hh"
#include		"Init.hh"
#include		"IOperand.hh"
#include		"myException.hh"

template <class T> 
class	Operand : public IOperand
{
private:
  T	  				_value;
  std::string				_svalue;
  eOperandType				_type;
  Init					*_bios;

public:
  Operand(const std::string &value, eOperandType t);
  virtual ~Operand();

  /*************/

  std::string const			&toString() const;

  /*************/

  int					getPrecision() const;
  eOperandType				getType() const;

  /*************/

  IOperand				*operator+(const IOperand &rhs) const;
  IOperand				*operator-(const IOperand &rhs) const;
  IOperand				*operator*(const IOperand &rhs) const;
  IOperand				*operator/(const IOperand &rhs) const;
  IOperand				*operator%(const IOperand &rhs) const;
};

template <typename T>
Operand<T>::Operand(const std::string &value, eOperandType t) : _svalue(value), _type(t)
{
  _bios = new Init();
}

template <typename T>
Operand<T>::~Operand()
{

}

  /*************/

template <typename T>
std::string const			&Operand<T>::toString() const
{
  return (this->_svalue);
}

  /*************/

template <typename T>
int					Operand<T>::getPrecision() const
{
  std::string str2;
  int	pos;

  pos = _svalue.find('.');
  //std::cout << _svalue << std::endl;
  if (pos != -1)
    str2 = this->_svalue.substr(pos, _svalue.size() - 1);
  else
    return (0);
  //std::cout << "apres" << std::endl;
  return (str2.size() - 1);
}

template <typename T>
eOperandType				Operand<T>::getType() const
{
  return (this->_type);
}

template <typename T>
IOperand				*Operand<T>::operator+(const IOperand &rhs) const
{ 
  eOperandType				t;
  std::string				resString;  
  std::stringstream			ss1(this->toString()), ss2(rhs.toString()), ss;
  long double				res, val1, val2;
  int					prec;

  ss1 >> val1;
  ss2 >> val2;
  res = val1 + val2;
  if (this->getType() == Float || rhs.getType() == Double)
    {
      prec = this->getPrecision();
      if (rhs.getPrecision() > prec)
	prec = rhs.getPrecision();
      ss << std::fixed << std::setprecision(prec) <<  res;
    }
  else
    ss << res;
  t = this->getType();
  if (this->getType() < rhs.getType())
    t = rhs.getType();
  return (this->_bios->createOperand(t, ss.str()));
}

  /***************/

template <typename T>
IOperand				*Operand<T>::operator-(const IOperand &rhs) const
{
  eOperandType				t;
  std::string				resString;  
  std::stringstream			ss1(this->toString()), ss2(rhs.toString()), ss;
  long double				res, val1, val2;
  int					prec;

  ss1 >> val1;
  ss2 >> val2;
  res = val1 - val2;
  if (this->getType() == Float || rhs.getType() == Double)
    {
      prec = this->getPrecision();
      if (rhs.getPrecision() > prec)
	prec = rhs.getPrecision();
      ss << std::fixed << std::setprecision(prec) <<  res;
    }
  else
    ss << res;
  t = this->getType();
  if (this->getType() < rhs.getType())
    t = rhs.getType();
  return (this->_bios->createOperand(t, ss.str()));

}

template <typename T>
IOperand				*Operand<T>::operator*(const IOperand &rhs) const
{
  eOperandType				t;
  std::string				resString;  
  std::stringstream			ss1(this->toString()), ss2(rhs.toString()), ss;
  long double				res, val1, val2;
  int					prec;

  ss1 >> val1;
  ss2 >> val2;
  res = val1 * val2;
  if (this->getType() == Float || rhs.getType() == Double)
    {
      prec = this->getPrecision();
      if (rhs.getPrecision() > prec)
	prec = rhs.getPrecision();
      ss << std::fixed << std::setprecision(prec) <<  res;
    }
  else
    ss << res;
  t = this->getType();
  if (this->getType() < rhs.getType())
    t = rhs.getType();
  return (this->_bios->createOperand(t, ss.str()));
}

template <typename T>
IOperand				*Operand<T>::operator/(const IOperand &rhs) const
{
  eOperandType				t;
  std::string				resString;  
  std::stringstream			ss1(this->toString()), ss2(rhs.toString()), ss;
  long double				res, val1, val2;
  int					prec;

  ss1 >> val1;
  ss2 >> val2;
  if (val2 == 0)
    throw myException::executionException("Error : division by division !");
  res = val1 / val2;
  if (this->getType() == Float || rhs.getType() == Double)
    {
      prec = this->getPrecision();
      if (rhs.getPrecision() > prec)
	prec = rhs.getPrecision();
      ss << std::fixed << std::setprecision(prec) <<  res;
    }
  else
    ss << res;
  t = this->getType();
  if (this->getType() < rhs.getType())
    t = rhs.getType();
  return (this->_bios->createOperand(t, ss.str()));
}


template <typename T>
IOperand				*Operand<T>::operator%(const IOperand &rhs) const
{
  eOperandType				t;
  std::string				resString;  
  std::stringstream			ss1(this->toString()), ss2(rhs.toString()), ss;
  long int				res, val1, val2;

  ss1 >> val1;
  ss2 >> val2;
  if (val2 == 0)
    throw myException::executionException("Error : modulo by division !");
  res = val1 % val2;
  ss << res;
  t = this->getType();
  if (this->getType() < rhs.getType())
    t = rhs.getType();
  return (this->_bios->createOperand(t, ss.str()));
}

template <>
inline IOperand				*Operand<float>::operator%(const IOperand &rhs) const
{
  throw myException::executionException("Error : modulo with a foat which is not a valid operation");
  std::string tmp = rhs.toString();
  return NULL;
}

template <>
inline IOperand				*Operand<double>::operator%(const IOperand &rhs) const
{
  throw myException::executionException("Error : modulo with a double which is not a valid operation");
  std::string tmp = rhs.toString();
  return NULL;
}

#endif
