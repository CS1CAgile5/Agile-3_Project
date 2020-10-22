// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControllerBase.h"

/*! \brief Enables or disables control
 *
 *
 *  This Function will enable or disable the players control based on the bool
 *  @param SetPlayerEnabled whether or not we want the player to have control at this time
 */
void APlayerControllerBase::SetPlayerEnabledState(bool SetPlayerEnabled) 
{
    if(SetPlayerEnabled)
    {
        GetPawn()->EnableInput(this);
    }
    else
    {
        GetPawn()->DisableInput(this);
    }
    bShowMouseCursor = SetPlayerEnabled;
    
}
