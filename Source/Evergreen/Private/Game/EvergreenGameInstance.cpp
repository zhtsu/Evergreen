// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/EvergreenGameInstance.h"

#include "LevelSequencePlayer.h"
#include "CommonMacro.h"
#include "Game/MiniGameBase.h"
#include "Item/ItemBase.h"
#include "Camera/CameraActor.h"

UEvergreenGameInstance* UEvergreenGameInstance::Singleton = nullptr;

UEvergreenGameInstance* UEvergreenGameInstance::GetEvergreenGameInstance()
{
	return Singleton;
}

UEvergreenGameInstance::UEvergreenGameInstance()
{
	Singleton = this;

	LoadStringTablesOnRuntime();
}

void UEvergreenGameInstance::OnStart()
{
	Super::OnStart();
	
}

void UEvergreenGameInstance::BeginDestroy()
{
	Super::BeginDestroy();
	
}

void UEvergreenGameInstance::SetEvergreenGameMode(EEvergreenGameMode InGameMode)
{
	GameMode = InGameMode;
	OnGameModeChanged.Broadcast(GameMode);
}

void UEvergreenGameInstance::PauseGame()
{
	SetCurrentGamePlayState(EGamePlayState::Paused);
}

void UEvergreenGameInstance::ResumeGame()
{
	ReturnPreviousGamePlayState();
}

void UEvergreenGameInstance::PlayCutscene(ULevelSequence* LevelSequence, ALevelSequenceActor*& LevelSequenceActor, ULevelSequencePlayer*& LevelSequencePlayer)
{
	SetCurrentGamePlayState(EGamePlayState::Cutscene);
	
	LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
		GetWorld(), LevelSequence, FMovieSceneSequencePlaybackSettings(), LevelSequenceActor);

	if (!LevelSequenceActor || !LevelSequencePlayer)
	{
		FAST_WARNING(TEXT("Unable to create level sequence player"));
		return;
	}
	
	LevelSequencePlayer->Play();
	LevelSequencePlayer->OnStop.AddDynamic(this, &UEvergreenGameInstance::ReturnPreviousGamePlayState);
}

void UEvergreenGameInstance::StartMiniGame(TSubclassOf<AMiniGameBase> MiniGameClass, UMiniGameData* MiniGameData)
{
	if (!MiniGameClass || CurrentMiniGame) return;
	
	SetCurrentGamePlayState(EGamePlayState::MiniGame);

	AMiniGameBase* MiniGame = Cast<AMiniGameBase>(GetWorld()->SpawnActor(MiniGameClass));
	if (MiniGame)
	{
		CurrentMiniGame = MiniGame;
		IMiniGameInterface::Execute_OnStartMiniGame(MiniGame, MiniGameData);
	}
}

void UEvergreenGameInstance::EndMiniGame()
{
	if (CurrentMiniGame == nullptr) return;
	
	SetCurrentGamePlayState(GamePlayState.PreviousGamePlayState);
	
	IMiniGameInterface::Execute_OnEndMiniGame(CurrentMiniGame);
	CurrentMiniGame->Destroy();
	CurrentMiniGame = nullptr;
}

bool UEvergreenGameInstance::IsAllowKeyboardInput() const
{
	bool bJudgeWithCurrentMiniGame = false;
	if (GamePlayState.CurrentGamePlayState == EGamePlayState::MiniGame)
	{
		if (CurrentMiniGame) bJudgeWithCurrentMiniGame = true;
		else bJudgeWithCurrentMiniGame = false;
	}

	if (bJudgeWithCurrentMiniGame)
	{
		return IsAllowInput() && CurrentMiniGame->bAllowKeyboardInput;
	}

	return GamePlayState.CurrentGamePlayState != EGamePlayState::Cutscene
		&& GamePlayState.CurrentGamePlayState != EGamePlayState::Paused
		&& GamePlayState.CurrentGamePlayState != EGamePlayState::MiniGame;
}

bool UEvergreenGameInstance::IsAllowInput() const
{
	return GamePlayState.CurrentGamePlayState != EGamePlayState::Cutscene
		&& GamePlayState.CurrentGamePlayState != EGamePlayState::Paused;
}

void UEvergreenGameInstance::CollectItem(AEvergreenItemBase* Item)
{
	if (!Item) return;
	
	if (!CollectedItemIDArray.Contains(Item->ItemID))
	{
		CollectedItemIDArray.Add(Item->ItemID);
		OnItemCollected.Broadcast(Item->ItemID);
		Item->Destroy();
	}
}

bool UEvergreenGameInstance::HasItem(FString ItemID)
{
	return CollectedItemIDArray.Contains(ItemID);
}

void UEvergreenGameInstance::ObserveItem(AEvergreenItemBase* Item, FViewTargetTransitionParams ViewTargetTransitionParams)
{
	if (!Item || !Item->TargetViewCamera) return;

	if (APlayerController* PlayerController = GetPrimaryPlayerController())
	{
		SetCurrentGamePlayState(EGamePlayState::Observing);

		Item->bIsBeingObserved = true;
		AEvergreenItemBase::CurrentObservedItem = Item;
		PlayerController->SetViewTarget(Item->TargetViewCamera, ViewTargetTransitionParams);
	}
}

void UEvergreenGameInstance::ReturnToPlayerView(FViewTargetTransitionParams ViewTargetTransitionParams)
{
	if (APlayerController* PlayerController = GetPrimaryPlayerController())
	{
		if (APawn* Player = PlayerController->GetPawn())
		{
			SetCurrentGamePlayState(EGamePlayState::Exploring);

			if (AEvergreenItemBase::CurrentObservedItem)
			{
				AEvergreenItemBase::CurrentObservedItem->bIsBeingObserved = false;
				AEvergreenItemBase::CurrentObservedItem = nullptr;
			}
			
			PlayerController->SetViewTarget(Player, ViewTargetTransitionParams);
		}
	}
}

void UEvergreenGameInstance::SetCurrentGamePlayState(EGamePlayState NewGamePlayState)
{
	if (NewGamePlayState == GamePlayState.CurrentGamePlayState)
	{
		return;
	}

	GamePlayState.PreviousGamePlayState = GamePlayState.CurrentGamePlayState;
	GamePlayState.CurrentGamePlayState = NewGamePlayState;
	OnGamePlayStateChanged.Broadcast(GamePlayState.CurrentGamePlayState);
}

void UEvergreenGameInstance::ReturnPreviousGamePlayState()
{
	SetCurrentGamePlayState(GamePlayState.PreviousGamePlayState);
}

void UEvergreenGameInstance::LoadStringTablesOnRuntime()
{
#ifndef WITH_EDITOR
	FStringTableRegistry::Get().UnregisterStringTable(FAssetPathHub::ST_ItemName_Reference);
	FStringTableRegistry::Get().Internal_LocTableFromFile(
		FAssetPathHub::ST_ItemName_Reference, TEXT("ST_ItemName"),
		FAssetPathHub::ST_ItemName_CSV_Path.ToString(), FPaths::ProjectContentDir());

	FStringTableRegistry::Get().UnregisterStringTable(FAssetPathHub::ST_ItemDescription_Reference);
	FStringTableRegistry::Get().Internal_LocTableFromFile(
		FAssetPathHub::ST_ItemDescription_Reference, TEXT("ST_ItemDescription"),
		FAssetPathHub::ST_ItemDescription_CSV_Path.ToString(), FPaths::ProjectContentDir());
#endif
}
