#pragma once

#include "Client_Defines.h"
#include "Base.h"

BEGIN(Client)

class CUIManager final : CBase
{
	DECLARE_SINGLETON(CUIManager)

public:
	CUIManager();
	virtual ~CUIManager() = default;



public:
	// For.Loading
	void Set_Loading();
	void Start_Loading();
	void End_Loading();

	// For.CutScreen
	void On_CutScreen();
	void Off_CutScreen();

	void Tick(_float TimeDelta);
	void LateTick(_float TimeDelta);

private:
	class CLoading* m_pLoading = nullptr;
	class CCutScreen* m_pCutScreen = nullptr;


public:
	virtual void Free() override;
};

END