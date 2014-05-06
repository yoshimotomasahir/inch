#include "include/functions.h"

#include "extractValue.cpp"

bool validateInputFile(const std::vector<Nuclide> & nuc,
		       inputs *draw,
		       const std::string &inputFilename
		       )
{
  std::ifstream infile(inputFilename.c_str());

  if (infile.is_open())
    {
      std::cout << "Reading " << inputFilename << " for input values {--";

      int lines_read(0);
      std::string line("");

      while (getline(infile,line))
	{
	  /*
	    TODO: The order of these conditions is critical, otherwise causes
	          a seg fault when accessing zeroth element of an empty line.
		  Make this more robust and order independent
	  */
	  //Let lines starting with '#' be comments
	  if ( !line.compare("") || line.at(0) == '#' )
	      continue;


	  if (line.find("section=") != std::string::npos)
	    {
	      draw->section=line.erase(0,line.size()-1);
	      ++lines_read;
	    }
	  else if (line.find("type=") != std::string::npos)
	    {
	      draw->type=line.erase(0,line.size()-1);

	      if (draw->type == "a")
		{
		  draw->experimental=1;
		  ++lines_read;
		}
	      else if (draw->type == "b")
		{
		  draw->experimental=0;
		  ++lines_read;
		}
	      else if (draw->type == "c")
		{
		  draw->experimental=2;
		  ++lines_read;
		}
	      else
		std::cout << "\nERROR: " << draw->type << " is not a valid choice for 'type'" << std::endl;
	    }
	  else if (line.find("choice=") != std::string::npos)
	    {
	      draw->choice=line.erase(0,line.size()-1);
	      ++lines_read;
	    }
	  else if (line.find("required=") != std::string::npos)
	    {
	      draw->required=line.erase(0,line.size()-1);
	      ++lines_read;
	    }
	  else if (line.find("Zmin=") != std::string::npos)
	    {
	      extractValue(line.erase(0,line.find('=')+1),0,line.length(),draw->Zmin);

	      if ((!atoi(line.c_str()) && line!="0") || (draw->Zmin<0 || draw->Zmin>118))
		{
		  std::cout << "\nERROR: " << line << " is not a valid choice for 'Zmin'" << std::endl;
		  return false;
		}
	      else
		++lines_read;
	    }
	  else if (line.find("Zmax=") != std::string::npos)
	    {
	      extractValue(line.erase(0,line.find('=')+1),0,line.length(),draw->Zmax);

	      if ((!atoi(line.c_str()) && line!="0") || (draw->Zmax<0 || draw->Zmax>118))
		{
		  std::cout << "\nERROR: " << line << " is not a valid choice for 'Zmax'" << std::endl;
		  return false;
		}
	      else
		++lines_read;
	    }
	  else if (line.find("Nmin=") != std::string::npos)
	    {
	      extractValue(line.erase(0,line.find('=')+1),0,line.length(),draw->Nmin);

	      if ((!atoi(line.c_str()) && line!="0") || (draw->Nmin<0 || draw->Nmin>176))
		{
		  std::cout << "\nERROR: " << line << " is not a valid choice for 'Nmin'" << std::endl;
		  return false;
		}
	      else
		++lines_read;
	    }
	  else if (line.find("Nmax=") != std::string::npos)
	    {
	      extractValue(line.erase(0,line.find('=')+1),0,line.length(),draw->Nmax);

	      if ((!atoi(line.c_str()) && line!="0") || (draw->Nmax<0 || draw->Nmax>176))
		{
		  std::cout << "\nERROR: " << line << " is not a valid choice for 'Nmax'" << std::endl;
		  return false;
		}
	      else
		++lines_read;
	    }
	  else
	    {
	      std::cout << "\nWARNING: " << line << " is not a valid input line. Ignoring." << std::endl;
	    }
	}
      infile.close();

      if (lines_read < 3)
	{
	  std::cout << "Not enough inputs have been read from the file." << std::endl;
	  return false;
	}

      if (draw->section == "a")
	{
	  if (draw->Zmin != 200 && draw->Zmax != 0)
	    {
	      std::cout << "\n**WARNING**\nThe option file contains a Z range but specifies that all nuclei should be drawn.\n"
			<< "The input range will be ignored, set section=b to select a range in Z.\n"
			<< "***********\n" << std::endl;
	    }

	  draw->Zmin=0;
	  draw->Zmax=118;
	  draw->Nmin=0;
	  draw->Nmax=176;
	}
      else if (draw->section == "b")
	{
	  if (draw->required == "a")
	    {
	      setNeutronLimits(nuc,draw);
	    }
	  else if (draw->required != "b")
	    {
	      std::cout << "\nERROR: " << draw->required << " is not a valid option for the 'required' field.\n"
			<< "       Ignoring input file.\n" << std::endl;
	      return false;
	    }

	  if (draw->Zmin > draw->Zmax)
	    {
	      std::cout << "\nERROR: Zmax(" << draw->Zmax << ") cannot be less than Zmin(" << draw->Zmin<< ")\n"
			<< "       Ignoring input file.\n" << std::endl;
	      return false;
	    }

	  if (draw->Nmin > draw->Nmax)
	    {
	      std::cout << "\nERROR: Nmax(" << draw->Nmax << ") cannot be less than Nmin(" << draw->Nmin<< ")\n"
			<< "       Ignoring input file.\n" << std::endl;
	      return false;
	    }
	}
      else
	{
	  std::cout << "\nERROR: " << draw->section << " is not a valid option for the 'section' field.\n"
		    << "       Ignoring input file.\n" << std::endl;
	  return false;
	}

      if (draw->type != "a" && draw->type != "b" && draw->type != "c")
	{
	  std::cout << "\nERROR: " << draw->type << " is not a valid option for the 'type' field.\n"
		    << "       Ignoring input file.\n" << std::endl;
	  return false;
	}

      if (draw->choice != "a" && draw->choice != "b" && draw->choice != "c" && draw->choice != "d" && draw->choice != "e")
	{
	  std::cout << "\nERROR: " << draw->choice << " is not a valid option for the 'choice' field.\n"
		    << "       Ignoring input file.\n" << std::endl;
	  return false;
	}

      std::cout << "--} done\n"
		<< "Read values:\n"
		<< "section: " << draw->section  << "\n";

      if (draw->section == "b")
	{
	  std::cout << "Zmin: "     << draw->Zmin << "\n"
		    << "Zmax: "     << draw->Zmax << "\n"
		    << "required: " << draw->required << "\n"
		    << "Nmin: "     << draw->Nmin << "\n"
		    << "Nmax: "     << draw->Nmax << "\n";
	}

      std::cout << "type: " << draw->type << "\n"
		<< "choice: " << draw->choice << std::endl;
    }
  else
    {
      std::cout << "\n\nERROR: " << inputFilename << " couldn't be opened, does it exist?\n" << std::endl;
      return false;
    }

  return true;
}
