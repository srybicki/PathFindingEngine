
/**************************************************************************************************

	Project: CO2301 Assignment - Path Finding

	   File: MapData.cpp

	 Author: Simon Rybicki

	   Date: 30/01/19

	Version: 1.0

	   Info: Implements map and coords file read operations.

**************************************************************************************************/

#include "MapData.hpp"

// Constructor. Sets default values for class properties.
CMapData::CMapData()
{
	mMapSize.mWidth = 0;
	mMapSize.mHeight = 0;

	mpStartNode = new SNode();
	mpGoalNode = new SNode();
	mpCurrentNode = new SNode();

	mFileKey = 0;

	mMapDataLoaded = READ_BAD;
	mCoordsDataLoaded = READ_BAD;
}

// Destructor.
CMapData::~CMapData() {}

// Loads the map size and terrain costs from a file.
bool CMapData::LoadMapData()
{
	mMapDataLoaded = READ_BAD;

	mFileKey = GetFileNameKey(MAP_FILE_NAME);

	if (mFileKey == 0)
	{
		cout << "\nERROR: Unable to get file key.";
	}
	else
	{
		string mapFileName;
		mapFileName = MAP_FILE_NAME;
		mapFileName[0] = mFileKey;

		mMapDataLoaded = ReadMapFile(mapFileName);

		if (!mMapDataLoaded)
		{
			cout << "\nERROR: Unable to read map data.";
		}
	}

	return mMapDataLoaded;
}

// Loads the start and goal node positions from a file.
bool CMapData::LoadCoordsData()
{
	mCoordsDataLoaded = READ_BAD;

	if (!mMapDataLoaded)
	{
		cout << "\nERROR: Map data has not been loaded.";
	}
	else
	{
		string coordsFileName;
		coordsFileName = COORDS_FILE_NAME;
		coordsFileName[0] = mFileKey;

		mCoordsDataLoaded = ReadCoordsFile(coordsFileName);

		if (!mCoordsDataLoaded)
		{
			cout << "\nERROR: Unable to read coords data.";
		}
	}

	return mCoordsDataLoaded;
}

// Clears data for map and size, start/goal nodes, node lists, file key and loaded states.
void CMapData::ClearData()
{
	mMap.clear();

	mMapSize.mWidth = 0;
	mMapSize.mHeight = 0;

	delete mpStartNode;
	delete mpGoalNode;
	delete mpCurrentNode;
	mpStartNode = new SNode();
	mpGoalNode = new SNode();
	mpCurrentNode = new SNode();

	mOpenList.clear();
	mClosedList.clear();
	mPathList.clear();

	mFileKey = 0;

	mMapDataLoaded = READ_BAD;
	mCoordsDataLoaded = READ_BAD;
}

// Checks if the map data has been loaded.
bool CMapData::IsMapDataLoaded()
{
	return mMapDataLoaded;
}

// Checks if the coords data has been loaded.
bool CMapData::IsCoordsDataLoaded()
{
	return mCoordsDataLoaded;
}

// Gets the map data.
TerrainMap& CMapData::GetMap()
{
	return mMap;
}

// Gets the map size.
SMapSize& CMapData::GetMapSize()
{
	return mMapSize;
}

// Gets the starts node.
SNode* CMapData::GetStartNode()
{
	return mpStartNode;
}

// Gets the goal node.
SNode* CMapData::GetGoalNode()
{
	return mpGoalNode;
}

// Gets the current node.
SNode* CMapData::GetCurrentNode()
{
	return mpCurrentNode;
}

// Updates the current node position to the first node on the open list.
void CMapData::UpdateCurrentNode()
{
	if (!mOpenList.empty())
	{
		mpCurrentNode->mX = mOpenList[0]->mX;
		mpCurrentNode->mY = mOpenList[0]->mY;
	}
}

// Checks if the open list is empty.
bool CMapData::IsOpenListEmpty()
{
	if (mOpenList.empty())
	{
		return true;
	}

	return false;
}

// Gets the opens list nodes.
NodeList& CMapData::GetOpenList()
{
	return mOpenList;
}

// Gets the closed list nodes.
NodeList& CMapData::GetClosedList()
{
	return mClosedList;
}

