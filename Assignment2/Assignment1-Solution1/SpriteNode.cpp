#include "SpriteNode.h"
#include "Game.hpp"

SpriteNode::SpriteNode(State* state,std::string spriteIMG)
	: Entity(state)
	, mSprite(spriteIMG)
{
}

void SpriteNode::drawCurrent() const
{
	/*renderer->World = getTransform();
	renderer->NumFramesDirty++;*/

	UINT objCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(ObjectConstants));
	UINT matCBByteSize = d3dUtil::CalcConstantBufferByteSize(sizeof(MaterialConstants));

	auto objectCB = state->getContext()->game->mCurrFrameResource->ObjectCB->Resource();
	auto matCB = state->getContext()->game->mCurrFrameResource->MaterialCB->Resource();

	if (renderer != nullptr)
	{
		state->getContext()->game->getCmdList()->IASetVertexBuffers(0, 1, &renderer->Geo->VertexBufferView());
		state->getContext()->game->getCmdList()->IASetIndexBuffer(&renderer->Geo->IndexBufferView());
		state->getContext()->game->getCmdList()->IASetPrimitiveTopology(renderer->PrimitiveType);

		CD3DX12_GPU_DESCRIPTOR_HANDLE tex(state->getContext()->game->mSrvDescriptorHeap->GetGPUDescriptorHandleForHeapStart());
		tex.Offset(renderer->Mat->DiffuseSrvHeapIndex, state->getContext()->game->mCbvSrvDescriptorSize);

		D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = objectCB->GetGPUVirtualAddress() + renderer->ObjCBIndex * objCBByteSize;
		D3D12_GPU_VIRTUAL_ADDRESS matCBAddress = matCB->GetGPUVirtualAddress() + renderer->Mat->MatCBIndex * matCBByteSize;

		state->getContext()->game->getCmdList()->SetGraphicsRootDescriptorTable(0, tex);
		state->getContext()->game->getCmdList()->SetGraphicsRootConstantBufferView(1, objCBAddress);
		state->getContext()->game->getCmdList()->SetGraphicsRootConstantBufferView(3, matCBAddress);

		state->getContext()->game->getCmdList()->DrawIndexedInstanced(renderer->IndexCount, 1, renderer->StartIndexLocation, renderer->BaseVertexLocation, 0);
	}

}

void SpriteNode::buildCurrent()
{
	auto render = std::make_unique<RenderItem>();
	renderer = render.get();
	renderer->World = getTransform();
	XMStoreFloat4x4(&renderer->TexTransform, XMMatrixScaling(50.0f, 50.0f, 1.0f));
	renderer->ObjCBIndex = (UINT)state->getContext()->game->getRenderItems().size();
	renderer->Mat = state->getContext()->game->getMaterials()["Desert"].get();
	renderer->Geo = state->getContext()->game->getGeometries()["boxGeo"].get();
	renderer->PrimitiveType = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	renderer->IndexCount = renderer->Geo->DrawArgs["box"].IndexCount;
	renderer->StartIndexLocation = renderer->Geo->DrawArgs["box"].StartIndexLocation;
	renderer->BaseVertexLocation = renderer->Geo->DrawArgs["box"].BaseVertexLocation;
	//mSpriteNodeRitem = render.get();
	state->getContext()->game->getRenderItems().push_back(std::move(render));
}
