#pragma once

namespace oglwork
{

struct buffer_trait
{};
struct texture_trait
{};
struct vao_trait
{};

template<typename Trait>
class OGLResource
{
public:
	OGLResource()
		: m_Counter(nullptr)
		, m_Object(0)
	{}

	~OGLResource()
	{
		Reset();
	}

	OGLResource(const OGLResource& other)
		: m_Counter(other.m_Counter)
		, m_Object(other.m_Object)
	{
		++(*m_Counter);
	}

	OGLResource& operator=(const OGLResource& other)
	{
		if (this != &other)
		{
			Reset();
			m_Counter = other.m_Counter;
			m_Object = other.m_Object;
			++(*m_Counter);
		}

		return *this;
	}

	OGLResource(OGLResource&& other)
		: m_Counter(other.m_Counter)
		, m_Object(other.m_Object)
	{
		other.m_Counter = nullptr;
		other.m_Object = 0;
	}

	OGLResource& operator=(OGLResource&& other)
	{
		if (this != &other)
		{
			Reset();
			std::swap(m_Counter, other.m_Counter);
			std::swap(m_Object, other.m_Object);
		}

		return *this;
	}
	
	GLuint Get() const
	{
		return m_Object;
	}

	void Generate()
	{
		m_Counter = new unsigned;
		Gen(1, &m_Object);
		*m_Counter = 1;
	}

	bool HasResource() const
	{
		return !!m_Object;
	}

	void Reset(GLuint object = 0)
	{
		if (m_Counter)
		{
			if (--(*m_Counter) == 0)
			{
				delete m_Counter;
				Delete(1, &m_Object);
			}
			m_Counter = nullptr;
			m_Object = 0;
		}

		if (object)
		{
			m_Counter = new unsigned;
			m_Object = object;
			*m_Counter = 1;
		}
	}

private:
	friend void SetResourceFunctionPointers();

	unsigned* m_Counter;
	GLuint m_Object;

	static APP_EXPORTED_SYMBOL void(__stdcall* Gen)(GLsizei, GLuint*);
	static APP_EXPORTED_SYMBOL void(__stdcall* Delete)(GLsizei, const GLuint*);
};

void SetResourceFunctionPointers();

}