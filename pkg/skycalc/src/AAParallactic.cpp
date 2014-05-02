/*
Module : AAPARALLACTIC.CPP
Purpose: Implementation for the algorithms which calculate various celestial globe angles
Created: PJN / 29-12-2003
History: None

Copyright (c) 2003 - 2013 by PJ Naughter (Web: www.naughter.com, Email: pjna@naughter.com)

All rights reserved.

Copyright / Usage Details:

You are allowed to include the source code in any product (commercial, shareware, freeware or otherwise) 
when your product is released in binary form. You are allowed to modify the source code in any way you want 
except you cannot modify the copyright details at the top of each module. If you want to distribute source 
code with your application, then you are only allowed to distribute versions released by the author. This is 
to maintain a single distribution point for the source code. 

*/


////////////////////// Includes ///////////////////////////////////////////////

#include "stdafx.h"
#include "AAParallactic.h"
#include "AACoordinateTransformation.h"
#include <cmath>
#include <Rcpp.h>
using namespace Rcpp;
using namespace std;


////////////////////// Implementation /////////////////////////////////////////

double CAAParallactic::ParallacticAngle(double HourAngle, double Latitude, double delta)
{
  HourAngle = CAACoordinateTransformation::HoursToRadians(HourAngle);
  Latitude = CAACoordinateTransformation::DegreesToRadians(Latitude);
  delta = CAACoordinateTransformation::DegreesToRadians(delta);

  return CAACoordinateTransformation::RadiansToDegrees(atan2(sin(HourAngle), tan(Latitude)*cos(delta) - sin(delta)*cos(HourAngle)));
}

double CAAParallactic::EclipticLongitudeOnHorizon(double LocalSiderealTime, double ObliquityOfEcliptic, double Latitude)
{
  LocalSiderealTime = CAACoordinateTransformation::HoursToRadians(LocalSiderealTime);
  Latitude = CAACoordinateTransformation::DegreesToRadians(Latitude);
  ObliquityOfEcliptic = CAACoordinateTransformation::DegreesToRadians(ObliquityOfEcliptic);

  double value = CAACoordinateTransformation::RadiansToDegrees(atan2(-cos(LocalSiderealTime), sin(ObliquityOfEcliptic)*tan(Latitude) + cos(ObliquityOfEcliptic)*sin(LocalSiderealTime)));
  return CAACoordinateTransformation::MapTo0To360Range(value);
}

double CAAParallactic::AngleBetweenEclipticAndHorizon(double LocalSiderealTime, double ObliquityOfEcliptic, double Latitude)
{
  LocalSiderealTime = CAACoordinateTransformation::HoursToRadians(LocalSiderealTime);
  Latitude = CAACoordinateTransformation::DegreesToRadians(Latitude);
  ObliquityOfEcliptic = CAACoordinateTransformation::DegreesToRadians(ObliquityOfEcliptic);

  double value = CAACoordinateTransformation::RadiansToDegrees(acos(cos(ObliquityOfEcliptic)*sin(Latitude) - sin(ObliquityOfEcliptic)*cos(Latitude)*sin(LocalSiderealTime)));
  return CAACoordinateTransformation::MapTo0To360Range(value);
}

double CAAParallactic::AngleBetweenNorthCelestialPoleAndNorthPoleOfEcliptic(double Lambda, double Beta, double ObliquityOfEcliptic)
{
  Lambda = CAACoordinateTransformation::DegreesToRadians(Lambda);
  Beta = CAACoordinateTransformation::DegreesToRadians(Beta);
  ObliquityOfEcliptic = CAACoordinateTransformation::DegreesToRadians(ObliquityOfEcliptic);

  double value = CAACoordinateTransformation::RadiansToDegrees(atan2(cos(Lambda)*tan(ObliquityOfEcliptic), sin(Beta)*sin(Lambda)*tan(ObliquityOfEcliptic) - cos(Beta)));
  return CAACoordinateTransformation::MapTo0To360Range(value);
}

