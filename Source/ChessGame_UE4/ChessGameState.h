// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ChessGameState.generated.h"

/**
 * 
 */
UCLASS()
class CHESSGAME_UE4_API AChessGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AChessGameState();

	UFUNCTION(BlueprintCallable, Category = "AlterGameState")
	void SwitchPlayers();

	UFUNCTION(BlueprintCallable, Category = "AccesChessBoard")
	class ATile* GetTile(int32 Row, int32 Column);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameStateInfo")
	int32 CurrentPlayer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GameStateInfo")
	int32 TilesPerLine;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameStateInfo")
	TMap<class ATile*, class AChessPiece*> ChessPiecesState;

	UPROPERTY(VisibleAnywhere, Category = "ChessBoardInfo")
	TArray<class ATile*> HighlightedTiles;

	UPROPERTY(VisibleAnywhere, Category = "ChessBoardInfo")
	TArray<class ATile*> Grid;
};
