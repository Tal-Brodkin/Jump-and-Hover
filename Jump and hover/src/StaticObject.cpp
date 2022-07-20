#include "StaticObject.h"







bool StaticObject::isToDelete() const
{
    return m_delete;
}



void StaticObject::deleteObject()
{
    m_delete = true;
}