////////////////////////////////////// ##############################################################
////////////////////////////////////// ##############################################################
////////////////////////////////////// ##############################################################
////////////////////////////////////// ##############################################################
////////////////////////////////////// ##############################################################

RcppExport SEXP CAAParallactic_ParallacticAngle(SEXP HourAngle_, SEXP Latitude_, SEXP delta_)
{ 
  double HourAngle = as<double>(HourAngle_); 
  double Latitude = as<double>(Latitude_);
  double delta = as<double>(delta_);
  HourAngle = CAACoordinateTransformation::HoursToRadians(HourAngle);
  Latitude = CAACoordinateTransformation::DegreesToRadians(Latitude);
  delta = CAACoordinateTransformation::DegreesToRadians(delta);

  return wrap(CAACoordinateTransformation::RadiansToDegrees(atan2(sin(HourAngle), tan(Latitude)*cos(delta) - sin(delta)*cos(HourAngle))));
}

RcppExport SEXP CAAParallactic_EclipticLongitudeOnHorizon(SEXP LocalSiderealTime_, SEXP ObliquityOfEcliptic_, SEXP Latitude_)
{  
   double LocalSiderealTime = as<double>(LocalSiderealTime_); 
   double ObliquityOfEcliptic = as<double>(ObliquityOfEcliptic_); 
   double Latitude = as<double>(Latitude_); 
   
  LocalSiderealTime = CAACoordinateTransformation::HoursToRadians(LocalSiderealTime);
  Latitude = CAACoordinateTransformation::DegreesToRadians(Latitude);
  ObliquityOfEcliptic = CAACoordinateTransformation::DegreesToRadians(ObliquityOfEcliptic);

  double value = CAACoordinateTransformation::RadiansToDegrees(atan2(-cos(LocalSiderealTime), sin(ObliquityOfEcliptic)*tan(Latitude) + cos(ObliquityOfEcliptic)*sin(LocalSiderealTime)));
  return wrap(CAACoordinateTransformation::MapTo0To360Range(value));
}

RcppExport SEXP CAAParallactic_AngleBetweenEclipticAndHorizon(SEXP LocalSiderealTime_, SEXP ObliquityOfEcliptic_, SEXP Latitude_)
{
   double LocalSiderealTime = as<double>(LocalSiderealTime_); 
   double ObliquityOfEcliptic = as<double>(ObliquityOfEcliptic_); 
   double Latitude = as<double>(Latitude_); 
   
  LocalSiderealTime = CAACoordinateTransformation::HoursToRadians(LocalSiderealTime);
  Latitude = CAACoordinateTransformation::DegreesToRadians(Latitude);
  ObliquityOfEcliptic = CAACoordinateTransformation::DegreesToRadians(ObliquityOfEcliptic);

  double value = CAACoordinateTransformation::RadiansToDegrees(acos(cos(ObliquityOfEcliptic)*sin(Latitude) - sin(ObliquityOfEcliptic)*cos(Latitude)*sin(LocalSiderealTime)));
  return wrap(CAACoordinateTransformation::MapTo0To360Range(value));
}

RcppExport SEXP CAAParallactic_AngleBetweenNorthCelestialPoleAndNorthPoleOfEcliptic(SEXP Lambda_, SEXP Beta_, SEXP ObliquityOfEcliptic_)
{ 
  double Lambda = as<double>(Lambda_); 
  double Beta = as<double>(Beta_); 
  double ObliquityOfEcliptic = as<double>(ObliquityOfEcliptic_); 
  
  Lambda = CAACoordinateTransformation::DegreesToRadians(Lambda);
  Beta = CAACoordinateTransformation::DegreesToRadians(Beta);
  ObliquityOfEcliptic = CAACoordinateTransformation::DegreesToRadians(ObliquityOfEcliptic);

  double value = CAACoordinateTransformation::RadiansToDegrees(atan2(cos(Lambda)*tan(ObliquityOfEcliptic), sin(Beta)*sin(Lambda)*tan(ObliquityOfEcliptic) - cos(Beta)));
  return wrap(CAACoordinateTransformation::MapTo0To360Range(value));
}
