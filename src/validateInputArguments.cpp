#include "include/functions.h"

bool validateInputArguments(const std::vector<Nuclide> &nuc,
			    inputs *draw,
			    const std::vector<std::string> &arguments
			    )
{
  int numArguments=arguments.size();

  //Ignore arguments after the 5th
  if (numArguments > 5)
    {
      char ignore;

      std::cout << "WARNING: Too many arguments given.\n"
		<< "Ignoring: ";

      for (int i=5; i<numArguments; ++i)
	std::cout << arguments[i] << " ";

      std::cout << "\nContinue ";

      do
	{
	  std::cout << "[y/n]: ";
	  std::cin  >> ignore;

	  if (ignore == 'y')
	    {
	      std::cout << "\nContinuing..." << std::endl;
	    }
	  else if (ignore == 'n')
	    {
	      std::cout << "\nExiting...\n" << std::endl;
	      exit(-1);
	    }
	  else
	    std::cout << "That wasn't y or n. Try again" << std::endl;
	}
      while (ignore != 'n' && ignore !='y');

      numArguments=5;
    }

  //Read option via << -flag file >> so, including the executable, we need
  //an odd number of arguments
  if (numArguments%2 == 1)
    {
      for (int i=1;i<numArguments;++i)
	{
	  if (arguments[i] == "-i")
	    {
	      if ( !validateInputFile(nuc,draw,arguments[i+1]) )
		{
		  std::cout << "ERROR - Bad inputfile." << std::endl;

		  return false;
		}
	    }

	  if (arguments[i] == "-o")
	    {
	      validateOutputFile(draw,arguments[i+1]);
	    }
	}
    }
  else
    {
      std::cout << "\n\n"
		<< "ERROR: An odd number of arguments is not allowed\n" << std::endl;

      return false;
    }

  return true;
}
