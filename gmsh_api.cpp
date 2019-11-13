#include "pch.h"
#include <gmsh.h>

// FUNCTION TO WRITE MESH FILES [NOT EXPORTED!]
// std::string volumeMeshFile - mesh file name
bool genarateMeshFile(std::string volumeMeshFile)
{
	std::string ext;
	for (int i = (volumeMeshFile.length() - 1); i >= 0; i--)
	{
		if (volumeMeshFile[i] == '.') break;
		std::stringstream ext_sream;
		ext_sream << volumeMeshFile[i];
		std::string symb = ext_sream.str();
		ext.append(symb);
	}
	if (ext.length()) reverse(ext.begin(), ext.end());

	if (ext == "msh" || "inp" || "key" || "celum" || "cgns" || "diff" || "unv" || "ir3" || "mesh" ||
		"mail" || "m" || "bdf" || "p3d" || "stl" || "wrl" || "vtk" || "dat" || "ply2" || "su2" || "neu")
	{
		gmsh::model::mesh::generate(2);
		gmsh::model::mesh::generate(3);
		gmsh::write(volumeMeshFile);
		std::string str = "Rotation body mesh file: " + volumeMeshFile + " is written." + '\n' + '\n' +
			              "PATH: " + std::filesystem::current_path().string();
		displayMassage(str, L"MeshHelperGMSH");
		return true;
	}
	else
	{
		std::string str = "File: " + volumeMeshFile + " isn't written." + '\n' + '\n' +
			              "FILE ISN'T A MESH FILE THAT GMSH 4.3.1 SUPPORTS!";
		displayMassage(str, L"MeshHelperGMSH : ERROR");
		return false;
	}
}

