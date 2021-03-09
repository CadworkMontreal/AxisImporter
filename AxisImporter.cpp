/*!
 * \file AxisImporter.cpp
 *
 * \author Cadwork Montreal
 * \date March 2021
 *
 * 
 */

// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "AxisImporter.h"

#include <csv2/reader.hpp>
using namespace csv2;

//************************************
// Method:    plugin_x64_init
// FullName:  plugin_x64_init
// Access:    public
// Returns:   bool
// Qualifier:
// Parameter: CwAPI3D::ControllerFactory * aFactory
//************************************
bool plugin_x64_init(CwAPI3D::ControllerFactory* aFactory)
{
  auto lSelectedCSVFileIString{aFactory->getUtilityController()->getUserFileFromDialog(L"CSV Files (*.csv)")};
  std::wstring lSelectedCSVFile{lSelectedCSVFileIString->data()};

  auto lImportedElements{aFactory->createEmptyElementIDList()};

  aFactory->getUtilityController()->disableAutoDisplayRefresh();

  if (Reader<delimiter<','>, quote_character<'"'>, first_row_is_header<true>, trim_policy::trim_whitespace> lReader; lReader.mmap(lSelectedCSVFile))
  {
    for (const auto& lRow : lReader)
    {
      std::wstring lID;

      double lX1{0.};
      double lY1{0.};
      double lZ1{0.};

      double lX2{0.};
      double lY2{0.};
      double lZ2{0.};

      std::wstring lName;

      uint8_t lCellCount{0};

      for (const auto& lCell : lRow)
      {
        std::wstring lTemp;

        switch (lCellCount)
        {
          case 0:
            lCell.read_value(lID);
            break;
          case 1:
            lCell.read_value(lTemp);
            lX1 = std::stod(lTemp);
            break;
          case 2:
            lCell.read_value(lTemp);
            lY1 = std::stod(lTemp);
            break;
          case 3:
            lCell.read_value(lTemp);
            lZ1 = std::stod(lTemp);
            break;
          case 4:
            lCell.read_value(lTemp);
            lX2 = std::stod(lTemp);
            break;
          case 5:
            lCell.read_value(lTemp);
            lY2 = std::stod(lTemp);
            break;
          case 6:
            lCell.read_value(lTemp);
            lZ2 = std::stod(lTemp);
            break;
          case 7:
            lCell.read_value(lTemp);
            break;
          default:
            break;
        }

        lCellCount++;
      }

      auto lNewElement{aFactory->getElementController()->createDrillingPoints(1., CwAPI3D::vector3D{lX1, lY1, lZ1}, CwAPI3D::vector3D{lX2, lY2, lZ2})};
      auto lNewElementSingleList{aFactory->createElementIDListFromElement(lNewElement)};
      aFactory->getAttributeController()->setName(lNewElementSingleList, lName.c_str());
      aFactory->getAttributeController()->setComment(lNewElementSingleList, lID.c_str());
      lImportedElements->append(lNewElement);
    }
  }

  aFactory->getUtilityController()->enableAutoDisplayRefresh();
  aFactory->getElementController()->recreateElements(lImportedElements);
  aFactory->getVisualizationController()->refresh();

  std::wstring lUserMessage{std::to_wstring(lImportedElements->count()) + L" element(s) imported..."};
  aFactory->getUtilityController()->printError(lUserMessage.c_str());

  return true;
}
