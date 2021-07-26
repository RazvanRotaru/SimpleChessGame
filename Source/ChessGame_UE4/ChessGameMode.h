// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ChessGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CHESSGAME_UE4_API AChessGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:	
	AChessGameMode();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure, Category = "InspectGameState")
	bool CanPlaceOn(class ATile* Tile);

	UFUNCTION(BlueprintCallable, Category = "AlterGameState")
	class AChessPiece* PlaceOn(class ATile* Tile, class AChessPiece* PlayerPiece);
	
	UFUNCTION(BlueprintCallable, Category = "InspectGameState")
	void HighlightPossibleMoves(class AChessPiece* Piece);

	UFUNCTION(BlueprintCallable, Category = "AlterGameState")
	void SwitchPlayers();

protected:
	class AChessGameState* ChessGameState;
};
