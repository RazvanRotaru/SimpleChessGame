// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessGameState.h"

AChessGameState::AChessGameState()
{
	CurrentPlayer = 0;
}

void AChessGameState::SwitchPlayers()
{
	CurrentPlayer = (CurrentPlayer + 1) % 2;
}

ATile* AChessGameState::GetTile(int32 Row, int32 Column)
{
	return Grid[Row * TilesPerLine + Column];
}
