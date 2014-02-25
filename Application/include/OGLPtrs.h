#pragma once

namespace oglwork
{

struct buffer_trait
{
	static void Generate(GLuint* object)
	{
		glGenBuffers(1, object);
	}

	static void Delete(GLuint* object)
	{
		glDeleteBuffers(1, object);
	}
};

struct texture_trait
{
	static void Generate(GLuint* object)
	{
		glGenTextures(1, object);
	}

	static void Delete(GLuint* object)
	{
		glDeleteTextures(1, object);
	}
};

struct vao_trait
{
	static void Generate(GLuint* object)
	{
		glGenVertexArrays(1, object);
	}

	static void Delete(GLuint* object)
	{
		glDeleteVertexArrays(1, object);
	}
};

struct program_trait
{
	static void Generate(GLuint* object)
	{
		*object = glCreateProgram();
	}

	static void Delete(GLuint* object)
	{
		glDeleteProgram(*object);
	}
};

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
		Trait::Generate(&m_Object);
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
				Trait::Delete(&m_Object);
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
};

}