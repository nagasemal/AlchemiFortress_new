#include "MyModelShader.hlsli"

Texture2D MachineTexture: register(t1);
Texture2D NomalTexture: register(t2);

void AddSpecular(inout float4 color, float3 specular)
{
	color.rgb += specular * color.a;
}

float ComputeFogFactor(float4 position)
{
	// ���ɍs���قǍ�������
	return saturate(dot(position, float4(0.0f, -0.05f, 0.0f, 0.0f)));
}

// �t�H�O�̐ݒ�
void ApplyFog(inout float4 color, float fogFactor)
{
	color.rgb = lerp(color.rgb, FogColor * color.a, fogFactor);
}

// �������C�g�̐ݒ�
// �����x�N�g���Ɩ@���x�N�g�������p�ɋ߂��قǃ��C�g�̒l��傫������
float4 ApplyLimLight(float3 normal)
{
	// �����_
	float3 invEye = normalize(mul(WorldInverseTranspose, EyePosition));
	
	//�@�������C�g
	float rim = pow(1.0 - clamp(dot(invEye,normal), 0.0, 1.0), 5.0);

	float3 eyedif = normalize(Eyes.xyz - EyePosition);


	// �����x�N�g���ƃ��C�g�x�N�g�����l���ɓ����
	// pow = ���x��
	// max = 1.0 �ȏ�ɍs���Ȃ��悤�ɂ���
	float dotLE_1 = pow(max(dot(eyedif, normalize(LightDirection[0])), 1.0), 30.0);
	float dotLE_2 = pow(max(dot(eyedif, normalize(LightDirection[1])), 1.0), 30.0);
	float dotLE_3 = pow(max(dot(eyedif, normalize(LightDirection[2])), 1.0), 30.0);

	return lerp(0, LimLightColor, rim  * dotLE_1 * dotLE_2 * dotLE_3);
}



// �O���[�X�P�[����
float ChangeGray(float4 col)
{
	return col.r * 0.3f + col.g * 0.6f + col.b * 0.1f;
}

// �Z�s�A��
float4 ChangeSepia(float4 col)
{
	float g = ChangeGray(col);
	return float4(g * 1.44f, g * 0.99f, g * 0.57f, col.a);
}

float4 ApplyPointLight(float3 position, float3 lightPos, float power,float rage)
{
    // �����̕���
    float3 lightDirection = position - lightPos;
    
    // �����܂ł̋���
    float lightDistance = length(lightDirection) * rage;

    // ��������̋����̉e��
    float atten = saturate(1.0f / (lightDistance * lightDistance));
    
    return atten * power;
}

// �}�b�n�o���h�΍�
#define SHADOW_EPSILON 0.0005f

float4 main(PSInput input) : SV_TARGET0
{
    float texInput = (float)Texture.Sample(Sampler, input.TexCoord);

	// �e�N�X�`���擾
	float3 modelTexture = MachineTexture.Sample(Sampler, input.TexCoord).rgb;

	// ���C�g�̌v�Z
    input.Normal = normalize(input.Normal); 
	
	    // �}�E�X���ӂ̃|�C���g���C�g
    float4 pointLight_mouse = ApplyPointLight(input.Position.xyz, MousePosition.xyz, 1.0f, 1.0f);
   
    float4 pointLight_crystal = float4(0.0f, 0.0f, 0.0f, 1.0f);
	
    // �N���X�^���̎��ӂ𔭌�������
    for (int i = 0; i < 3; i++)
    {
        pointLight_crystal += ApplyPointLight(input.Position.xyz, CrystalPosition[i].xyz, 1.0f, 1.5f - cos(Time.w));
    }
	
	// �m�[�}���}�b�v�擾
	float3 nomalTex = NomalTexture.Sample(Sampler, input.TexCoord).rgb;

    float4 diff = pow(dot(nomalTex, input.Diffuse.rgb + pointLight_crystal.rgb + pointLight_mouse.rgb), 0.5f) + ApplyLimLight(input.Normal);

    float4 color = diff;

	// �c������
	input.Specular *= SpecularPower;

	// �X�y�L�����[��ݒ肷��
    AddSpecular(color, pow(clamp(dot(input.Specular, nomalTex), 0.0f, 1.0f), 2.0f));

	// ���X�ɐF��h�郋�[���摜)
	color.rgb *= PaintColor.rgb * step(texInput, 1 - Time.z);

    color += AddScreen(color, float4(0.1, 0.1, 0.0, 0.25f)) * pointLight_mouse;
   
    color += AddScreen(color, float4(0.2, 0.0, 0.2, 0.25f)) * pointLight_crystal;
	
	// ���Ԍo�߂ŏo��������(���[���摜)
	color.w = step(texInput, Time.x);
	
    color.w *= DiffuseColor.w;
	
    color.w *= PaintColor.w;

	return float4(color.xyz, color.w);
}