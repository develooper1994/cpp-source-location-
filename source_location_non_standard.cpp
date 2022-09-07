#include <iostream>
#include <cstdint>

namespace sourceLocationModern {
struct sourceLocation {
public:
#if not defined(__apple_build_version__) and defined(__clang__) and (__clang_major__ >= 9)
    static constexpr sourceLocation current(const char* filename = __builtin_FILE(),
        const char* functionname = __builtin_FUNCTION(),
        const uint_least32_t linenumber = __builtin_LINE(),
        const uint_least32_t coloffset = __builtin_COLUMN()) noexcept
	{
        return sourceLocation(filename, functionname, linenumber, coloffset);
    }	
#elif defined(__GNUC__) and (__GNUC__ > 4 or (__GNUC__ == 4 and __GNUC_MINOR__ >= 8))
    static constexpr sourceLocation current(const char* filename = __builtin_FILE(),
        const char* functionname = __builtin_FUNCTION(),
        const uint_least32_t linenumber = __builtin_LINE(),
        const uint_least32_t coloffset = 0) noexcept
	{
        return sourceLocation(filename, functionname, linenumber, coloffset);
    }
#else
    static constexpr sourceLocation current(const char* filename = "notsupported",
        const char* functionname = "notsupported",
        const uint_least32_t linenumber = 0,
        const uint_least32_t coloffset = 0) noexcept
    {
        return sourceLocation(filename, functionname, linenumber, coloffset);
    }
#endif

    sourceLocation(const sourceLocation&) = default;
    sourceLocation(sourceLocation&&) = default;

    constexpr const char* file_name() const noexcept{
        return filename;
    }

    constexpr const char* function_name() const noexcept{
        return functionname;
    }

    constexpr uint_least32_t line() const noexcept{
        return linenumber;
    }

    constexpr std::uint_least32_t column() const noexcept{
        return coloffset;
    }

private:
    constexpr sourceLocation(const char* filename, const char* functionname, const uint_least32_t linenumber,
        const uint_least32_t coloffset) noexcept
        : filename(filename)
        , functionname(functionname)
        , linenumber(linenumber)
        , coloffset(coloffset)
    {
    }

    const char* filename;
    const char* functionname;
    const std::uint_least32_t linenumber;
    const std::uint_least32_t coloffset;
};
} // namespace sourceLocationModern

/*
namespace sourceLocation_legacy {
struct sourceLocation {
public:
#if not defined(__apple_build_version__) and defined(__clang__) and (__clang_major__ >= 9)
    inline static const sourceLocation current(const char* filename = __builtin_FILE(),
        const char* functionname = __builtin_FUNCTION(),
        const uint_least32_t linenumber = __builtin_LINE(),
        const uint_least32_t coloffset = __builtin_COLUMN())
#elif defined(__GNUC__) and (__GNUC__ > 4 or (__GNUC__ == 4 and __GNUC_MINOR__ >= 8))
    inline static const sourceLocation current(const char* filename = __builtin_FILE(),
        const char* functionname = __builtin_FUNCTION(),
        const uint_least32_t linenumber = __builtin_LINE(),
        const uint_least32_t coloffset = 0)
#else
    inline static const sourceLocation current(const char* filename = "notsupported",
        const char* functionname = "notsupported",
        const uint_least32_t linenumber = 0,
        const uint_least32_t coloffset = 0)
#endif
    {
        return sourceLocation(filename, functionname, linenumber, coloffset);
    }

    sourceLocation(const sourceLocation&)
	{
		
	}
    sourceLocation(sourceLocation&&) = default;

    inline const const char* file_name() const
    {
        return filename;
    }

    inline const const char* function_name() const
    {
        return functionname;
    }

    inline const uint_least32_t line() const
    {
        return linenumber;
    }

    inline const std::uint_least32_t column() const
    {
        return coloffset;
    }

private:
    inline const sourceLocation(const char* filename, const char* functionname, const uint_least32_t linenumber,
        const uint_least32_t coloffset)
        : filename(filename)
        , functionname(functionname)
        , linenumber(linenumber)
        , coloffset(coloffset)
    {}

    const char* filename;
    const char* functionname;
    const std::uint_least32_t linenumber;
    const std::uint_least32_t coloffset;
};
} // namespace sourceLocation_legacy
*/



void subrotune1(){
	auto location = sourceLocationModern::sourceLocation::current();
	std::cout << location.file_name() << ":" << location.line() << ":"
			  << location.column() << ":" << location.function_name() << ": "
			  << "Hello World!" << std::endl;
}

void subrotune2(){
	auto location = sourceLocationModern::sourceLocation::current();
	std::cout << location.file_name() << ":" << location.line() << ":"
			  << location.column() << ":" << location.function_name() << ": "
			  << "Hello World!" << std::endl;
}

int main(){
/*
	root@<user>-lp-59:/mnt/c/Users/<user>/Desktop# g++ source_location_non_standard.cpp -o source_location_non_standard
	root@<user>-lp-59:/mnt/c/Users/<user>/Desktop# ./source_location_non_standard
	source_location_non_standard.cpp:137:0:subrotune1: Hello World!
	source_location_non_standard.cpp:144:0:subrotune2: Hello World!
*/

	subrotune1();
	subrotune2();
}