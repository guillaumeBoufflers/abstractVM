#include		<sstream>
#include		"../headers/IOperand.hh"
#include		"../headers/Io.hh"
#include		"../headers/Chipset.hh"
#include		"../headers/Cpu.hh"
#include		"../headers/genException.hh"



void	avm(char *file)
{
  try
    {
      Io	IO(file);
      std::list<std::string> listf = IO.getList();
      Chipset chip(listf);
      std::list<std::string> instru = chip.getInstruct();
      Cpu cpu(instru);
    }
  catch (const std::exception & e ) { std::cerr << e.what();}
}

int	main(int ac, char **av)
{
  if (ac != 1 && ac != 2)
    {
    std::cerr << "Usage : ./avm | ./avm file" << std::endl;
    return (0);
    }
  (ac == 2) ? avm(av[1]) : avm(NULL);
}
