#ifndef			__IOPERAND_HH__
#define			__IOPERAND_HH__

#include		<iostream>
#include		<string>
#include		"enum.hh"

class	IOperand
{
public:
  virtual std::string const			&toString() const = 0; // Renvoie une string reprensentant l'instance

  virtual int					getPrecision() const = 0; // Renvoie la precision du type de l'instance
  virtual eOperandType				getType() const = 0; // Renvoie le type de l'instance. Voir plus bas

  virtual IOperand				*operator+(const IOperand &rhs) const = 0; // Somme
  virtual IOperand				*operator-(const IOperand &rhs) const = 0; // Difference
  virtual IOperand				*operator*(const IOperand &rhs) const = 0; // Produit
  virtual IOperand				*operator/(const IOperand &rhs) const = 0; // Quotient
  virtual IOperand				*operator%(const IOperand &rhs) const = 0; // Modulo
  virtual ~IOperand(){};
};

#endif
