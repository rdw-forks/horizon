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
 * This is proprietary software. Unauthorized copying,
 * distribution, or modification of this file, via any
 * medium, is strictly prohibited. All rights reserved.
 **************************************************/


#define BOOST_TEST_MODULE "AStarTest"

#include <boost/test/unit_test.hpp>
#include <cstring>
#include <fstream>
#include <cstdint>
#include <cmath>

#include "Server/Zone/Game/Map/Path/AStar.hpp"
#include "Server/Zone/Game/Map/Grid/Cell/Cell.hpp"
#include "Server/Zone/Game/Map/Grid/GridDefinitions.hpp"

using namespace Horizon::Zone;

// #define PRINT_FILE

#define MAP_WIDTH 268
#define MAP_HEIGHT 300

#include "prontera.cpp"

Cell cell[MAP_WIDTH][MAP_HEIGHT];

bool check_collision(int16_t x, int16_t y)
{
	if (x < 0 || y < 0 ||
		x >= MAP_WIDTH || y >= MAP_HEIGHT)
		return true;

	return cell[x][y].isWalkable() ? false : true;
}

// This test imitates the client's path search behavior as it 
// searches for a path within the MAX_VIEW_RANGE of the player
// and not the entire map.
// The client searches for a path from the player's current position
// to the destination position. If the destination is not within the
// MAX_VIEW_RANGE, the client searches for a path to the nearest
// walkable cell within the MAX_VIEW_RANGE.
// - The client does not search for a path to the destination if the
// destination is not within the MAX_VIEW_RANGE.
// - The client does not search for a path to the destination if the
// destination is not walkable.
// - The client does not search for a path to the destination if the
// destination is the same as the player's current position.
BOOST_AUTO_TEST_CASE(AStarTest)
{
	Horizon::Zone::AStar::Generator astar({ MAP_WIDTH, MAP_HEIGHT }, &check_collision, true, &Horizon::Zone::AStar::Heuristic::manhattan);
	astar.setHeuristic(&AStar::Heuristic::manhattan);
	
	std::srand(std::time(nullptr));
	
	int total_time = 0;
	int idx = 0;
	// maps are stored from max-y,x down to 0,0
	// we store in cell[][] starting from 0,0 to max-y 0
	for (int y = MAP_HEIGHT - 1; y >= 0; y--) {
		for (int x = 0; x < MAP_WIDTH; ++x) {
			cell[x][y] = Cell(prontera[idx++]);
		}
	}

	std::vector<std::pair<MapCoords, MapCoords>> start_end;
	for (int i = 0; i < 10000; i++) {
		MapCoords start, end;

		do {
			start = MapCoords( rand() % MAP_WIDTH - 1, rand() % MAP_HEIGHT - 1 );
		} while(check_collision(start.x(), start.y()));

		std::vector<MapCoords> path;
		do {
			do {
				end = MapCoords( rand() % MAP_WIDTH - 1, rand() % MAP_HEIGHT - 1 );
			} while(check_collision(end.x(), end.y()));
		} while (!start.is_within_range(end, MAX_VIEW_RANGE) && ((path = astar.findPath(start, end)).size() == 0 || (path.at(0).x() != end.x() && path.at(0).y() != end.y())));
		
		start_end.push_back(std::make_pair(start, end));
		//std::cout << "Generated " << i << " start: " << start.x() << ", " << start.y() << " end: " << end.x() << ", " << end.y() << std::endl;
	}
	
	for (int i = 0; i < 10000; i++) {
		MapCoords start = start_end[i].first;
		MapCoords end = start_end[i].second;

		auto start_time = std::chrono::high_resolution_clock::now();
		auto path = astar.findPath(start, end);
		auto finish_time = std::chrono::high_resolution_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(finish_time - start_time);
		bool path_found = path.size() != 0;
		//printf("Manhattan: %lldus %d %s size: %lld (%d, %d) -> (%d, %d)\n", elapsed.count(), i, path_found ? "path found" : "path not found", path.size(), start.x(), start.y(), end.x(), end.y());
		total_time += elapsed.count();
		if (path.size() == 0)
			BOOST_FAIL("Path not found");
#ifdef PRINT_FILE
		std::ofstream mapfile;
		char filename[100];
		snprintf(filename, 100, "izlude-%d.txt", i);
		mapfile.open(filename);
		for (int y = MAP_HEIGHT - 1; y >= 0; --y) {
			for (int x = 0; x < MAP_WIDTH; ++x) {
				MapCoords coords = MapCoords(x, y);
				bool found = false;
	
				for (auto c : path) {
					if (coords == c) {
						if (start.x() == x && start.y() == y)
							mapfile << "@ (" << x << ", " << y << ")";
						else if (end.x() == x && end.y() == y)
							mapfile << "T (" << x << ", " << y << ")";
						else if (c.x() == x && c.y() == y)
							mapfile << "^";
						found = true;
					}
				}
	
				if (!found) {
					if (start.x() == x && start.y() == y)
						mapfile << "@ (" << x << ", " << y << ")";
					else if (end.x() == x && end.y() == y)
						mapfile << "T (" << x << ", " << y << ")";
					else if (cell[x][y].isWalkable())
						mapfile << " ";
					else
						mapfile << "|";
				}
			}
	
			mapfile << "\n";
		}
	
		mapfile.close();
#endif
	}
	std::cout << "total time: " << total_time << std::endl;

//	start_time = std::chrono::high_resolution_clock::now();
//	astar.setHeuristic(&AStar::Heuristic::octagonal);
//	astar.navigate(start, end);
//	finish_time = std::chrono::high_resolution_clock::now();
//	elapsed = finish_time - start_time;
//	printf("Octogonal: %.2fs\n", elapsed.count());

	//BOOST_ASSERT(path->size() > 1);
}
