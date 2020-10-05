#pragma once


namespace Steel
{

/*Represents a game scene, should be extended and set with `game->SetScene(scene);`*/
class Scene
{
private:
	

public:

    Scene() {}
    virtual ~Scene() {}
	
    /*Called before any other method to do any necessary initialization*/
    virtual void Init() {}
    /*Called after `Init`, should be used to load all assets required by the scene*/
    virtual void PreLoadAssets() {}
    /*Called at each frame to update the logic and movement of game objects*/
    virtual void Update(double dt) {}
    /*Called when the scene is destroyed*/
    virtual void OnDestroy() {}


};

}