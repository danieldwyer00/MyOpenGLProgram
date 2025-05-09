#pragma once
#include <vector>
#include "Vertex.h"

static void Draw(const std::vector<DrawDetails>& details)
{
	for(const auto& d : details)
	{
		glBindVertexArray(d.vao);
		glDrawElements(GL_TRIANGLES, d.numElements, GL_UNSIGNED_INT, nullptr);
	}
	glBindVertexArray(0);
}