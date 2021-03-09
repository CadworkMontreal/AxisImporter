/*!
 * \file AxisImporter.h
 *
 * \author Cadwork Montreal
 * \date March 2021
 *
 * 
 */

#pragma once

#define CWAPI3D_PLUGIN_NAME L"AxisImporter"
#define CWAPI3D_AUTHOR_NAME L"Cadwork Montreal"
#define CWAPI3D_AUTHOR_EMAIL L"montreal@cadwork.ca"

#include <CwAPI3D/CwAPI3D.h>

CWAPI3D_PLUGIN bool plugin_x64_init(CwAPI3D::ControllerFactory* aFactory);
