#pragma once
#include "pch.h"

// FUNCTION FOR CREATING A GEOMETRIC BODY MODEL AND VOLUME TETRAEDRIC MESH
// double &meshStep - mesh step read from inifile, int &numberPoints - amount of points read from inifile
// double &rotateAxeBeginPointX, double &rotateAxeBeginPointY, double &rotateAxeBeginPointZ - coordinates of the starting point of the axis of rotation
// double &rotateAxeEndPointX, double &rotateAxeEndPointY, double &rotateAxeEndPointZ - coordinates of the end point of the axis of rotation
// double *&pointX, double *&pointY, double *&pointZ - arrays of coordinates of points read from inifile
// std::string &volumeMeshFile - volumetric tetrahedral mesh file name read from inifile
bool createModel(double& meshStep, int& numberPoints,
	             double& rotateAxeBeginPointX, double& rotateAxeBeginPointY, double& rotateAxeBeginPointZ,
	             double& rotateAxeEndPointX, double& rotateAxeEndPointY, double& rotateAxeEndPointZ,
	             double*& pointX, double*& pointY, double*& pointZ, std::string& volumeMeshFile);

// MAIN FUNCTION
// const WCHAR* - name inifile with points, const WCHAR* BodySectionName - name of the desired section with points
bool CreateRotationBodyMesh(const WCHAR* IniFileName, const WCHAR* BodySectionName);