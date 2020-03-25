#ifndef PONG_IENTITY_HPP
#define PONG_IENTITY_HPP

class IEntity
{
public:
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual ~IEntity() = default;
};

#endif
