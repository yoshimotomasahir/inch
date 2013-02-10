#include "functions.h"

void writeEPS(const std::vector<Nuclide> &in, inputs *draw)
{
  //-Open the output file to write to
  std::ofstream out_file(draw->outfile.c_str());
  std::vector<Nuclide>::const_iterator nuc_it;

  if (out_file.is_open())
    {
      //-Set up eps header and definitions
      createProlog(draw,out_file);

      //-Set the scale and a border of half a unit. 
      out_file << "u dup scale\n"
	       << "0.5 dup translate" << std::endl;

      //-For positioning and alignment, draw a grid with spacings of 5 units.
      if (draw->grid)
	drawGrid(draw,out_file);

      //-Postscript doesn't support transparency, thus draw shaded
      //-area of the r-process before nuclei and the outline after.
      //-----------------------------
      //- r-process -- shaded path --
      //-----------------------------
      if (draw->r_process)
	drawRprocess(draw,out_file,1);

      std::vector<float> partition_value;
      std::vector<std::string> partition_colour;
      std::vector<bool> draw_partition(12,0);
      float
	key_height=0.5,
	key_scale=0;

      setColours(partition_colour,partition_value,draw);

      drawNuclei(in,partition_colour,partition_value,draw_partition,draw,out_file);

      setKeyScale(draw,key_height,key_scale,draw_partition);

      //-----------------
      //- Magic numbers -
      //-----------------
      if (draw->magic_numbers)
	drawMagicNumbers(draw,out_file);
      else
	std::cout << "\nNot drawing the magic numbers" << std::endl;

      //--------------
      //- Drip lines -
      //--------------
      if (draw->single_drip_lines > 0)
	drawSingleDriplines(in,draw,out_file);
      else
	std::cout << "Drawing neither of the single particle drip lines" << std::endl;

      if (draw->double_drip_lines > 0)
	drawDoubleDriplines(in,draw,out_file);
      else
	std::cout << "Drawing neither of the double particle drip lines" << std::endl;


      //-----------------------------
      //- r-process -- path outline -
      //-----------------------------
      if (draw->r_process)
	drawRprocess(draw,out_file,0);
      else
	std::cout << "Not drawing the r-process path" << std::endl;

      //-------
      //- Key -
      //-------
      if (draw->key)
	drawKey(draw,out_file,key_height,key_scale,partition_colour,draw_partition,partition_value);
      else
	std::cout << "Not drawing the key" << std::endl;

      //Hack - When all nuclei are drawn, key is in top left.
      //Below stops extra space being created on the right.  
      if (draw->section == "a" || (draw->Zmax-draw->Zmin) == 118)
	key_scale=0;

      out_file << "end grestore\n\n"
	       << "%%Trailer\n"
	       << "%%BoundingBox: " << "0 0 " << (int) (draw->Nmax-draw->Nmin+2+14.5*key_scale)*draw->size << " " << (draw->Zmax-draw->Zmin+2)*draw->size
	       << "\n%%EOF" << std::endl;

      out_file.close();
    }
  else
    {
      std::cout << "\nERROR: Couldn't open " << draw->outfile << " to create the chart." << std::endl;
      exit(-1);
    }
}
