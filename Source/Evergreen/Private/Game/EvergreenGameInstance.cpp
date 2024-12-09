// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/EvergreenGameInstance.h"

#include "Evergreen/Evergreen.h"
#include "LevelSequencePlayer.h"
#include "MovieSceneBindingProxy.h"
#include "Compilation/MovieSceneCompiledDataManager.h"

void UEvergreenGameInstance::SetEvergreenGameMode(EEvergreenGameMode InGameMode)
{
	GameMode = InGameMode;
	OnGameModeChanged.Broadcast(GameMode);
}

void UEvergreenGameInstance::PauseGame()
{
}

void UEvergreenGameInstance::ResumeGame()
{
}

void UEvergreenGameInstance::PlayCutscene(ULevelSequence* LevelSequence, ALevelSequenceActor*& LevelSequenceActor, ULevelSequencePlayer*& LevelSequencePlayer,
		FMovieSceneObjectBindingID ViewTargetBindingID, FViewTargetTransitionParams ViewTargetTransitionParams,
		bool bReturnToPreviousViewTarget)
{
	LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
		GetWorld(), LevelSequence, FMovieSceneSequencePlaybackSettings(), LevelSequenceActor);

	if (!LevelSequenceActor || !LevelSequencePlayer)
	{
		FAST_WARNING(TEXT("Unable to create level sequence player"))
		return;
	}

	FMovieSceneBindingProxy MovieSceneBindingProxy = ResolveBindingID(LevelSequencePlayer->GetSequence(), ViewTargetBindingID);

	UObject* NewViewTarget = nullptr;
	TArray<UObject*> OutObjects;
	LocateBoundObjects(LevelSequencePlayer->GetSequence(), MovieSceneBindingProxy, OutObjects);
	if (OutObjects.Num() > 0)
	{
		NewViewTarget = OutObjects[0];
	}
	
	if (NewViewTarget)
	{
		if (APlayerController* PlayerController = GetPrimaryPlayerController())
		{
			PreviousViewTarget = PlayerController->GetViewTarget();
			PlayerController->SetViewTarget(Cast<AActor>(NewViewTarget), ViewTargetTransitionParams);
		}
	}

	LevelSequencePlayer->Play();
	if (bReturnToPreviousViewTarget)
	{
		LevelSequencePlayer->OnStop.AddDynamic(this, &UEvergreenGameInstance::ReturnPreviousViewTarget);
	}
}

void UEvergreenGameInstance::ReturnPreviousViewTarget()
{
	if (APlayerController* PlayerController = GetPrimaryPlayerController())
	{
		PlayerController->SetViewTarget(PreviousViewTarget);
	}
}

void UEvergreenGameInstance::StartMiniGame(TSubclassOf<AMiniGameBase> MiniGameClass)
{
}

// Copy From MovieSceneSequenceExtensions.cpp
FMovieSceneBindingProxy UEvergreenGameInstance::ResolveBindingID(UMovieSceneSequence* RootSequence, FMovieSceneObjectBindingID InObjectBindingID)
{
	if (!RootSequence)
	{
		FFrame::KismetExecutionMessage(TEXT("Cannot call ResolveBindingID on a null sequence"), ELogVerbosity::Error);
		return FMovieSceneBindingProxy();
	}

	UMovieSceneSequence* Sequence = RootSequence;

	FMovieSceneCompiledDataID DataID = UMovieSceneCompiledDataManager::GetPrecompiledData()->Compile(RootSequence);

	const FMovieSceneSequenceHierarchy* Hierarchy = UMovieSceneCompiledDataManager::GetPrecompiledData()->FindHierarchy(DataID);
	if (Hierarchy)
	{
		if (UMovieSceneSequence* SubSequence = Hierarchy->FindSubSequence(InObjectBindingID.ResolveSequenceID(MovieSceneSequenceID::Root, Hierarchy)))
		{
			Sequence = SubSequence;
		}
	}

	return FMovieSceneBindingProxy(InObjectBindingID.GetGuid(), Sequence);
}

// Copy From MovieSceneSequenceExtensions.cpp
void UEvergreenGameInstance::LocateBoundObjects(UMovieSceneSequence* Sequence, const FMovieSceneBindingProxy& InBinding, TArray<UObject*>& OutObjects)
{
	if (!Sequence)
	{
		FFrame::KismetExecutionMessage(TEXT("Cannot call LocateBoundObjects on a null sequence"), ELogVerbosity::Error);
		OutObjects = TArray<UObject*>();
	}

	class FTransientPlayer : public IMovieScenePlayer
	{
	public:
		FMovieSceneRootEvaluationTemplateInstance Template;
		virtual FMovieSceneRootEvaluationTemplateInstance& GetEvaluationTemplate() override { return Template; }
		virtual void UpdateCameraCut(UObject* CameraObject, const EMovieSceneCameraCutParams& CameraCutParams) override {}
		virtual void SetViewportSettings(const TMap<FViewportClient*, EMovieSceneViewportParams>& ViewportParamsMap) override {}
		virtual void GetViewportSettings(TMap<FViewportClient*, EMovieSceneViewportParams>& ViewportParamsMap) const override {}
		virtual EMovieScenePlayerStatus::Type GetPlaybackStatus() const { return EMovieScenePlayerStatus::Stopped; }
		virtual void SetPlaybackStatus(EMovieScenePlayerStatus::Type InPlaybackStatus) override {}
	} Player;

	Player.State.AssignSequence(MovieSceneSequenceID::Root, *Sequence, Player);

	TArrayView<TWeakObjectPtr<>> Objects = Player.FindBoundObjects(InBinding.BindingID, MovieSceneSequenceID::Root);
	for (TWeakObjectPtr<> WeakObject : Objects)
	{
		if (WeakObject.IsValid())
		{
			OutObjects.Add(WeakObject.Get());
		}
	}
}
