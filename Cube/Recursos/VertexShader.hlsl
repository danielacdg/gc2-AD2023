//VertexSahder.hlsl
//
//

//Constantes de matrices


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
    PS_Input vsOut = (PS_Input) 0;

    // Dibujar vertices en base a matrices
    
    
    vsOut.pos = vertex.pos;
    vsOut.tex0 = vertex.tex0;

    return vsOut;
}