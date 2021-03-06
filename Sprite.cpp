#include "Sprite.h"

Sprite::Sprite(){
	m_sourceRect = { 0.0f, 0.0f, 1.0f, 1.0f };
	m_rIds.m_topoID = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
	m_origin = m_pos = { 0.0f,	0.0f, 0.0f };
	m_dim = { 0.0f, 1.0f, 1.0f, 0.0f };
	m_centered = false;
	m_sprWH = { 0.5f, 0.5 };

	
}

void Sprite::SetDimensions(float x, float y) {

	
	m_sprWH = { x,y };
	m_origin = { 0.0f,	0.0f, 0.0f };
	m_centered = true;

}


XMFLOAT2 Sprite::GetSprWH() {
	return m_sprWH;
}

void Sprite::SetAbsolute(XMFLOAT4 a){
	m_dim = a;
	m_centered = false;
}

void Sprite::Create(){

	m_zd = 0.0f;
	VertexPU verts[4];

	if (m_centered) {

		verts[0] = { XMFLOAT3(-m_sprWH.x, m_sprWH.y, m_zd),			XMFLOAT2(m_sourceRect.x	, m_sourceRect.y) };
		verts[1] = { XMFLOAT3(m_sprWH.x, m_sprWH.y, m_zd),			XMFLOAT2(m_sourceRect.x + m_sourceRect.z, m_sourceRect.y) };
		verts[2] = { XMFLOAT3(-m_sprWH.x, -m_sprWH.y, m_zd),			XMFLOAT2(m_sourceRect.x	, m_sourceRect.y + m_sourceRect.w) };
		verts[3] = { XMFLOAT3(m_sprWH.x, -m_sprWH.y, m_zd),		XMFLOAT2(m_sourceRect.x + m_sourceRect.z, m_sourceRect.y + m_sourceRect.w) };
	}
	else {

		verts[0] = { XMFLOAT3(m_dim.x, m_dim.y, m_zd), XMFLOAT2(m_sourceRect.x, m_sourceRect.y) };
		verts[1] = { XMFLOAT3(m_dim.z, m_dim.y, m_zd),		XMFLOAT2(m_sourceRect.x + m_sourceRect.z, m_sourceRect.y) };
		verts[2] = { XMFLOAT3(m_dim.x, m_dim.w, m_zd),		XMFLOAT2(m_sourceRect.x	, m_sourceRect.y + m_sourceRect.w) };
		verts[3] = { XMFLOAT3(m_dim.z, m_dim.w, m_zd),		XMFLOAT2(m_sourceRect.x + m_sourceRect.z, m_sourceRect.y + m_sourceRect.w) };

	}


	m_numElements = ARRAYSIZE(verts);

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));

	if (m_isAnimated) {


		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;


		
		
	}
	else {

		bd.Usage = D3D11_USAGE_DEFAULT;

	}

	bd.ByteWidth = sizeof(VertexPU) * m_numElements;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	InitData.pSysMem = verts;
	gDevice->CreateBuffer(&bd, &InitData, &m_vertexBuffer);


}

void Sprite::Draw(){


	SetResources();

	XMMATRIX tmpWorldMatrix = XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
	gContext->UpdateSubresource(gcbPerMesh.Get(), 0, 0, &tmpWorldMatrix, 0, 0);
	gContext->Draw(m_numElements, 0);




}

void Sprite::Draw(XMFLOAT3 p) {


	SetResources();

	XMMATRIX tmpWorldMatrix = XMMatrixTranslation(p.x, p.y, p.z);
	gContext->UpdateSubresource(gcbPerMesh.Get(), 0, 0, &tmpWorldMatrix, 0, 0);
	gContext->Draw(m_numElements, 0);




}

void Sprite::MovePos(XMFLOAT3 p){
	m_pos.x += p.x;
	m_pos.y += p.y;
	m_pos.z += p.z;
}

void Sprite::SetPos(XMFLOAT3 p){
	m_pos = { p.x, p.y, p.z };
}

XMFLOAT3 Sprite::GetPos(){
	return m_pos;
}

void Sprite::AssignResources(UINT texID, UINT vsID, UINT psID){

	m_rIds.m_textureID = texID;
	m_rIds.m_vsID = vsID;
	m_rIds.m_psID = psID;

}

void Sprite::SetSourceRect(int i){
	m_sourceRect = gDat.GetTexture(m_rIds.m_textureID)->GetSourceRectIndex(i);
	m_texCoordChanged = true;

}

void Sprite::SetResources(){

	gDat.SetResources(m_rIds);
	
	if (m_texCoordChanged) {
		UpdateVertexBuffer();
		m_texCoordChanged = false;
	}

	UINT stride = sizeof(VertexPU);
	UINT offset = 0;

	gContext->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);


}

void Sprite::UpdateVertexBuffer() {

	m_zd = 0.0f;
	VertexPU verts[4];

	if (m_centered) {

		verts[0] = { XMFLOAT3(-m_sprWH.x, m_sprWH.y, m_zd),			XMFLOAT2(m_sourceRect.x	, m_sourceRect.y) };
		verts[1] = { XMFLOAT3(m_sprWH.x, m_sprWH.y, m_zd),			XMFLOAT2(m_sourceRect.x + m_sourceRect.z, m_sourceRect.y) };
		verts[2] = { XMFLOAT3(-m_sprWH.x, -m_sprWH.y, m_zd),			XMFLOAT2(m_sourceRect.x	, m_sourceRect.y + m_sourceRect.w) };
		verts[3] = { XMFLOAT3(m_sprWH.x, -m_sprWH.y, m_zd),		XMFLOAT2(m_sourceRect.x + m_sourceRect.z, m_sourceRect.y + m_sourceRect.w) };
	}
	else {

		verts[0] = { XMFLOAT3(m_dim.x, m_dim.y, m_zd),		XMFLOAT2(m_sourceRect.x, m_sourceRect.y) };
		verts[1] = { XMFLOAT3(m_dim.z, m_dim.y, m_zd),		XMFLOAT2(m_sourceRect.x + m_sourceRect.z, m_sourceRect.y) };
		verts[2] = { XMFLOAT3(m_dim.x, m_dim.w, m_zd),		XMFLOAT2(m_sourceRect.x	, m_sourceRect.y + m_sourceRect.w) };
		verts[3] = { XMFLOAT3(m_dim.z, m_dim.w, m_zd),		XMFLOAT2(m_sourceRect.x + m_sourceRect.z, m_sourceRect.y + m_sourceRect.w) };

	}

	m_numElements = ARRAYSIZE(verts);

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	gContext->Map(m_vertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	memcpy(mappedResource.pData, verts, sizeof(VertexPU) * m_numElements);
	gContext->Unmap(m_vertexBuffer.Get(), 0);


}


void Sprite::Update(double deltaTime) {



}