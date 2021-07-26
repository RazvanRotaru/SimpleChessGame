// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessPlayerState.h"
#include "ChessPiece.h"

AChessPlayerState::AChessPlayerState()
{
	CurrentScore = 0;
}

int32 AChessPlayerState::GetCurrentScore()
{
	return CurrentScore;
}

void AChessPlayerState::GainPoints(int32 Value)
{
	CurrentScore += Value;
}

void AChessPlayerState::SelectPiece(AChessPiece* Piece)
{
	UE_LOG(LogClass, Log, TEXT("You have selected something"));

	SelectedPiece = Piece;
	SourceTile = SelectedPiece->GetCurrentTile();
	SelectedPiece->SelectPiece(true);
}

void AChessPlayerState::UnselectPiece()
{
	UE_LOG(LogClass, Log, TEXT("Unselected something"));
	
	SelectedPiece->SelectPiece(false);
	SelectedPiece = nullptr;
	SourceTile = nullptr;
}

bool AChessPlayerState::IsHoldingPiece() const
{
	return SelectedPiece != nullptr;
}

AChessPiece* AChessPlayerState::GetSelectedPiece() const
{
	return SelectedPiece;
}
