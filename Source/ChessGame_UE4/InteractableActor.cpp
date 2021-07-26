// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableActor.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/PrimitiveComponent.h"

// Sets default values
AInteractableActor::AInteractableActor()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	SetRootComponent(StaticMesh);
}

// Called when the game starts or when spawned
void AInteractableActor::BeginPlay()
{
	Super::BeginPlay();

	UMaterial* DyanmicMaterial = LoadObject<UMaterial>(nullptr, TEXT("Material'/Game/ChessBoard/Materials/DynamicColor.DynamicColor'"));
	DynamicMaterialInstance = UMaterialInstanceDynamic::Create(DyanmicMaterial, this);

	StaticMesh->SetMaterial(0, DynamicMaterialInstance);

	StaticMesh->OnBeginCursorOver.AddDynamic(this, &AInteractableActor::BeginCursorOver);
	StaticMesh->OnEndCursorOver.AddDynamic(this, &AInteractableActor::EndCursorOver);
	StaticMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void AInteractableActor::BeginCursorOver_Implementation(UPrimitiveComponent* Component)
{
}

void AInteractableActor::EndCursorOver_Implementation(UPrimitiveComponent* Component)
{
}

void AInteractableActor::Highlight(bool bValue)
{
	DynamicMaterialInstance->SetScalarParameterValue(FName("BlendFactor"), bValue ? 1.f : 0.f);
}

UStaticMeshComponent* AInteractableActor::GetMesh() const
{
	return StaticMesh;
}

FVector AInteractableActor::GetSize() const
{
	return StaticMesh->GetStaticMesh()->GetBounds().GetBox().GetSize();
}

void AInteractableActor::SetDefaultColors(FLinearColor BaseColor, FLinearColor SelectedColor, float BlendFactor)
{
	if (DynamicMaterialInstance == nullptr)
	{
		return;
	}
	DynamicMaterialInstance->SetVectorParameterValue(FName("BaseColor"), BaseColor);
	DynamicMaterialInstance->SetVectorParameterValue(FName("SelectedColor"), SelectedColor);
	DynamicMaterialInstance->SetScalarParameterValue(FName("BlendFactor"), BlendFactor);
}