// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "MyPlayer.generated.h"

UCLASS()
class COLOSSUSCHALLENGE_API AMyPlayer : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	class USpringArmComponent* SpringArmComponent;
	
	UPROPERTY(EditDefaultsOnly)
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	class UMyAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	class UBaseAttributeSet* AttributeSet;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UGameplayEffect> DefaultAttributeEffect;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<class UGameplayAbility>> DefaultAbilities;
	
public:
	// Sets default values for this character's properties
	AMyPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	virtual void InitializeAttributeSet();
	virtual void GiveDefaultAbility();
};
