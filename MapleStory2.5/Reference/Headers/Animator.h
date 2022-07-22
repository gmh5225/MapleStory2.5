#pragma once

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CAnimator final : public CComponent
{
private:
	CAnimator();
	CAnimator(LPDIRECT3DDEVICE9 pGraphic_Device);
	CAnimator(const CAnimator& rhs);
	virtual ~CAnimator() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg) override;

public:
	HRESULT Create_Texture(_uint iLevelIndex, const _tchar * pPrototypeTag, void * pArg);
	HRESULT Bind_Texture(const _tchar* pTexTag, _uint iCount);
	HRESULT Play_Loof(const _tchar * pTexTag, _float delay, _float fTimeDelta);

public:
	static CAnimator* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CAnimator* Clone(void* pAvg) override;
	virtual void Free() override;

private:
	class CTexture* Find_Component(const _tchar* pComponentTag);
	
private:
	map<const _tchar*, class CTexture*> m_AniTexture;
	typedef map<const _tchar*, CTexture*> ANITEXTURE;

	_float m_fAnimPerTime;
	_uint m_iAnimCount;
};

END

