// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "ChessPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class CHESSGAME_UE4_API AChessPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AChessPlayerState();
	
	UFUNCTION(BlueprintPure, Category = "PlayerStateInfo")
	int32 GetCurrentScore();

	UFUNCTION(BlueprintCallable, Category = "AlterPlayerState")
	void GainPoints(int32 Value);

	UFUNCTION(BlueprintCallable, Category = "AlterPlayerState")
	virtual void SelectPiece(class AChessPiece* Piece);

	UFUNCTION(BlueprintCallable, Category = "AlterPlayerState")
	virtual void UnselectPiece();

	UFUNCTION(BlueprintPure, Category = "PlayerStateInfo")
	bool IsHoldingPiece() const;

	UFUNCTION(BlueprintCallable, Category = "AlterPlayerState")
	class AChessPiece* GetSelectedPiece() const;

private:
	UPROPERTY(VisibleAnywhere, Category = "PlayerState")
	int32 CurrentScore;

	UPROPERTY(VisibleAnywhere, Category = "PlayerState")
	class ATile* SourceTile;

	UPROPERTY(VisibleAnywhere, Category = "PlayerState")
	class AChessPiece* SelectedPiece;
};
