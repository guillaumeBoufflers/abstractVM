#include	"../headers/Cpu.hh"
#include	"../headers/genException.hh"

Cpu::Cpu(std::list<std::string> &instructs) : _instruction(instructs)
{
  this->_mem = new Memory();
  this->_bios = new Init();
  initMaps();
  initPtrFunc();
  execInstruct();
}

 Cpu::~Cpu()
 {

 }

void	Cpu::pop()
{
  this->_mem->mFrontPop();
}

void	Cpu::pushInList(std::string &str)
{
  this->_res.push_front(str);
}

void	Cpu::dump()
{
  std::string		str;
  std::list<IOperand *>	nnew;
  IOperand		*n;

  nnew = this->_mem->getPile();
  while (!nnew.empty())
    {
      if (nnew.empty() == true)
	throw myException::executionException("emtpy stack !");
      n = nnew.back();
      nnew.pop_back();
      str = n->toString();
      this->pushInList(str);
    }
}

eOperandType	Cpu::whatIsTheType(std::string func) const
{
  eOperandType		ret;

  for (std::map<std::string, eOperandType>::const_iterator it = this->_checkType.begin(); it != this->_checkType.end(); ++it)
    {
      std::string tmp = it->first;
      if (tmp == func)
	{
	  ret = it->second;
     	  break;
	}
    }
  return (ret);
}

void	Cpu::assert(std::vector<std::string> fields)
{ 
  IOperand	*op;
  IOperand	*op2;
  eOperandType	type;
  
  type = whatIsTheType(fields[1]);
  op = _bios->createOperand(type, fields[2]);
  op2 = this->_mem->mFrontGet();
  if ((op->getType() != op2->getType()) || (op->toString() != op2->toString()))
    throw myException::executionException("the value checked by assert doesnt match with the first value of the stack", &this->_res);
}

void	Cpu::print()
{
  IOperand		*n;
  std::string		msend;
  char			bitch[2];
  int			v;
  char			c;

  n = this->_mem->mFrontGet();
  if (n->getType() == Int8)
    {
      std::stringstream	ss(n->toString());;
      ss >> v;
      c = v;
      bitch[0] = c;
      bitch[1] = '\0';
      msend = bitch;
      this->pushInList(msend);
    }
  else
    throw myException::executionException("Error : the value checked by print doesn't match with an int8", &this->_res);
}

void	Cpu::push(std::vector<std::string> fields)
{
  eOperandType	type;

  type = whatIsTheType(fields[1]);
  this->_mem->mFrontPush(_bios->createOperand(type, fields[2]));
}

std::vector<std::string> Cpu::split(char delim, std::string work) 
{
  std::vector<std::string> flds;
  std::string buf = "";
  work = work.data();
  size_t	i = 0;

  if (!flds.empty()) 
    flds.clear();
  while (i < work.length()) 
    {
      while (work[i] != delim && i < work.length() )
	{
	  buf += work[i];
	  i++;
	}
      flds.push_back(buf);
      buf = "";
      while (work[i] == delim && i < work.length() )
	i++;
    }
  return (flds);
}

void	Cpu::add()
{
  IOperand *n1;
  IOperand *n2;

  if (this->_mem->myStackSize() < 2)
    throw myException::executionException("stack is not big enough to add!", &this->_res);
  n1 = this->_mem->mFrontGet();
  this->_mem->mFrontPop();
  n2 = this->_mem->mFrontGet();
  this->_mem->mFrontPop();
  this->_mem->mFrontPush(*n1 + *n2);
}

void	Cpu::sub()
{
  IOperand *n;
  IOperand *n1;
  IOperand *n2;

  if (this->_mem->myStackSize() < 2)
    throw myException::executionException("stack is not big enough to sub!", &this->_res);
  n1 = this->_mem->mFrontGet();
  this->_mem->mFrontPop();
  n2 = this->_mem->mFrontGet();
  n = *n1 - *n2;
  this->_mem->mFrontPop();
  this->_mem->mFrontPush(n);
}

