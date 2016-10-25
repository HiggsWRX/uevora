/*global THREE, ImprovedNoise*/

function init(mesh) {
    'use strict';

    var WIDTH, HEIGHT, renderer, scene, camera, controls, ambientLight, shadowLight, pointLight, pointLight2;

    WIDTH = window.innerWidth;
    HEIGHT = window.innerHeight;
    renderer = new THREE.WebGLRenderer({
        alpha: true,
        antialias: true
    });
    renderer.setPixelRatio(window.devicePixelRatio);
    renderer.setSize(WIDTH, HEIGHT);
    renderer.setClearColor("lightblue");
    document.getElementById('world').appendChild(renderer.domElement);

    scene = new THREE.Scene();

    camera = new THREE.PerspectiveCamera(
        60, // abertura
        WIDTH / HEIGHT, // proporção largura/altura
        0.1, // corte perto
        10000 // corte longe
    );
    camera.position.set(100, 50, 220);
    camera.lookAt(scene.position);
    controls = new THREE.TrackballControls(camera, renderer.domElement);
    controls.zoomSpeed = 0.1;
    controls.panSpeed = 0.1;

    ambientLight = new THREE.AmbientLight('white', 0.5);
    scene.add(ambientLight);
    
    shadowLight = new THREE.DirectionalLight('moccasin', 0.7);
    shadowLight.position.set(-200, 100, 200);
    shadowLight.castShadow = true;
    scene.add(shadowLight);
    
    scene.add(mesh);

    return {
        camera: camera,
        scene: scene,
        renderer: renderer,
        controls: controls
    };
}

function animate(world) {
    'use strict';

    window.requestAnimationFrame(function () {
        animate(world);
    });

    world.scene.rotation.y += 0.001;
    world.renderer.render(world.scene, world.camera);
    world.controls.update();
}

function groundGeo() {
    'use strict';

    var ground = new THREE.BoxGeometry(3, 0.1, 3);

    return ground;
}

/* Gera uma elevation grid aleatoriamente 
   para ser usada na construção do chão */
function generateHeight(width, height) {
    'use strict';

    var data, perlin, size, quality, z, x, y;

    data = new Uint8Array(width * height);
    perlin = new ImprovedNoise();
    size = width * height;
    quality = 2;
    z = Math.random() * 100;

    for (var j = 0; j < 4; j++) {
        quality *= 4;

        for (var i = 0; i < size; i++) {
            x = i % width;
            y = ~~(i / width);
            data[i] += Math.abs(perlin.noise(x / quality, y / quality, z) * 0.5) * quality + 10;
        }
    }

    return data;
}

function generateTexture(data, width, height) {
    'use strict';
    var canvas, context, image, imageData,
        level, diff, vector3, sun, shade;

    vector3 = new THREE.Vector3(0, 0, 0);
    sun = new THREE.Vector3(1, 1, 1);
    sun.normalize();
    canvas = document.createElement('canvas');
    canvas.width = width;
    canvas.height = height;
    context = canvas.getContext('2d');
    context.fillStyle = '#000';
    context.fillRect(0, 0, width, height);
    image = context.getImageData(0, 0, width, height);
    imageData = image.data;
    for (var i = 0, j = 0, l = imageData.length; i < l; i += 4, j++) {
        vector3.x = data[j - 1] - data[j + 1];
        vector3.y = 2;
        vector3.z = data[j - width] - data[j + width];
        vector3.normalize();
        shade = vector3.dot(sun);
        imageData[i] = (46 + shade * 128) * (data[j] * 0.007);
        imageData[i + 1] = (46 + shade * 96) * (data[j] * 0.007);
        imageData[i + 2] = (46 + shade * 96) * (data[j] * 0.007);
    }
    context.putImageData(image, 0, 0);
    return canvas;
}

