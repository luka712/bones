#include "utils.h"

F32 Bones::Utils::ConvertU8ToF32(U8 first, U8 second, U8 third, U8 fourth)
{
	F32_U32 u(first);
	u.m_asU32 |= second << 8;
	u.m_asU32 |= third << 16;
	u.m_asU32 |= fourth << 24;
	return u.m_asF32;
}
