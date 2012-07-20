#include <set>
#include <utility>

#include <igloo/igloo_alt.h>

namespace igloo
{
	template<typename T1, typename T2>
	struct Stringizer< std::pair<T1, T2> >
	{
		static std::string
		ToString(const std::pair<T1, T2> &value)
		{
			std::ostringstream buf;
			buf << "("
				<< igloo::Stringize(value.first) << ", "
				<< igloo::Stringize(value.second)
				<< ")";
			return buf.str();
		}
	};

	template<typename T>
	struct Stringizer<std::set<T> > :
	        detail::SequentialContainerStringizer< std::set<T> >
	{
	};
}