function drawGround() {
    'use strict';
    
    var data, quality, step, rock, rockT, rockG, rockM, water, waterL, waterG, waterT, waterM;

    data = generateHeight(1024, 1024);
    rockT = new THREE.CanvasTexture(generateTexture(data, 1024, 1024));
    rockM = new THREE.MeshBasicMaterial({
        map: rockT,
        overdraw: 0.5
    });

    quality = 16;
    step = 1024 / quality;

    rockG = new THREE.PlaneGeometry(2000, 2000, quality - 1, quality - 1);
    rockG.rotateX(-Math.PI / 2);
    for (var i = 0, j = 0, k = 0, l = rockG.vertices.length; i < l; i++) {
        var x = i % quality,
            y = Math.floor(i / quality);
        rockG.vertices[i].y = (data[(x * step) + (y * step) * 1024] * 1 - 126) * 0.8;
    }
    rock = new THREE.Mesh(rockG, rockM);

    rock.scale.set(0.005, 0.0015, 0.005);
    rock.receiveShadow = true;

    return rock;
}

function leftBladeGeo() {
    'use strict';

    var crossSectionPoints, crossSection, spinePoints, spine, parameters;

    crossSectionPoints = [
        new THREE.Vector2(0, 0.1),
        new THREE.Vector2(-0.05, 0),
        new THREE.Vector2(0, -0.1),
        new THREE.Vector2(0.05, 0)
    ];
    crossSection = new THREE.Shape(crossSectionPoints);

    spinePoints = [
        new THREE.Vector3(0, -0.5, 0),
        new THREE.Vector3(0, 0.45, 0)
    ];
    spine = new THREE.CatmullRomCurve3(spinePoints);

    parameters = {
        extrudePath: spine
    };

    return new THREE.ExtrudeGeometry(crossSection, parameters);
}

function leftGuardGeo() {
    'use strict';

    var guard = new THREE.BoxGeometry(0.4, 0.1, 0.1, 2, 2, 2);
    guard.vertices[0].x -= 0.02;
    guard.vertices[1].x -= 0.02;
    guard.vertices[2].x -= 0.02;

    guard.vertices[0].z -= 0.02;
    guard.vertices[2].z += 0.02;

    guard.vertices[6].x -= 0.02;
    guard.vertices[7].x -= 0.02;
    guard.vertices[8].x -= 0.02;

    guard.vertices[6].z -= 0.02;
    guard.vertices[8].z += 0.02;

    guard.vertices[9].x += 0.02;
    guard.vertices[10].x += 0.02;
    guard.vertices[11].x += 0.02;

    guard.vertices[9].z += 0.02;
    guard.vertices[11].z -= 0.02;

    guard.vertices[15].x += 0.02;
    guard.vertices[16].x += 0.02;
    guard.vertices[17].x += 0.02;

    guard.vertices[15].z += 0.02;
    guard.vertices[17].z -= 0.02;

    guard.vertices[24].z += 0.02;
    guard.vertices[25].z -= 0.02;

    return guard;
}

function drawGrip() {
    'use strict';

    var grip = new THREE.BoxGeometry(0.05, 0.25, 0.02);
    grip.vertices[2].x += 0.015;
    grip.vertices[3].x += 0.015;
    grip.vertices[6].x -= 0.015;
    grip.vertices[7].x -= 0.015;

    return grip;
}

