/***************************************************
 *       _   _            _                        *
 *      | | | |          (_)                       *
 *      | |_| | ___  _ __ _ _______  _ __          *
 *      |  _  |/ _ \| '__| |_  / _ \| '_  \        *
 *      | | | | (_) | |  | |/ / (_) | | | |        *
 *      \_| |_/\___/|_|  |_/___\___/|_| |_|        *
 ***************************************************
 * This file is part of Horizon (c).
 *
 * Copyright (c) 2019 Sagun K. (sagunxp@gmail.com).
 * Copyright (c) 2019 Horizon Dev Team.
 *
 * Base Author - Sagun Khosla <sagunxp@gmail.com>
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 **************************************************/

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "AStarTest"

#include "Server/Zone/Game/Map/Grid/Cell/Cell.hpp"

#include "Server/Zone/Game/Map/Path/stlastar.hpp" // See header for copyright and usage information

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <stdio.h>
#include <math.h>

#define DEBUG_LISTS 0
#define DEBUG_LIST_LENGTHS_ONLY 0

using namespace std;

// Global data

// The world map

#define MAP_WIDTH 268
#define MAP_HEIGHT 300

Horizon::Zone::Cell cell[MAP_WIDTH][MAP_HEIGHT];

#include "prontera.cpp"

int izlude_real[80700];

// map helper functions
int GetMap( int x, int y )
{
	if( x < 0 ||
	    x >= MAP_WIDTH ||
		 y < 0 ||
		 y >= MAP_HEIGHT
		|| !cell[x][y].isWalkable()
	  )
	{
		return 1;
	}

	return izlude_real[(y*MAP_WIDTH)+x] ? 1 : 0;
}



// Definitions

class MapSearchNode
{
public:
	int x;	 // the (x,y) positions of the node
	int y;	
	
	MapSearchNode() { x = y = 0; }
	MapSearchNode( int px, int py ) { x=px; y=py; }

	float GoalDistanceEstimate( MapSearchNode &nodeGoal );
	bool IsGoal( MapSearchNode &nodeGoal );
	bool GetSuccessors( AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node );
	float GetCost( MapSearchNode &successor );
	bool IsSameState( MapSearchNode &rhs );

	void PrintNodeInfo(); 
};

bool MapSearchNode::IsSameState( MapSearchNode &rhs )
{

	// same state in a maze search is simply when (x,y) are the same
	if( (x == rhs.x) &&
		(y == rhs.y) )
	{
		return true;
	}
	else
	{
		return false;
	}

}

void MapSearchNode::PrintNodeInfo()
{
	char str[100];
	sprintf( str, "Node position : (%d,%d)\n", x,y );

	cout << str;
}

// Here's the heuristic function that estimates the distance from a Node
// to the Goal. 

float MapSearchNode::GoalDistanceEstimate( MapSearchNode &nodeGoal )
{
	return abs(x - nodeGoal.x) + abs(y - nodeGoal.y);
}

bool MapSearchNode::IsGoal( MapSearchNode &nodeGoal )
{

	if( (x == nodeGoal.x) &&
		(y == nodeGoal.y) )
	{
		return true;
	}

	return false;
}

// This generates the successors to the given Node. It uses a helper function called
// AddSuccessor to give the successors to the AStar class. The A* specific initialisation
// is done for each node internally, so here you just set the state information that
// is specific to the application
bool MapSearchNode::GetSuccessors( AStarSearch<MapSearchNode> *astarsearch, MapSearchNode *parent_node )
{

	int parent_x = -1; 
	int parent_y = -1; 

	if( parent_node )
	{
		parent_x = parent_node->x;
		parent_y = parent_node->y;
	}
	

	MapSearchNode NewNode;

	// push each possible move except allowing the search to go backwards

	if( (GetMap( x-1, y ) < 1) 
		&& !((parent_x == x-1) && (parent_y == y))
	  ) 
	{
		NewNode = MapSearchNode( x-1, y );
		astarsearch->AddSuccessor( NewNode );
	}	

	if( (GetMap( x, y-1 ) < 1) 
		&& !((parent_x == x) && (parent_y == y-1))
	  ) 
	{
		NewNode = MapSearchNode( x, y-1 );
		astarsearch->AddSuccessor( NewNode );
	}	

	if( (GetMap( x+1, y ) < 1)
		&& !((parent_x == x+1) && (parent_y == y))
	  ) 
	{
		NewNode = MapSearchNode( x+1, y );
		astarsearch->AddSuccessor( NewNode );
	}	

		
	if( (GetMap( x, y+1 ) < 1) 
		&& !((parent_x == x) && (parent_y == y+1))
		)
	{
		NewNode = MapSearchNode( x, y+1 );
		astarsearch->AddSuccessor( NewNode );
	}	


	// Diagonal

	if ((GetMap(x - 1, y - 1) < 1)
		&& !((parent_x == x - 1) && (parent_y == y - 1))
		)
	{
		NewNode = MapSearchNode(x - 1, y - 1);
		astarsearch->AddSuccessor(NewNode);
	}

	if ((GetMap(x + 1, y - 1) < 1)
		&& !((parent_x == x + 1) && (parent_y == y - 1))
		)
	{
		NewNode = MapSearchNode(x + 1, y - 1);
		astarsearch->AddSuccessor(NewNode);
	}

	if ((GetMap(x + 1, y + 1) < 1)
		&& !((parent_x == x + 1) && (parent_y == y + 1))
		)
	{
		NewNode = MapSearchNode(x + 1, y + 1);
		astarsearch->AddSuccessor(NewNode);
	}


	if ((GetMap(x - 1, y + 1) < 1)
		&& !((parent_x == x - 1) && (parent_y == y + 1))
		)
	{
		NewNode = MapSearchNode(x - 1, y + 1);
		astarsearch->AddSuccessor(NewNode);
	}

	return true;
}

