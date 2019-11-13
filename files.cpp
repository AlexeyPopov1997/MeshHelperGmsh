#include "pch.h"

// GLOBAL DEBUG FLAG
bool debugging = false;

// FUNCTION FOR CONVERTING A STRING TYPE TO WCHAR [NOT EXPORTED!]
wchar_t* strToWstr(const std::string& str)
{
	const int maxSize = 1024 * 1024;
	static wchar_t buff[maxSize];
	int nSize = ::MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<int>(str.length() + 1), NULL, NULL);
	wchar_t* tBuff = buff;
	if (nSize > maxSize)
	{
		tBuff = new wchar_t[nSize];
	}
	::MultiByteToWideChar(CP_UTF8, 0, str.c_str(), static_cast<int>(str.length() + 1), buff, nSize);
	wchar_t* result(tBuff);
	if (tBuff != buff) delete[] tBuff;
	return result;
}

// INTERNAL PROCEDURE FOR RECEIVING THE COORDINATES OF THEIR INI FILE [NOT EXPORTED!]
// [REQUIRED FOR CORRECT WORK readIniFile (...)!]
void getCoordinates(const std::string& stringOfCordinates, double& pointX, double& pointY, double& pointZ)
{
	std::string sentence = stringOfCordinates;
	std::istringstream iss(sentence);
	std::vector<std::string> tokens;
	std::copy(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>(), std::back_inserter<std::vector<std::string> >(tokens));
	pointX = std::stod(tokens[0]);
	pointY = std::stod(tokens[1]);
	pointZ = std::stod(tokens[2]);
}

void displayMassage(const std::string& string, const wchar_t* signal)
{
	HWND hWnd = GetForegroundWindow();
	ShowWindow(hWnd, SW_HIDE);
	if (MessageBox(hWnd, strToWstr(string), signal, MB_OKCANCEL) == 1) ShowWindow(hWnd, SW_SHOW);
}

