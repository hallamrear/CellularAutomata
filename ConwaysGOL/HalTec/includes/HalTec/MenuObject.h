#pragma once
#include "Rigidbody.h"

class MenuObject :
    public Rigidbody
{
public:
    MenuObject(std::string texture_path, Transform transform);
    ~MenuObject() override;

    void			Update(double deltaTime) override;
    void			Render() override;
};