// Gets the path list nodes.
NodeList& CMapData::GetPathList()
{
	return mPathList;
}

// Saves the path node positions to a text file.
void CMapData::SavePath(const NodeList& path)
{
	ofstream outputFile;
	outputFile.open(PATH_FILE_NAME);

	for (const auto& node : path)
	{
		outputFile << node->mX << " " << node->mY << "\n";
	}

	outputFile.close();
}

// Resets the open, closed and path lists.
void CMapData::ResetLists()
{
	mOpenList.clear();
	mClosedList.clear();
	mPathList.clear();
}

// Gets the key character at the start of a file name.
char CMapData::GetFileNameKey(string fileName)
{
	for (unsigned int ch = CHAR_CODE_A; ch <= CHAR_CODE_Z; ++ch)
	{
		fileName[0] = static_cast<char>(ch);

		if (FileExists(fileName))
		{
			return ch;
		}
	}

	return 0;  // No key found.
}

// Checks if a file exists and is not locked.
bool CMapData::FileExists(string fileName)
{
	ifstream file(fileName);

	return file.good();
}

// Reads a map data file, validates and stores the data.
bool CMapData::ReadMapFile(string& fileName)
{
	ifstream mapFile(fileName);

	if (!mapFile.is_open())
	{
		cout << "\n Error: Unable to open file " << fileName;
		return READ_BAD;
	}
	else
	{
		string line, errorInfo;
		int numbers[2];

		// Check if first read line is successful.
		if (!getline(mapFile, line))
		{
			cout << "\n Error: Unable to read line for map size.";
			return READ_BAD;
		}
		else
		{
			// Get the map size values from the read line.
			GetNumbersFromReadLine(errorInfo, line, numbers);

			if (errorInfo.length() != 0)
			{
				cout << errorInfo;
				return READ_BAD;
			}

			// Check the map size values are less than min size.
			if (numbers[0] < MIN_MAP_SIZE || numbers[1] < MIN_MAP_SIZE)
			{
				cout << "\n Error: Map size cannot be less than " << MIN_MAP_SIZE;
				return READ_BAD;
			}

			// Set the map size values.
			mMapSize.mWidth = numbers[0];
			mMapSize.mHeight = numbers[1];
		}

		vector<ETerrainCost> mapRow;

		for (int i = 2; i < (mMapSize.mHeight + 2); ++i)
		{
			// Check if read next line is successful.
			if (!getline(mapFile, line))
			{
				cout << "\n Error: Only " << i << "/" << mMapSize.mHeight << " of map data exist";
				mapFile.close();
				return READ_BAD;
			}
			else
			{
				// Check if data row size is map width.
				if (line.length() < mMapSize.mWidth)
				{
					cout << "\n Error: Only " << line.length() << "/" << mMapSize.mWidth << " of map data exists on line " << i;
					mapFile.close();
					return READ_BAD;
				}

				// Check if values in line are numbers.
				if (!IsValidNumber(line, 0, mMapSize.mWidth))
				{
					cout << "\n Error: Invalid numbers on line " << i;
					mapFile.close();
					return READ_BAD;
				}

				// Add values to map terrain list.
				for (int j = 0; j < mMapSize.mWidth; ++j)
				{
					int tCost = static_cast<int>(line[j] - '0');

					mapRow.push_back(static_cast<ETerrainCost>(tCost));
				}
			}

			// IMPORTANT: Add each row at the beginning to display correctly.
			mMap.insert(mMap.begin(), mapRow);
			mapRow.clear();
		}

		mapFile.close();
	}

	return READ_GOOD;
}

