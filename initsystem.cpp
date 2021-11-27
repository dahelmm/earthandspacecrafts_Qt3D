#include "initsystem.h"
#include <math.h>

InitSystem::InitSystem()
{

    rootEntity = new Qt3DCore::QEntity;
    rootTransform = new Qt3DCore::QTransform(rootEntity);


    //создание сферы космоса
    universe = new Qt3DCore::QEntity(rootEntity);
    universeSphere = new Qt3DExtras::QSphereMesh(universe);
    universeSphere->setRadius(-4000);
    universeSphere->setRings(200);

    //применение текстуры к сфере космоса
    universeTextureMaterial = new Qt3DExtras::QTextureMaterial(universe);
    universeTextureLoader = new Qt3DRender::QTextureLoader(universe);
    universeTextureLoader->setSource(QUrl("qrc:/texture/Textures/2k_stars+milky_way.jpg"));
    universeTextureMaterial->setTexture(universeTextureLoader);

    //модуль для преобразования сущности космоса
    universeTransform = new Qt3DCore::QTransform(universe);


    //создание Земли
    earthEntity = new Qt3DCore::QEntity(rootEntity);
    earthSphere= new Qt3DExtras::QSphereMesh(earthEntity);
    earthSphere->setRadius(500);
    earthSphere->setRings(500);

    earthTexture= new Qt3DRender::QTextureLoader(earthEntity);
    earthTextureMaterial= new Qt3DExtras::QTextureMaterial(earthEntity);
    earthTexture->setSource(QUrl("qrc:/texture/Textures/Tierra2k.jpg"));
    earthTextureMaterial->setTexture(earthTexture);

//    phongEarth = new Qt3DExtras::QPhongMaterial(earthEntity);
//    phongEarth->setDiffuse(Qt::black);
//    phongEarth->setAmbient(Qt::white);
    //модуль для управления сферой
    earthTransform = new Qt3DCore::QTransform(earthEntity);
    earthTransform->setTranslation(QVector3D(0.0,0.0,0.0));
    earthTransform->setRotationX(45);

    propertyAnimationEarth = new QPropertyAnimation(earthEntity);
    propertyAnimationEarth->setTargetObject(earthTransform);
    propertyAnimationEarth->setPropertyName("Earth");
    propertyAnimationEarth->setStartValue(QVariant(0.0));
    propertyAnimationEarth->setEndValue(QVariant(360.0));
    propertyAnimationEarth->setDuration(100000);
    propertyAnimationEarth->setLoopCount(-1);
    propertyAnimationEarth->start();

    QObject::connect(propertyAnimationEarth,&QPropertyAnimation::valueChanged,earthTransform,[this](const QVariant & value){
            earthTransform->setRotation(QQuaternion::fromEulerAngles(QVector3D(0.0,value.toFloat(),0.0)));

    });

    grSC1 = new Qt3DCore::QEntity(rootEntity);
    grSC1Transform = new Qt3DCore::QTransform(grSC1);
    grSC1Transform->setRotationX(45);

    grSC1Animation = new QPropertyAnimation(grSC1);
    grSC1Animation->setTargetObject(grSC1Transform);
    grSC1Animation->setStartValue(QVariant(0.0));
    grSC1Animation->setEndValue(QVariant(360.0));
    grSC1Animation->setPropertyName("grSC1");
    grSC1Animation->setLoopCount(-1);
    grSC1Animation->setDuration(40000);
    grSC1Animation->start();

    QObject::connect(grSC1Animation,&QPropertyAnimation::valueChanged,grSC1Transform,[this](const QVariant & value){
        grSC1Transform->setRotation(QQuaternion::fromEulerAngles(QVector3D(0.0,value.toFloat(),0.0)));
        grSC1Transform->setRotation(QQuaternion::fromEulerAngles(QVector3D(0.0,0.0,value.toFloat())));
    });

    //SpaceCraft #1
    sc1 = new Qt3DCore::QEntity(grSC1);
    sc1SceneLoader = new Qt3DRender::QSceneLoader(sc1);
    sc1SceneLoader->setSource(QUrl("qrc:/obj/SpaceCraft/Voyager.obj"));

    sc1Transform = new Qt3DCore::QTransform(sc1);
    sc1Transform->setTranslation(QVector3D(-600.0,0.0,0.0));
    sc1Transform->setScale(10.0);

    sc1Animation = new QPropertyAnimation(sc1);
    sc1Animation->setTargetObject(sc1Transform);
    sc1Animation->setPropertyName("sc1");
    sc1Animation->setStartValue(QVariant(0.0));
    sc1Animation->setEndValue(QVariant(360.0));
    sc1Animation->setLoopCount(-1);
    sc1Animation->setDuration(20000);
    sc1Animation->start();

    QObject::connect(sc1Animation,&QPropertyAnimation::valueChanged,sc1Transform,[this](const QVariant & value){
            sc1Transform->setRotation(QQuaternion::fromEulerAngles(QVector3D(0.0,value.toFloat(),value.toFloat())));
    });


//    grSC2debujar = new Qt3DCore::QEntity(rootEntity);
//    grSC2DebujarTransform = new Qt3DCore::QTransform(grSC2debujar);


    grSC2Tr = new Qt3DCore::QEntity(rootEntity);
    grSC2TrTransform = new Qt3DCore::QTransform(grSC2Tr);



    grSC2 = new Qt3DCore::QEntity(grSC2Tr);
    grSC2Transform = new Qt3DCore::QTransform(grSC2);

    grSC2Animation = new QPropertyAnimation(grSC2);
    grSC2Animation->setTargetObject(grSC2Transform);
    grSC2Animation->setStartValue(QVariant(0.0));
    grSC2Animation->setEndValue(QVariant(360.0));
    grSC2Animation->setPropertyName("grSC11");
    grSC2Animation->setLoopCount(-1);
    grSC2Animation->setDuration(10000);
    grSC2Animation->start();

    perigey = earthSphere->radius()+300.0;
    apogey = earthSphere->radius()+600.0;
    A = perigey+apogey;
    B = A*0.5;


    orbita = new Qt3DRender::QGeometryRenderer(grSC2);



    pointVertex.resize(3*500*sizeof(float));
    positions = reinterpret_cast<float*>(pointVertex.data());

    orbitaGeometry = new Qt3DRender::QGeometry(orbita);

    buf = new Qt3DRender::QBuffer(orbitaGeometry);
    int i = 0;

    QObject::connect(grSC2Animation,&QPropertyAnimation::valueChanged,grSC2Animation,[this,i](const QVariant & value)mutable->int{

        double XF = (A * (cos((value.toFloat())*radToGrad))/**gradToRad*/);
        double ZF = (B * (sin((value.toFloat())*radToGrad))/**gradToRad*/);
        grSC2Transform->setTranslation(QVector3D(apogey-XF,0.0,ZF));

    });

//    *positions++ = grSC2Transform->translation().x();
//    *positions++ = grSC2Transform->translation().y();
//    *positions++ = grSC2Transform->translation().z();
    *positions++ = 600.0;
    *positions++ = 0.0;
    *positions++ = 0.0;

//                positions+=3;





    buf->setData(pointVertex);

    orbitaAttribute = new Qt3DRender::QAttribute(orbitaGeometry);

    orbitaAttribute->setName(Qt3DRender::QAttribute::defaultPositionAttributeName());
    orbitaAttribute->setVertexBaseType(Qt3DRender::QAttribute::Float);
    orbitaAttribute->setVertexSize(3);
    orbitaAttribute->setAttributeType(Qt3DRender::QAttribute::VertexAttribute);
    orbitaAttribute->setBuffer(buf);
    orbitaAttribute->setByteStride(3*sizeof(float));
    orbitaAttribute->setCount(2);




    orbita->setPrimitiveType(Qt3DRender::QGeometryRenderer::LineStrip);

    material = new Qt3DExtras::QPhongMaterial(orbita);
    material->setAmbient(QColor(Qt::white));





    //добавление КА №2
    sc2 = new Qt3DCore::QEntity(grSC2);
    sc2SceneLoader = new Qt3DRender::QSceneLoader(sc2);
    sc2SceneLoader->setSource(QUrl("qrc:/obj/SpaceCraft/ARC_Target.obj"));

    sc2Transform =  new Qt3DCore::QTransform(sc2);
//    sc2Transform->setTranslation(QVector3D(0.0,0.0,0.0));
    sc2Transform->setScale(10.0);

    sc2Animation = new QPropertyAnimation(sc2);
    sc2Animation->setTargetObject(sc2Transform);
    sc2Animation->setPropertyName("sc2");
    sc2Animation->setStartValue(QVariant(0.0));
    sc2Animation->setEndValue(QVariant(360.0));
    sc2Animation->setLoopCount(-1);
    sc2Animation->setDuration(20000);
    sc2Animation->start();

    QObject::connect(sc2Animation,&QPropertyAnimation::valueChanged,sc2Transform,[this](const QVariant & value){
            sc2Transform->setRotation(QQuaternion::fromEulerAngles(QVector3D(0.0,value.toFloat(),0.0)));
    });


    pointEntity = new Qt3DCore::QEntity(universe);
    lightTransform = new Qt3DCore::QTransform(pointEntity);
    pointLight= new Qt3DRender::QDirectionalLight(pointEntity);
    pointLight->setWorldDirection(QVector3D(-1,1,-1));
    pointLight->setIntensity(0);
    pointLight->setColor(Qt::red);

    lightTransform->setTranslation(QVector3D(600.0,0.0,0.0));




    //добавление компонентов всех сущностей

    //sc2
    sc2->addComponent(sc2Transform);
    sc2->addComponent(sc2SceneLoader);

    grSC2Tr->addComponent(material);
    orbitaGeometry->addAttribute(orbitaAttribute);
    orbita->setGeometry(orbitaGeometry);
    grSC2Tr->addComponent(orbita);

    grSC2->addComponent(grSC2Transform);
    grSC2Tr->addComponent(grSC2TrTransform);

    //освещение
    pointEntity->addComponent(lightTransform);
    pointEntity->addComponent(pointLight);

    //sc1
    sc1->addComponent(sc1Transform);
    sc1->addComponent(sc1SceneLoader);
    grSC1->addComponent(grSC1Transform);

    //Земля
    earthEntity->addComponent(earthTransform);
    earthEntity->addComponent(earthTextureMaterial);
    earthEntity->addComponent(earthSphere);

    //космос
    universe->addComponent(universeTransform);
    universe->addComponent(universeTextureMaterial);
    universe->addComponent(universeSphere);

    rootEntity->addComponent(rootTransform);






    camera = view.camera();
    camera->lens()->setPerspectiveProjection(90,static_cast<float>(view.width())/view.height(),0.1,10000.0);
    camera->setViewCenter(QVector3D(0.0,0.0,0.0));
    camera->setPosition(QVector3D(0.0,0.0,1000.0));
    camera->setUpVector(QVector3D(0,1,0));


    cameraController = new customCameraController(rootEntity);
    cameraController->setCamera(camera);
    cameraController->setLookSpeed(100.0);
    cameraController->setLinearSpeed(50.0);

    view.setRootEntity(rootEntity);
    view.show();




}


