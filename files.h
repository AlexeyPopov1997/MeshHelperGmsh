#pragma once
#include "pch.h"

// FUNCTIONS FOR DISPLAYING MESSAGES ON THE SCREEN 
// const std::string &string - name of the line to be displayed,
// const std::string &signal - type of message
void displayMassage(const std::string& string, const wchar_t* signal);

// READ FUNCTION INIFILE
// const std::string &fileName - name of the ini-file, const std::string &sectionName - name of the desired section, 
// double &meshStep - mesh step read from inifile,
// std::string &volumeMeshFile - mesh file name read from inifile,
// int &numberPoints - the number of points read from the inifile,
// double &rotateAxeBeginPointX, double &rotateAxeBeginPointY, double &rotateAxeBeginPointZ - coordinates of the starting point of the axis of rotation,
// double &rotateAxeEndPointX, double &rotateAxeEndPointY, double &rotateAxeEndPointZ - coordinates of the end point of the axis of rotation,
// double *&pointX, double *&pointY, double *&pointZ - arrays of coordinates of points read from inifile
bool readIniFile(const std::string& fileName, const std::string& sectionName, double& MeshStep, std::string& VolumeMeshFile, int& NumberPoints,
	             double& RotateAxeBeginPointX, double& RotateAxeBeginPointY, double& RotateAxeBeginPointZ,
	             double& RotateAxeEndPointX, double& RotateAxeEndPointY, double& RotateAxeEndPointZ,
	             double*& PointX, double*& PointY, double*& PointZ);