bool createModel(double& meshStep, int& numberPoints,
	             double& rotateAxeBeginPointX, double& rotateAxeBeginPointY, double& rotateAxeBeginPointZ,
	             double& rotateAxeEndPointX, double& rotateAxeEndPointY, double& rotateAxeEndPointZ,
	             double*& pointX, double*& pointY, double*& pointZ, std::string& volumeMeshFile)
{
	double pi = 3.1415926535;

	gmsh::initialize();
	std::vector<int> pointTag(numberPoints);
	for (int i = 0; i < numberPoints; i++)
	{
		pointTag[i] = i + 1;
		gmsh::model::geo::addPoint(pointX[i], pointY[i], pointZ[i], meshStep, pointTag[i]);
	}
	///////////////////////////////////////////////////////////////////POINT_CHECKING_BEGIN/////////////////////////////////////////////////////////////////////////////////////////////////////
	double determinamt;
	if (numberPoints % 2 == 0)
	{
		for (int i = 0; i < numberPoints; i = i + 2)
		{
			determinamt = (rotateAxeEndPointX - rotateAxeBeginPointX) * (pointY[i] - rotateAxeBeginPointY) * (pointZ[i + 1] - rotateAxeBeginPointZ) +
				          (pointX[i + 1] - rotateAxeBeginPointX) * (rotateAxeEndPointY - rotateAxeBeginPointY) * (pointZ[i] - rotateAxeBeginPointZ) +
				          (pointX[i] - rotateAxeBeginPointX) * (pointY[i + 1] - rotateAxeBeginPointY) * (rotateAxeEndPointZ - rotateAxeBeginPointZ) -
				          (pointX[i + 1] - rotateAxeBeginPointX) * (pointY[i] - rotateAxeBeginPointY) * (rotateAxeEndPointZ - rotateAxeBeginPointZ) -
				          (rotateAxeEndPointX - rotateAxeBeginPointX) * (pointY[i + 1] - rotateAxeBeginPointY) * (pointZ[i] - rotateAxeBeginPointZ) -
				          (pointX[i] - rotateAxeBeginPointX) * (rotateAxeEndPointY - rotateAxeBeginPointY) * (pointZ[i + 1] - rotateAxeBeginPointZ);
			if (determinamt != 0)
			{
				std::string str = "Error! Point " + std::to_string(i + 1) + " doesn't belong to the plane of the axis of rotation!" + '\n' + '\n' +
					              "Singal Place: line 36 [gmshAPI.cpp - function: createModel(...)]";
				displayMassage(str, L"MeshHelperGMSH : ERROR");
				return false;
			}
		}
	}
	else
	{
		for (int i = 0; i < numberPoints - 1; i = i + 2)
		{
			determinamt = (rotateAxeEndPointX - rotateAxeBeginPointX) * (pointY[i] - rotateAxeBeginPointY) * (pointZ[i + 1] - rotateAxeBeginPointZ) +
				          (pointX[i + 1] - rotateAxeBeginPointX) * (rotateAxeEndPointY - rotateAxeBeginPointY) * (pointZ[i] - rotateAxeBeginPointZ) +
				          (pointX[i] - rotateAxeBeginPointX) * (pointY[i + 1] - rotateAxeBeginPointY) * (rotateAxeEndPointZ - rotateAxeBeginPointZ) -
				          (pointX[i + 1] - rotateAxeBeginPointX) * (pointY[i] - rotateAxeBeginPointY) * (rotateAxeEndPointZ - rotateAxeBeginPointZ) -
				          (rotateAxeEndPointX - rotateAxeBeginPointX) * (pointY[i + 1] - rotateAxeBeginPointY) * (pointZ[i] - rotateAxeBeginPointZ) -
				          (pointX[i] - rotateAxeBeginPointX) * (rotateAxeEndPointY - rotateAxeBeginPointY) * (pointZ[i + 1] - rotateAxeBeginPointZ);
			if (determinamt != 0)
			{
				std::string str = "Error! Point " + std::to_string(i + 1) + " doesn't belong to the plane of the axis of rotation!" + '\n' + '\n' +
					              "Singal Place: line 55 [gmshAPI.cpp - function: createModel(...)]";
				displayMassage(str, L"MeshHelperGMSH : ERROR");
				return false;
			}
		}
		determinamt = (rotateAxeEndPointX - rotateAxeBeginPointX) * (pointY[numberPoints - 2] - rotateAxeBeginPointY) * (pointZ[numberPoints - 1] - rotateAxeBeginPointZ) +
			          (pointX[numberPoints - 1] - rotateAxeBeginPointX) * (rotateAxeEndPointY - rotateAxeBeginPointY) * (pointZ[numberPoints - 2] - rotateAxeBeginPointZ) +
			          (pointX[numberPoints - 2] - rotateAxeBeginPointX) * (pointY[numberPoints - 1] - rotateAxeBeginPointY) * (rotateAxeEndPointZ - rotateAxeBeginPointZ) -
			          (pointX[numberPoints - 1] - rotateAxeBeginPointX) * (pointY[numberPoints - 2] - rotateAxeBeginPointY) * (rotateAxeEndPointZ - rotateAxeBeginPointZ) -
		   	          (rotateAxeEndPointX - rotateAxeBeginPointX) * (pointY[numberPoints - 1] - rotateAxeBeginPointY) * (pointZ[numberPoints - 1] - rotateAxeBeginPointZ) -
			          (pointX[numberPoints - 2] - rotateAxeBeginPointX) * (rotateAxeEndPointY - rotateAxeBeginPointY) * (pointZ[numberPoints - 1] - rotateAxeBeginPointZ);
		if (determinamt != 0)
		{
			std::string str = "Error! Point " + std::to_string(numberPoints) + " doesn't belong to the plane of the axis of rotation!" + '\n' + '\n' +
				              "Singal Place: line 69 [gmshAPI.cpp - function: createModel(...)]";
			displayMassage(str, L"MeshHelperGMSH : ERROR");
			return false;
		}
	}
	////////////////////////////////////////////////////////////////////POINT_CHECKING_END/////////////////////////////////////////////////////////////////////////////////////////////////////

	int numberLines = numberPoints - 1;

	double symetryAxisX = rotateAxeEndPointX - rotateAxeBeginPointX,
		   symetryAxisY = rotateAxeEndPointY - rotateAxeBeginPointY;

	int lineNumber = 0;

	for (int i = 0; i < numberPoints - 1; i++)
	{
		if ((pointY[i + 1] - rotateAxeBeginPointY) * symetryAxisX != (pointX[i + 1] - rotateAxeBeginPointX) * symetryAxisY)
		{
			lineNumber++;
			gmsh::model::geo::addLine(pointTag[i], pointTag[i + 1], lineNumber);
		}
		else
		{
			if ((pointY[i] - rotateAxeBeginPointY) * symetryAxisX != (pointX[i] - rotateAxeBeginPointX) * symetryAxisY)
			{
				lineNumber++;
				gmsh::model::geo::addLine(pointTag[i], pointTag[i + 1], lineNumber);
			}
			else
			{
				numberLines--;
			}
		}
	}

	std::vector<std::pair<int, int>> lineTag(numberLines);
	for (int i = 0; i < numberLines; i++)
	{
		lineTag[i].first = 1;
		lineTag[i].second = i + 1;
	}

	/////////////////////////////////////////////////////////////////CREATE_SURFACE_BEGIN////////////////////////////////////////////////////////////////////////////////////////
	std::vector<std::pair<int, int> > si1[100];
	for (int i = 0; i < numberLines; i++) gmsh::model::geo::revolve({ {1, lineTag[i].second} }, 0, 0, 0, 0, 1, 0, pi / 2, si1[i]);
	std::vector<std::pair<int, int> > si2[100];
	for (int i = 0; i < numberLines; i++) gmsh::model::geo::revolve({ {1, si1[i][0].second} }, 0, 0, 0, 0, 1, 0, pi / 2, si2[i]);
	std::vector<std::pair<int, int> > si3[1000];
	for (int i = 0; i < numberLines; i++) gmsh::model::geo::revolve({ {1,si2[i][0].second} }, 0, 0, 0, 0, 1, 0, pi / 2, si3[i]);
	std::vector<std::pair<int, int> > si4[100];
	for (int i = 0; i < numberLines; i++) gmsh::model::geo::revolve({ {1,si3[i][0].second} }, 0, 0, 0, 0, 1, 0, pi / 2, si4[i]);
	std::vector<int> surfaceTag(4 * numberLines);
	for (int i = 0, j = 0; i < numberLines, j < numberLines; i++, j++) surfaceTag[i] = si1[j][1].second;
	for (int i = numberLines, j = 0; i < 2 * numberLines, j < numberLines; i++, j++) surfaceTag[i] = si2[j][1].second;
	for (int i = 2 * numberLines, j = 0; i < 3 * numberLines, j < numberLines; i++, j++) surfaceTag[i] = si3[j][1].second;
	for (int i = 3 * numberLines, j = 0; i < 4 * numberLines, j < numberLines; i++, j++) surfaceTag[i] = si4[j][1].second;

	int surfaceLoopTag = 1;
	gmsh::model::geo::addSurfaceLoop(surfaceTag, surfaceLoopTag);

	/////////////////////////////////////////////////////////////////CREATE_SURFACE_END///////////////////////////////////////////////////////////////////////////////////////////

	int volumeTag = 1;
	gmsh::model::geo::addVolume({ surfaceLoopTag }, volumeTag);
	gmsh::model::geo::synchronize();
	genarateMeshFile(volumeMeshFile);
	return true;
}