function leftHandleGeo() {
    'use strict';

    var coordinates, faces, handle, botPart, grip;

    coordinates = [
        new THREE.Vector3(0, 0.05, 0),

        new THREE.Vector3(0.09, 0, 0.03),
        new THREE.Vector3(-0.09, 0, 0.03),
        new THREE.Vector3(-0.09, 0, -0.03),
        new THREE.Vector3(0.09, 0, -0.03)
    ];

    faces = [
        new THREE.Face3(0, 2, 1),
        new THREE.Face3(0, 3, 2),
        new THREE.Face3(0, 4, 3),
        new THREE.Face3(0, 1, 4),

        new THREE.Face3(1, 2, 3),
        new THREE.Face3(1, 3, 4)
    ];

    handle = new THREE.Geometry();
    handle.vertices = coordinates;
    handle.faces = faces;
    handle.computeFaceNormals();
    handle.computeBoundingSphere();

    botPart = new THREE.BoxGeometry(0.18, 0.05, 0.06);
    botPart.applyMatrix(new THREE.Matrix4().makeTranslation(0, -0.025, 0));

    handle.merge(botPart);

    grip = drawGrip();
    grip.applyMatrix(new THREE.Matrix4().makeTranslation(0, -0.17, 0));
    handle.merge(grip);

    return handle;
}

function drawLeftSword() {
    'use strict';

    var blade, bladeG, bladeM, guardG, guardM, guard, handleG, handleM, handle, sword;

    bladeG = leftBladeGeo();
    bladeM = new THREE.MeshPhongMaterial({
        color: 0x809aa0,
        shading: THREE.FlatShading
    });
    blade = new THREE.Mesh(bladeG, bladeM);
    blade.position.y = -0.1;

    guardG = leftGuardGeo();
    guardM = new THREE.MeshPhongMaterial({
        color: 0x6d8287,
        shading: THREE.FlatShading
    });
    guard = new THREE.Mesh(guardG, guardM);
    guard.position.y = 0.4;

    handleG = leftHandleGeo();
    handleM = new THREE.MeshPhongMaterial({
        color: 0x91acb3,
        shading: THREE.FlatShading
    });
    handle = new THREE.Mesh(handleG, handleM);
    handle.position.y = 0.73;

    sword = new THREE.Object3D();
    sword.add(blade);
    sword.add(guard);
    sword.add(handle);
    sword.castShadow = true;
    sword.receiveShadow = true;

    return sword;
}

function middleBladeGeo() {
    'use strict';

    var crossSectionPoints, crossSection, spinePoints, spine, parameters;

    crossSectionPoints = [
        new THREE.Vector2(0, 0.1),
        new THREE.Vector2(-0.01, 0.09),
        new THREE.Vector2(-0.05, 0.01),
        new THREE.Vector2(-0.05, 0),
        new THREE.Vector2(-0.05, -0.01),
        new THREE.Vector2(-0.01, -0.09),
        new THREE.Vector2(0, -0.1),
        new THREE.Vector2(0.01, -0.09),
        new THREE.Vector2(0.05, -0.01),
        new THREE.Vector2(0.05, 0),
        new THREE.Vector2(0.05, 0.01),
        new THREE.Vector2(0.01, 0.1)
    ];
    crossSection = new THREE.Shape(crossSectionPoints);

    spinePoints = [
        new THREE.Vector3(0, -0.6, 0),
        new THREE.Vector3(0, 0.45, 0)
    ];

    spine = new THREE.CatmullRomCurve3(spinePoints);

    parameters = {
        extrudePath: spine
    };

    return new THREE.ExtrudeGeometry(crossSection, parameters);
}

function middleGuardGeo() {
    'use strict';

    var guard = new THREE.BoxGeometry(0.4, 0.05, 0.1, 5, 1, 1);
    guard.vertices[0].y -= 0.026; // top right
    guard.vertices[1].y -= 0.026;
    guard.vertices[2].y -= 0.016;
    guard.vertices[3].y -= 0.016;

    guard.vertices[4].y -= 0.026; // top left
    guard.vertices[5].y -= 0.026;
    guard.vertices[6].y -= 0.016;
    guard.vertices[7].y -= 0.016;

    guard.vertices[9].y += 0.008;
    guard.vertices[10].y += 0.008;

    guard.vertices[13].y += 0.008;
    guard.vertices[14].y += 0.008;

    guard.vertices[8].y -= 0.008;
    guard.vertices[11].y -= 0.008;
    guard.vertices[12].y -= 0.008;
    guard.vertices[15].y -= 0.008;

    guard.vertices[17].y += 0.016;
    guard.vertices[18].y += 0.016;
    guard.vertices[21].y += 0.008;
    guard.vertices[22].y += 0.008;

    return guard;
}

