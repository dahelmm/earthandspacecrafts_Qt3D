#ifndef INITSYSTEM_H
#define INITSYSTEM_H

#include <Qt3DCore>
#include <Qt3DExtras>
#include <Qt3DRender>
#include "customcameracontroller.h"

class InitSystem
{

public:
    const double PI = 3.1416;
    const double gradToRad = 57.29577951;
    const double radToGrad = 0.0174533;
    double perigey;
    double apogey;
    double A;
    double B;
    QByteArray pointVertex;
    float *positions;

    //создание главной сущности
    Qt3DCore::QEntity *rootEntity;
    Qt3DExtras::Qt3DWindow view; //создание главного окна
    Qt3DCore::QTransform *rootTransform;

    //создание сущности космоса
    Qt3DCore::QEntity *universe; //сущность
    Qt3DExtras::QSphereMesh *universeSphere;//сфера
    //текстура космоса
    Qt3DExtras::QTextureMaterial *universeTextureMaterial;
    Qt3DRender::QTextureLoader *universeTextureLoader;
    Qt3DCore::QTransform *universeTransform;


    //создание Земли
    Qt3DCore::QEntity *earthEntity; //сущность
    Qt3DExtras::QSphereMesh *earthSphere; //сфера
    Qt3DRender::QTextureLoader *earthTexture; //загрузчик текстур
    Qt3DExtras::QTextureMaterial *earthTextureMaterial;
    Qt3DCore::QTransform *earthTransform;
    QPropertyAnimation *propertyAnimationEarth;


    Qt3DCore::QEntity *grSC1; //сущность для орбитальной группировки
    Qt3DCore::QTransform *grSC1Transform;
    QPropertyAnimation *grSC1Animation;
    //добавление КА
    Qt3DCore::QEntity *sc1;
    Qt3DRender::QSceneLoader *sc1SceneLoader;
    Qt3DCore::QTransform *sc1Transform;
    QPropertyAnimation *sc1Animation;

    Qt3DCore::QEntity *grSC2Tr;
    Qt3DCore::QTransform *grSC2TrTransform;

//    Qt3DCore::QEntity *grSC2debujar;
//    Qt3DCore::QTransform *grSC2DebujarTransform;

    Qt3DCore::QEntity *grSC2;
    Qt3DCore::QTransform *grSC2Transform;
    QPropertyAnimation *grSC2Animation;

    Qt3DRender::QGeometryRenderer *orbita;
    Qt3DRender::QGeometry *orbitaGeometry;
    Qt3DRender::QBuffer *buf;
    Qt3DRender::QAttribute *orbitaAttribute;
    Qt3DExtras::QPhongMaterial *material;

    //добавление КА №2
    Qt3DCore::QEntity *sc2;
    Qt3DRender::QSceneLoader *sc2SceneLoader;
    Qt3DCore::QTransform *sc2Transform;
    QPropertyAnimation *sc2Animation;


    //освещение
    Qt3DCore::QEntity *pointEntity;
    Qt3DCore::QTransform *lightTransform;
    Qt3DRender::QDirectionalLight *pointLight;



    Qt3DRender::QCamera *camera;
    customCameraController *cameraController; //управление камерой

    InitSystem();
};

#endif // INITSYSTEM_H