// Reads a coords data file, validates and stores the data.
bool CMapData::ReadCoordsFile(string& fileName)
{
	ifstream mapFile(fileName);

	if (!mapFile.is_open())
	{
		cout << "\n Error: Unable to open file " << fileName;
		return READ_BAD;
	}
	else
	{
		string line, errorInfo;
		int numbers[2];

		// Read first line to get size.
		if (!getline(mapFile, line))
		{
			cout << "\n Error: Unable to read line for first number.";
			return READ_BAD;
		}
		else
		{
			// Get the first coordinate values.
			GetNumbersFromReadLine(errorInfo, line, numbers);

			if (errorInfo.length() != 0)
			{
				cout << errorInfo;
				return READ_BAD;
			}

			// Check if start position is NOT within map area.
			if (numbers[0] < 0 || numbers[0] > (mMapSize.mWidth - 1) ||
				numbers[1] < 0 || numbers[1] > (mMapSize.mHeight - 1))
			{
				cout << "\n Error: Start coordinates (" << numbers[0] << "," << numbers[1] << ") are outside of the map area.";
				return READ_BAD;
			}

			// Set the first coordinate values.
			mpStartNode->mX = numbers[0];
			mpStartNode->mY = numbers[1];
		}

		// Read second line to get size.
		if (!getline(mapFile, line))
		{
			cout << "\n Error: Unable to read line for second number.";
			return READ_BAD;
		}
		else
		{
			// Get the second coordinate values.
			GetNumbersFromReadLine(errorInfo, line, numbers);

			if (errorInfo.length() != 0)
			{
				cout << errorInfo;
				return READ_BAD;
			}

			// Check if goal position is NOT within map area.
			if (numbers[0] < 0 || numbers[0] > (mMapSize.mWidth - 1) ||
				numbers[1] < 0 || numbers[1] > (mMapSize.mHeight - 1))
			{
				cout << "\n Error: Goal coordinates (" << numbers[0] << "," << numbers[1] << ") are outside of the map area.";
				return READ_BAD;
			}

			// Set the second coordinate values.
			mpGoalNode->mX = numbers[0];
			mpGoalNode->mY = numbers[1];
		}
	}

	return READ_GOOD;
}

// Gets two numbers from a single line read.
void CMapData::GetNumbersFromReadLine(string& errorInfo, string& readLine, int numbers[2])
{
	// Check if size values do NOT exist.
	int mapSizeLineLen = readLine.length();

	if (mapSizeLineLen == 0)
	{
		errorInfo = "\n Error: Number values do not exist.";
		return;
	}

	int splitIndex = BAD_INDEX;

	// Find the index where the space is between the numbers in the parameter string.
	for (int i = 0; i < mapSizeLineLen; ++i)
	{
		if (readLine[i] == CHAR_SPLIT)
		{
			splitIndex = i;
			break;
		}
	}

	if (splitIndex == BAD_INDEX)
	{
		errorInfo = "\n Error: Unable to detect 2 number values.";
		return;
	}

	int firstNumberIndex = 0;                                  // Starting index position of the first number.
	int secondNumberIndex = splitIndex + 1;                    // Starting index position of the second number.
	int firstNumberSize = splitIndex;                          // Number of characters in the first number.
	int secondNumberSize = mapSizeLineLen - (splitIndex + 1);  // Number of characters in the second number.

	if (!IsValidNumber(readLine, firstNumberIndex, firstNumberSize) ||
		!IsValidNumber(readLine, secondNumberIndex, secondNumberSize))
	{
		errorInfo = "\n Error: A number is invalid.";
		return;
	}

	// Get the number values.
	numbers[0] = ConvertToNumber(readLine, firstNumberIndex, firstNumberSize);
	numbers[1] = ConvertToNumber(readLine, secondNumberIndex, secondNumberSize);
}

// Checks if the number characters contain numbers.
bool CMapData::IsValidNumber(string& number, const int& index, int& size)
{
	for (int i = index; i < size; ++i)
	{
		if (isdigit(number[i]) == false)
		{
			return false;
		}
	}

	return true;
}

// Converts an characters of a number into a single integer value.
int CMapData::ConvertToNumber(string& number, const int& index, int& size)
{
	int endIndex = index;     // Last search index of the character array.
	int multiplierValue = 1;  // First multiplier value. This will go up on each loop iteration (1, 10, 100, 1000).
	int nextNumber = 0;       // The next character as number value.
	int finalNumber = 0;      // The final number to return (array of characters as number).

	for (int i = (index + (size - 1)); i >= endIndex; --i)
	{
		nextNumber = static_cast<int>(number[i] - '0');
		finalNumber += (nextNumber * multiplierValue);
		multiplierValue *= 10;
	}

	return finalNumber;
}