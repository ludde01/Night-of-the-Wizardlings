#include <Pch/Pch.h>
#include "HudObject.h"

/*	Position and size in world space	*/
HudObject::HudObject(const std::string& texturePath, const glm::vec2& position, const glm::vec2& scale)
{
	loadTexture(texturePath);
	setupBuffers();

	m_position = position;
	m_size = scale;
	
	// Re-do them to NDC coords
	m_position.x = (m_position.x / SCREEN_WIDTH) * 2 - 1;
	m_position.y = (m_position.y / SCREEN_HEIGHT) * 2 - 1;

	m_size.x /= SCREEN_WIDTH;
	m_size.y /= SCREEN_HEIGHT;

	m_alpha = 1.0f;

	updateModelMatrix();
}

HudObject::~HudObject()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
}

void HudObject::setPosition(const glm::vec3& position)
{
	m_position = position;
	updateModelMatrix();
}

void HudObject::setScale(const glm::vec3& scale)
{
	m_size = scale;
	updateModelMatrix();
}

void HudObject::setAlpha(const float& alpha)
{
	m_alpha = alpha;
}

const glm::mat4& HudObject::getModelMatrix() const
{
	return m_modelMatrix;
}

const GLuint& HudObject::getVAO() const
{
	return m_vao;
}

const GLuint& HudObject::getVBO() const
{
	return m_vbo;
}

const GLuint& HudObject::getTextureID() const
{
	return m_textureID;
}

const float& HudObject::getAlpha() const
{
	return m_alpha;
}

void HudObject::setupBuffers()
{
	// setup plane VAO
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	
	glBindVertexArray(m_vao);
	
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}

void HudObject::loadTexture(const std::string& texturePath)
{
	auto* tmap = HudTextureMap::getInstance();
	const GLuint* tID = tmap->getTextureID(texturePath);
	if (tID != nullptr) {
		m_textureID = *tID;
		return;
	}

	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	// load and generate the texture
	int width, height, nrChannels;
	unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, NULL);
	if (data)
	{
		GLenum format = {};

		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);

		glGenerateMipmap(GL_TEXTURE_2D);
		tmap->addTextureID(texturePath, m_textureID);
	}
	else
	{
		logError("(HudObject.cpp) Failed to load texture {0}", texturePath.c_str());
	}
	
	stbi_image_free(data);




}

void HudObject::updateModelMatrix()
{
	m_modelMatrix = glm::mat4(1.0f);
	m_modelMatrix = glm::translate(m_modelMatrix, glm::vec3(m_position, 1.0f));
	m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(m_size, 1.0f));
}