#include "include/functions.h"

void drawEPSRprocess(inputs *draw,
		     std::ofstream &out_file,
		     const bool shaded
		     )
{
  //r-process data starts at Z=26.
  //no need to do anything if we aren't displaying above that.
  if (draw->Zmax < 26)
    return;

  if (shaded)
    {
      out_file << "\n%----------------------------\n"
	       << "%- r-process -- shaded path -\n"
	       << "%----------------------------\n"
	       << "gs\n"
	       << "0.9 setgray" << std::endl;
    }
  else
    {
      out_file << "\n%-----------------------------\n"
	       << "%- r-process -- path outline -\n"
	       << "%-----------------------------\n"
	       << "black rgb\n"
	       << "0.1 u div sl" << std::endl;
    }

  std::ifstream rp(draw->r_proc_path.c_str());

  if (rp.is_open())
    {
      bool initial=true;
      int n_rp, z_rp;
      std::string line;
      std::stringstream in;

      if (!shaded)
	std::cout << "Reading "
		  << draw->r_proc_path.substr(draw->r_proc_path.find_last_of("/")+1)
		  << " for the r-process nuclei";

      while (getline(rp,line))
	{
	  if ( !line.compare("") || line.at(0) == '#' )
	    continue;

	  in.clear();
	  in << line;

	  in >> n_rp >> z_rp;

	  if (   z_rp >= draw->Zmin
	      && z_rp <= draw->Zmax
	      && n_rp >= draw->Nmin
	      && n_rp <= draw->Nmax
	      )
	    {
	      out_file << std::setw(3) << n_rp-draw->Nmin << " "
		       << std::setw(3) << z_rp-draw->Zmin << " "
		       << (initial ? "m" : "l") << "\n";

	      initial=false;
	    }
	}
      rp.close();
    }
  else
    {
      std::cout << "***ERROR***: " << draw->r_proc_path
		<< " couldn't be opened to read the r-process path." << std::endl;

      //We have set things up ready to draw,
      //need to tidy up before exiting with error.
      if (shaded)
	out_file << "fill\n"
		 << "gr\n" << std::endl;
      else
	out_file << "st" << std::endl;

      return;
    }

  if (shaded)
    {
      out_file << "fill\n"
	       << "gr\n" << std::endl;
    }
  else
    {
      out_file << "st" << std::endl;

      std::cout << " - done" << std::endl;
    }
}
