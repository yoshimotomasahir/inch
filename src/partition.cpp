#include "partition.hpp"
#include "converter.hpp"

#include <iostream>

void Partition::clearData()
{
  values.clear();
  values.shrink_to_fit();
}

void Partition::setDefaultColours()
{
  clearData();

  if ( scheme == "a" )
    {
      setDefaultMassExcessColours();
    }
  else if ( scheme == "b" )
    {
      setDefaultRelativeErrorColours();
    }
  else if ( scheme == "c" )
    {
      setDefaultDecayColours();
    }
  else if ( scheme == "d" )
    {
      setDefaultHalfLifeColours();
    }
  else if ( scheme == "e" )
    {
      setDefaultIsomerEnergyColours();
    }
}

void Partition::setDefaultMassExcessColours()
{
  /// Two separate colours for stable isotopes
  values.emplace_back(section{"black", 3.0, false});
  values.emplace_back(section{"magenta", 3.0, false});
  ///
  values.emplace_back(section{"blue", 3.0, false});
  values.emplace_back(section{"cyan", 10.0, false});
  values.emplace_back(section{"green", 20.0, false});
  values.emplace_back(section{"yellow", 50.0, false});
  values.emplace_back(section{"orange", 100.0, false});
  values.emplace_back(section{"red", std::numeric_limits<double>::max(), false});
}

void Partition::setDefaultRelativeErrorColours()
{
  values.emplace_back(section("black", 2.0e-05, false));
  values.emplace_back(section("blue", 1.0e-04, false));
  values.emplace_back(section("green", 5.0e-04, false));
  values.emplace_back(section("yellow", 1.0e-03, false));
  values.emplace_back(section("orange", 5.0e-03, false));
  values.emplace_back(section("red", 1000.0, false));
}

void Partition::setDefaultDecayColours()
{
  //colour.emplace_back("black");
  //colour.emplace_back("yellow");
  //colour.emplace_back("blue");
  //colour.emplace_back("red");
  //colour.emplace_back("magenta");
  //colour.emplace_back("cyan");
  //colour.emplace_back("darkgreen");
  //colour.emplace_back("navyblue");
  //colour.emplace_back("purple");
  //colour.emplace_back("green");
  //colour.emplace_back("orange");

  values.emplace_back(section("black", 1.0, false));
  values.emplace_back(section("yellow", 1.0, false));
  values.emplace_back(section("blue", 1.0, false));
  values.emplace_back(section("red", 1.0, false));
  values.emplace_back(section("magenta", 1.0, false));
  values.emplace_back(section("cyan", 1.0, false));
  values.emplace_back(section("darkgreen", 1.0, false));
  values.emplace_back(section("navyblue", 1.0, false));
  values.emplace_back(section("purple", 1.0, false));
  values.emplace_back(section("green", 1.0, false));
  values.emplace_back(section("orange", 1.0, false));
}

void Partition::setDefaultHalfLifeColours()
{
  /// Use units of seconds
  values.emplace_back(section("red", 0.1, false));
  values.emplace_back(section("orange", 3.0, false));
  values.emplace_back(section("yellow", 2.0*static_cast<double>(Converter::TimeInSeconds::minutes), false));
  values.emplace_back(section("green", 1.0*static_cast<double>(Converter::TimeInSeconds::hours), false));
  values.emplace_back(section("cyan", 1.0*static_cast<double>(Converter::TimeInSeconds::days), false));
  values.emplace_back(section("blue", 1.0*static_cast<double>(Converter::TimeInSeconds::years), false));
  values.emplace_back(section("magenta", 1.0e9*static_cast<double>(Converter::TimeInSeconds::years), false));
  values.emplace_back(section{"black", std::numeric_limits<double>::max(), false});
}


void Partition::setDefaultIsomerEnergyColours()
{
  //value.emplace_back(20.0);
  //value.emplace_back(50.0);
  //value.emplace_back(100.0);
  //value.emplace_back(500.0);
  //value.emplace_back(1000.0);
  //
  //colour.emplace_back("red");
  //colour.emplace_back("orange");
  //colour.emplace_back("yellow");
  //colour.emplace_back("green");
  //colour.emplace_back("blue");
  //colour.emplace_back("magenta");
  ///// For an empty square i.e. no isomer
  ///// This should always be last.
  //colour.emplace_back("white");

  values.emplace_back(section("red", 20.0, false));
  values.emplace_back(section("orange", 50.0, false));
  values.emplace_back(section("yellow", 100.0, false));
  values.emplace_back(section("green", 500.0, false));
  values.emplace_back(section("blue", 1000.0, false));
  values.emplace_back(section{"magenta", std::numeric_limits<double>::max(), false});
  /// For an empty square i.e. no isomer
  /// This should always be last.
  values.emplace_back(section("white", 1.0, false));
}


