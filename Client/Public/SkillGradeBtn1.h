#pragma once
#include "UI.h"

BEGIN(Client)
class CSkillGradeBtn1 final : public  CUI
{
private:
	CSkillGradeBtn1(LPDIRECT3DDEVICE9 pGraphic_Device);
	CSkillGradeBtn1(const CSkillGradeBtn1& rhs);
	virtual ~CSkillGradeBtn1() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;
	virtual HRESULT Render() override;

public:
	void Change_Texture();

public:
	static CSkillGradeBtn1* Create(LPDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone(void* pArg);
	virtual void Free() override;

};
END

