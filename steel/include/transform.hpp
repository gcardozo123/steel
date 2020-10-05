#pragma once

#include "actor_component.hpp"
#include "vector2.hpp"

namespace Steel
{
	class Transform : public ActorComponent
	{
	private:
		Vector2 position;
		Vector2 scale;
		Vector2 size;			//current size
		Vector2 original_size;	//size of the texture on the file system
		Vector2 pivot;			// (0, 0) = top left, (1, 1) = bottom right
		//TODO: Transform parent;
		double rotation;

		void _SetSize(double width, double height);
		void _SetPosition(double x, double y);
		void _SetScale(double x, double y);

	public:
		Transform(WeakActorPtr owner=WeakActorPtr())
			: 
			ActorComponent(ActorComponentId(typeid(this)), owner),
			scale(1.0, 1.0),
			rotation(0.0),
			pivot(0.5, 0.5)
		{}
		
		Vector2 GetPosition() { return position; }
		Vector2 GetScale() { return scale; }
		Vector2 GetSize() { return size; }

		void SetScale(double value);
		void SetScale(const Vector2 &value);
		void SetScale(double x, double y);
		
		void SetPosition(const Vector2 &value);
		void SetPosition(double x, double y);

		void SetSize(double width, double height);
		void SetSize(const Vector2 &value);

		//TODO original_size should be auto updated once a texture is found
		void SetOriginalSize(const Vector2 &value);

	};
}