// given this node, what does it cost to move to successor. In the case
// of our map the answer is the map terrain value at this node since that is 
// conceptually where we're moving

float MapSearchNode::GetCost( MapSearchNode &successor )
{
	return (float) GetMap( x, y );

}

BOOST_AUTO_TEST_CASE(AStarTest)
{
	cout << "STL A* Search implementation\n(C)2001 Justin Heyes-Jones\n";

	int idx = 0;

	for (int y = MAP_HEIGHT - 1; y >= 0; --y) {
		for (int x = MAP_WIDTH - 1; x >= 0; --x) {
			cell[x][y] = Horizon::Zone::Cell(izlude_real[idx++] = izlude[(y * MAP_WIDTH) + x]);
		}
	}

	// Our sample problem defines the world as a 2d array representing a terrain
	// Each element contains an integer from 0 to 5 which indicates the cost 
	// of travel across the terrain. Zero means the least possible difficulty 
	// in travelling (think ice rink if you can skate) whilst 5 represents the 
	// most difficult. 9 indicates that we cannot pass.

	// Create an instance of the search class...

	AStarSearch<MapSearchNode> astarsearch;

	unsigned int SearchCount = 0;

	const unsigned int NumSearches = 1;

	std::srand(std::time(nullptr));

	while(SearchCount < NumSearches)
	{

		// Create a start state
		MapSearchNode nodeStart;
		nodeStart.x = 106;
		nodeStart.y = 150; 

		// Define the goal state
		MapSearchNode nodeEnd;
		nodeEnd.x = 149;
		nodeEnd.y = 100; 
		
		// Set Start and goal states
		
		astarsearch.SetStartAndGoalStates( nodeStart, nodeEnd );

		unsigned int SearchState;
		unsigned int SearchSteps = 0;

		std::vector<MapSearchNode *> path;
		do
		{
			SearchState = astarsearch.SearchStep();

			SearchSteps++;

	#if DEBUG_LISTS

			cout << "Steps:" << SearchSteps << "\n";

			int len = 0;

			cout << "Open:\n";
			MapSearchNode *p = astarsearch.GetOpenListStart();
			while( p )
			{
				len++;
	#if !DEBUG_LIST_LENGTHS_ONLY			
				((MapSearchNode *)p)->PrintNodeInfo();
	#endif
				p = astarsearch.GetOpenListNext();
				
			}

			cout << "Open list has " << len << " nodes\n";

			len = 0;

			cout << "Closed:\n";
			p = astarsearch.GetClosedListStart();
			while( p )
			{
				len++;
	#if !DEBUG_LIST_LENGTHS_ONLY			
				p->PrintNodeInfo();
	#endif			
				p = astarsearch.GetClosedListNext();
			}

			cout << "Closed list has " << len << " nodes\n";
	#endif

		}
		while( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SEARCHING );

		if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SUCCEEDED )
		{
			cout << "Search found goal state\n";

				MapSearchNode *node = astarsearch.GetSolutionStart();

	#if DISPLAY_SOLUTION
				cout << "Displaying solution\n";
	#endif
				int steps = 0;

				node->PrintNodeInfo();
				for( ;; )
				{
					node = astarsearch.GetSolutionNext();

					if( !node )
					{
						break;
					}

					node->PrintNodeInfo();
					steps ++;

					path.push_back(node);
				};

				for (int y = MAP_HEIGHT - 1; y >= 0; --y) {
					for (int x = MAP_WIDTH - 1; x >= 0; --x) {
						std::vector<MapSearchNode*>::iterator it = std::find_if(path.begin(), path.end(), [x, y](MapSearchNode* m) { return (m->x == x && m->y == y); });
						
						if (it != path.end()) {
							std::cout << "^";
						}
						else if (izlude[(y * MAP_WIDTH) + x])
							std::cout << ".";
						else
							std::cout << " ";
					}
					std::cout << std::endl;
				}

				cout << "Solution steps " << steps << endl;

				// Once you're done with the solution you can free the nodes up
				astarsearch.FreeSolutionNodes();

	
		}
		else if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_FAILED ) 
		{
			cout << "Search terminated. Did not find goal state\n";
		
		}

		// Display the number of loops the search went through
		cout << "SearchSteps : " << SearchSteps << "\n";

		SearchCount ++;

		astarsearch.EnsureMemoryFreed();
	}

	//Horizon::Zone::Cell cell[MAP_WIDTH][MAP_HEIGHT];
	//
	//for (int y = MAP_HEIGHT - 1; y >= 0; --y) {
	//	for (int x = 0; x < MAP_WIDTH; ++x) {
	//		cell[x][y] = Horizon::Zone::Cell(izlude[idx++]);
	//	}
	//}

	//int idx = 0;
	//for (int y = 0; y < MAP_HEIGHT - 1; ++y) {
	//	for (int x = 0; x < MAP_WIDTH - 1; ++x) {
	//		std::cout << izlude[(y * MAP_WIDTH) + x];
	//	}
	//	std::cout << std::endl;
	//}
}