void	Cpu::mul()
{
  IOperand *n;
  IOperand *n1;
  IOperand *n2;

  if (this->_mem->myStackSize() < 2)
    throw myException::executionException("stack is not big enough to mul!", &this->_res);
  n1 = this->_mem->mFrontGet();
  this->_mem->mFrontPop();
  n2 = this->_mem->mFrontGet();
  n = *n1 * (*n2);
  this->_mem->mFrontPop();
  this->_mem->mFrontPush(n);
}

void	Cpu::div()
{
  IOperand *n;
  IOperand *n1;
  IOperand *n2;

  if (this->_mem->myStackSize() < 2)
    throw myException::executionException("stack is not big enough to div!", &this->_res);
  n1 = this->_mem->mFrontGet();
  this->_mem->mFrontPop();
  n2 = this->_mem->mFrontGet();
  n = *n1 / *n2;
  this->_mem->mFrontPop();
  this->_mem->mFrontPush(n);
}

void	Cpu::mod()
{
  IOperand *n;
  IOperand *n1;
  IOperand *n2;

  if (this->_mem->myStackSize() < 2)
    throw myException::executionException("stack is not big enough to mod!", &this->_res);
  n1 = this->_mem->mFrontGet();
  this->_mem->mFrontPop();
  n2 = this->_mem->mFrontGet();
  n = *n1 % *n2;
  this->_mem->mFrontPop();
  this->_mem->mFrontPush(n);
}

void	Cpu::initPtrFunc()
{
  this->creation[0] = &Cpu::add;
  this->creation[1] = &Cpu::sub;
  this->creation[2] = &Cpu::mul;
  this->creation[3] = &Cpu::div;
  this->creation[4] = &Cpu::mod;
  this->creation[5] = &Cpu::pop;
  this->creation[6] = &Cpu::dump;
  this->creation[7] = &Cpu::print;
}

void	Cpu::initMaps()
{
  this->_mmap["add"] = 0;
  this->_mmap["sub"] = 1;
  this->_mmap["mul"] = 2;
  this->_mmap["div"] = 3;
  this->_mmap["mod"] = 4;
  this->_mmap["pop"] = 5;
  this->_mmap["dump"] = 6;
  this->_mmap["print"] = 7;
  this->_checkType["int8"] = Int8;
  this->_checkType["int16"] = Int16;
  this->_checkType["int32"] = Int32;
  this->_checkType["float"] = Float;
  this->_checkType["double"] = Double;
}

int	Cpu::exec(std::string func, int *isDumpToDo)
{
  int		ret = -1;

  for (std::map<std::string,int>::const_iterator it = this->_mmap.begin(); it != this->_mmap.end(); ++it)
    {
      std::string tmp = it->first;
      if (tmp == func)
	{
	  ret = it->second;
	  if (ret == 6)
	    (*isDumpToDo) = 1;
	  (this->*creation[ret])();
	  return (ret);
	}
    }
  return (-1);
}

void	Cpu::execInstruct()
{
  int				next;
  int				isDumpToDo;
  int				isAnExit;
  std::string			str;
  std::vector<std::string>	fields;

  next = 0;
  isDumpToDo = 0;
  isAnExit = 0;
  while (!(this->_instruction.empty()) && next == 0)
    {
      fields.clear();
      str.clear();
      str = this->_instruction.front();
      fields = split(' ', str);
      if (fields.front() == "exit")
	{
	  next = 1;
	  isAnExit = 1;
	}
      else
	{
	  if (exec(fields.front(), &isDumpToDo) == -1)
	    {
	      if (fields.front() == "assert")
		this->assert(fields);
	      else
		this->push(fields);
	    }
	  this->_instruction.pop_front();
	}
    }
  if (isDumpToDo == 1)
    this->_io->doDump(this->_res);
  if (isAnExit == 0)
    throw myException::executionException("Exit ain't present in the file");
}
