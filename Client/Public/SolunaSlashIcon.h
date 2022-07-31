#pragma once
#include "UI.h"

BEGIN(Client)
class CSolunaSlashIcon final : public  CUI
{
private:
	CSolunaSlashIcon(LPDIRECT3DDEVICE9 pGraphic_Device);
	CSolunaSlashIcon(const CSolunaSlashIcon& rhs);
	virtual ~CSolunaSlashIcon() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	void Change_Texture();

public:
	static CSolunaSlashIcon* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;

private:
	_uint m_iSkillPoint;
	LPD3DXFONT m_NoticeFont;
};
END

