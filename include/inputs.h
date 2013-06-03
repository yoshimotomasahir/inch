#ifndef INPUTS_H
#define INPUTS_H

#include <string>

class inputs
{
 public:
  inputs();
  ~inputs();
  bool
    grid,
    magic_numbers,
    write_isotope,
    r_process,
    key,
    own_nuclei,
    AME,
    key_relative;
  
  int
    Zmin,
    Zmax,
    Nmin,
    Nmax,
    size,
    experimental,
    np_rich,
    single_drip_lines,
    double_drip_lines,
    file_type;
  
  float
    curve,
    key_height,
    key_scale,
    chart_height,
    chart_width;
  
  std::string
    path,
    mass_table,
    mass_table_AME,
    mass_table_NUBASE,
    my_nuclei,
    r_proc_path,
    neutron_drip,
    proton_drip,
    two_neutron_drip,
    two_proton_drip,
    choice,
    required,
    section,
    type,
    options,
    outfile,
    FRDM,
    version;
};

#endif
