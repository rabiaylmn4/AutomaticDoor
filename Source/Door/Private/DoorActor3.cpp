#include "DoorActor3.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"

ADoorActor3::ADoorActor3()
{
    PrimaryActorTick.bCanEverTick = true;
    //KOK
    RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = RootComp;

    //KAPICERCEVESİ
    DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
    DoorFrame->SetupAttachment(RootComp);
    DoorFrame->SetCollisionEnabled(ECollisionEnabled::NoCollision); // Frame collision kapalı, karakter geçsin

    //KAPI KANADI
    DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
    DoorMesh->SetupAttachment(RootComp);

   
    DoorMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    DoorMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    DoorMesh->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Ignore);

    //TETIKLEME KUTUSU
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    TriggerBox->SetupAttachment(RootComp);
    TriggerBox->SetBoxExtent(FVector(120.f, 120.f, 200.f));
    TriggerBox->SetRelativeLocation(FVector(100.f, 0.f, 100.f));
    TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TriggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);

    //varsayilan degerler
    CurrentYaw = 0.f;
    TargetYaw = 0.f;
    bWantsOpen = false;

    OpenAngle = 90.f;
    InterpSpeed = 4.f;
}

void ADoorActor3::BeginPlay()
{
    Super::BeginPlay();
    //olay baglama
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ADoorActor3::OnOverlapBegin);
    TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ADoorActor3::OnOverlapEnd);
}

void ADoorActor3::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Kapi acilma / kapanma hedef acisi
    TargetYaw = bWantsOpen ? OpenAngle : 0.f;

    // Yumusak gecis
    CurrentYaw = FMath::FInterpTo(CurrentYaw, TargetYaw, DeltaTime, InterpSpeed);

    //Yeni rotasyonu uygula
    FRotator NewRotation = FRotator(0.f, CurrentYaw, 0.f);
    DoorMesh->SetRelativeRotation(NewRotation);
}

void ADoorActor3::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this && Cast<ACharacter>(OtherActor))
    {
        bWantsOpen = true;
        UKismetSystemLibrary::PrintString(this, TEXT("Player entered: Door opening"));
    }
}

void ADoorActor3::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && OtherActor != this && Cast<ACharacter>(OtherActor))
    {
        bWantsOpen = false;
        UKismetSystemLibrary::PrintString(this, TEXT("Player left: Door closing"));
    }
}
