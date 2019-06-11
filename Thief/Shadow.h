#pragma once
#include "GameObject.h"

class Shadow : public GameObject
{
public:
	Shadow(const char* filename);
	
	// sets if the shadow is visible
	void setVisible(bool vis);
	// returns the visible status
	bool getVisible() { return m_visible; }

	// sets the matrix of the object to be identical to another
	void setTransform(const Matrix3& other);

private:
	// determines if the shadow is drawn or not
	bool m_visible;
};