void Partition::setUserColours(const std::vector<std::string>& _colours, const std::vector<double>& _values)
{
  clearData();

  if ( scheme == "a" )
    {
      setUserMassExcessColours(_colours, _values);
    }
  else if ( scheme == "b" )
    {
      setUserRelativeErrorColours(_colours, _values);
    }
  else if ( scheme == "c" )
    {
      setUserDecayColours(_colours, _values);
    }
  else if ( scheme == "d" )
    {
      setUserHalfLifeColours(_colours, _values);
    }
  else if ( scheme == "e" )
    {
      setUserIsomerEnergyColours(_colours, _values);
    }
}

void Partition::setUserMassExcessColours(const std::vector<std::string>& /*_colours*/, const std::vector<double>& /*_values*/)
{
}

void Partition::setUserRelativeErrorColours(const std::vector<std::string>& /*_colours*/, const std::vector<double>& /*_values*/)
{
}

void Partition::setUserDecayColours(const std::vector<std::string>& /*_colours*/, const std::vector<double>& /*_values*/)
{
}

void Partition::setUserHalfLifeColours(const std::vector<std::string>& /*_colours*/, const std::vector<double>& /*_values*/)
{
}

void Partition::setUserIsomerEnergyColours(const std::vector<std::string>& /*_colours*/, const std::vector<double>& /*_values*/)
{
}

void Partition::setAutoColours(std::vector<Nuclide> theTable, const int parts /*=PARTS*/)
{
  clearData();

  if ( scheme == "a" )
    {
      sort(std::begin(theTable), std::end(theTable),
           []( const auto& lhs, const auto& rhs )
           {
             return lhs.NUBASE_ME < rhs.NUBASE_ME;
           }
        );

      setAutoMassExcessColours(theTable, parts);
    }
  else if ( scheme == "b" )
    {
      sort(std::begin(theTable), std::end(theTable),
           []( const auto& lhs, const auto& rhs )
           {
             return lhs.NUBASE_dME < rhs.NUBASE_dME;
           }
           );

      setAutoRelativeErrorColours(theTable, parts);
    }
  /* Not implemented, see header file for reason
  else if ( scheme == "c" )
    {
      setAutoDecayColours(theTable, parts);
    }
  */
  else if ( scheme == "d" )
    {
      sort(std::begin(theTable), std::end(theTable),
           []( const auto& lhs, const auto& rhs )
           {
             return lhs.hl < rhs.hl;
           }
           );

      setAutoHalfLifeColours(theTable, parts);
    }
  else if ( scheme == "e" )
    {
      sort(std::begin(theTable), std::end(theTable),
           []( const auto& lhs, const auto& rhs )
           {
             return lhs.is_nrg < rhs.is_nrg;
           }
        );

      setAutoIsomerEnergyColours(theTable, parts);
    }
}

void Partition::setAutoMassExcessColours(std::vector<Nuclide> theTable, const int parts /*=PARTS*/)
{
  std::cout << parts << " | " << theTable.front().NUBASE_ME << " | " << theTable.back().NUBASE_ME << std::endl;
}

void Partition::setAutoRelativeErrorColours(std::vector<Nuclide> theTable, const int parts /*=PARTS*/)
{
  std::cout << parts << " | " <<  theTable.front().NUBASE_dME << " | " << theTable.back().NUBASE_dME << std::endl;
}

void Partition::setAutoHalfLifeColours(std::vector<Nuclide> theTable, const int parts /*=PARTS*/)
{
  std::cout << parts << " | " <<  theTable.front().hl << " | " << theTable.back().hl << std::endl;
}

void Partition::setAutoIsomerEnergyColours(std::vector<Nuclide> theTable, const int parts /*=PARTS*/)
{
  std::cout << parts << " | " <<  theTable.front().is_nrg << " | " << theTable.back().is_nrg << std::endl;
}

/*
void Partition::resetSort(std::vector<Nuclide> &theTable)
{
  sort(std::begin(theTable), std::end(theTable),
       []( const auto& lhs, const auto& rhs )
       {
         return lhs.A < rhs.A;
       }
       );
}
*/
