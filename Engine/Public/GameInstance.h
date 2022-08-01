#pragma once

#include "Timer_Manager.h"
#include "Graphic_Device.h"
#include "Input_Device.h"
#include "Level_Manager.h"
#include "Object_Manager.h"
#include "Component_Manager.h"
#include "Map_Manager.h"
#include "VIBuffer_Cube.h"
#include "Picking.h"
#include <iostream>
#include <random>

/* Ŭ���̾�Ʈ�� �����ֱ����� ���� ��ǥ���� Ŭ�����̴�. */
/* ���� �Ŵ���Ŭ�������� �ֿ��Լ��� Ŭ��� �����ش�.  */
/* �����ʱ�ȭ. */
/* ��������. */

BEGIN(Engine)

class ENGINE_DLL CGameInstance final : public CBase
{
	DECLARE_SINGLETON(CGameInstance)

private:
	CGameInstance();
	virtual ~CGameInstance() = default;

public: /* For.Engine */
	HRESULT Initialize_Engine(_uint iNumLevel, HINSTANCE hInst, const GRAPHICDESC& GraphicDesc, IDirect3DDevice9** pOut);
	void Tick_Engine(_float fTimeDelta);
	void Clear(_uint iLevelIndex);
	

public: /* For.Graphic_Device */
	void Render_Begin(void);
	void Render_End(HWND hWnd = 0);

public: /* For.Level_Manager */				
	HRESULT Open_Level(_uint iLevelIndex, class CLevel* pNewLevel);
	HRESULT Render_Level();

public: /* For.Object_Manager */
	HRESULT Add_Prototype(const _tchar* pPrototypeTag, class CGameObject* pPrototype);
	HRESULT Add_GameObjectToLayer(const _tchar* pPrototypeTag, _uint iLevelIndex, const _tchar* pLayerTag, void* pArg = nullptr);
	class CComponent* Get_ComponentPtr(_uint iLevelIndex, const _tchar* pLayerTag, const _tchar* pComponentTag, _uint iLayerIndex);
	class CGameObject* Get_ObjectPtr(_uint iLevelIndex, const _tchar* pLayerTag, _uint iLayerIndex);


public: /*For.Component_Manager*/
	HRESULT Add_Prototype(_uint iLevelIndex, const _tchar* pPrototypeTag, class CComponent* pPrototype);
	class CComponent* Clone_Component(_uint iLevelIndex, const _tchar* pPrototypeTag, void* pArg = nullptr);

public: /* for.Timer_Manager */
	_float Get_TimeDelta(const _tchar* pTimerTag);
	HRESULT Add_Timer(const _tchar* pTimerTag);
	HRESULT Update_Timer(const _tchar* pTimerTag);	

public: /* For.Input_Device */
	_char Get_DIKState(_uchar eKeyID);
	_char Get_DIMKeyState(DIMK eMouseKeyID);
	_long Get_DIMMoveState(DIMM eMouseMoveID);
	_bool Key_Down(_uchar eKeyID);
	_bool Key_Up(_uchar eKeyID);
	_bool Key_Pressing(_uchar eKeyID);
	_bool Mouse_Down(DIMK eMouseKeyID);
	_bool Mouse_Up(DIMK eMouseKeyID);
	_bool Mouse_Pressing(DIMK eMouseKeyID);


public:
	_uint Get_Random(_uint iStart, _uint iEnd);


public: /* For.Map_Manager */
	list<CMap_Manager::CUBEDATA>* ReadMap(const _tchar* pMapTag);
	list<CMap_Manager::MODELDESC>* ReadModel(const _tchar* pMapTag);
	list<_tchar*>* GetVoxelNames();

private:
	CGraphic_Device*				m_pGraphic_Device = nullptr;
	CInput_Device*					m_pInput_Device = nullptr;
	CLevel_Manager*					m_pLevel_Manager = nullptr;
	CObject_Manager*				m_pObject_Manager = nullptr;
	CComponent_Manager*				m_pComponent_Manager = nullptr;
	CTimer_Manager*					m_pTimer_Manager = nullptr;
	CMap_Manager*					m_pMap_Manager = nullptr;
	CPicking*						m_pPicking = nullptr;


public:
	static void Release_Engine();
	virtual void Free() override;
};

END