function middleHandleGeo() {
    'use strict';

    var handle = middleGuardGeo();
    handle.rotateZ(Math.PI);

    return handle;
}

function drawMiddleSword() {
    'use strict';

    var bladeG, bladeM, blade, guardG, guardM, guard,
        handleG, handleM, handle, gripG, gripM, grip, sword;

    bladeG = middleBladeGeo();
    bladeM = new THREE.MeshPhongMaterial({
        color: 0x809aa0,
        shading: THREE.FlatShading
    });
    blade = new THREE.Mesh(bladeG, bladeM);
    blade.position.y = -0.1;

    guardG = middleGuardGeo();
    guardM = new THREE.MeshPhongMaterial({
        color: 0x6d8287,
        shading: THREE.FlatShading
    });
    guard = new THREE.Mesh(guardG, guardM);
    guard.position.y = 0.36;

    handleG = middleHandleGeo();
    handleM = new THREE.MeshPhongMaterial({
        color: 0x91acb3,
        shading: THREE.FlatShading
    });
    handle = new THREE.Mesh(handleG, handleM);
    handle.position.y = 0.625;
    handle.scale.set(0.4, 0.5, 0.5);

    gripG = drawGrip();
    gripM = new THREE.MeshPhongMaterial({
        color: 0x91acb3,
        shading: THREE.FlatShading
    });
    grip = new THREE.Mesh(gripG, gripM);
    grip.position.y = 0.5;

    sword = new THREE.Object3D();
    sword.add(blade);
    sword.add(guard);
    sword.add(handle);
    sword.add(grip);

    return sword;
}

function rightBladeGeo() {
    'use strict';

    var crossSectionPoints, crossSection, spinePoints, spine, parameters;

    crossSectionPoints = [
        new THREE.Vector2(0, 0.1),
        new THREE.Vector2(-0.04, 0.03),
        new THREE.Vector2(-0.025, 0),
        new THREE.Vector2(-0.04, -0.03),
        new THREE.Vector2(0, -0.1),
        new THREE.Vector2(0.04, -0.03),
        new THREE.Vector2(0.025, 0),
        new THREE.Vector2(0.04, 0.03)
    ];
    crossSection = new THREE.Shape(crossSectionPoints);

    spinePoints = [
        new THREE.Vector3(0, -0.75, 0),
        new THREE.Vector3(0, 0.5, 0)
    ];

    spine = new THREE.CatmullRomCurve3(spinePoints);

    parameters = {
        extrudePath: spine
    };

    return new THREE.ExtrudeGeometry(crossSection, parameters);
}

/* Função extensa em termos de número de linhas, porem como
   não existe um padrão não é possível "automatizar" com um
   for ou algo parecido. */
