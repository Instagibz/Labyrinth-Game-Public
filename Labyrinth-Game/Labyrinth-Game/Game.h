#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <Windows.h>
#include <chrono>

#include "Player.h"




class Labyrinth_Game {

private:
	std::string MapStr;
	bool Gamewon = false;

	std::chrono::steady_clock::time_point BeginTime;
	std::chrono::steady_clock::time_point EndTime;

	struct Board {
		std::vector<int> Size = { 0, 0 };
		std::vector<int> Start = { 0, 0 };
		std::vector<int> Finish = { 0, 0 };
		std::vector<std::vector<char>> Map;
	} BoardObj;
	
	PlayerObj Player;

public: 

	
	Labyrinth_Game::Labyrinth_Game(std::string Labyrinth);
	Labyrinth_Game::~Labyrinth_Game();

	void Labyrinth_Game::DrawGame(void);
	void Labyrinth_Game::ParseBoard(void);
	void Labyrinth_Game::Init(void);
	bool Labyrinth_Game::Update(void);
	void Labyrinth_Game::ProcessInput(void);
	void Labyrinth_Game::GameLoop(void);


};