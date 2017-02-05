#pragma once
#include <vector>



class PlayerObj {

private:
	std::vector<int> Position = { 0, 0 };
	int MoveCount = 0, InvMoveCount = 0;

public:
	PlayerObj::PlayerObj(std::vector<int>Pos);
	PlayerObj::PlayerObj();

	void PlayerObj::SetPos(std::vector<int> Pos);
	std::vector<int> PlayerObj::GetPos();
	void PlayerObj::IncreaseMoveCount();
	int PlayerObj::GetMoveCount();
	void PlayerObj::IncreaseInvMoveCount();
	int PlayerObj::GetInvalidMoveCount();
};