function drawQuarterGuardGeo() {
    'use strict';

    var guard = new THREE.BoxGeometry(0.4, 0.1, 0.1, 10, 1, 1);
    guard.vertices[0].y -= 0.02;
    guard.vertices[3].z += 0.025;
    guard.vertices[1].y -= 0.02;
    guard.vertices[1].z += 0.025;

    guard.vertices[16].z += 0.03;
    guard.vertices[43].z += 0.03;

    guard.vertices[15].y -= 0.005;
    guard.vertices[15].z += 0.035;
    guard.vertices[42].z += 0.035;
    guard.vertices[24].y -= 0.005;

    guard.vertices[14].y -= 0.01;
    guard.vertices[14].z += 0.04;
    guard.vertices[41].z += 0.04;
    guard.vertices[23].y -= 0.01;

    guard.vertices[13].y -= 0.022;
    guard.vertices[13].z += 0.045;
    guard.vertices[40].z += 0.045;
    guard.vertices[22].y -= 0.022;

    guard.vertices[12].y -= 0.035;
    guard.vertices[12].z += 0.05;
    guard.vertices[39].z += 0.05;
    guard.vertices[21].y -= 0.035;

    guard.vertices[11].y -= 0.05;
    guard.vertices[11].z += 0.055;
    guard.vertices[38].z += 0.055;
    guard.vertices[20].y -= 0.05;

    guard.vertices[10].y -= 0.03;
    guard.vertices[10].z += 0.06;
    guard.vertices[37].z += 0.06;
    guard.vertices[19].y -= 0.03;

    guard.vertices[9].z += 0.065;
    guard.vertices[36].z += 0.065;

    guard.vertices[8].y -= 0.03;
    guard.vertices[8].z += 0.07;
    guard.vertices[17].y -= 0.03;
    guard.vertices[35].z += 0.07;

    guard.vertices[4].y -= 0.08;
    guard.vertices[4].z += 0.09;
    guard.vertices[5].y -= 0.08;

    guard.vertices[6].z += 0.09;

    return guard;
}

/* Para desenhar a guarda da espada da direita optou-se por
   se modelar apenas 1 quarto da geometria e depois espelhar
   na horizontal e vertical obtendo a geometria completa */
function rightGuardGeo() {
    'use strict';

    var firstQ, secondQ, thirdQ, fourthQ;

    firstQ = drawQuarterGuardGeo();

    secondQ = drawQuarterGuardGeo();
    secondQ.rotateY(-Math.PI);
    secondQ.applyMatrix(new THREE.Matrix4().makeTranslation(0.4, 0, 0.1));
    firstQ.merge(secondQ);

    thirdQ = drawQuarterGuardGeo();
    thirdQ.rotateX(Math.PI);
    thirdQ.applyMatrix(new THREE.Matrix4().makeTranslation(0, -0.1, 0.1));
    firstQ.merge(thirdQ);

    fourthQ = drawQuarterGuardGeo();
    fourthQ.rotateZ(Math.PI);
    fourthQ.applyMatrix(new THREE.Matrix4().makeTranslation(0.4, -0.1, 0));

    firstQ.merge(fourthQ);

    return firstQ;
}

function drawRightGuard() {
    'use strict';

    var guardG, guardM, guard, guardG2, guardM2, guard2;

    guardG = rightGuardGeo();
    guardM = new THREE.MeshPhongMaterial({
        color: 0x6d8287,
        shading: THREE.FlatShading
    });
    guard = new THREE.Mesh(guardG, guardM);

    guardG2 = rightGuardGeo();
    guardM2 = new THREE.MeshPhongMaterial({
        color: 0x6d8287,
        shading: THREE.FlatShading
    });
    guardM2.side = THREE.DoubleSide;
    guard2 = new THREE.Mesh(guardG2, guardM2);

    guard2.position.z = 0.1;
    guard2.scale.z = -1;

    guard.add(guard2);

    return guard;
}

function rightHandleGeo() {
    'use strict';

    var handle = drawRightGuard();
    handle.scale.set(0.25, 0.25, 0.25);

    return handle;
}

function ornamentGeo() {
    'use strict';

    var ornG = new THREE.BoxGeometry(0.05, 0.1, 0.03, 3, 1, 1);
    ornG.vertices[0].y -= 0.02;
    ornG.vertices[0].x += 0.01;
    ornG.vertices[1].y -= 0.02;
    ornG.vertices[1].x += 0.01;
    ornG.vertices[4].y -= 0.02;
    ornG.vertices[4].x -= 0.01;
    ornG.vertices[5].y -= 0.02;
    ornG.vertices[5].x -= 0.01;

    return ornG;
}

