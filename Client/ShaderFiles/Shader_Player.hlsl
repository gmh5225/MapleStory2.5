
float4x4		g_WorldMatrix, g_ViewMatrix, g_ProjMatrix;
texture			g_Texture;

float4			g_vCamPosition;
float4			g_vPlayerColor;
float			g_fFogRange = 5.f;

sampler DefaultSampler = sampler_state
{
	Texture = g_Texture;
	minfilter = linear;
	magfilter = linear;
	mipfilter = linear;
};

texture			g_Texture1;

sampler DefaultSampler1 = sampler_state
{
	Texture = g_Texture1;
	minfilter = linear;
	magfilter = linear;
	mipfilter = linear;
};



struct VS_IN
{
	float3		vPosition : POSITION;
	float2		vTexUV : TEXCOORD0;
};

struct VS_OUT
{
	float4		vPosition : POSITION;
	float2		vTexUV : TEXCOORD0;
	float4		vWorldPos : TEXCOORD1;
};

/* ���ؽ� ���̴�. */
/* ������ �⺻���� ��ȯ�۾��� �����Ѵ�. */
/* ���������� ������ �����Ѵ�. */
VS_OUT VS_MAIN(VS_IN In)
{
	VS_OUT		Out;

	/* ������ ��ġ�� ��������� ���Ѵ�. */
	/* ������ ��ġ�� ������� ���Ѵ�. */
	/* ������ ��ġ�� ��������� ���Ѵ�. */

	matrix		matWV, matWVP;

	matWV = mul(g_WorldMatrix, g_ViewMatrix);
	matWVP = mul(matWV, g_ProjMatrix);

	Out.vPosition = mul(float4(In.vPosition, 1.f), matWVP);
	Out.vTexUV = In.vTexUV;
	Out.vWorldPos = mul(float4(In.vPosition, 1.f), g_WorldMatrix);

	return Out;
}

/* w.������ ������. */
/* ����Ʈ ��ȯ. */
/* �����Ͷ����� (�ȼ��� �����Ѵ�.) */

struct PS_IN
{
	float4		vPosition : POSITION;
	float2		vTexUV : TEXCOORD0;
	float4		vWorldPos : TEXCOORD1;

};

/* �ȼ� ���̴�. */
/* �ȼ��� ���� ���������� �����Ѵ�. */
struct PS_OUT
{
	vector		vColor : COLOR0;
};

PS_OUT PS_MAIN(PS_IN In)
{
	PS_OUT		Out;

	vector		vColor = tex2D(DefaultSampler, In.vTexUV);


	Out.vColor = vColor * g_vPlayerColor;


	return Out;
}

technique DefaultTecnique
{
	pass Default
	{
		VertexShader = compile vs_3_0 VS_MAIN();
		PixelShader = compile ps_3_0 PS_MAIN();
	}

	/*pass Blending
	{
	VertexShader = compile vs_3_0 VS_MAIN();
	PixelShader = compile ps_3_0 PS_MAIN_BLENDING();
	}*/
}
