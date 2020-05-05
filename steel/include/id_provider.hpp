#pragma once

namespace Steel
{
	class IdProvider
	{
	private:
		static unsigned int current_id;
	
	public:
		static unsigned int New()
		{
			return current_id++;
		}
	};
}