function drawOrnament() {
    'use strict';

    var orn, ornG, ornM, midOrn, leftOrn, rightOrn;

    orn = new THREE.Object3D();

    ornG = ornamentGeo();
    ornM = new THREE.MeshPhongMaterial({
        color: 0xabc8d0,
        shading: THREE.FlatShading
    });
    midOrn = new THREE.Mesh(ornG, ornM);
    midOrn.scale.y = 1.5;

    leftOrn = new THREE.Mesh(ornG, ornM);
    leftOrn.rotateZ(Math.PI / 4);
    leftOrn.position.x -= 0.04;

    rightOrn = new THREE.Mesh(ornG, ornM);
    rightOrn.rotateZ(-Math.PI / 4);
    rightOrn.position.x += 0.04;


    orn.add(midOrn);
    orn.add(leftOrn);
    orn.add(rightOrn);

    return orn;
}

function drawRightSword() {
    'use strict';

    var bladeG, bladeM, blade, guard, handle, gripG, gripM, grip, ornament, sword;

    bladeG = rightBladeGeo();
    bladeM = new THREE.MeshPhongMaterial({
        color: 0x809aa0,
        shading: THREE.FlatShading
    });
    blade = new THREE.Mesh(bladeG, bladeM);

    guard = drawRightGuard();
    guard.position.set(-0.1, 0.55, -0.03);
    guard.scale.set(0.5, 0.5, 0.6);

    handle = rightHandleGeo();
    handle.position.set(-0.05, 0.8, -0.015);

    gripG = drawGrip();
    gripM = new THREE.MeshPhongMaterial({
        color: 0x91acb3,
        shading: THREE.FlatShading
    });
    grip = new THREE.Mesh(gripG, gripM);
    grip.position.y = 0.65;

    ornament = drawOrnament();
    ornament.scale.set(0.6, 0.6, 0.6);
    ornament.position.y = 0.84;

    sword = new THREE.Object3D();
    sword.add(blade);
    sword.add(guard);
    sword.add(handle);
    sword.add(grip);
    sword.add(ornament);

    return sword;
}

function drawSkyBox() {
    var aCubeMap = THREE.ImageUtils.loadTextureCube([
		  'media/px.jpg',
		  'media/nx.jpg',
		  'media/py.jpg',
		  'media/ny.jpg',
		  'media/pz.jpg',
		  'media/nz.jpg'
    ]);
    aCubeMap.format = THREE.RGBFormat;

    var aShader = THREE.ShaderLib['cube'];
    aShader.uniforms['tCube'].value = aCubeMap;

    var aSkyBoxMaterial = new THREE.ShaderMaterial({
        fragmentShader: aShader.fragmentShader,
        vertexShader: aShader.vertexShader,
        uniforms: aShader.uniforms,
        depthWrite: false,
        side: THREE.BackSide
    });

    var aSkybox = new THREE.Mesh(
        new THREE.BoxGeometry(100, 100, 100),
        aSkyBoxMaterial
    );

    return aSkybox;
}

function modelWorld() {
    'use strict';

    var world, skybox, ground, leftSword, middleSword, rightSword;

    world = new THREE.Object3D();
    skybox = drawSkyBox();
    ground = drawGround();
    leftSword = drawLeftSword();
    middleSword = drawMiddleSword();
    rightSword = drawRightSword();

    ground.position.y -= 0.4;
    leftSword.position.x = -0.4;
    leftSword.position.y = 0.1;
    middleSword.position.z = -0.3;
    middleSword.position.y = 0.2;
    rightSword.position.x = 0.4;
    rightSword.position.y = 0.2;

    world.add(ground);
    world.add(skybox);
    world.add(leftSword);
    world.add(middleSword);
    world.add(rightSword);

    world.scale.set(100, 100, 100);

    return world;
}

/* Nota: O chão é aleatoriamente gerado, podendo conter por vezes
   artefactos indesejados. Basta fazer refresh na página */
function main() {
    'use strict';

    var world = init(modelWorld());
    animate(world);
}