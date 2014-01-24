#include	"../headers/Io.hh"
#include	"../headers/myException.hh"

Io::Io(char *file) : _file(file)
{
  this->readInput();
}

Io::~Io()
{

}

void	Io::doDump(std::list<std::string> ml)
{
  for (std::list<std::string>::const_iterator it = ml.begin(); it != ml.end(); ++it)
    std::cout << *it << std::endl;
}

std::list<std::string>	Io::getList() const
{
  return (this->content);
}

void	Io::putFileInList(std::ifstream &file)
{
  if(file)
    {
      std::string	content;
      while(std::getline(file, content))
	this->content.push_back(content);
    }
}

void	Io::putInputInList()
{
  std::string	input_line;
  while(input_line != ";;") 
    {
      getline(std::cin, input_line);
      this->content.push_back(input_line);
    }
  this->content.pop_back();
}

void	Io::readInput() 
{
  std::ifstream fichier(this->_file, std::ios::in);

  if (this->_file == NULL)
    putInputInList();
  else if(fichier)
    putFileInList(fichier);
  else
    throw myException::lexicalException("No such file");
}
  
  
