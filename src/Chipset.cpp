#include	"../headers/Chipset.hh"
#include	"../headers/genException.hh"
#include	"../headers/myException.hh"
#include	"../headers/Cpu.hh"
#include	<algorithm>

Chipset::Chipset(std::list<std::string> &list) : file(list), num(1)
{
  initMap();
  traverseList();
}

Chipset::~Chipset()
{

}

std::list<std::string> &	Chipset::getInstruct()
{
  return (this->final);
}

void	Chipset::initMap()
{
  this->verif["push"] = 1;
  this->verif["pop"] = 0;
  this->verif["assert"] = 1;
  this->verif["add"] = 0;
  this->verif["dump"] = 0;
  this->verif["sub"] = 0;
  this->verif["mul"] = 0;
  this->verif["div"] = 0;
  this->verif["mod"] = 0;
  this->verif["print"] = 0;
  this->verif["exit"] = 0;
  this->verifC["int8"] = 1;
  this->verifC["int16"] = 1;
  this->verifC["int32"] = 1;
  this->verifC["double"] = 0;
  this->verifC["float"] = 0;
}

/* regarde si des ; sont présents dans la chaine passée en paramètre
 
   si la valeur de retour est 0 , il y a une erreur de syntaxe */

int	Chipset::checkComa(std::string &line, char c) const
{
  int	a = 0;

  if ((a = line.find(";")) == -1)
    return (-1);
  std::string tmp = line.substr(0, a + 1);
  const char *str = tmp.c_str();
  a = 0;
  while (str[a] && str[a] != ';')
    {
      if (str[a] != ';' && str[a] != c)
	return (0);
      a++;
    }
  return (1);
}

/* verifie la syntaxe des paramètres selon que ce soit un entier ou un nombre à virgule 
   
   utilise un algo de la stl , et la position des points pour définir si c'est bon */

std::string	&Chipset::checkParam(std::string &param, int entier)
{
  std::string	nbr = param.substr(1, param.size() - 2);
  std::string	sav(nbr);
  int	a = nbr.find("-"), b = 0;


  (a != -1 && a != 0) ? throw myException::lexicalException("Erreur de syntaxe sur le nombre" , num) : nbr = nbr;
  if (a == 0)
    nbr = nbr.substr(1, nbr.size() - 1);
  if (entier == 1)
    {
      ((nbr.find_first_not_of("0123456789")) != std::string::npos) ? throw myException::lexicalException("Erreur de syntaxe sur le nombre", num) : param.clear();
      return (param = sav);
    }
  //else if (entier == 0)
  //    {
  ((nbr.find_first_not_of("0123456789.")) != std::string::npos) ? throw myException::lexicalException("Erreur de syntaxe sur le nombre", num) : param.clear();
  a = nbr.find(".");
  (a == -1) ? throw myException::lexicalException("Erreur : la valeur du type n'est pas respectée", num) : b = nbr.rfind(".");
  (a != b) ? throw myException::lexicalException("Erreur : la valeur du type n'est pas respectée", num) : (a = b);
  ((a == 0 || (size_t)a == (nbr.size() - 1))) ? throw myException::lexicalException("Erreur : la valeur du type n'est pas respectée", num) : param = sav;
  return (param);
  // }
}

/* concatene correctement la chaine finale d'une instruction complexe correcte

   elle met ensuite le tout dans la liste finale envoyée au processeur */

void	Chipset::putComplexInList(std::string &instr, std::string &type, std::string &val)
{
  std::string toSend;

  type.erase(0, 1);
  toSend.append(instr);
  toSend.append(" ");
  toSend.append(type);
  toSend.append(" ");
  toSend.append(val);
  final.push_back(toSend);
}

/* verifie les paramètres assert et push */

void	Chipset::checkComplex(std::string &instr, std::string &line)
{
  std::string	param(""), type(""), typeV(" "), tmp(line.substr(0, instr.size()));
  int		a = 0, b = 0, c = 0;
  std::string::iterator it;

  (tmp != instr) ? (throw myException::lexicalException("Erreur de syntaxe sur l'instruction", num)) : tmp.clear();
  for (std::map<std::string, int>::const_iterator it = verifC.begin(); it != verifC.end(); ++it)
    {
      if ((a = line.find(it->first)) != -1)
	{
	  type = it->first; a = it->second ; break;
	}
      b++;
    }
  (type == "") ? (throw myException::lexicalException("Erreur : le type n'existe pas", num)) : tmp = line.substr(instr.size(), type.size() + 1);
  typeV.append(type);
  (tmp != typeV) ? (throw myException::lexicalException("Erreur de syntaxe sur le type", num)) : tmp.clear();
  c = instr.size() + typeV.size();
  tmp = line.substr(c);
  c = tmp.find(')');
  tmp = tmp.substr(0, c + 1);
  it = tmp.begin();
  (*it == '(' && tmp.size() >= 3) ? (param = checkParam(tmp, a)) : (throw myException::lexicalException("Erreur de syntaxe sur le parametre", num));
  a = typeV.size() + instr.size() + tmp.size() + 2;
  type = line.substr(a, line.size() - a);
  a = checkComa(type, ' ');
  (a == 0) ? throw myException::lexicalException("Erreur de syntaxe après l'instruction", num) : checkEndLine(type);
  putComplexInList(instr, typeV, param);
}

/* regarde ce qu'il reste à la fin de la ligne et leve des exceptions si il y a des erreurs */

void	Chipset::checkEndLine(std::string &end) const
{
  int	a = 0;
  const char *str = end.c_str();

  while (str[a] && str[a] != ';')
    {
      if (str[a] != ';' && str[a] != ' ')
	throw myException::lexicalException("Erreur de syntaxe après l'instruction", num);
      a++;
    }
}

/*  verifie tous les paramètres ne prenant pas d'arguments */

void	Chipset::checkSimple(std::string &instr, std::string &line)
{
  std::string	tmp = line.substr(0, instr.size());
  int		a = 0;

  (tmp != instr) ? (throw myException::lexicalException("Erreur de syntaxe sur l'instruction", num)) : tmp.clear();
  tmp = line.substr(instr.size(), line.size() - instr.size());
  a = checkComa(tmp, ' ');
  (a == 0) ? throw myException::lexicalException("Erreur de syntaxe après l'instruction", num) : checkEndLine(tmp);
  final.push_back(instr);
}

/* verifie que l'instruction existe, et apelle la verification adéquate des paramètres */

void	Chipset::checkInstruction(std::string &line)
{
  size_t	a = std::string::npos;;
  std::string	inst;

  for (std::map<std::string, int>::const_iterator it = verif.begin(); it != verif.end(); ++it)
    {
      if ((a = line.find(it->first)) != std::string::npos)
	{
	  inst = it->first; break;
	}
    }
  (a == std::string::npos) ? (throw myException::lexicalException("Synxtaxe incorrect", num)) : (a = a);
  if (verif[inst] == 0)
    return (checkSimple(inst, line));
  else
    return(checkComplex(inst, line));
}

void	Chipset::parseList(std::string &line)
{
  int	nb = 0;

  if((nb = this->checkComa(line, '\0')) != 1)
    checkInstruction(line);
}

void Chipset::traverseList()
{
  for (std::list<std::string>::const_iterator it = file.begin(); it != file.end(); ++it)
    {
      std::string tmp = *it;      
      this->parseList(tmp);
      this->num++;
    }
}
