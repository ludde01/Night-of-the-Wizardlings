#include <Pch/Pch.h>
#include "PlayState.h"
// TODO move to mesh
#include <Loader/BGLoader.h>


PlayState::PlayState()
{
	m_shaderMap = m_shaderMap->getInstance();
	m_shaderMap->createShader("Basic_Forward", "VertexShader.vs", "FragShader.fs");


	// TODO move to mesh and file filepath
	m_object = GameObject("Character");
	m_object.loadMesh("TestScene.mesh");

	/*
	BGLoader tempLoader;
	tempLoader.LoadMesh(MESHPATH + "WalkingTest.mesh");

	m_mesh.setUpMesh(tempLoader.GetVertices(0),
		tempLoader.GetVertexCount(0),
		tempLoader.GetFaces(0),
		tempLoader.GetFaceCount(0));
	m_mesh.setUpBuffers();

	Material tempMaterial;
	tempMaterial = tempLoader.GetMaterial(0);	
	MaterialMap::getInstance()->createMaterial((std::string)tempLoader.GetMaterial(0).name, tempMaterial);
	tempLoader.Unload();*/


	m_renderer = m_renderer->getInstance();

}

PlayState::~PlayState()
{
	MaterialMap::getInstance()->destroy();
}

void PlayState::update(float dt)
{
	m_renderer->update(dt);
}

void PlayState::render()
{
	m_object.bindMaterialToShader("Basic_Forward");
	Renderer::getInstance()->render(m_object.getMesh()->getBuffers(), m_object.getMesh()->getPos());

}