bool CreateRotationBodyMesh(const WCHAR* IniFileName, const WCHAR* BodySectionName)
{
	std::wstring iniFileName_wstr(IniFileName);
	std::string iniFileName_str(iniFileName_wstr.begin(), iniFileName_wstr.end());

	std::wstring bodySectionName_wstr(BodySectionName);
	std::string bodySectionName_str(bodySectionName_wstr.begin(), bodySectionName_wstr.end());

	std::string str = "IniFileName: " + iniFileName_str + '\n' +
		              "BodySectionName: " + bodySectionName_str + '\n' + '\n' +
		              "FUNCTION CreateRotationBodyMesh(const WCHAR* IniFileName, const WCHAR* BodySectionName) IS CALLED." + '\n' + '\n' +
		              "Click OK to continue.";
	displayMassage(str, L"MeshHelperGMSH");

	double meshStep;
	std::string volumeMeshFile;
	int numberPoints;
	double rotateAxeBeginPointX, rotateAxeBeginPointY, rotateAxeBeginPointZ;
	double rotateAxeEndPointX, rotateAxeEndPointY, rotateAxeEndPointZ;
	double *pointX, *pointY, *pointZ;

	if (readIniFile(iniFileName_str, bodySectionName_str, meshStep, volumeMeshFile, numberPoints,
		            rotateAxeBeginPointX, rotateAxeBeginPointY, rotateAxeBeginPointZ,
		            rotateAxeEndPointX, rotateAxeEndPointY, rotateAxeEndPointZ,
		            pointX, pointY, pointZ) == false)
	{
		std::string str = "IniFile: " + iniFileName_str + " cantains an error!";
		displayMassage(str, L"MeshHelperGMSH : ERROR");
		return false;
	}
	else
	{
		if (createModel(meshStep, numberPoints,
			            rotateAxeBeginPointX, rotateAxeBeginPointY, rotateAxeBeginPointZ,
			            rotateAxeEndPointX, rotateAxeEndPointY, rotateAxeEndPointZ,
			            pointX, pointY, pointZ, volumeMeshFile) == false)
		{
			std::string str = "File: " + volumeMeshFile + " isn't written." + '\n' + '\n' +
				              "ROTATION BODY MESH FILE ISN'T CREATED!";
			displayMassage(str, L"MeshHelperGMSH");
			return false;
		}
		else
		{
			return true;
		}
	}
}