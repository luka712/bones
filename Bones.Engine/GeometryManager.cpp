#include "GeometryManager.hpp"
#include "QuadScreenGeometry.hpp"
#include "EnvironmentMapGeometry.hpp"
#include "BoxGeometry.hpp"
#include "QuadGeometry.hpp"
#include "Constants.hpp"

using Bones::Managers::GeometryManager;

QuadScreenGeometry* GeometryManager::m_quadScreenGeometry = nullptr;
EnvironmentMapGeometry* GeometryManager::m_environmentMapGeometry = nullptr;
BoxGeometry* GeometryManager::m_boxGeometry = nullptr;
QuadGeometry* GeometryManager::m_quadGeometry = nullptr;

QuadScreenGeometry* GeometryManager::GetOrCreateQuadScreenGeometry()
{
	if (m_quadScreenGeometry == nullptr)
	{
		m_quadScreenGeometry = new QuadScreenGeometry();
		m_quadScreenGeometry->InitializeBuffers();
	}

	return m_quadScreenGeometry;
}

EnvironmentMapGeometry* GeometryManager::GetOrCreateEnvironmentMapGeometry()
{
	if (m_environmentMapGeometry == nullptr)
	{
		m_environmentMapGeometry = new EnvironmentMapGeometry();
		m_environmentMapGeometry->InitializeBuffers();
	}

	return m_environmentMapGeometry;
}

BoxGeometry* GeometryManager::GetOrCreateBoxGeometry()
{
	if (m_boxGeometry == nullptr)
	{
		m_boxGeometry = new BoxGeometry();
		m_boxGeometry->InitializeBuffers();
	}

	return m_boxGeometry;
}

QuadGeometry* Bones::Managers::GeometryManager::GetOrCreateQuadGeometry()
{
	if (m_quadGeometry == nullptr)
	{
		m_quadGeometry = new QuadGeometry();
		m_quadGeometry->InitializeBuffers();
	}

	return m_quadGeometry;
}

void GeometryManager::Delete()
{
	DELETE_PTR(m_quadScreenGeometry);
	DELETE_PTR(m_environmentMapGeometry);
	DELETE_PTR(m_boxGeometry);
	DELETE_PTR(m_quadGeometry);
}
