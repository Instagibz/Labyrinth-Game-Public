#include "Game.h"


Labyrinth_Game::Labyrinth_Game(std::string Labyrinth) {
	this->MapStr = Labyrinth;
	this->Init();
}
Labyrinth_Game::~Labyrinth_Game(void) {}



void Labyrinth_Game::DrawGame(void) {
	system("cls");

	for (int y = 0; y < this->BoardObj.Size[1]; y++) {

		for (int x = 0; x < this->BoardObj.Size[0]; x++) {
			if (x == this->Player.GetPos().at(0) && y == this->Player.GetPos().at(1)) { std::cout << '@'; }
			else { std::cout << this->BoardObj.Map[y][x]; }
		}
		std::cout << std::endl;
	}

}
void Labyrinth_Game::ParseBoard(void) {
	int x = 0, y = 0;
	std::vector<char> Temp;

	for (auto& i : this->MapStr) {

		if (i == '.') {
			this->BoardObj.Start.at(0) = x;
			this->BoardObj.Start.at(1) = y;
		}
		else if (i == '!') {
			this->BoardObj.Finish.at(0) = x;
			this->BoardObj.Finish.at(1) = y;
		}
		else if (i == '\n') {
			y++;
			this->BoardObj.Size.at(0) = x;
			x = 0;
			this->BoardObj.Map.push_back(Temp);
			Temp.clear();
			continue;
		}
		Temp.push_back(i);
		x++;
	}
	this->BoardObj.Size.at(1) = y;

}

void Labyrinth_Game::Init(void) {
	this->ParseBoard();
	this->Player.SetPos(this->BoardObj.Start);
}

void Labyrinth_Game::ProcessInput() {
	if (GetAsyncKeyState(VK_UP)) {
		if ((this->Player.GetPos().at(1) - 1) < 0 || this->BoardObj.Map[this->Player.GetPos().at(1) - 1][this->Player.GetPos().at(0)] == '#') { /*std::cout << "Invalid Move" << std::endl;*/ this->Player.IncreaseInvMoveCount(); }
		else { this->Player.SetPos(std::vector<int>{this->Player.GetPos()[0], this->Player.GetPos().at(1) - 1}); this->Player.IncreaseMoveCount(); }
		return;
	}
	if (GetAsyncKeyState(VK_DOWN)) {
		if ((this->Player.GetPos().at(1) + 1) >= this->BoardObj.Size[1] || this->BoardObj.Map[this->Player.GetPos().at(1) + 1][this->Player.GetPos().at(0)] == '#') { /*std::cout << "Invalid Move" << std::endl;*/ this->Player.IncreaseInvMoveCount(); }
		else { this->Player.SetPos(std::vector<int>{this->Player.GetPos()[0], this->Player.GetPos().at(1) + 1}); this->Player.IncreaseMoveCount(); }
		return;
	}

	if (GetAsyncKeyState(VK_RIGHT)) {
		if ((this->Player.GetPos().at(0) + 1) >= this->BoardObj.Size[0] || this->BoardObj.Map[this->Player.GetPos().at(1)][this->Player.GetPos().at(0) + 1] == '#') { /*std::cout << "Invalid Move" << std::endl;*/ this->Player.IncreaseInvMoveCount(); }
		else { this->Player.SetPos(std::vector<int>{this->Player.GetPos().at(0) + 1, this->Player.GetPos().at(1)}); this->Player.IncreaseMoveCount(); }
		return;
	}
	if (GetAsyncKeyState(VK_LEFT)) {
		if ((this->Player.GetPos().at(0) - 1) < 0 || this->BoardObj.Map[this->Player.GetPos().at(1)][this->Player.GetPos().at(0) - 1] == '#') { /*std::cout << "Invalid Move" << std::endl;*/ this->Player.IncreaseInvMoveCount(); }
		else { this->Player.SetPos(std::vector<int>{this->Player.GetPos().at(0) - 1, this->Player.GetPos().at(1)}); this->Player.IncreaseMoveCount(); }
		return;
	}
}
bool Labyrinth_Game::Update(void) {

	if (this->Player.GetPos() == this->BoardObj.Finish) { this->Gamewon = true; this->EndTime = std::chrono::steady_clock::now(); }

	if (!this->Gamewon) {
		this->ProcessInput();
		return true;
	}
	else {
		std::cout << "GAME WON!" << std::endl << std::endl;;
		std::cout << "You made " << this->Player.GetMoveCount() << " Valid-Moves and " << this->Player.GetInvalidMoveCount() << " Invalid-Moves" << std::endl;
		std::cout << "You took " << std::chrono::duration_cast<std::chrono::seconds>(this->EndTime - this->BeginTime).count() << " Seconds to complete the game!" << std::endl;
		return false;
	}

}
void Labyrinth_Game::GameLoop(void) {
	this->BeginTime = std::chrono::steady_clock::now();

	if (!this->Gamewon) { this->DrawGame(); }

	std::vector<int> OldPlayerPos = this->BoardObj.Start;
	DWORD BytesWritten = 0;

	while (this->Update()) {

		if (OldPlayerPos != this->Player.GetPos()) {
			//Restore symbol at old playerpos
			COORD ConsoleCoord = { (short)OldPlayerPos.at(0), (short)OldPlayerPos.at(1) };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleCoord);
			char TempStr[2] = { this->BoardObj.Map[OldPlayerPos.at(1)][OldPlayerPos.at(0)], '\0' };
			WriteConsoleOutputCharacterA(GetStdHandle(STD_OUTPUT_HANDLE), (LPCSTR)TempStr, sizeof(char), ConsoleCoord, &BytesWritten);
			
			//Write playersymbol at new pos
			ConsoleCoord = { (short)this->Player.GetPos().at(0), (short)this->Player.GetPos().at(1) };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleCoord);
			WriteConsoleOutputCharacterA(GetStdHandle(STD_OUTPUT_HANDLE), "@", sizeof(char), ConsoleCoord, &BytesWritten);

			//place cursor at the end again
			ConsoleCoord = { 0, (short)this->BoardObj.Size.at(1) + 1 };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), ConsoleCoord);
		}

		OldPlayerPos = this->Player.GetPos();
		Sleep(50);
	}
}