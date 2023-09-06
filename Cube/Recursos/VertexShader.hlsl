//VertexSahder.hlsl
//
//

//Constantes de buffers matrices
cbuffer cbChangesEveryFrame : register(b0) {
    matrix worldMatrix;
};
cbuffer cbNeverChanges : register(b1) {
    matrix viewMatrix;
};
cbuffer cbChangeOnResize : register(b2) {
    matrix projMatrix;
};

struct VS_Input
{
    float4 pos : POSITION;
    float2 tex0 : TEXCOORD0;
};

struct PS_Input
{
    float4 pos : SV_POSITION;
    float2 tex0 : TEXCOORD0;
};

PS_Input VS_Main(VS_Input vertex)
{
    PS_Input vsOut = (PS_Input)0;

    // Dibujar vertices en base a matrices
    vsOut.pos = mul(vertex.pos, worldMatrix);
    vsOut.pos = mul(vsOut.pos, viewMatrix);
    vsOut.pos = mul(vsOut.pos, projMatrix);

    vsOut.tex0 = vertex.tex0;
    vsOut.tex0 = vertex.tex0;

    return vsOut;
}