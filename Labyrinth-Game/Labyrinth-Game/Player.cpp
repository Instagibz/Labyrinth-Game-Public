#include "Player.h"

PlayerObj::PlayerObj(void) {}
PlayerObj::PlayerObj(std::vector<int>Pos) { this->Position = Pos; }

void PlayerObj::SetPos(std::vector<int>Pos) { this->Position = Pos; }
std::vector<int> PlayerObj::GetPos() { return this->Position; }
void PlayerObj::IncreaseMoveCount() { this->MoveCount++; }
int PlayerObj::GetMoveCount() { return this->MoveCount; }
void PlayerObj::IncreaseInvMoveCount() { this->InvMoveCount++; }
int PlayerObj::GetInvalidMoveCount() { return this->InvMoveCount; }
