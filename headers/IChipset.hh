#ifndef __ICHIPSET_HH__
#define __ICHIPSET_HH__

#include	<list>
#include	<string>
#include	<fstream>
#include	<iostream>

class	IChipset
{
public:
  virtual ~IChipset(){};
  virtual	void traverseList() = 0;
  virtual	void parseList(std::string &line)  = 0;
  virtual	void initMap() = 0;
  virtual	int  checkComa(std::string &line, char c) const  = 0;
  virtual	void checkInstruction(std::string &line) = 0;
  
  
  virtual	void checkSimple(std::string &instr, std::string &line) = 0;
  virtual std::list<std::string> &	getInstruct() = 0;
  virtual void	putComplexInList(std::string &a, std::string &b, std::string &c) = 0;
  virtual	std::string &checkParam(std::string &param, int size) = 0;

  virtual	void checkComplex(std::string &instr, std::string &line) = 0;
  
  virtual void	checkEndLine(std::string &end) const = 0;
};

#endif
