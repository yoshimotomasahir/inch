#ifndef NUCLIDE_HPP
#define NUCLIDE_HPP

#include <string>
#include <vector>
#include <cmath>
#include <cstdarg>
#include <algorithm>

#include "extractValue.hpp"

static constexpr int NUBASE_START_A=0;
static constexpr int NUBASE_END_A=3;
static constexpr int NUBASE_START_Z=4;
static constexpr int NUBASE_END_Z=7;
static constexpr int NUBASE_START_STATE=7;
static constexpr int NUBASE_END_STATE=8;
static constexpr int NUBASE_START_ME=18;
static constexpr int NUBASE_END_ME=29;
static constexpr int NUBASE_START_DME=29;
static constexpr int NUBASE_END_DME=38;
static constexpr int NUBASE_START_ISOMER=39;
static constexpr int NUBASE_END_ISOMER=46;
static constexpr int NUBASE_START_DISOMER=48;
static constexpr int NUBASE_END_DISOMER=56;
static constexpr int NUBASE_START_HALFLIFEVALUE=60;
static constexpr int NUBASE_END_HALFLIFEVALUE=69;
static constexpr int NUBASE_START_HALFLIFEUNIT=69;
static constexpr int NUBASE_END_HALFLIFEUNIT=71;
static constexpr int NUBASE_START_SPIN=79;
static constexpr int NUBASE_END_SPIN=93;
//After the 2003 table, the discovery
//year was added, alterting the positions
static constexpr int NUBASE_START_YEAR=106;
static constexpr int NUBASE_END_YEAR=110;
//Let the 03 position be the odd-one-out and thus
//have the slightly awkward name
static constexpr int NUBASE_START_DECAYSTRING_03=106;
static constexpr int NUBASE_START_DECAYSTRING=111;
//The decay string goes to EOL, put here, commented,
//to show that we haven't just forgotten about it.
//static constexpr int NUBASE_END_DECAYSTRING=EOL;

static constexpr int AME_START_A=16;
static constexpr int AME_END_A=19;
static constexpr int AME_START_Z=11;
static constexpr int AME_END_Z=14;
static constexpr int AME_START_ME=29;
static constexpr int AME_END_ME=41;
static constexpr int AME_START_DME=42;
static constexpr int AME_END_DME=53;

static constexpr int AME_HEADER_LENGTH=39;
static constexpr int AME_EXPERIMENTAL_MARKER=52;

class Nuclide
{
public:
  //Constructors
  //default
  explicit Nuclide(std::string line);
  //copy
  Nuclide(const Nuclide&) = default;
  //move
  Nuclide(Nuclide&&) = default;

  //Assignment
  //copy
  Nuclide& operator=(const Nuclide&) = default;
  //move
  Nuclide& operator=(Nuclide&&) = default;

  //Destructors
  ~Nuclide() = default;

  bool own = false;

  int exp = 0;
  int A = 0;
  int Z = 0;
  int N = 0;
  int st = 0;
  int pi = 0;
  int pi_exp = 0;
  int J_exp = 0;
  int J_tent = 0;
  int rich = 0;
  int show = 0;
  int year = 1900;

  double NUBASE_ME = 0.1;
  double NUBASE_dME = 1.0e4;
  double AME_ME = 0.1;
  double AME_dME = 1.0e4;
  double s_n = 0.0;
  double ds_n = 0.0;
  double s_2n = 0.0;
  double ds_2n = 0.0;
  double s_p = 0.0;
  double ds_p = 0.0;
  double s_2p = 0.0;
  double ds_2p = 0.0;
  double dV_pn = 0.0;
  double ddV_pn = 0.0;
  double is_nrg = -999.99;
  double dis_nrg = -999.99;
  double hl = 0.0;
  double J = 0.0;

  std::string symbol;
  std::string decay;
  std::string colour;
  std::string full_data;

  template<typename... Args>
  constexpr double errorQuadrature(Args... args) const;

  constexpr void setOwn(const bool val) noexcept {own = val;}
  constexpr void setN() noexcept {N = A-Z;}

  inline void setA() {extractValue(full_data,NUBASE_START_A,NUBASE_END_A,A);}
  inline void setZ() {extractValue(full_data,NUBASE_START_Z,NUBASE_END_Z,Z);}
  inline void setState() {extractValue(full_data,NUBASE_START_STATE,NUBASE_END_STATE,st);}
  inline void setNubaseMassExcess() {extractValue(full_data,NUBASE_START_ME,NUBASE_END_ME,NUBASE_ME);}
  inline void setNubaseMassExcessError() {extractValue(full_data,NUBASE_START_DME,NUBASE_END_DME,NUBASE_dME);}
  inline void setYear() {extractValue(full_data, NUBASE_START_YEAR, NUBASE_END_YEAR,year);}

  inline void setSymbol(const std::string &_symbol) noexcept {symbol = _symbol;}
  inline void setAMEMassExcess(const std::string &line) {extractValue(line,AME_START_ME,AME_END_ME,AME_ME);}
  inline void setAMEMassExcessError(const std::string &line) {extractValue(line,AME_START_DME,AME_END_DME,AME_dME);}

  void setExperimental();
  constexpr void setExperimental(const int val) noexcept {exp = val;}

  void setSpinParity();
  void setIsomerEnergy();
  void setHalfLife();
  void setSeparationEnergies(std::vector<Nuclide> &nuc);
  void setDecayMode(std::vector<bool> &pnSide, const int table_year);
  void setNeutronOrProtonRich(const std::vector<bool> &pnSide);
};

#endif // NUCLIDE_HPP
