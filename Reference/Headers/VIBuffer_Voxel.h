#pragma once

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CVIBuffer_Voxel final : public CVIBuffer
{
private:
	CVIBuffer_Voxel(LPDIRECT3DDEVICE9 pGraphic_Device);
	CVIBuffer_Voxel(const CVIBuffer_Voxel& rhs);
	virtual ~CVIBuffer_Voxel() = default;

public:
	virtual HRESULT Initialize_Prototype(vector<tagVertexColor>* pVoxelDatas);
	virtual HRESULT Initialize(void* pArg) override;

public:
	static CVIBuffer_Voxel* Create(LPDIRECT3DDEVICE9 pGraphic_Device, vector<tagVertexColor>* pVoxelDatas);
	virtual CComponent* Clone(void* pArg);
	virtual void Free() override;
};

END