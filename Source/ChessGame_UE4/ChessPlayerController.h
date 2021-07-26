// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ChessPlayerController.generated.h"

UENUM(BlueprintType)
enum class EPlayerColor : uint8 {
	WHITE = 0 UMETA(DispalyName = "White"),
	BLACK = 1 UMETA(DispalyName = "Black")
};
/**
 * 
 */
UCLASS()
class CHESSGAME_UE4_API AChessPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AChessPlayerController();
	AChessPlayerController(EPlayerColor Color);

	UFUNCTION(BlueprintCallable, Category = "PlayerController")
	virtual int32 GetPoints(int32 Ammount);
	
	UFUNCTION(BlueprintPure, Category = "Interactions")
	virtual bool CanGrab(class AChessPiece* Piece) const;

	UFUNCTION(BlueprintCallable, Category = "Interactions")
	virtual void Grab(class AChessPiece* Piece) const;

	UFUNCTION(BlueprintPure, Category = "PlayerInfo")
	int32 GetColor() const;

	UFUNCTION(BlueprintCallable, Category = "Interactions")
	void SetColor(EPlayerColor NewColor);

	UFUNCTION(BlueprintNativeEvent, Category = "Interactions")
	void OnLeftClick();
	virtual void OnLeftClick_Implementation();

protected:
	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "PlayerInfo")
	class AChessPlayerState* State;
	
	UPROPERTY(EditDefaultsOnly, Category = "PlayerInfo")
	EPlayerColor Color;

	UPROPERTY(VisibleAnywhere, Category = "PlayerInfo")
	class AChessGameMode* ChessGameMode;
};
