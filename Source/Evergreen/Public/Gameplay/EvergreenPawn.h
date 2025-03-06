// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EvergreenPawn.generated.h"

UCLASS()
class EVERGREEN_API AEvergreenPawn : public APawn
{
	GENERATED_BODY()

public:
	AEvergreenPawn();
	
	FORCEINLINE class UCineCameraComponent* GetCamera() const { return Camera; }
	
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* RootScene;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCineCameraComponent* Camera;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Evergreen Character", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AEvergreenCharacter> ThirdPersonPlayerClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Evergreen Character", meta = (AllowPrivateAccess = "true"))
	FTransform ThirdPersonPlayerGeneratedTransform;
};
