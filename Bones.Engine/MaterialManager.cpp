#include "MaterialManager.hpp"
#include "MaterialShader.hpp"
#include "StandardMaterial.hpp"
#include "MaterialStructs.hpp"
#include "MaterialShaderStructs.hpp"
#include "DELETE_MACROS.h"

using Bones::Managers::MaterialManager;

map<string, StandardMaterial*> MaterialManager::m_standardMaterialsCache = map<string, StandardMaterial*>();

//StandardMaterial& MaterialManager::operator[](string name)
//{
//    return *m_standardMaterialsCache.at(name);
//}

StandardMaterial* MaterialManager::CreateStandardMaterial(const string& name, standard_material_options opts)
{
    map<string, StandardMaterial*>::iterator it = m_standardMaterialsCache.find(name);
    if (it != m_standardMaterialsCache.end())
    {
        LOG_FORMAT("Overwriting standard material with name %s. Material with same name was already added.", name.c_str());
    }

    StandardMaterial* ptr = new StandardMaterial(name, opts);
    ptr->Initialize();
    m_standardMaterialsCache.emplace(name, ptr);
    return ptr;
}

StandardMaterial* MaterialManager::CreateStandardMaterial(const string& name,  StandardMaterialOptions opts)
{
    return MaterialManager::CreateStandardMaterial(name, opts.ConvertToBits());
}

bool MaterialManager::DeleteStandardMaterial(const string& name)
{
    map<string, StandardMaterial*>::iterator it = m_standardMaterialsCache.find(name);
    if (it == m_standardMaterialsCache.end())
    {
        LOG_FORMAT("Cannot remove %s from material shaders. Resource does not exist.", name.c_str());
        return false;
    }

    delete it->second;
    m_standardMaterialsCache.erase(name);
    return true;
}

void MaterialManager::Delete()
{
    DELETE_MAP(m_standardMaterialsCache);
}
