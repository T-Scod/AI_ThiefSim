#include "Shadow.h"

Shadow::Shadow(const char * filename)
{
	m_texture = new aie::Texture(filename);
	m_visible = false;
}

// sets if the shadow is visible
void Shadow::setVisible(bool vis)
{
	m_visible = vis;
}

// sets the matrix of the object to be identical to another
void Shadow::setTransform(const Matrix3 & other)
{
	m_obj = other;
}