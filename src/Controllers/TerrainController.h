#ifndef TERRAINCONTROLLER_H
#define TERRAINCONTROLLER_H

#include "../UI/TerrainUI.h"
#include "../Generators/TerrainGenerator.h"
#include "GeneratorController.h"

class TerrainUI;

class TerrainController : public GeneratorController {
public:
    TerrainController(Renderer* renderer);
    ~TerrainController() override = default;

    void Generate() override;
    void DisplayUI() override;
    void Update() override;
    void RandomizeSeed() override;
    IGeneratorStrategy& getGenerator() override;

private:
    TerrainGenerator generator;
    TerrainUI* terrainUI;

    void UpdateParameters() override;

};

#endif