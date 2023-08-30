// VertexShader.hlsl
//
//
//

struct VS_Input {
    float4 pos : POSITION;
    float2 uv : TEXCOORD;
};

struct PS_Output {
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD;
};

PS_Output VS_Main(VS_Input vertices)
{
    PS_Output psOut = (PS_Output)0;

    psOut.pos = vertices.pos;
    psOut.uv = vertices.uv;

    return psOut;
}