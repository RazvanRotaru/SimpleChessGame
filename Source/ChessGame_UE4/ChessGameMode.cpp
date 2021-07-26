// Fill out your copyright notice in the Description page of Project Settings.


#include "ChessGameMode.h"
#include "ChessPlayerState.h"
#include "ChessGameState.h"
#include "ChessPlayerController.h"
#include "ChessPiece.h"
#include "Kismet/GameplayStatics.h"
#include "Tile.h"

AChessGameMode::AChessGameMode()
{
	//static ConstructorHelpers::FObjectFinder<AChessPlayerState> PlayerStateBP(TEXT("PlayerState'/Game/Meshes/Queen.Queen'"));
	PrimaryActorTick.bCanEverTick = true;

	//ChessGameState = GetGameState<AChessGameState>();

}

void AChessGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ChessGameState = GetGameState<AChessGameState>();

}

bool AChessGameMode::CanPlaceOn(ATile* Tile)
{
	if (Tile != nullptr)
	{
		return ChessGameState->HighlightedTiles.Contains(Tile);
	}

	return false;
}

AChessPiece* AChessGameMode::PlaceOn(ATile* Tile, AChessPiece* PlayerPiece)
{
	AChessPiece* PreviousPiece = ChessGameState->ChessPiecesState.FindRef(Tile);
	ChessGameState->ChessPiecesState.Add(Tile) = PlayerPiece;
	ChessGameState->ChessPiecesState.Remove(PlayerPiece->GetCurrentTile());

	for (ATile* HighlightedTile : ChessGameState->HighlightedTiles)
	{
		HighlightedTile->Highlight(false);
	}
	ChessGameState->HighlightedTiles.Empty();

	PlayerPiece->MoveTo(Tile);

	return PreviousPiece;
}

void AChessGameMode::HighlightPossibleMoves(AChessPiece* SelectedPiece)
{
	if (SelectedPiece != nullptr)
	{
		TArray<FVector2D> PossibleMoves = SelectedPiece->GetPossibleMoves();
		for (FVector2D Move : PossibleMoves)
		{
			Move *= ChessGameState->CurrentPlayer == 0 ? -1 : +1;
			ATile* SourceTile = SelectedPiece->GetCurrentTile();
			Move += FVector2D(SourceTile->Row, SourceTile->Column);

			if ((Move.X >= 0 && Move.X < ChessGameState->TilesPerLine)
				&& (Move.Y >= 0 && Move.Y < ChessGameState->TilesPerLine))
			{
				ATile* Tile = ChessGameState->GetTile(Move.X, Move.Y);
				Tile->Highlight(true);
				ChessGameState->HighlightedTiles.Add(Tile);
			}
		}
	}
}

void AChessGameMode::SwitchPlayers()
{
	ChessGameState->SwitchPlayers();
	UE_LOG(LogClass, Log, TEXT("Player is now: %d"), ChessGameState->CurrentPlayer);
}

