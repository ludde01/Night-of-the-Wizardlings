#ifndef _DSTRGENERATOR_h
#define _DSTRGENERATOR_h
//#include <Pch/Pch.h>
#include <GameObject/DestructibleObject.h>

enum DSTRType
{
	DSTR1,
	DSTR2,
	DSTR3,
	DSTR4
};

class DstrGenerator
{
public:
	DstrGenerator();
	~DstrGenerator();

	void initPoints(glm::vec2 position = glm::vec2());
	void setBreakSettings(DSTRType type, float breakPoints, float breakAreaRadius, float gravity);
	void setBreakPoints(float breakPoints);
	void setBreakRadius(float breakAreaRadius);
	void setBreakGravity(float gravity);
	void setBreakType(DSTRType type);

	void offsetPoints(glm::vec2 position = glm::vec2());

	void update();

	void Destroy(DestructibleObject* object, glm::vec2 hitPosition = glm::vec3(0.0f), glm::vec3 hitDirection = glm::vec3(0.0f));

	void meshFromClipped(const float& scale, const std::vector<glm::vec2>& polygon, glm::vec3& normal);

	const unsigned int seedRand(int seed = -1);
	const unsigned int getSeed(unsigned int seed) const { return m_seed; }

	void Clear();

private:
	// Tools
	VoroniCalculator m_voroniCalc;
	VoroniDiagram m_diagram;
	VoroniClipper m_clipper;
	std::vector<glm::vec2> m_randomPoints;
	int m_seed;	// Seed for randomizer, used for network consistency

	// Allocation
	std::vector<glm::vec2> m_clipped;	// Cleared in m_clipper
	std::vector<Vertex> m_newVertices;	// Cleared in mesh from clipped
	std::vector<Face> m_newFace;		// Cleared in mesh from clipped
	int count = 0;
	int vi = 0;
	int uvi = 0;
	int ni = 0;
	int ti = 0;
	int mi = 1;


	// TODO: init these correctly
	DSTRType m_dstType = DSTR1;
	unsigned int m_breakPoints;
	float m_breakAreaRadius;
	float m_timeSinceLastDestruction = 0.0f;
	btVector3 m_initGravity;
};

#endif
