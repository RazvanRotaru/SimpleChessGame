// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableActor.generated.h"

UCLASS()
class CHESSGAME_UE4_API AInteractableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableActor();

	UFUNCTION(BlueprintPure, Category = "Tile")
	FVector GetSize() const;


	UFUNCTION(BlueprintCallable, Category = "Tile")
	void Highlight(bool bValue);

	UFUNCTION(BlueprintPure, Category = "Tile")
	class UStaticMeshComponent* GetMesh() const;

	UFUNCTION(BlueprintCallable, Category = "Tile")
	void SetDefaultColors(FLinearColor BaseColor, FLinearColor SelectedColor, float BlendFactor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, Category = "Collision")
	void BeginCursorOver(class UPrimitiveComponent* Component);
	virtual void BeginCursorOver_Implementation(class UPrimitiveComponent* Component);

	UFUNCTION(BlueprintNativeEvent, Category = "Collision")
	void EndCursorOver(class UPrimitiveComponent* Component);
	virtual void EndCursorOver_Implementation(class UPrimitiveComponent* Component);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tile", Meta = (BlueprintProtected = "true"))
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile", Meta = (BlueprintProtected = "true"))
	class UMaterialInstanceDynamic* DynamicMaterialInstance;
};