bool readIniFile(const std::string& fileName, const std::string& sectionName, double& meshStep, std::string& volumeMeshFile, int& numberPoints,
	             double& rotateAxeBeginPointX, double& rotateAxeBeginPointY, double& rotateAxeBeginPointZ,
	             double& rotateAxeEndPointX, double& rotateAxeEndPointY, double& rotateAxeEndPointZ,
	             double*& pointX, double*& pointY, double*& pointZ)
{
	CIniFile IniFile(fileName);
	if (IniFile.ReadFile() == 0)
	{
		std::string str = "IniFile: " + fileName + " isn't read!" + '\n' +
			              "Path: " + std::filesystem::current_path().string() + '\n';
		displayMassage(str, L"MeshHelperGMSH : ERROR");
		return false;
	}
	else
	{
		/////////////////////////////////////////////////////////////////////////DEBUGGING//////////////////////////////////////////////////////////////////////////
		if (debugging)
		{
			std::string str = "IniFile: " + fileName + " is read.\n" + '\n' +
				              "Singal Place: line 64 [files.cpp - function: readIniFile(...)]";
			displayMassage(str, L"MeshHelperGMSH : DEBUG MESSAGE");
		}
		/////////////////////////////////////////////////////////////////////////DEBUGGING//////////////////////////////////////////////////////////////////////////

		std::string contourNodesSection = IniFile.GetValue(sectionName, "ContourNodesSection");
		if (contourNodesSection == "")
		{
			std::string str = "IniFile: " + fileName + '\n' +
				              "Section Name: " + sectionName + '\n' + '\n' +
				              "KEY VALUE \"ContourNodesSection\": " + contourNodesSection + " IS FAILED!" + '\n' + '\n' +
				              "CHECK THE KEY VALUE \"ContourNodesSection\" !";
			displayMassage(str, L"MeshHelperGMSH : ERROR");
			return false;
		}

		/////////////////////////////////////////////////////////////////////////DEBUGGING//////////////////////////////////////////////////////////////////////////
		if (debugging)
		{
			std::string str = "IniFile: " + fileName + '\n' +
				              "Section Name: " + sectionName + '\n' + '\n' +
				              "KEY VALUE \"ContourNodesSection\": " + contourNodesSection + '\n' + '\n' +
				              "CHECK THE VALUE FOR EXTRA SPACES AND TYPOS, AND ALSO CHECK UPPER/LOWER CASE!" + '\n' + '\n' +
				              "Singal Place: line 87 [files.cpp - function: readIniFile(...)]";
			displayMassage(str, L"MeshHelperGMSH : DEBUG MESSAGE");
		}
		/////////////////////////////////////////////////////////////////////////DEBUGGING//////////////////////////////////////////////////////////////////////////

		string rotateAxeBeginPoint = IniFile.GetValue(sectionName, "RotateAxeBeginPoint");
		if (rotateAxeBeginPoint == "")
		{
			std::string str = "IniFile: " + fileName + '\n' +
				              "Section Name: " + sectionName + '\n' + '\n' +
				              "KEY VALUE \"RotateAxeBeginPoint\": " + rotateAxeBeginPoint + " IS FAILED!" + '\n' + '\n' +
				              "CHECK THE KEY VALUE \"RotateAxeBeginPoint\" !";
			displayMassage(str, L"MeshHelperGMSH : ERROR");
			return false;
		}

		/////////////////////////////////////////////////////////////////////////DEBUGGING//////////////////////////////////////////////////////////////////////////
		if (debugging)
		{
			std::string str = "IniFile: " + fileName + '\n' +
				              "Section Name: " + sectionName + '\n' + '\n' +
				              "KEY VALUE \"RotateAxeBeginPoint\": " + rotateAxeBeginPoint + '\n' + '\n' +
				              "CHECK THE VALUE FOR EXTRA SPACES AND TYPOS, AND ALSO CHECK UPPER/LOWER CASE!" + '\n' + '\n' +
				              "Singal Place: line 110 [files.cpp - function: readIniFile(...)]";
			displayMassage(str, L"MeshHelperGMSH : DEBUG MESSAGE");
		}
		/////////////////////////////////////////////////////////////////////////DEBUGGING//////////////////////////////////////////////////////////////////////////

		getCoordinates(rotateAxeBeginPoint, rotateAxeBeginPointX, rotateAxeBeginPointY, rotateAxeBeginPointZ);
		std::string rotateAxeEndPoint = IniFile.GetValue(sectionName, "RotateAxeEndPoint");
		if (rotateAxeEndPoint == "")
		{
			std::string str = "IniFile: " + fileName + '\n' +
				              "Section Name: " + sectionName + '\n' + '\n' +
			 	              "KEY VALUE \"RotateAxeEndPoint\": " + rotateAxeEndPoint + " IS FAILED!" + '\n' + '\n' +
				              "CHECK THE KEY VALUE \"RotateAxeEndPoint\" !";
			displayMassage(str, L"MeshHelperGMSH : ERROR");
			return false;
		}

		/////////////////////////////////////////////////////////////////////////DEBUGGING//////////////////////////////////////////////////////////////////////////
		if (debugging)
		{
			std::string str = "IniFile: " + fileName + '\n' +
				              "Section Name: " + sectionName + '\n' + '\n' +
				              "KEY VALUE \"RotateAxeEndPoint\": " + rotateAxeEndPoint + '\n' + '\n' +
				              "CHECK THE VALUE FOR EXTRA SPACES AND TYPOS, AND ALSO CHECK UPPER/LOWER CASE!" + '\n' + '\n' +
				              "Singal Place: line 134 [files.cpp - function: readIniFile(...)]";
			displayMassage(str, L"MeshHelperGMSH : DEBUG MESSAGE");
		}
		/////////////////////////////////////////////////////////////////////////DEBUGGING//////////////////////////////////////////////////////////////////////////

		getCoordinates(rotateAxeEndPoint, rotateAxeEndPointX, rotateAxeEndPointY, rotateAxeEndPointZ);
		std::string meshStep_str = IniFile.GetValue(sectionName, "MeshStep");
		if (meshStep_str == "")
		{
			std::string str = "IniFile: " + fileName + '\n' +
				              "Section Name: " + sectionName + '\n' + '\n' +
				              "KEY VALUE \"MeshStep\": " + meshStep_str + " IS FAILED!" + '\n' + '\n' +
				              "CHECK THE KEY VALUE \"MeshStep\" !";
			displayMassage(str, L"MeshHelperGMSH : ERROR");
			return false;
		}

		/////////////////////////////////////////////////////////////////////////DEBUGGING//////////////////////////////////////////////////////////////////////////
		if (debugging)
		{
			std::string str = "IniFile: " + fileName + '\n' +
				              "Section Name: " + sectionName + '\n' + '\n' +
				              "KEY VALUE \"MeshStep\": " + meshStep_str + '\n' + '\n' +
				              "CHECK THE VALUE FOR EXTRA SPACES AND TYPOS, AND ALSO CHECK UPPER/LOWER CASE!" + '\n' + '\n' +
				              "Singal Place: line 158 [files.cpp - function: readIniFile(...)]";
			displayMassage(str, L"MeshHelperGMSH : DEBUG MESSAGE");
		}
		/////////////////////////////////////////////////////////////////////////DEBUGGING//////////////////////////////////////////////////////////////////////////

		meshStep = std::stod(meshStep_str);
		volumeMeshFile = IniFile.GetValue(sectionName, "VolumeMeshFile");

		/////////////////////////////////////////////////////////////////////////DEBUGGING//////////////////////////////////////////////////////////////////////////
		if (debugging)
		{
			std::string str = "IniFile: " + fileName + '\n' +
				              "Section Name: " + sectionName + '\n' + '\n' +
				              "KEY VALUE \"VolumeMeshFile\": " + volumeMeshFile + '\n' + '\n' +
				              "CHECK THE VALUE FOR EXTRA SPACES AND TYPOS, AND ALSO CHECK UPPER/LOWER CASE!" + '\n' + '\n' +
				              "Singal Place: line 116 [files.cpp - function: readIniFile(...)]";
			displayMassage(str, L"MeshHelperGMSH : DEBUG MESSAGE");
		}
		/////////////////////////////////////////////////////////////////////////DEBUGGING//////////////////////////////////////////////////////////////////////////

		numberPoints = IniFile.NumValues(contourNodesSection);
		std::vector<std::string> points(numberPoints);
		pointX = new double[numberPoints];
		pointY = new double[numberPoints];
		pointZ = new double[numberPoints];
		for (int i = 0; i < numberPoints; i++)
		{
			std::stringstream n;
			n << i + 1;
			std::string number = n.str();
			std::string point("P");
			point.append(number);
			points[i] = IniFile.GetValue(contourNodesSection, point);
			if (points[i] == "")
			{
				std::string str = "IniFile: " + fileName + '\n' +
					              "Section Name: " + sectionName + '\n' + '\n' +
					              "KEY VALUE \"P" + number + "\": " + points[i] + " IS FAILED!" + '\n' + '\n' +
					              "CHECK THE KEY VALUE \"P" + number + "\" !";
				displayMassage(str, L"MeshHelperGMSH : ERROR");
				return false;
			}

			/////////////////////////////////////////////////////////////////////////DEBUGGING//////////////////////////////////////////////////////////////////////////
			if (debugging)
			{
				std::string str = "IniFile: " + fileName + '\n' +
					              "Section Name: " + contourNodesSection + '\n' + '\n' +
					              "KEY VALUE \"P" + number + "\": " + points[i] + '\n' + '\n' +
					              "CHECK THE VALUE FOR EXTRA SPACES AND TYPOS, AND ALSO CHECK UPPER/LOWER CASE!" + '\n' + '\n' +
					              "Singal Place: line 208 [files.cpp - function: readIniFile(...)]";
				displayMassage(str, L"MeshHelperGMSH : DEBUG MESSAGE");
			}
			/////////////////////////////////////////////////////////////////////////DEBUGGING//////////////////////////////////////////////////////////////////////////

			getCoordinates(points[i], pointX[i], pointY[i], pointZ[i]);
		}
		return true;
	}
}