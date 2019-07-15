
/**************************************************************************************************

	Project: CO2301 Assignment - Path Finding

	   File: MapData.hpp

	 Author: Simon Rybicki

	   Date: 30/01/19

	Version: 1.0

	   Info: Defines map and coords file read operations.

**************************************************************************************************/

// Custom include file.
#include "Definitions.hpp"

// System include files.
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Set min and max possible terrain costs.
const int MIN_TERRAIN_COST = 0;
const int MAX_TERRAIN_COST = 3;

// Default file names.
const string MAP_FILE_NAME = " Map.txt";
const string COORDS_FILE_NAME = " Coords.txt";

// ASCII alphabet range (a-z).
const unsigned int CHAR_CODE_A = 97;
const unsigned int CHAR_CODE_Z = 122;

// Character separating two numbers in a file.
const char CHAR_SPLIT = ' ';

// Minimum width and height of the map.
const int MIN_MAP_SIZE = 1;

// File read states.
const bool READ_GOOD = true;
const bool READ_BAD = false;

// The file name of the save path file.
const string PATH_FILE_NAME = "output.txt";

class CMapData
{

public:

	// Constructor. Sets default values for class properties.
	// Param:
	// Return: Map data object.
	CMapData();

	// Destructor.
	// Param:
	// Return:
	~CMapData();

	// Loads the map size and terrain costs from a file.
	// Param:
	// Return: True or false.
	bool LoadMapData();

	// Loads the start and goal node positions from a file.
	// Param:
	// Return: True or false.
	bool LoadCoordsData();

	// Clears data for map and size, start/goal nodes, node lists, file key and loaded states.
	// Param:
	// Return:
	void ClearData();

	// Checks if the map data has been loaded.
	// Param:
	// Return: True or false.
	bool IsMapDataLoaded();

	// Checks if the coords data has been loaded.
	// Param:
	// Return: True or false.
	bool IsCoordsDataLoaded();

	// Gets the map data.
	// Param:
	// Return: Map.
	TerrainMap& GetMap();

	// Gets the map size.
	// Param:
	// Return: Map size.
	SMapSize& GetMapSize();

	// Gets the starts node.
	// Param:
	// Return: Start node.
	SNode* GetStartNode();

	// Gets the goal node.
	// Param:
	// Return: Goal node.
	SNode* GetGoalNode();

	// Get the current node.
	// Param:
	// Return: Current node.
	SNode* GetCurrentNode();

	// Updates the current node position to the first node on the open list.
	// Param:
	// Return:
	void UpdateCurrentNode();

	// Checks if the open list is empty.
	// Param:
	// Return: True or false.
	bool IsOpenListEmpty();

	// Gets the opens list nodes.
	// Param:
	// Return: Open list.
	NodeList& GetOpenList();

	// Gets the closed list nodes.
	// Param:
	// Return: Closed list.
	NodeList& GetClosedList();

	// Gets the path list nodes.
	// Param:
	// Return: Path list.
	NodeList& GetPathList();

	// Saves the path node positions to a text file.
	// Param: Node list.
	// Return:
	void CMapData::SavePath(const NodeList& path);

	// Resets the open, closed and path lists.
	// Param:
	// Return:
	void ResetLists();

private:

	TerrainMap mMap;
	SMapSize mMapSize;
	SNode* mpStartNode;
	SNode* mpGoalNode;
	SNode* mpCurrentNode;
	NodeList mOpenList;
	NodeList mClosedList;
	NodeList mPathList;
	char mFileKey;
	bool mMapDataLoaded;
	bool mCoordsDataLoaded;

	// Gets the key character at the start of a file name.
	// Param:
	// Return: Character.
	char GetFileNameKey(string);

	// Check if a file exists and is not locked.
	// Param: Name of file.
	// Return: True or False.
	bool FileExists(string);

	// Reads a map data file, validates and stores the data.
	// Param: Map file name.
	// Return: True or False.
	bool ReadMapFile(string&);

	// Reads a coords data file, validates and stores the data.
	// Param: Coords file name.
	// Return: True or False.
	bool ReadCoordsFile(string&);

	// Gets two numbers from a single line read.
	// Param: Error information, Line text, Numbers.
	// Return:
	void GetNumbersFromReadLine(string&, string&, int[2]);

	// Checks if the number characters contain numbers.
	// Param: Number characters, Index position, Size of number.
	// Return: True or False.
	bool IsValidNumber(string&, const int&, int&);

	// Converts an characters of a number into a single integer value.
	// Param: Number characters, Index position, Size of number.
	// Return: Number.
	int ConvertToNumber(string&, const int&, int&);

};